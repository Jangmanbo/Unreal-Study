// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class COMPONENTANDCOLLISIO_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// GetMovementComponent : 다른 클래스가 Pawn이 사용중인 PawnMovementComponent에 접근 시 사용
	// 우리가 만든 MovementComponent를 가져가서 사용하도록 변경
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UParticleSystemComponent* OurParticleSystem;

	// CollidingPawn이 CollidingPawnMovementComponent를 소유하고 사용하도록
	class UCollidingPawnMovementComponent* OurMovementComponent;

	// Pawn이 입력을 받을 함수들
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Turn(float AxisValue);

	void ParticleToggle();
};
