// Copyright Epic Games, Inc. All Rights Reserved.


#include "Space_ShooterGameModeBase.h"
#include "Alien_Actor.h"
#include "Math/RandomStream.h"

ASpace_ShooterGameModeBase::ASpace_ShooterGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ------------- Initialization --------------
	
	// Activate Constants
	WaveSize = 10;
	WaveSpawnFrequency = 1;

	// -----X-------
	MinX = 1200;
	MaxX = 3600;

	// -----Y-------
	MinY = 1200;
	MaxY = 3600;

	// -----Z-------
	MinZ = 1200;
	MaxZ = 3600;

	GameWon = false;
}

void ASpace_ShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ------------- Const Set on Begin --------------

	MaxWaves = 3;
	CurrentWave = 1;
	LeftToSpawn = WaveSize * (CurrentWave);
}

void ASpace_ShooterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ------------- Wave Spawning --------------
	
	//Clock
	clock += DeltaTime;
	WaveSpawnFrequency = 1;

	if (clock > WaveSpawnFrequency && !GameWon)
	{
		//Resets Clock
		clock = 0.f;
	
		
		

		//Determen witch area the alien can spawn, randomizes each 8th of a square centred on Origo
		FVector Location;
		int Area = FMath::RandRange(1, 8);

		if (Area == 1)
			Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));
		else if (Area == 2)
			Location = FVector(FMath::RandRange(MinX, MaxX), -(FMath::RandRange(MinY, MaxY)), FMath::RandRange(MinZ, MaxZ));
		else if (Area == 3)
			Location = FVector(-(FMath::RandRange(MinX, MaxX)), FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));
		else if (Area == 4)
			Location = FVector(-(FMath::RandRange(MinX, MaxX)), -(FMath::RandRange(MinY, MaxY)), FMath::RandRange(MinZ, MaxZ));
		else if (Area == 5)
			Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), -(FMath::RandRange(MinZ, MaxZ)));
		else if (Area == 6)
			Location = FVector(FMath::RandRange(MinX, MaxX), -(FMath::RandRange(MinY, MaxY)), -(FMath::RandRange(MinZ, MaxZ)));
		else if (Area == 7)
			Location = FVector(-(FMath::RandRange(MinX, MaxX)), FMath::RandRange(MinY, MaxY), -(FMath::RandRange(MinZ, MaxZ)));
		else if (Area == 8)
			Location = FVector(-(FMath::RandRange(MinX, MaxX)), -(FMath::RandRange(MinY, MaxY)), -(FMath::RandRange(MinZ, MaxZ)));

		//Spawns actor with the given location
			GetWorld()->SpawnActor<AActor>(AAlien_Actor_BP, Location, FRotator::ZeroRotator);

		//Decreases the amount of aliens to spawn before new wave
		LeftToSpawn--;

		//Determains if there are no more aliens left to spawn for the wave it increases the wave count
		if (LeftToSpawn <= 0)
		{
			ChangeWave(MaxWaves);
			//Increases wave counter and decreases spawnfrequency for a heigher difficulty and resets the amount of aliens to spawn for the new wave
			CurrentWave++;
			WaveSpawnFrequency--;
			LeftToSpawn = WaveSize * CurrentWave;
		}
	}
}

void ASpace_ShooterGameModeBase::ChangeWave(int wave)
{
	//Sets gamewon to true if current wave = max wave of 3.
	if (CurrentWave >= wave)
	{
		// Wins Game
		GameWon = true;
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, "Game Won");
		return;
	}
}
