// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerCardWidget::CardUpdate(bool IsRed, const FString& SelectedCharacter)
{
	if (IsRed)
	{
		TeamImage->SetBrushTintColor(FSlateColor(FColor::Red));
	}
	else
	{
		TeamImage->SetBrushTintColor(FSlateColor(FColor::Blue));
	}

	CharacterText->SetText(FText::FromString(SelectedCharacter));
}
