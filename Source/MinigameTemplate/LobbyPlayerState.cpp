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

int32 ALobbyPlayerState::GetPlayerEnterID()
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

	//Widget Also Changes.
	UpdatePlayerListWidget();

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

FString ALobbyPlayerState::GetSelectedCharacter()
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
	auto LobbyPC = Cast<ALobbyPlayerController>(GetPlayerController());
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

void ALobbyPlayerState::UpdatePlayerListWidget()
{
	AController* PC;
	if (HasAuthority())
	{
		
		//PC = GetOwningController();
		PC = GetWorld()->GetFirstPlayerController();

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("-------------"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, PC->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("-------------"));
	}
	else
	{
		PC = GetWorld()->GetFirstPlayerController();

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("-------------"));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, PC->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("-------------"));
	}
	if (PC == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No Controller : LobbyPS -> UpdatePlayerListWidget()")); //BP.... (No StaticClass(). It Returns Pawn
		return;
	}

	// call PC's edit widget.
	auto LobbyPC = Cast<ALobbyPlayerController>(PC);
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

	auto LobbyPC = Cast<ALobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(LobbyPC))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LobbyPC Is Not Valid : LobbyPS -> UpdatePlayerListWidget()")); //BP.... (No StaticClass(). It Returns Pawn
		return;
	}
	LobbyPC->LobbyWidgetUpdate();
}
