// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Door.generated.h"

UCLASS()
class VTE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	float CloseTime;	// 문이 열렸다가 닫히는 시간

	float DoorDeltaTime;	// 문이 열렸다가 닫히는 과정

	bool bOpen;	// 문이 열린 상태인지 표현

	FTimerHandle DoorTimerHandle;	// 타이머 관리

	FRotator OriginRotation;	// 문의 원래 상태를 저장

	// 문 열기
	void Open();

	// 문 닫기
	void Close();
};
