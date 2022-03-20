// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNREALFUNCTION_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Damage")
	float DamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FString str;

	// BlueprintImplementableEvent : 디자이너가 기능을 구현
	// -> 함수의 본체가 필요 X
	//	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")

	// BlueprintNativeEvent : 디자이너가 기능을 구현, 디자이너가 구현하지 않았을 때의 기본 기능을 프로그래머가 구현 가능
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
	void CallFromCpp();
	virtual void CallFromCpp_Implementation();	디자이너가 구현하지 않았을 때의 기본 기능

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FunctionName();

	// 블루프린트에서 사용 가능
	// 카테고리를 할당해야 블루프린트에서 정상적으로 동작
	UFUNCTION(BlueprintCallable, Category="Damage")
	void CalculateDPS();

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
