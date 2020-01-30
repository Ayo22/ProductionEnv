// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"
#include "Animation/AnimInstance.h"
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
public:
	UAnimInstance* animInstancePtr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	// movement "constants" (their not actually constant but I dont change them)
	float percision;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float max_forward_speed;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float max_backward_speed;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float linear_acceleration;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float linear_deceleration;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float linear_rollout;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float boost_multiplier;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float traction;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float max_angular_speed;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float max_angular_drift_speed;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float angular_acceleration;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float angular_deceleration;
	UPROPERTY(EditAnywhere, Category = CarPhysics) float mass;

	// movement variables
	/// this velocity is relative to the forward direction and is rotated before applying to the car
	FVector linearVelocity;
	/// this velocity is relative to the forward direction and rotates the current rotation before applying
	FVector angularVelocity;

	// input variables
	FVector2D input_moveAxis;
	bool input_boost;
	bool input_drift;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void UpdateCarDynamics(float delta);
	virtual void UpdateCarDynamics_Implementation(float delta);
	virtual bool UpdateCarDynamics_Validate(float delta);

	// input 

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void BoostPressed(); //Bound to input
	virtual void BoostPressed_Implementation();
	virtual bool BoostPressed_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void BoostReleased(); //Bound to input
	virtual void BoostReleased_Implementation();
	virtual bool BoostReleased_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void DriftPressed(); //Bound to input
	virtual void DriftPressed_Implementation();
	virtual bool DriftPressed_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void DriftReleased(); //Bound to input
	virtual void DriftReleased_Implementation();
	virtual bool DriftReleased_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void MoveHorizontal(float hAxisDir_); //Bound to input
	virtual void MoveHorizontal_Implementation(float hAxisDir_);
	virtual bool MoveHorizontal_Validate(float hAxisDir_);

	UFUNCTION(Reliable, Server, WithValidation)
		virtual void MoveVertical(float vAxisDir_); //Bound to input
	virtual void MoveVertical_Implementation(float vAxisDir_);
	virtual bool MoveVertical_Validate(float vAxisDir_);

};
