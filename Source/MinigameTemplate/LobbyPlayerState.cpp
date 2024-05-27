// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MinigameTemplateCharacter.h"
#include "LobbyPlayerController.h"


void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	OnPawnSet.AddDynamic(this, &ThisClass::SetPlayerPawn);
}

void ALobbyPlayerState::SetPlayerEnterID(int32 NewEnterID)
{
	PlayerEnterID = NewEnterID;
}

int32 ALobbyPlayerState::GetPlayerEnterID() const
{
	return PlayerEnterID;
}

void ALobbyPlayerState::SetIsRedTeamTo(bool IsChecked)
{
	//if server
	if (HasAuthority())
	{
		// 그냥 값 변경
		IsRedTeam = IsChecked;
		// OnIsRedTeamChanged()호출해서 자신의 화면 업데이트.
		OnIsRedTeamChanged();
	}
	else
	{
		// 서버로 전송. 
		SV_SetIsRedTeamTo(IsChecked);
	}
}

bool ALobbyPlayerState::GetIsRedTeam() const
{
	return IsRedTeam;
}

void ALobbyPlayerState::SV_SetIsRedTeamTo_Implementation(bool IsChecked)
{
	// 값 변경
	IsRedTeam = IsChecked;
	// 화면 업데이트.
	OnIsRedTeamChanged();
}

void ALobbyPlayerState::OnRep_IsRedTeam()
{
	// 화면 업데이트 함수 호출
	OnIsRedTeamChanged();

	//Widget Also Changes.
	UpdatePlayerListWidget();

}

void ALobbyPlayerState::OnIsRedTeamChanged()
{
	AMinigameTemplateCharacter* LobbyPlayerCharacter = Cast<AMinigameTemplateCharacter> (GetPawn() );
	if (!IsValid(LobbyPlayerCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Pawn From PS Not available"));
		return;
	}
	LobbyPlayerCharacter->SetMaterialByPlayerTeam(IsRedTeam);

	//Widget Also Changes.

	UpdatePlayerListWidget();

}

void ALobbyPlayerState::SetSelectedCharacter(FString NewCharacter)
{
	// If Server, Just Do it
// else Client, Pass to Server.
	if (HasAuthority())
	{
		SelectedCharacter = NewCharacter;
		OnChangeCharacter();

	}
	else
	{
		SV_RequestChangeCharacter(NewCharacter);
	}
}

FString ALobbyPlayerState::GetSelectedCharacter() const
{
	return SelectedCharacter;
}

void ALobbyPlayerState::SV_RequestChangeCharacter_Implementation(const FString& NewCharacterName)
{
	SelectedCharacter = NewCharacterName;
	OnChangeCharacter();
}

void ALobbyPlayerState::OnChangeCharacter()
{
	// Only In Server.
	// call controller's change character?
	ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(GetPlayerController());
	if (!IsValid(LobbyPC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PlayerController Not Available : OnChangeCharacter()"));
		return;
	}
	LobbyPC->ChangeCharacter(SelectedCharacter);

	//Change UI
	UpdatePlayerListWidget();
}

void ALobbyPlayerState::OnRep_SelectedCharacter()
{
	// on client. change ui
	UpdatePlayerListWidget();
}

void ALobbyPlayerState::OnRep_bIsHost()
{
}

void ALobbyPlayerState::OnRep_bIsReady()
{
	// Call On Ready Change..
	OnReadyChanged();
}

void ALobbyPlayerState::OnReadyChanged()
{
	// change Widget's Readytext...
}

void ALobbyPlayerState::SetIsReady(bool bNewIsReady)
{
	bIsReady = bNewIsReady;
	// Call On Ready Change...
	OnReadyChanged();
}

bool ALobbyPlayerState::GetIsReady() const
{
	return bIsReady;
}

void ALobbyPlayerState::UpdatePlayerListWidget()
{
	AController* PC = GetWorld()->GetFirstPlayerController();

	if (PC == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No Controller : LobbyPS -> UpdatePlayerListWidget()")); //BP.... (No StaticClass(). It Returns Pawn
		return;
	}

	// call PC's edit widget.
	ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(PC);
	if (!IsValid(LobbyPC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyPC Is Not Valid : LobbyPS -> UpdatePlayerListWidget()")); //BP.... (No StaticClass(). It Returns Pawn
		return;
	}
	LobbyPC->LobbyWidgetUpdate();

}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, IsRedTeam);
	DOREPLIFETIME(ALobbyPlayerState, SelectedCharacter);
	DOREPLIFETIME(ALobbyPlayerState, PlayerEnterID);
}

void ALobbyPlayerState::SetPlayerPawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (!HasAuthority())
	{
		AMinigameTemplateCharacter* NewCharacter = Cast<AMinigameTemplateCharacter>(NewPawn);
		if (!IsValid(NewCharacter))
		{
			return;
		}
		NewCharacter->SetMaterialByPlayerTeam(IsRedTeam);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnPawnSet"));
	}

	ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(LobbyPC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyPC Is Not Valid : LobbyPS -> UpdatePlayerListWidget()")); //BP.... (No StaticClass(). It Returns Pawn
		return;
	}
	LobbyPC->LobbyWidgetUpdate();
}
