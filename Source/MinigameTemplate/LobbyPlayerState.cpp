// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "MinigameTemplateCharacter.h"


void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	OnPawnSet.AddDynamic(this, &ThisClass::SetPlayerPawn);
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

bool ALobbyPlayerState::GetIsRedTeam()
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
}

void ALobbyPlayerState::OnIsRedTeamChanged()
{
	auto LobbyPlayerCharacter = Cast<AMinigameTemplateCharacter> (GetPawn() );
	if (!IsValid(LobbyPlayerCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Pawn From PS Not available"));
		return;
	}
	LobbyPlayerCharacter->SetMaterialByPlayerTeam(IsRedTeam);

}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, IsRedTeam);
}

void ALobbyPlayerState::SetPlayerPawn(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	if (!HasAuthority())
	{
		auto NewCharacter = Cast<AMinigameTemplateCharacter>(NewPawn);
		if (!IsValid(NewCharacter))
		{
			return;
		}
		NewCharacter->SetMaterialByPlayerTeam(IsRedTeam);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnPawnSet"));
	}
}
