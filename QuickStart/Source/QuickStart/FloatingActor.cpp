// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingSpeed = FVector(1.0f, 1.0f, 1.0f);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Actor를 움직이기
	FVector NewLocation = GetActorLocation();	
	float DeltaX = (FMath::Sin(RunningTime.X + DeltaTime * FloatingSpeed.X) - FMath::Sin(RunningTime.X));
	float DeltaY = (FMath::Sin(RunningTime.Y + DeltaTime * FloatingSpeed.Y) - FMath::Sin(RunningTime.Y));
	float DeltaZ = (FMath::Sin(RunningTime.Z + DeltaTime * FloatingSpeed.Z) - FMath::Sin(RunningTime.Z));
	NewLocation += FVector(DeltaX, DeltaY, DeltaZ) * 20.0f;
	// DeltaTime : 이전 프레임에 Tick이 호출되고 얼마의 시간이 흐른 뒤 다시 Tick이 호출되었는지
	// RunningTime : 액터가 생성되어 레벨에 배치된 후 얼마의 시간이 흘렀는지
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);
}

