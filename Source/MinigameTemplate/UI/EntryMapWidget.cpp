// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryMapWidget.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"

#include "Interfaces/OnlineSessionInterface.h"


void UEntryMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (CreateRoomButton)
	{
		CreateRoomButton->OnClicked.AddDynamic(this, &UEntryMapWidget::OnCreateRoomButtonClicked);
	}

	if (FindRoomButton)
	{
		FindRoomButton->OnClicked.AddDynamic(this, &UEntryMapWidget::OnFindRoomButtonClicked);
	}
}

void UEntryMapWidget::OnCreateRoomButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CreateButton"));
	//IOnlineSubsystem::Get()->GetSessionInterface()->CreateSession();

}

void UEntryMapWidget::OnFindRoomButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FindButton"));

}
