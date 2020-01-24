// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS(Abstract, Blueprintable)
class PRODUCTIONENV_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	AAbility() {}
	// Sets default values for this actor's properties
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Activate() PURE_VIRTUAL(AAbility::Activate, ;);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Use() PURE_VIRTUAL(AAbility::Use, ;);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
