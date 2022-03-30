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
	float TimeBetweenCameraChanges;	// ���� ī�޶�� ��ȯ�� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothBlendTime;	// ī�޶� ��ȯ �� �ε巴�� ���ϴ� �ð�
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

	// ī�޶� ���� ����ü�� �迭�� �����Ͽ� ����
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
