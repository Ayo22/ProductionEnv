// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"

APlayerCar::APlayerCar() : boomCamera(nullptr), followCamera(nullptr), carMoveComponent(nullptr), root(nullptr), mesh(nullptr) {
	bReplicates = true;
	bReplicateMovement = true;
	//Create the components and attach them
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = root;

	boomCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom Camera"));
	boomCamera->SetupAttachment(root);

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	followCamera->SetupAttachment(boomCamera);

	carMoveComponent = CreateDefaultSubobject<UCarMoveComponent>(TEXT("Car Movement Component"));
	carMoveComponent->SetUpdatedComponent(root);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
	
}

void APlayerCar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	//All movement is handled by the CarMoveComponent
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", carMoveComponent, &UCarMoveComponent::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", carMoveComponent, &UCarMoveComponent::MoveVertical);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, carMoveComponent, &UCarMoveComponent::BoostPressed);
	PlayerInputComponent->BindAction("Boost", IE_Released, carMoveComponent, &UCarMoveComponent::BoostReleased);
	PlayerInputComponent->BindAction("Drift", IE_Pressed, carMoveComponent, &UCarMoveComponent::DriftPressed);
	PlayerInputComponent->BindAction("Drift", IE_Released, carMoveComponent, &UCarMoveComponent::DriftReleased);
}


void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCar::SetPlayer_Implementation(EAutoReceiveInput::Type t)
{
	if (Controller == NULL)
{
		type = t;
		APlayerCar::AutoPossessPlayer = type;
		UE_LOG(LogTemp, Warning, TEXT("Assigned player to possess"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Assigned"));
	}

}

bool APlayerCar::SetPlayer_Validate(EAutoReceiveInput::Type t)
{
	return true;
}
