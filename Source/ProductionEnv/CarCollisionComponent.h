// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Components/SphereComponent.h"

#include "Engine.h"

#include "Engine/TriggerBox.h"

#include "CarCollisionComponent.generated.h"





UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PRODUCTIONENV_API UCarCollisionComponent : public UActorComponent

{

	GENERATED_BODY()



public:

	// Sets default values for this component's properties

	UCarCollisionComponent();



protected:

	// Called when the game starts

	virtual void BeginPlay() override;



public:

	// Called every frame

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	UPROPERTY(EditAnywhere, Category = CarCollision)

		USphereComponent* Collider;



	//UPROPERTY(EditAnywhere, Category = CarCollision)

	//	CarPickupComponent* Pickup;



	UFUNCTION(BlueprintCallable, Category = "CarCollision")

		void OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	UPROPERTY(EditAnywhere)

		class AActor* Car;



	UPROPERTY(EditAnywhere)

		class AActor* Pickup;

};
