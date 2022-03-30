// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		FChangeCameraData NowCamera = Cameras[NowCameraIndex];

		TimeToNextCameraChange += NowCamera.TimeBetweenCameraChanges;

		// 로컬 플레이어의 컨트롤을 처리하는 액터를 가져옴
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
		if (controller)
		{
			if ((controller->GetViewTarget() != NowCamera.Camera) && (NowCamera.Camera != nullptr))
			{
				// 블랜딩 타임이 다 되면 
				if (NowCamera.SmoothBlendTime <= 0.0f)
				{
					controller->SetViewTarget(NowCamera.Camera);	// 바로 NowCamera로 변경

				}
				// 블랜딩 타임 중이면
				else
				{
					controller->SetViewTargetWithBlend(NowCamera.Camera, NowCamera.SmoothBlendTime);	// 부드럽게 NowCamera로 변경
				}
			}
			/*
			// 지금 바라보는 타깃이 CameraOne이 아닌 경우
			if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				controller->SetViewTarget(CameraOne);	//바로 CameraOne으로 변경
			}
			// 지금 바라보는 타깃이 CameraTwo가 아닌 경우
			else if ((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				controller->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);	// 부드럽게 CameraTwo로 변경
			}
			*/
		}

		NowCameraIndex++;
		// index가 범위 외
		if (NowCameraIndex >= Cameras.Num())
		{
			NowCameraIndex = 0;
		}
	}
}

