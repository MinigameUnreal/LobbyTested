// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../LobbyPlayerController.h"
#include "../LobbyPlayerState.h"

void UCharacterSelectWidget::NativeConstruct()
{
	SelectCharacterButton->OnClicked.AddDynamic(this, &ThisClass::OnSelectCharacter);

	CharacterNameText->SetText(FText::FromString(CharacterName));
}

void UCharacterSelectWidget::OnSelectCharacter()
{
	auto CurrentPawn = GetOwningPlayerPawn();
	if (!IsValid(CurrentPawn))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, TEXT("Pawn Not Valid"));
		return;
	}

	if (CurrentPawn->GetClass() == CharacterClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, TEXT("Same Class Selected"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, TEXT("Change To New Selected Character Class"));
		// Do Character Change
		// First Toss to Player Controller
		auto LobbyPC = Cast<ALobbyPlayerController> (GetOwningPlayer() );
		if (!IsValid(LobbyPC))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PC Not Available"));

			return;
		}
		auto LobbyPS = LobbyPC->GetPlayerState<ALobbyPlayerState>();
		// call Lobby Controller's Change Pawn Func.
		if (!IsValid(LobbyPS))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PS Not Available : CharacterSelectWidget::OnSelectCharacter()"));

			return;
		}
		LobbyPS->SetSelectedCharacter(CharacterName);
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, CurrentPawn->GetClass()->GetName()); //BP.... (No StaticClass(). It Returns Pawn
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, CharacterClass->GetName());	//BP_.....
}
