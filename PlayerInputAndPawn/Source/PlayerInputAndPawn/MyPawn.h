// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class PLAYERINPUTANDPAWN_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// USceneComponent : transform(위치, 회전) 정보를 가짐
	// , 월드에 배치 가능한 다른 컴포넌트들의 부모 클래스
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	// 입력을 처리할 함수
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	FVector CurrentVelocity;	// 현재 속도
	bool bGrowing;	// 크기가 커지는 중인지 여부

	float InputTime;	// 방향키 입력이 지속된 시간
};
