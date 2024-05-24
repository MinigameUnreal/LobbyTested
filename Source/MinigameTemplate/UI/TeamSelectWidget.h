// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UTeamSelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* IsRedTeamCheckBox;

protected:
	UFUNCTION()
	void OnIsRedTeamSettedTo(bool bIsChecked);
};
