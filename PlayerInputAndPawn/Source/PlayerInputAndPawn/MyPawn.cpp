// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 게임이 시작되면 자동으로 플레이어의 입력이 연결
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	UCameraComponent* OurCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// 생성한 OurCamera를 RootComponent에 부착, RootComponent의 트랜스폼을 기준으로 위치 및 회전 지정
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// UStaticMeshComponent : OurVisibleComponent에 보이는 물체
	// RootComponent에 부착
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Grow 키에 대한 반응으로 컴포넌트의 크기 조절
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;	// 컴포넌트의 크기를 가져옴

		// bGrowing 변수의 상태에 따라 CurrentScale의 값을 늘리거나 줄임
		if (bGrowing)
		{
			// 방향키를 누른 직후에 스페이스바를 누르면 즉시 최대 크기로 변화
			if (InputTime > 0.0f && InputTime <= 0.5f)
				CurrentScale = 2.0f;
			else
				CurrentScale += DeltaTime;
		}
		else
		{
			CurrentScale -= DeltaTime * 0.5f;
		}
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);	// 크기가 너무 커지지 않게 (2배까지)
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));	// 컴포넌트의 크기 지정
	}

	// MoveX, MoveY 키에 대한 반응으로 이동 처리
	{
		if (!CurrentVelocity.IsZero())
		{
			// InputTime이 1보다 크면 현재 속도에 3을 곱함 -> 이동키를 1초 이상 누르면 속도가 빨라짐
			InputTime += DeltaTime;
			FVector NewLocatiion = GetActorLocation() + (CurrentVelocity * DeltaTime * (InputTime <= 1.0f ? 1.0f : 3.0f));
			SetActorLocation(NewLocatiion);
		}
		else // 입력이 들어오지 않음
		{
			InputTime = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 바인딩 : 함수와 입력 매핑을 연결
	// Grow 키를 누르면 StartGrowing, 떼면 StopGrowing와 바인딩
	// 액션 매핑
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// 축 매핑
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	// AxisValue의 값을 [-1, 1]로 제한
	// MoveX 입력 매핑에 W, ↑ 모두 등록되어 있으면 두 값이 합산되기 때문
	// 제한하지 않으면 입동 속도가 2배가 되는 문제 발생
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}