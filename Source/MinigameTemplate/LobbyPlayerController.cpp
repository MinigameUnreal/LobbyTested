// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h" 

void ALobbyPlayerController::BeginPlay()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI LobbyInputMode;
	SetInputMode(LobbyInputMode);

	if (IsLocalController())
	{
		UUserWidget* LobbyWidget = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
		LobbyWidget->AddToViewport();
	}

}

void ALobbyPlayerController::RequestChangeCharacter(const FString& NewCharacterName)
{
	// If Server, Just Do it
	if (HasAuthority())
	{
		TSubclassOf<APawn>* NewCharacterClass = CharacterClassesMap.Find(NewCharacterName);
		if (IsValid(*NewCharacterClass))
		{
			ChangeCharacter(*NewCharacterClass);
		}

	}
	// If Client, Pass to Server.


}

void ALobbyPlayerController::SV_RequestChangeCharacter_Implementation(const FString& NewCharacterName)
{
}

void ALobbyPlayerController::ChangeCharacter(TSubclassOf<APawn> NewCharacter)
{
	// Only In Server.
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald,NewCharacter->GetName() );

	// Destroy Pawn, ReSpawn, Possess
	auto CurrentPawn = GetPawn();
	FTransform SpawnTransform = GetPawn()->GetTransform();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetPawn()->Destroy();
	APawn* NewPawn = Cast<APawn>( GetWorld()->SpawnActor(NewCharacter, &SpawnTransform, SpawnParameters) );
	Possess(NewPawn);
}
