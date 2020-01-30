// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMatchGameMode.h"


ADeathMatchGameMode::ADeathMatchGameMode() : playerBP(nullptr), pointsPerKill(50), killsToWin(20), dmPlayer1Kills(0), dmPlayer2Kills(0), dmPlayer3Kills(0), dmPlayer4Kills(0)
{
	spawnPoints.Init(nullptr, 4);
	players.Init(nullptr, 4);
}

void ADeathMatchGameMode::StartGame()
{
	SpawnPlayers();
}

// everytime a kill is made the car should call the end game function to check if the game has ended
void ADeathMatchGameMode::EndGame(int playerKills_, int player_)
{
	// kills is just a temporary variable. Will turn into Player->Kills when it's added
	if (playerKills_ >= killsToWin)
	{
		// this will be replaced by showing UI in the future but this will just show a debug message
		UE_LOG(LogTemp, Warning, TEXT("EndGame"));
		switch (player_)
		{
		case 1:
			UE_LOG(LogTemp, Warning, TEXT("Player 1 was won the game!"));
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("Player 2 was won the game!"));
			break;
		case 3:
			UE_LOG(LogTemp, Warning, TEXT("Player 3 was won the game!"));
			break;
		case 4:
			UE_LOG(LogTemp, Warning, TEXT("Player 4 was won the game!"));
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough kills to trigger end"));
	}

}

void ADeathMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartGame();
}

void ADeathMatchGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void ADeathMatchGameMode::AddKills(int dmKills_, int dmPlayer_)
{
	// just for the purpose of testing it'll add 1 and then call end game
	switch (dmPlayer_)
	{
	case 1:
		dmPlayer1Kills += dmKills_;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 received kills"));
		EndGame(dmKills_, dmPlayer_);
		break;
	case 2:
		dmPlayer2Kills += dmKills_;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 received kills"));
		EndGame(dmKills_, dmPlayer_);
		break;
	case 3:
		dmPlayer3Kills += dmKills_;
		UE_LOG(LogTemp, Warning, TEXT("Player 3 received kills"));
		EndGame(dmKills_, dmPlayer_);
		break;
	case 4:
		dmPlayer4Kills += dmKills_;
		UE_LOG(LogTemp, Warning, TEXT("Player 4 received kills"));
		EndGame(dmKills_, dmPlayer_);
		break;
	}

}

void ADeathMatchGameMode::SetSpawnPoint(ASpawner* spawnPoints_, int index) {
	//Get the index of the spawn points in the level and assign said spawn points to the spawn points array 
	if (index == 0) {
		spawnPoints[0] = spawnPoints_;
	}

	else if (index == 1) {
		spawnPoints[1] = spawnPoints_;
	}

	else if (index == 2) {
		spawnPoints[2] = spawnPoints_;
	}

	else {
		spawnPoints[3] = spawnPoints_;
	}
}

void ADeathMatchGameMode::SpawnPlayers()
{
	UWorld* wrld = GetWorld();
	FActorSpawnParameters param;

	//loop through each spawn point and spawn a car there 
	for (int i = 0; i < 4; ++i) {
		wrld->SpawnActor(playerBP, &spawnPoints[i]->location, &spawnPoints[i]->rotator, param);
		players[i] = playerBP.GetDefaultObject();
		players[i]->SetPlayer((EAutoReceiveInput::Type)(i + 1));
	}
}


