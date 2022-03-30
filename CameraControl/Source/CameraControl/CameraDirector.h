// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FChangeCameraData
{
	GENERATED_USTRUCT_BODY();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenCameraChanges;	// 다음 카메라로 전환될 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothBlendTime;	// 카메라 전환 시 부드럽게 변하는 시간
};

UCLASS()
class CAMERACONTROL_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 카메라를 담은 구조체를 배열에 저장하여 관리
	UPROPERTY(EditAnywhere)
	TArray<FChangeCameraData> Cameras;

	int32 NowCameraIndex;

	/*
	UPROPERTY(EditAnywhere)
	AActor* CameraOne;
	UPROPERTY(EditAnywhere)
	AActor* CameraTwo;
	*/

	UPROPERTY(EditAnywhere)
	float TimeToNextCameraChange;
};
