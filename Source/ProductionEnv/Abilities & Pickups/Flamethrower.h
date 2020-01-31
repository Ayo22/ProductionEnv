// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Flamethrower.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONENV_API AFlamethrower : public AAbility
{
	GENERATED_BODY()
public:

	AFlamethrower();
	virtual void Activate() override;
	virtual void Use() override;
	int abilityID;
};
