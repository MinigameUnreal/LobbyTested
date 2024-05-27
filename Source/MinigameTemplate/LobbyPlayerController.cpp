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
		TObjectPtr<APlayerState> PS = LobbyGS->PlayerArray[i];
		LobbyWidget->PlayersListWrapBox->GetChildAt(i);
	}
	// from game state -> edit widget.
	LobbyWidget->PlayersListWrapBox->GetChildAt(0);
}
