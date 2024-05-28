// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UStartButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UFUNCTION()
	void OnStartButtonClicked();
	
};
