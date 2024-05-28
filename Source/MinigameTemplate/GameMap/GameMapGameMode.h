// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API AGameMapGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	// is it playercontroller changing test.
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
};
