// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuntion)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFuntion);

	// PawnOwner : �� ������Ʈ�� �����ϰ� �ִ� ��
	// UpdatedComponent : UPawnMovementComponent�� �θ�Ŭ������ UMovementComponent Ŭ������ ����
	// �� �����Ʈ ������Ʈ�� �̵���Ű�� ������Ʈ �ؾ� �� ������Ʈ
	// ShouldSkipUpdate : �̵��� ������Ʈ�� �̵��� �� ���ų� ������ ���� �ʾҴ��� �Ǻ��Ͽ� �˷��ִ� �Լ�
	// 3������ �� �����Ʈ ������Ʈ�� �̵������� �������� Ȯ��
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// ConsumeInputVector : �Էµ� �̵� ���͸� ������
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		// SafeMoveUpdatedComponent : ��ֹ��� ���� PawnMovementComponent�� �̵���Ŵ
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			// SlideAlongSurface : ������Ʈ�� �̵��ϴٰ� �浹�� �߻��ϸ�
			// ���ڸ��� ���ߴ� ���� �ƴ϶� �浹ü�� ǥ���� Ÿ�� �̲��������� �̵��ϵ���
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}