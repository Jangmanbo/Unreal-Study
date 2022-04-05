// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// 파라미터1 : -1이면 앞에서 띄운 로그를 밀어내고 새로운 로그를 띄움
	// -1이 아니면 앞선 로그를 지우고 새로운 로그를 띄움
	// 파라미터2 : 로그가 화면에 남아있는 시간
	// 파라미터3 : 로그 색상
	// 파라미터4 : 출력할 메세지
	// AddOnScreenDebugMessage : 블루프린트의 Print String과는 달리 출력 로그 패널에는 로그가 남지 않음
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello 2"));

	// 블루프린트의 Print String의 기능을 그대로 C++ 클래스에서 사용
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello 3"), true, true, FLinearColor::Green, 2.0f);
}

