// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HowTo_UMGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HOWTO_UMG_API AHowTo_UMGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// �������Ʈ���� �� �Լ��� ȣ�� ����
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> MewWidgetClass);

protected:
	virtual void BeginPlay() override;
	
	// ������ ���۵� �� ǥ�õ� UI ������ ������ ������Ƽ
	// TSubclassOf : �𸮾󿡼� UCLASS Ÿ�� �������� �����ϴ� ���ø� Ŭ����
	// <>���� ���ø� ���ڿ� Ÿ���� ��ġ�ϰų� �� Ÿ���� ��ӹ��� Ÿ������ ��Ÿ���߿� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	// ���� ȭ�鿡 ǥ�õǰ� �ִ� UI ������ ������ ������Ƽ
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
