// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinigameTemplateGameMode.h"
#include "MinigameTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerState.h"
#include "LobbyGameStateBase.h"

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

void AMinigameTemplateGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto LobbyPC = Cast<ALobbyPlayerController>(NewPlayer);
	if (!IsValid(LobbyPC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnPostLogin, LobbyPlayerController Not Valid"));
		return;
	}
	auto LobbyPS = LobbyPC->GetPlayerState<ALobbyPlayerState>();
	if (!IsValid(LobbyPS))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnPostLogin, LobbyPlayerState Not Valid"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("OnPostLogin, LobbyPlayerState Available?")); // It Seems Okay.


	auto LobbyGS = GetGameState<ALobbyGameStateBase>();
	if (!IsValid(LobbyGS))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnPostLogin, GameState Not Valid"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("%d : Current GameState's PlayerArray's Num"), LobbyGS->PlayerArray.Num())); // It Seems Okay 2

	// access to controller's widget edit function here

}
