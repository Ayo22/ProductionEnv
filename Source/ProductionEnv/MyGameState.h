// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DeathMatchGameMode.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONENV_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameState();
	virtual void BeginPlay() override;
	void AddKills(int kills_, int player_);
	int player1Kills;
	int player2Kills;
	int player3Kills;
	int player4Kills;



};
