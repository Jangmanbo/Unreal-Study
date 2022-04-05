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

	// USceneComponent : transform(��ġ, ȸ��) ������ ����
	// , ���忡 ��ġ ������ �ٸ� ������Ʈ���� �θ� Ŭ����
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	// �Է��� ó���� �Լ�
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	FVector CurrentVelocity;	// ���� �ӵ�
	bool bGrowing;	// ũ�Ⱑ Ŀ���� ������ ����

	float InputTime;	// ����Ű �Է��� ���ӵ� �ð�
};
