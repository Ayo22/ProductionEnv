// Fill out your copyright notice in the Description page of Project Settings.





#include "CarCollisionComponent.h"



// Sets default values for this component's properties

UCarCollisionComponent::UCarCollisionComponent()

{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features

	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;



	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("TouchSphereCollider"));

	Collider->SetSphereRadius(20.f, false);

	Collider->SetGenerateOverlapEvents(true);

	

	Collider->OnComponentBeginOverlap.AddDynamic(this, &UCarCollisionComponent::OnCollision);

}





// Called when the game starts

void UCarCollisionComponent::BeginPlay()

{

	Super::BeginPlay();



	// ...

	

}





// Called every frame

void UCarCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)

{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	// ...

}



void UCarCollisionComponent::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{

	if (Car)

	{

		if (GEngine)

		{

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("CarCollision"));

		}

		

	}



	if (Pickup)

	{

		if (GEngine)

		{

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("PickupCollision"));

		}

	}

}
