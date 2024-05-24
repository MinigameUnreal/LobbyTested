// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectCharacterButton;	
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterNameText;

protected:
	UFUNCTION()
	void OnSelectCharacter();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<APawn> CharacterClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CharacterName;
	
};
