// Fill out your copyright notice in the Description page of Project Settings.


#include "CarMoveComponent.h"

// Sets default values for this component's properties
UCarMoveComponent::UCarMoveComponent() :speed(0.0f), maxSpeed(20.0f), acceleration(4.0f), friction(0.0f), frictionMax(1.5f), torque(0.0f), hAccel(0.0f), vAccel(0.0f), currentVelocity(FVector::ZeroVector) {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
	// ...

}

void UCarMoveComponent::UpdateCarDynamics_Implementation() {

	if (FMath::Abs(vAccel) > 0.0f) //Accelerating
	{
		if (friction < frictionMax) {
			friction += 0.03f;
		}

		if (vAccel > 0.0f) {
			if (currentVelocity.Y < maxSpeed)
				currentVelocity.Y = currentVelocity.Y + vAccel * (GetWorld()->GetDeltaSeconds()) - friction * (GetWorld()->GetDeltaSeconds());
		} else {
			if (currentVelocity.Y > -maxSpeed * 0.5f)
				currentVelocity.Y = currentVelocity.Y + vAccel * (GetWorld()->GetDeltaSeconds()) + friction * (GetWorld()->GetDeltaSeconds());

		}
	} else //If the player is not pressing w or s, start deaccelerating
	{
		if (FMath::Abs(currentVelocity.Y) < 0.3f) //If we're near zero, just stop
		{
			currentVelocity.Y = 0.0f;
			friction = 0.0f;
		} else if (currentVelocity.Y > 0.0f) // Otherwise deaccelerate if you're moving forward...
			currentVelocity.Y = currentVelocity.Y - acceleration * (GetWorld()->GetDeltaSeconds());
		else //...or if you're moving backwards
			currentVelocity.Y = currentVelocity.Y + acceleration * (GetWorld()->GetDeltaSeconds());
	}

	if (FMath::Abs(hAccel) > 0.0f && FMath::Abs(vAccel) > 0.0f && FMath::Abs(currentVelocity.Y) > 2.0f) //Only move right and left if you're moving forward
	{
		currentVelocity.X = currentVelocity.X + hAccel * (GetWorld()->GetDeltaSeconds());
	} else {
		if (FMath::Abs(currentVelocity.X) < 0.3f) //If less than zero, just reset.
			currentVelocity.X = 0.0f;
		else if (currentVelocity.X > 0.0f) //Choose how to deaccelerate
			currentVelocity.X = currentVelocity.X - acceleration * (GetWorld()->GetDeltaSeconds());
		else
			currentVelocity.X = currentVelocity.X + acceleration * (GetWorld()->GetDeltaSeconds());
	}

	UE_LOG(LogTemp, Warning, TEXT("Velocity.x =  %f"), currentVelocity.X);
	UE_LOG(LogTemp, Warning, TEXT("Velocity.y =  %f"), currentVelocity.Y);
	//Velocity.Y = currentVelocity.Y*UpdatedComponent->GetForwardVector().X; //Update component's velocity
	//Velocity.X = currentVelocity.X*UpdatedComponent->GetRightVector().Y;
	Velocity = UpdatedComponent->GetComponentRotation().RotateVector(currentVelocity); //Rotate velocity by the components rotation
	MoveUpdatedComponent(Velocity, UpdatedComponent->GetComponentRotation(), false); //Move the RootComponent in the rotation of the RootComponent
	UpdateComponentVelocity(); //Push the velocity update
}
bool UCarMoveComponent::UpdateCarDynamics_Validate() { return true; }

void UCarMoveComponent::Boost() { }

void UCarMoveComponent::MoveHorizontal_Implementation(float hAxis_) {
	UE_LOG(LogTemp, Warning, TEXT("Horizontal %f"), hAxis_);
	hAccel = acceleration * hAxis_; //Get acceleration direction
	UpdateCarDynamics();
}

bool UCarMoveComponent::MoveHorizontal_Validate(float hAxis_) { return true; }


void UCarMoveComponent::MoveVertical_Implementation(float vAxis_) {
	UE_LOG(LogTemp, Warning, TEXT("Vertical %f"), vAxis_);
	vAccel = acceleration * vAxis_; //Get acceleartion direction
	UpdateCarDynamics();
}
bool UCarMoveComponent::MoveVertical_Validate(float vAxis_) { return true; }