// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	CloseTime = 3.0f;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	// 게임이 시작할 당시 액터의 회전 상태 저장
	OriginRotation = GetActorRotation();
	// Door 클래스의 Open 함수를 0.03.초 간격으로 반복 호출
	GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Open, 0.03f, true);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorDeltaTime += DeltaTime;
}

void ADoor::Open()
{
	if (!bOpen)
	{
		bOpen = true;
		DoorDeltaTime = 0.0f;
	}

	// 열린 상태로 문을 회전
	FRotator rotation = GetActorRotation();
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(0.0f, 90.0f, DoorDeltaTime), 0.0f);
	SetActorRotation(rotation);

	if (DoorDeltaTime > 1.0f)
	{
		// 현재 작동중인 타이머 중지
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
		// CloseTime이 지난 후에 Close 함수를 호출하는 타이머를 동작
		// Close가 0.03초마다 동작
		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Close, 0.03f, true, CloseTime);
	}
}

void ADoor::Close()
{
	if (bOpen)
	{
		bOpen = false;
		DoorDeltaTime = 0.0f;
	}

	// 닫힌 상태로 문을 회전
	FRotator rotation = GetActorRotation();
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(90.0f, 0.0f, DoorDeltaTime), 0.0f);
	SetActorRotation(rotation);

	// 문이 닫히는 동작 종료
	if (DoorDeltaTime > 1.0f)
	{
		// 현재 작동중인 타이머 중지
		GetWorldTimerManager().ClearTimer(DoorTimerHandle);
	}
}

