// Fill out your copyright notice in the Description page of Project Settings.


#include "CarAbilityComponent.h"

// Sets default values for this component's properties
UCarAbilityComponent::UCarAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ability = nullptr;

	// ...
}


// Called when the game starts
void UCarAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCarAbilityComponent::AbilityPickUp(AAbility* ab_)
{
	ability = ab_;
}



