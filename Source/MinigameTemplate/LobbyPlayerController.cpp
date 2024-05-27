// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h" 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LobbyPlayerState.h"
#include "MinigameTemplateCharacter.h"
#include "UI/LobbyWidget.h"
#include "Components/WrapBox.h"
#include "LobbyGameStateBase.h"
#include "UI/PlayerCardWidget.h"

void ALobbyPlayerController::BeginPlay()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI LobbyInputMode;
	SetInputMode(LobbyInputMode);

	if (IsLocalController())
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
		Widget->AddToViewport();

		LobbyWidget = Cast<ULobbyWidget>(Widget);
		if (!IsValid(LobbyWidget))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyWidget Error : LobbyPlayerController BeginPlay()"));
			return;
		}

		// can i get all playerstate here?
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%d asdflkjlk"), GetWorld()->GetGameState()->PlayerArray.Num() ) );

		LobbyWidgetUpdate();

	}

	
}


void ALobbyPlayerController::ChangeCharacter(const FString& NewCharacterName)
{
	// Only In Server.
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald,NewCharacter->GetName() );
	TSubclassOf<APawn>* NewCharacterClass = CharacterClassesMap.Find(NewCharacterName);
	// Destroy Pawn, ReSpawn, Possess
	auto CurrentPawn = GetPawn();
	FTransform SpawnTransform = GetPawn()->GetTransform();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetPawn()->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Spawn Actor Start-------"));
	APawn* NewPawn = Cast<APawn>( GetWorld()->SpawnActor(*NewCharacterClass, &SpawnTransform, SpawnParameters) );
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Spawn Actor Done-------"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Possess Actor Start-------"));
	Possess(NewPawn);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Possess Actor Done-------"));


}

void ALobbyPlayerController::LobbyWidgetUpdate()
{
	if (!IsValid(LobbyWidget))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyWidget Error : LobbyPlayerController LobbyWidgetUpdate()"));
		return;
	}

	// get game state. 
	auto LobbyGS = GetWorld()->GetGameState<ALobbyGameStateBase>();
	if (!IsValid(LobbyGS))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("GameState Not Valid : LobbyPlayerController LobbyWidgetUpdate()"));
		return;
	}

	int32 NumberOfPlayers = LobbyGS->PlayerArray.Num();
	for (int32 i = 0; i < NumberOfPlayers; ++i)
	{
		ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(LobbyGS->PlayerArray[i]);
		if (!IsValid(LobbyPS))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyPS Not Valid : LobbyPlayerController LobbyWidgetUpdate()"));
			continue;
		}
		auto PlayerCard = Cast<UPlayerCardWidget>( LobbyWidget->PlayersListWrapBox->GetChildAt( i ) );
		if (!IsValid(PlayerCard))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PlayerCard Not Valid : LobbyPlayerController LobbyWidgetUpdate()"));
			continue;
		}

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Player %d card ready to edit"), i));
		PlayerCard->CardUpdate(LobbyPS->GetIsRedTeam(), LobbyPS->GetSelectedCharacter());
	}
	// from game state -> edit widget.
	//LobbyWidget->PlayersListWrapBox->GetChildAt(0);
}
