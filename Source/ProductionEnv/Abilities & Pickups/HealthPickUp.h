// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONENV_API AHealthPickUp : public APickUp
{
	GENERATED_BODY()

public:
	AHealthPickUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pick Up")
	FStatPickUp stats;

	FStatPickUp GetStat() override;

	bool Initialize() override;

};
