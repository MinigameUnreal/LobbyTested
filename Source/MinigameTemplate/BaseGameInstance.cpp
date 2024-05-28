// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

const TSubclassOf<APawn>* const UBaseGameInstance::FindCharacterClass(const FString& CharacterName)
{
	if (!CharacterClassesMap.Contains(CharacterName))
	{
		return nullptr;
	}

	return CharacterClassesMap.Find(CharacterName);
}
