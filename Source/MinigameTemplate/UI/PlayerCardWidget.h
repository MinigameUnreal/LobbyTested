// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UPlayerCardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* TeamImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterText;

public:
	void CardUpdate(bool IsRed, const FString& SelectedCharacter);
	
};
