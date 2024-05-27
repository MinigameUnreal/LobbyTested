// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// 먼저들어온 사람부터 0, 1, 2, 3...
	int32 PlayerEnterID = 0;
public:
	void SetPlayerEnterID(int32 NewEnterID);
	int32 GetPlayerEnterID();

// ----------- IsRedTeam's
protected:
	UPROPERTY(ReplicatedUsing = OnRep_IsRedTeam)
	bool IsRedTeam;

public:
	void SetIsRedTeamTo(bool IsChecked);
	bool GetIsRedTeam();

protected:
	UFUNCTION(Server, Reliable)
	void SV_SetIsRedTeamTo(bool IsChecked);
	
	//클라이언트에서 값 변경 notify받는 함수, 안에서 OnIsRedTeamChanged호출.
	UFUNCTION()
	void OnRep_IsRedTeam();

	void OnIsRedTeamChanged();

// ------------ Selected Character's 
protected:
	UPROPERTY(ReplicatedUsing = OnRep_SelectedCharacter)
	FString SelectedCharacter = "Quinn";

public:
	void SetSelectedCharacter(FString NewCharacter);
	FString GetSelectedCharacter();

protected:
	UFUNCTION(Server, Reliable)
	void SV_RequestChangeCharacter(const FString& NewCharacterName);

	void OnChangeCharacter();
	
	UFUNCTION()
	void OnRep_SelectedCharacter();


	// ------------- Change LobbyUI's Player List widget.
protected:
	// Update UI
	void UpdatePlayerListWidget();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	// Call when OnPawnSet Done.
	UFUNCTION()
	void SetPlayerPawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
};
