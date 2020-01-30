// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"Car/PlayerCar.h"
#include "Spawner.h"
#include "GameFramework/GameModeBase.h"
#include "DeathMatchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONENV_API ADeathMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnPoints)
		TArray<ASpawner*> spawnPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayersToSpawn)
		TSubclassOf<class APlayerCar> playerBP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayableCharacters)
		TArray<APlayerCar*> players;

	ADeathMatchGameMode();
	void EndGame();
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	void AddKills();


protected:

	void StartGame();

private:
	UPROPERTY(VisibleAnywhere)
		int pointsPerKill;
	int killsToWin;
	int kills;
	UFUNCTION(BlueprintCallable)
		void SetSpawnPoint(ASpawner* spawnPoint_, int index);
	void SpawnPlayers();
	//UFUNCTION(BlueprintCallable)
		//void SetPlayers(APlayerCar* player_, int index);
	
};
