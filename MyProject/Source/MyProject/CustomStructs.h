// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStructs.generated.h"

/**
 * 
 */
class MYPROJECT_API CustomStructs
{
public:
	CustomStructs();
	~CustomStructs();
};

// Atomic : 구조체가 항상 하나의 단위로 직렬화 (디테일 창만 표시, 디테일 창에서만 수정 가능)
// BlueprintType : 구조체를 블루프린트에서 사용 가능
USTRUCT(Atomic, BlueprintType)
struct FCustomStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* actor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float f;
};