// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState() : player1Kills(0), player2Kills(0), player3Kills(0), player4Kills(0)
{

}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	AddKills(22, 1);
	UE_LOG(LogTemp, Error, TEXT("BEGIN PLAY!"));
}




void AMyGameState::AddKills(int kills_, int player_)
{
	
	ADeathMatchGameMode * mode = Cast<ADeathMatchGameMode>(GetWorld()->GetAuthGameMode());
	switch (player_)
	{
	case 1:
		player1Kills += kills_;
		UE_LOG(LogTemp, Error, TEXT("Player 1 received kills"));
		mode->AddKills(kills_, player_);
		break;
	case 2:
		player2Kills += kills_;
		UE_LOG(LogTemp, Error, TEXT("Player 2 received kills"));
		mode->AddKills(kills_, player_);
		break;
	case 3:
		player3Kills += kills_;
		UE_LOG(LogTemp, Error, TEXT("Player 3 received kills"));
		mode->AddKills(kills_, player_);
		break;
	case 4:
		player4Kills += kills_;
		UE_LOG(LogTemp, Error, TEXT("Player 4 received kills"));
		mode->AddKills(kills_, player_);
		break;
	case 0:
		UE_LOG(LogTemp, Error, TEXT("0 given to the switch"));
	}
	
}


