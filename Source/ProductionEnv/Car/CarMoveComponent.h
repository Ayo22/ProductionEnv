// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"
#include "CarMoveComponent.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONENV_API UCarMoveComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCarMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float speed;
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float maxSpeed;
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float acceleration;
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float friction;
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float frictionMax;
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		float torque;


	float hAccel;
	float vAccel;



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void UpdateCarDynamics(); //Bound to input
	virtual void UpdateCarDynamics_Implementation();
	virtual bool UpdateCarDynamics_Validate();

	UFUNCTION()
		virtual void Boost(); //Bound to input

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void MoveHorizontal(float hAxisDir_);
	virtual void MoveHorizontal_Implementation(float hAxisDir_);
	virtual bool MoveHorizontal_Validate(float hAxisDir_);
	UFUNCTION(Reliable, Server, WithValidation)
		virtual void MoveVertical(float vAxisDir_);
	virtual void MoveVertical_Implementation(float vAxisDir_);
	virtual bool MoveVertical_Validate(float vAxisDir_);
	UPROPERTY(EditAnywhere, Category = CarPhysics)
		FVector currentVelocity;
};
