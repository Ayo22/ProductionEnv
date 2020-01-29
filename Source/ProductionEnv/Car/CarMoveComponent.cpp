// Fill out your copyright notice in the Description page of Project Settings.


#include "CarMoveComponent.h"

// Sets default values for this component's properties
UCarMoveComponent::UCarMoveComponent()
	: percision(1.0f)
	, max_forward_speed(20.0f)
	, max_backward_speed(17.0f)
	, linear_acceleration(80.0f)
	, linear_deceleration(28.0f)
	, boost_multiplier(3.0f)
	, traction(50.0f)
	, max_angular_speed(1.0f)
	, angular_acceleration(1.0f)
	, angular_deceleration(1.0f)
	, mass(2)
	, linearVelocity(FVector::ZeroVector)
	, angularVelocity(FVector::ZeroVector)
	, input_moveAxis(FVector2D::ZeroVector)
	, input_boost(false)
	, input_drift(false) {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// server stuff
	bReplicates = true;
	// ...


}

// Called when the game starts
void UCarMoveComponent::BeginPlay() {
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCarMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// update the car physics
	UpdateCarDynamics(DeltaTime);
}

bool UCarMoveComponent::UpdateCarDynamics_Validate(float delta) { return true; }
void UCarMoveComponent::UpdateCarDynamics_Implementation(float delta) {
	// get the current rotation
	FRotator rotation = UpdatedComponent->GetComponentRotation();

	// do linear movement
	if (input_moveAxis.Y != 0) {
		if (input_moveAxis.Y > 0) { // move forward
			// constants
			const float max_spd = max_forward_speed * (input_boost ? boost_multiplier : 1.0f);
			const float linear_accel = linear_acceleration * (input_boost ? boost_multiplier : 1.0f);

			if (FMath::Abs(linearVelocity.X - max_spd) < percision) linearVelocity.X = max_spd;
			else if (linearVelocity.X > max_spd)					linearVelocity.X -= linear_deceleration * delta;
			else if (linearVelocity.X < max_spd)					linearVelocity.X += linear_accel * delta;

		}
		if (input_moveAxis.Y < 0) { // move backward
			// constants
			const float max_spd = max_backward_speed * (input_boost ? boost_multiplier : 1.0f);
			const float linear_accel = linear_acceleration * (input_boost ? boost_multiplier : 1.0f);

			if (FMath::Abs(linearVelocity.X + max_spd) < percision) linearVelocity.X = -max_spd;
			else if (linearVelocity.X < -max_spd)					linearVelocity.X += linear_deceleration * delta;
			else if (linearVelocity.X > -max_spd)					linearVelocity.X -= linear_accel * delta;

		}
	}

	// do traction
	if (linearVelocity.Y == 0.0f) linearVelocity.Y = 0.0f;
	else if (linearVelocity.Y < 0.0f) linearVelocity.Y += traction * delta;
	else if (linearVelocity.Y > 0.0f) linearVelocity.Y -= traction * delta;

	// do angular movement



	// rotate the velocity accoring to rotation
	Velocity = rotation.RotateVector(linearVelocity);

	// gravity is important
	Velocity.Z -= mass * 9.18f * delta;

	// this moves the object
	MoveUpdatedComponent(Velocity, UpdatedComponent->GetComponentRotation(), false);

	// get velocity
	linearVelocity = rotation.GetInverse().RotateVector(Velocity);

	// this needs to be called at the end of an update
	UpdateComponentVelocity();
}


////////////////////////// Input //////////////////////////

bool UCarMoveComponent::BoostPressed_Validate() { return true; }
void UCarMoveComponent::BoostPressed_Implementation() {
	input_boost = true;
}

bool UCarMoveComponent::BoostReleased_Validate() { return true; }
void UCarMoveComponent::BoostReleased_Implementation() {
	input_boost = false;
}

bool UCarMoveComponent::DriftReleased_Validate() { return false; }
void UCarMoveComponent::DriftReleased_Implementation() {

}

bool UCarMoveComponent::DriftPressed_Validate() { return false; }
void UCarMoveComponent::DriftPressed_Implementation() {

}

bool UCarMoveComponent::MoveHorizontal_Validate(float hAxis_) { return true; }
void UCarMoveComponent::MoveHorizontal_Implementation(float hAxis_) {
	input_moveAxis.X = hAxis_;
}


bool UCarMoveComponent::MoveVertical_Validate(float vAxis_) { return true; }
void UCarMoveComponent::MoveVertical_Implementation(float vAxis_) {
	input_moveAxis.Y = vAxis_;
}