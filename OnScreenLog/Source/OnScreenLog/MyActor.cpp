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

	// �Ķ����1 : -1�̸� �տ��� ��� �α׸� �о�� ���ο� �α׸� ���
	// -1�� �ƴϸ� �ռ� �α׸� ����� ���ο� �α׸� ���
	// �Ķ����2 : �αװ� ȭ�鿡 �����ִ� �ð�
	// �Ķ����3 : �α� ����
	// �Ķ����4 : ����� �޼���
	// AddOnScreenDebugMessage : �������Ʈ�� Print String���� �޸� ��� �α� �гο��� �αװ� ���� ����
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello 2"));

	// �������Ʈ�� Print String�� ����� �״�� C++ Ŭ�������� ���
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello 3"), true, true, FLinearColor::Green, 2.0f);
}

