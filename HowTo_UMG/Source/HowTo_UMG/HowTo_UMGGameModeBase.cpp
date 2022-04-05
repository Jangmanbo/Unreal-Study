// Copyright Epic Games, Inc. All Rights Reserved.


#include "HowTo_UMGGameModeBase.h"
#include <Blueprint/UserWidget.h>

void AHowTo_UMGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);	// ������ ���۵� �� UI�� ǥ��
}

void AHowTo_UMGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> MewWidgetClass)
{
	// CurrentWidget�� ����ִ��� �˻�
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();	// ȭ�鿡�� UI�� ����
		CurrentWidget = nullptr;	// CurrentWidget�� ���
	}

	// MewWidgetClass�� ��ȿ���� �˻�
	if (MewWidgetClass != nullptr)
	{
		// CreateWidget���� ���� �� ������ CurrentWidget�� ����
		CurrentWidget = CreateWidget(GetWorld(), MewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();	// ViewPort�� ǥ��
		}
	}
}
