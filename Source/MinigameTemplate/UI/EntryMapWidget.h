// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryMapWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UEntryMapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreateRoomButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* FindRoomButton;


protected:
	UFUNCTION()
	void OnCreateRoomButtonClicked();

	UFUNCTION()
	void OnFindRoomButtonClicked();
};
