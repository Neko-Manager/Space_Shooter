// Copyright Epic Games, Inc. All Rights Reserved.


#include "Space_ShooterGameModeBase.h"
#include "Alien_Actor.h"
#include "Math/RandomStream.h"

ASpace_ShooterGameModeBase::ASpace_ShooterGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Activate Constants
	WaveSize = 10;

	WaveSpawnFrequency = 1;

	MinX = 200;
	MaxX = 400;

	MinY = 200;
	MaxY = 400;
	
	MinZ = 100;
	MaxZ = 400;

	GameWon = false;

}

void ASpace_ShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 1;
	AliensToSpawn = WaveSize * (CurrentWave);
}

void ASpace_ShooterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	clock += DeltaTime;

	if (clock > 5) {

		FVector Location1 = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));

		GetWorld()->SpawnActor<AActor>(AAlien_Actor_BP, Location1, FRotator::ZeroRotator);
		clock = 0;
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Emerald, "Spawn");
	}

}

void ASpace_ShooterGameModeBase::ChangeWave(int wave)
{
	if (WaveSize < wave)
	{
		// Wins Game
		GameWon = true;
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, "Game Won");
		return;
	}
}
