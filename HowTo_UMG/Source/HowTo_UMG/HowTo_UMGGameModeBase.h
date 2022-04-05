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
	// 블루프린트에서 이 함수를 호출 가능
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> MewWidgetClass);

protected:
	virtual void BeginPlay() override;
	
	// 게임이 시작될 때 표시될 UI 위젯을 저장할 프로퍼티
	// TSubclassOf : 언리얼에서 UCLASS 타입 안정성을 보장하는 템플릿 클래스
	// <>안의 템플릿 인자와 타입이 일치하거나 이 타입을 상속받은 타입인지 런타임중에 확인
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	// 현재 화면에 표시되고 있는 UI 위젯을 저장할 프로퍼티
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
