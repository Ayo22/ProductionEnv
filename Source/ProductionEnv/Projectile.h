// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class PRODUCTIONENV_API AProjectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = Projectile)
		float projectileSpeed;


	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = ProjectileMovement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void ProjectileDirection(const FVector& ShootDirection);
};
