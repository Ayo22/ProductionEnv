// Fill out your copyright notice in the Description page of Project Settings.


#include "CarMoveComponent.h"

// Sets default values for this component's properties
UCarMoveComponent::UCarMoveComponent()
	: percision(1.0f)
	, max_forward_speed(50.0f)
	, max_backward_speed(17.0f)
	, linear_acceleration(70.0f)
	, linear_deceleration(48.0f)
	, linear_rollout(25.0f)
	, boost_multiplier(3.0f)
	, traction(50.0f)
	, max_angular_speed(1.0f)
	, max_angular_drift_speed(2.0f)
	, angular_acceleration(10.0f)
	, angular_deceleration(20.0f)
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
	// constant
	const float perc = percision * delta;

	// do linear movement
	if (input_moveAxis.Y != 0) {
		const float scalar = FMath::Abs(linearVelocity.X);

		if (input_moveAxis.Y > 0) { // move forward
			// constants
			const float max_spd = max_forward_speed * (input_boost ? boost_multiplier : 1.0f);
			const float linear_accel = linear_acceleration * (input_boost ? boost_multiplier : 1.0f);

			if (FMath::IsNearlyEqual(linearVelocity.X, max_spd, perc))		linearVelocity.X = max_spd;
			else if (linearVelocity.X > max_spd)							linearVelocity.X -= linear_deceleration * delta;
			else if (linearVelocity.X < max_spd)							linearVelocity.X += linear_accel * delta;

		}
		if (input_moveAxis.Y < 0) { // move backward
			// constants
			const float max_spd = max_backward_speed * (input_boost ? boost_multiplier : 1.0f);
			const float linear_accel = linear_acceleration * (input_boost ? boost_multiplier : 1.0f);

			if (FMath::IsNearlyEqual(linearVelocity.X, -max_spd, perc))		linearVelocity.X = -max_spd;
			else if (linearVelocity.X < -max_spd)							linearVelocity.X += linear_deceleration * delta;
			else if (linearVelocity.X > -max_spd)							linearVelocity.X -= linear_accel * delta;

		}
	} else {
		// this is for rolling without holding forward/backward

		if (FMath::IsNearlyZero(linearVelocity.X, perc))		linearVelocity.X = 0.0f;
		else if (linearVelocity.X > 0.0f)						linearVelocity.X -= linear_rollout * delta;
		else if (linearVelocity.X < 0.0f)						linearVelocity.X += linear_rollout * delta;
	}


	// do traction
	if (FMath::IsNearlyZero(linearVelocity.Y, perc))		linearVelocity.Y = 0.0f;
	else if (linearVelocity.Y < 0.0f)				linearVelocity.Y += traction * delta;
	else if (linearVelocity.Y > 0.0f)				linearVelocity.Y -= traction * delta;


	// do angular movement
	if (input_moveAxis.X != 0 && linearVelocity.X > 0.0f) {
		// constants
		const float scalar = FMath::Abs(linearVelocity.X / max_forward_speed);
		const float ang_speed = scalar * max_angular_speed;
		const float ang_accel = scalar * angular_acceleration;

		if (input_moveAxis.X < 0) {

			if (FMath::IsNearlyEqual(angularVelocity.Z, -ang_speed, perc * 10.0f))		angularVelocity.Z = -ang_speed;
			else if (angularVelocity.Z < -ang_speed)							angularVelocity.Z += ang_accel * delta;
			else if (angularVelocity.Z > -ang_speed)							angularVelocity.Z -= ang_accel * delta;
		}
		if (input_moveAxis.X > 0) {

			if (FMath::IsNearlyEqual(angularVelocity.Z, ang_speed, perc * 10.0f))		angularVelocity.Z = ang_speed;
			else if (angularVelocity.Z > ang_speed)								angularVelocity.Z -= ang_accel * delta;
			else if (angularVelocity.Z < ang_speed)								angularVelocity.Z += ang_accel * delta;
		}

	} else if (input_moveAxis.X != 0 && linearVelocity.X < 0.0f) {
		// constants
		const float scalar = FMath::Abs(linearVelocity.X / max_forward_speed);
		const float ang_speed = scalar * max_angular_speed;
		const float ang_accel = scalar * angular_acceleration;

		if (input_moveAxis.X < 0) {

			if (FMath::IsNearlyEqual(angularVelocity.Z, ang_speed, perc * 10.0f))		angularVelocity.Z = ang_speed;
			else if (angularVelocity.Z > ang_speed)								angularVelocity.Z -= ang_accel * delta;
			else if (angularVelocity.Z < ang_speed)								angularVelocity.Z += ang_accel * delta;
		}
		if (input_moveAxis.X > 0) {

			if (FMath::IsNearlyEqual(angularVelocity.Z, -ang_speed, perc * 10.0f))		angularVelocity.Z = -ang_speed;
			else if (angularVelocity.Z < -ang_speed)							angularVelocity.Z += ang_accel * delta;
			else if (angularVelocity.Z > -ang_speed)							angularVelocity.Z -= ang_accel * delta;
		}

	} else {

		//UE_LOG(LogTemp, Warning, TEXT("angular velocity = %f, perc = %f"), angularVelocity.Z, perc);

		if (FMath::IsNearlyZero(angularVelocity.Z, perc * 10.0f))		angularVelocity.Z = 0.0f;
		else if (angularVelocity.Z < 0.0f)						angularVelocity.Z += angular_deceleration * delta;
		else if (angularVelocity.Z > 0.0f)						angularVelocity.Z -= angular_deceleration * delta;
	}


	// get the current rotation
	FRotator rotation = UpdatedComponent->GetComponentRotation();

	// rotate angular velocity to be in word space
	// this doesnt work yet
	///FVector UP = UpdatedComponent->GetUpVector();
	///FVector worldAngVel = .RotateVector(angularVelocity);

	// calculate new rotation
	FRotator newRotation = rotation + FRotator::MakeFromEuler(angularVelocity);

	// rotate the velocity accoring to rotation
	Velocity = newRotation.RotateVector(linearVelocity);

	// gravity is important
	///Velocity.Z -= mass * 9.18f * delta;

	// this moves the object
	MoveUpdatedComponent(Velocity, newRotation, false);

	// this needs to be called at the end of an update
	UpdateComponentVelocity();

	// get velocity
	linearVelocity = newRotation.GetInverse().RotateVector(Velocity);
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