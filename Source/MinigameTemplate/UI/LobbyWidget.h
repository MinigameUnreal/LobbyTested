// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* PlayersListWrapBox;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* ReadyOrStartSwitcher;

public:
	void SwitchSwitcherWidget(bool bIsReady);
};
