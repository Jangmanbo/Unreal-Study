// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerSceneComponent.h"

// Sets default values for this component's properties
USpawnerSceneComponent::USpawnerSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 3개의 자손을 스폰
	for (int i = 0; i < 3; i++)
	{
		// UStaticMeshComponent 생성
		// 컴포넌트의 이름이 같으면 안되므로 i를 붙임
		UStaticMeshComponent* Child= CreateDefaultSubobject< UStaticMeshComponent>(FName(TEXT("Child"), i));
		Child->SetupAttachment(this);
		// UStaticMesh 에셋을 가져와 Child에 설정
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
		if (MeshAsset.Succeeded())
		{
			Child->SetStaticMesh(MeshAsset.Object);
		}

		// 생성된 컴포넌트들을 부모를 중심으로 원형으로 배치
		// Childs 배열에 넣어줌
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
		// Childs 배열에 들어있는 자식 컴포넌트들과 SpawnerSceneComponent를 파괴
		for (int i = 0; i < Childs.Num(); i++)
		{
			Childs[i]->DestroyComponent();
		}
		DestroyComponent();
	}
}

