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

	// USphereComponent : ��ü�� ���� ó���� �ϴ� ������Ʈ
	// �浹�� ó��, ���� ���̴� ���¸� ������ ����
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;	// SphereComponent�� RootComponent��
	SphereComponent->InitSphereRadius(40.0f);	// ��ü�� ũ�� ����
	// �ݸ��� ���������� �̸� ����
	// == �� ������Ʈ�� ���� �ݸ����� � �ݸ������� �浹�� ������ ������ ����
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// ���� ���̰� �ϱ� ���ؼ� UStaticMeshComponent ����
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);	// RootComponent�� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));	// ��ü ������ ����ƽ �޽� ������ �ҷ���
	// ���� �ε忡 �����ϸ�
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);	//SphereVisual�� �޽ø� �ҷ��� ����ƽ �޽� �������� ����
		// ũ��, ��ġ ����
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OurParticleSystem"));	// UParticleSystemComponent�� �����Ͽ� OurParticleSystem�� ����
	OurParticleSystem->SetupAttachment(RootComponent);	// RootComponent�� ����
	OurParticleSystem->bAutoActivate = false;	// ��ƼŬ�� ���۵� �� �ڵ����� ������ ���� ����
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));// ��ƼŬ ��ġ ����
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_FIre.P_Fire"));	// ��ƼŬ ������ �ҷ���
	// ���� �ε忡 �����ϸ�
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);	// OurParticleSystem�� ���� ����
	}
	
	// USpringArmComponent : ī�޶� ĳ���ͺ��� �ణ ������ �����̸鼭 ���󰡴� ���
	// or ���� �հ� ���� �ʰ� ���ִ� ����� �����ϴ� ������Ʈ
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);	// RootComponent�� ����
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));	// SpringArm�� ���� ����
	SpringArm->TargetArmLength = 400.0f;	// ���󰡾� �� Ÿ�ٰ��� �Ÿ�
	SpringArm->bEnableCameraLag = true;	// SpringArm�� ��ٷ� ������ �ʰ� õõ�� ���� ������
	SpringArm->CameraLagSpeed = 3.0f;	// ���󰡴� �ӵ� ����

	UCameraComponent* Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));	// SpringArm�� ������ ī�޶� ����
	// SpringArm�� ����
	// USpringArmComponent::SocketName : ī�޶� SpringArm�� ����� ���Ͽ� ���� �� ����
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;	// OurMovementComponent�� RootComponent�� ���� ������Ʈ�ϵ���

	// CollidingPawn�� �⺻ �÷��̾ �����ϵ��� ����
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
	
	// �Լ��� �Է� ������ ���ε�
	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	InputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

// GetMovementComponent : �ٸ� Ŭ������ Pawn�� ������� PawnMovementComponent�� ���� �� ���
// �츮�� ���� MovementComponent�� �������� ����ϵ��� ����
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	// OurMovementComponent�� ���� Ȯ��
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{ 
		// AddInputVector�� Actor�� ���� ����� �Է� ���� ���ؼ� �ѱ�
		// AddInputVector �Լ��� �����Ʈ ������Ʈ�� ���޵� �Էº��ʹ� ConsumeInputVector �Լ��� �̿��� ������
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	// OurMovementComponent�� ���� Ȯ��
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		// AddInputVector�� Actor�� ������ ����� �Է� ���� ���ؼ� �ѱ�
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	// GetActorRotation : Actor�� ȸ�� ���¸� ������
	// AxisValue��ŭ ȸ��
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		// ToggleActive : ��ƼŬ ����/����
		OurParticleSystem->ToggleActive();
	}
}