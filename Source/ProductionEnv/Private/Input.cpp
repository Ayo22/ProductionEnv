// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Input.h"

// Sets default values
AInput::AInput()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f; //how far the camera is
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;

}

void AInput::MoveForward(float axis)
{
	FRotator Rotation = Controller->GetControlRotation(); //get rotation
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); //get yaw rotation

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //get forward axis 
	AddMovementInput(Direction, axis); //will pass depending on the button being pressed
}

void AInput::MoveRight(float axis)
{
	FRotator Rotation = Controller->GetControlRotation(); //get rotation
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); //get yaw rotation

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //get right axis
	AddMovementInput(Direction, axis);
}

// Called when the game starts or when spawned
void AInput::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInput::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInput::MoveRight);

}

