// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMPONENTANDCOLLISIO_API UCollidingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	// Actor 클래스의 Tick 함수 역할
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFuntion) override;
};
