// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car/BaseCar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CarMoveComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCar.generated.h"

/**
 *
 */
UCLASS()
class PRODUCTIONENV_API APlayerCar : public ABaseCar 
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* boomCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* followCamera;

	UPROPERTY(EditAnywhere, Category = CarMovementComponent)
		UCarMoveComponent* carMoveComponent;

	UPROPERTY(EditAnywhere, Category = RootComponent)
		USceneComponent* root;


	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = AnimationInstance)
		UAnimInstance* wheelAnimator;

	UPROPERTY(EditAnywhere, Category = Rotator)
		FRotator wheelRotation;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Type)
		TEnumAsByte<EAutoReceiveInput::Type> type;
public:

	APlayerCar();

	UFUNCTION(Reliable, Server, WithValidation)
		void SetPlayer(EAutoReceiveInput::Type t);
	void SetPlayer_Implementation(EAutoReceiveInput::Type t);
	bool SetPlayer_Validate(EAutoReceiveInput::Type t);

};
