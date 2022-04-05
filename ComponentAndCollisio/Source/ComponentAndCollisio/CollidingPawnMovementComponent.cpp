// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuntion)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFuntion);

	// PawnOwner : 이 컴포넌트를 소유하고 있는 폰
	// UpdatedComponent : UPawnMovementComponent의 부모클래스인 UMovementComponent 클래스의 변수
	// 이 무브먼트 컴포넌트가 이동시키고 업데이트 해야 할 컴포넌트
	// ShouldSkipUpdate : 이동된 컴포넌트가 이동할 수 없거나 렌더링 되지 않았는지 판별하여 알려주는 함수
	// 3가지로 이 무브먼트 컴포넌트가 이동가능한 상태인지 확인
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// ConsumeInputVector : 입력된 이동 벡터를 가져옴
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		// SafeMoveUpdatedComponent : 장애물을 피해 PawnMovementComponent를 이동시킴
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			// SlideAlongSurface : 컴포넌트가 이동하다가 충돌이 발생하면
			// 제자리에 멈추는 것이 아니라 충돌체의 표면을 타고 미끄러지듯이 이동하도록
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}