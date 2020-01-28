// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "Input.generated.h"

UCLASS()
class PRODUCTIONENV_API AInput : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInput();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(float axis);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float axis);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
