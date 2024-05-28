// Fill out your copyright notice in the Description page of Project Settings.


#include "StartButtonWidget.h"
#include "Components/Button.h"

void UStartButtonWidget::NativeConstruct()
{
	StartButton->OnClicked.AddDynamic(this, &ThisClass::OnStartButtonClicked);

}

void UStartButtonWidget::OnStartButtonClicked()
{
	// do i have to check, here is server again?
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, TEXT("StartButton Clicked"));
	GetWorld()->ServerTravel("TempGameMap");
}
