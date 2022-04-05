// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 블루프린트 클래스 불러오기
	// ConstructorHelpers::FClassFinder<BP 클래스가 상속받는 클래스 타입> BpClass(경로);
	static ConstructorHelpers::FClassFinder<APawn> BpClass(TEXT("/Game/StarterContent/BP_TextClass"));
	// 클래스가 제대로 불러와졌는지 확인
	if (BpClass.Succeeded() && BpClass.Class != NULL)
	{

	}

	// 리소스(ex. StaticMesh, Texture) 가져오기
	// ConstructorHelpers::FObjectFinder<리소스 타입>
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("MeshComponent"));
	static ConstructorHelpers::FObjectFinder< UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	// 리소스가 제대로 불러와졌는지 확인
	if (MeshAsset.Succeeded() && MeshAsset.Object != NULL)
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

