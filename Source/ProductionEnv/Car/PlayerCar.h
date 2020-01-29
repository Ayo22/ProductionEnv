// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car/BaseCar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CarMoveComponent.h"
#include "Components/InputComponent.h"
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
		UStaticMeshComponent* mesh;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetPlayer(int playerNum_);

	virtual void BeginPlay() override;


public:
	APlayerCar();

};
