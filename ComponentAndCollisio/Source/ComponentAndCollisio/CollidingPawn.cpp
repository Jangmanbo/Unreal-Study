// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// USphereComponent : 구체의 물리 처리를 하는 컴포넌트
	// 충돌만 처리, 눈에 보이는 형태를 가지지 않음
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;	// SphereComponent를 RootComponent로
	SphereComponent->InitSphereRadius(40.0f);	// 구체의 크기 설정
	// 콜리전 프로파일의 이름 지정
	// == 이 컴포넌트가 가진 콜리전이 어떤 콜리전과의 충돌을 감지할 것인지 설정
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// 눈에 보이게 하기 위해서 UStaticMeshComponent 생성
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);	// RootComponent에 부착
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));	// 구체 형태의 스태틱 메시 에셋을 불러옴
	// 에셋 로드에 성공하면
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);	//SphereVisual의 메시를 불러온 스태틱 메시 에셋으로 설정
		// 크기, 위치 지정
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OurParticleSystem"));	// UParticleSystemComponent를 생성하여 OurParticleSystem에 저장
	OurParticleSystem->SetupAttachment(RootComponent);	// RootComponent에 부착
	OurParticleSystem->bAutoActivate = false;	// 파티클이 시작될 때 자동으로 켜지는 것을 방지
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));// 파티클 위치 조정
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_FIre.P_Fire"));	// 파티클 에셋을 불러옴
	// 에셋 로드에 성공하면
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);	// OurParticleSystem에 에셋 설정
	}
	
	// USpringArmComponent : 카메라가 캐릭터보다 약간 느리게 움직이면서 따라가는 기능
	// or 벽을 뚫고 들어가지 않게 해주는 기능을 제공하는 컴포넌트
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);	// RootComponent에 부착
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));	// SpringArm의 각도 조절
	SpringArm->TargetArmLength = 400.0f;	// 따라가야 할 타겟과의 거리
	SpringArm->bEnableCameraLag = true;	// SpringArm이 곧바로 따라가지 않고 천천히 따라갈 것인지
	SpringArm->CameraLagSpeed = 3.0f;	// 따라가는 속도 지정

	UCameraComponent* Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));	// SpringArm에 부착할 카메라 생성
	// SpringArm에 부착
	// USpringArmComponent::SocketName : 카메라를 SpringArm에 내장된 소켓에 붙일 수 있음
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;	// OurMovementComponent가 RootComponent를 따라서 업데이트하도록

	// CollidingPawn을 기본 플레이어가 조종하도록 설정
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 함수와 입력 매핑을 바인딩
	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	InputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

// GetMovementComponent : 다른 클래스가 Pawn이 사용중인 PawnMovementComponent에 접근 시 사용
// 우리가 만든 MovementComponent를 가져가서 사용하도록 변경
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	// OurMovementComponent의 상태 확인
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{ 
		// AddInputVector에 Actor의 정면 방향과 입력 값을 곱해서 넘김
		// AddInputVector 함수로 무브먼트 컴포넌트에 전달된 입력벡터는 ConsumeInputVector 함수를 이용해 꺼내짐
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	// OurMovementComponent의 상태 확인
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		// AddInputVector에 Actor의 오른쪽 방향과 입력 값을 곱해서 넘김
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	// GetActorRotation : Actor의 회전 상태를 가져옴
	// AxisValue만큼 회전
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		// ToggleActive : 파티클 동작/멈춤
		OurParticleSystem->ToggleActive();
	}
}