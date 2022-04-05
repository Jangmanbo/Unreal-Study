// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerSceneComponent.h"

// Sets default values for this component's properties
USpawnerSceneComponent::USpawnerSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 3���� �ڼ��� ����
	for (int i = 0; i < 3; i++)
	{
		// UStaticMeshComponent ����
		// ������Ʈ�� �̸��� ������ �ȵǹǷ� i�� ����
		UStaticMeshComponent* Child= CreateDefaultSubobject< UStaticMeshComponent>(FName(TEXT("Child"), i));
		Child->SetupAttachment(this);
		// UStaticMesh ������ ������ Child�� ����
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
		if (MeshAsset.Succeeded())
		{
			Child->SetStaticMesh(MeshAsset.Object);
		}

		// ������ ������Ʈ���� �θ� �߽����� �������� ��ġ
		// Childs �迭�� �־���
		float radian = (2.0f * PI) / 3.0f;
		radian *= i;
		FVector Location = FVector(FMath::Cos(radian), FMath::Sin(radian), 0.0f) * 100.0f;
		Child->SetRelativeLocation(Location);
		Childs.Add(Child);
	}

	DestroyTimer = 3.0f;
}


// Called when the game starts
void USpawnerSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnerSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DestroyTimer -= DeltaTime;
	if (DestroyTimer < 0.0f)
	{
		// Childs �迭�� ����ִ� �ڽ� ������Ʈ��� SpawnerSceneComponent�� �ı�
		for (int i = 0; i < Childs.Num(); i++)
		{
			Childs[i]->DestroyComponent();
		}
		DestroyComponent();
	}
}

