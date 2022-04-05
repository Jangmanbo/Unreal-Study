// Copyright Epic Games, Inc. All Rights Reserved.


#include "HowTo_UMGGameModeBase.h"
#include <Blueprint/UserWidget.h>

void AHowTo_UMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);	// 게임이 시작될 때 UI를 표시
}

void AHowTo_UMGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> MewWidgetClass)
{
	// CurrentWidget이 비어있는지 검사
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();	// 화면에서 UI를 제거
		CurrentWidget = nullptr;	// CurrentWidget을 비움
	}

	// MewWidgetClass가 유효한지 검사
	if (MewWidgetClass != nullptr)
	{
		// CreateWidget으로 만든 새 위젯을 CurrentWidget에 저장
		CurrentWidget = CreateWidget(GetWorld(), MewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();	// ViewPort에 표시
		}
	}
}
