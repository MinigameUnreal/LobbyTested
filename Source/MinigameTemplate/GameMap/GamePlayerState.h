// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePlayerState.h"
#include "GamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API AGamePlayerState : public ABasePlayerState
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void SetPlayerEnterID(int32 NewEnterID);
	virtual void SetIsRedTeamTo(bool IsChecked);
	virtual void SetSelectedCharacter(FString NewCharacter);

public:
	// Call when OnPawnSet Done. Since TeamColor is not replicated, Do Initial Paint.
	UFUNCTION()
	void SetPlayerPawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
};
