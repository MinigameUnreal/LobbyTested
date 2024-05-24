// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSelectWidget.h"
#include "Components/CheckBox.h"
#include "../LobbyPlayerState.h"

void UTeamSelectWidget::NativeConstruct()
{
	IsRedTeamCheckBox->OnCheckStateChanged.AddDynamic(this, &ThisClass::OnIsRedTeamSettedTo);
	
}

void UTeamSelectWidget::OnIsRedTeamSettedTo(bool bIsChecked)
{
	if (bIsChecked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Clicked to Red"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Clicked to Blue"));
	}


	auto PS = GetOwningPlayerState();
	if (!IsValid( PS ))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PlayerState Not Valid"));
	}
	auto LobbyPS = Cast<ALobbyPlayerState>(PS);
	if (!IsValid(LobbyPS))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyPlayerState Not Valid"));

	}

	LobbyPS->SetIsRedTeamTo(bIsChecked);

}
