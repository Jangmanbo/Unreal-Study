// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "MyProject.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Log, TEXT("Constructor"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("Error Message"));
	UE_LOG(LogTemp, Warning, TEXT("Warning Message"));
	UE_LOG(LogTemp, Display, TEXT("Display Message"));

	// 직접 생성한 로그 카테고리 (프로젝트이름.h, cpp에 선언)
	UE_LOG(MyLogCategory, Log, TEXT("My Category Log"));

	FString CharacterName = TEXT("HiWer");
	UE_LOG(LogTemp, Log, TEXT("Character Name = %s"), *CharacterName);

	bool isAttackable = true;
	UE_LOG(LogTemp, Log, TEXT("Is Attackable = %s"), isAttackable ? TEXT("true") : TEXT("false"));

	int hp = 100;
	UE_LOG(LogTemp, Log, TEXT("HP = %d"), hp);

	float AttackSpeed = 1.0f;
	UE_LOG(LogTemp, Log, TEXT("Attack Speed = %f"), AttackSpeed);

	FVector CharacterPosition = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Position = %s"), *CharacterPosition.ToString());

	// 여러 타입의 변수를 한 번에 로그 출력
	UE_LOG(LogTemp, Log, TEXT("Character Name = %s, HP = %d, Attack Speed = %f"), *CharacterName, hp, AttackSpeed);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("Tick"));

}

