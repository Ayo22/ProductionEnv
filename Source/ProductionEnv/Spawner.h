// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeathMatchGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PRODUCTIONENV_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector location;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator rotator;
	UPROPERTY(EditAnywhere, BluePrintReadOnly)
		int index;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
