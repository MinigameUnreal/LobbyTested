// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMETEMPLATE_API ALobbyPlayerState : public ABasePlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

// -------- Player Enter ID Function Override -------
public:
	virtual void SetPlayerEnterID(int32 NewEnterID) override;

// ----------- IsRedTeam's ----------------------------
public:
	virtual void SetIsRedTeamTo(bool IsChecked) override;

protected:
	UFUNCTION(Server, Reliable)
	void SV_SetIsRedTeamTo(bool IsChecked);
	
	//클라이언트에서 값 변경 notify받는 함수, 안에서 OnIsRedTeamChanged호출.
	virtual void OnRep_IsRedTeam() override;
	virtual void OnIsRedTeamChanged() override;

// ------------ Selected Character's ----------------------
public:
	virtual void SetSelectedCharacter(FString NewCharacter) override;

protected:
	UFUNCTION(Server, Reliable)
	void SV_RequestChangeCharacter(const FString& NewCharacterName);

	virtual void OnChangeCharacter() override;
	virtual void OnRep_SelectedCharacter() override;

// ------------- IsReady, IsHost Related Functions Only In LobbyPlayerState -------------
protected:
	UPROPERTY(ReplicatedUsing = OnRep_bIsHost)
	bool bIsHost;

	UPROPERTY(ReplicatedUsing = OnRep_bIsReady)
	bool bIsReady;

	UFUNCTION()
	void OnRep_bIsHost();

	UFUNCTION()
	void OnRep_bIsReady();

	void OnReadyChanged();


public:
	void SetIsReady(bool bNewIsReady);
	bool GetIsReady() const;

// ------------- Change LobbyUI's Player List widget. ------------
protected:
	// Update UI
	void UpdatePlayerListWidget();


public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	// Call when OnPawnSet Done. Since TeamColor is not replicated, Do Initial Paint.
	UFUNCTION()
	void SetPlayerPawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);
};
