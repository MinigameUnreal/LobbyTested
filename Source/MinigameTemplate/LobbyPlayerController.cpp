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

		auto LobbyWidget = Cast<ULobbyWidget>(Widget);
		if (!IsValid(LobbyWidget))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyWidget Error : LobbyPlayerController BeginPlay()"));
			return;
		}

		// can i get all playerstate here?
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%d asdflkjlk"), GetWorld()->GetGameState()->PlayerArray.Num() ) );

		//LobbyWidget->PlayersListWrapBox->GetAllChildren();
		//LobbyWidget->PlayersListWrapBox->AddChildToWrapBox();

	}



	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Add Mapping Context"));
	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() ))
	//{
	//	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//}
	
}

void ALobbyPlayerController::RequestChangeCharacter(const FString& NewCharacterName)
{
	// If Server, Just Do it
	// else Client, Pass to Server.
	if (HasAuthority())
	{
		TSubclassOf<APawn>* NewCharacterClass = CharacterClassesMap.Find(NewCharacterName);
		if (IsValid(*NewCharacterClass))
		{
			ChangeCharacter(*NewCharacterClass);
		}

	}
	else
	{
		SV_RequestChangeCharacter(NewCharacterName);
	}

}

void ALobbyPlayerController::SV_RequestChangeCharacter_Implementation(const FString& NewCharacterName)
{
	TSubclassOf<APawn>* NewCharacterClass = CharacterClassesMap.Find(NewCharacterName);
	if (IsValid(*NewCharacterClass))
	{
		ChangeCharacter(*NewCharacterClass);
	}
}

void ALobbyPlayerController::ChangeCharacter(TSubclassOf<APawn> NewCharacter)
{
	// Only In Server.
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald,NewCharacter->GetName() );

	// Destroy Pawn, ReSpawn, Possess
	auto CurrentPawn = GetPawn();
	FTransform SpawnTransform = GetPawn()->GetTransform();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetPawn()->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Spawn Actor Start-------"));
	APawn* NewPawn = Cast<APawn>( GetWorld()->SpawnActor(NewCharacter, &SpawnTransform, SpawnParameters) );
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Spawn Actor Done-------"));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Possess Actor Start-------"));
	Possess(NewPawn);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, TEXT("------------Possess Actor Done-------"));

}
