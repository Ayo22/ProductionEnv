// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUp.h"
#include "CarPickupComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRODUCTIONENV_API UCarPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCarPickupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void StatPickUp(FStatPickUp pickUp_);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	int RetrieveStats(FString key_);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	TMap<FString, int> stats;

		
};
