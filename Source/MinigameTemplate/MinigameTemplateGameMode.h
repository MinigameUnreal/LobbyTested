// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MinigameTemplateGameMode.generated.h"

UCLASS(minimalapi)
class AMinigameTemplateGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMinigameTemplateGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	int32 PlayerIDOfNextPlayer = 0;
};



