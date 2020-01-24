// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPickupComponent.h"

// Sets default values for this component's properties
UCarPickupComponent::UCarPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCarPickupComponent::StatPickUp(FStatPickUp pickUp_)
{
	stats.Add(pickUp_.key, pickUp_.val);
}

int UCarPickupComponent::RetrieveStats(FString key_)
{
	return *stats.Find(key_);
}

