// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, TSubclassOf<APawn>> CharacterClassesMap;

public:
	const TSubclassOf<APawn>* const FindCharacterClass(const FString& CharacterName);
};
