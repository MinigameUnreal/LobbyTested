// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinigameTemplateGameMode.h"
#include "MinigameTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerState.h"

AMinigameTemplateGameMode::AMinigameTemplateGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ALobbyPlayerController::StaticClass();
	PlayerStateClass = ALobbyPlayerState::StaticClass();
}
