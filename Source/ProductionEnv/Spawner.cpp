// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner() :location(NULL),rotator(NULL),index(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	location = GetActorLocation();
	rotator = GetActorRotation();
	ADeathMatchGameMode* dm = Cast<ADeathMatchGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (dm) {
		dm->SetSpawnPoint(this, index);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("DM Game mode returned nullprt"));
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

