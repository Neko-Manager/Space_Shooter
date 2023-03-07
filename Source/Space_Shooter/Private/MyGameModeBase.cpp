// Fill out your copyright notice in the Description page of Project Settings.


//#include "MyGameModeBase.h"
//
//
//
//AMyGameModeBase::AMyGameModeBase()
//{
//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//
//	// Activate Constants
//	WaveSize = 10;
//
//	WaveSpawnFrequency = 1;
//
//	MinX = 1500;
//	MaxX = 2000;
//
//	MinY = -400;
//	MaxY = 400;
//
//	MinZ = 200;
//	MaxZ = 600;
//
//	GameWon = false;
//
//
//
//
//}
//
//void AMyGameModeBase::BeginPlay()
//{
//	Super::BeginPlay();
//
//	CurrentWave = 1;
//	AliensToSpawn = WaveSize*(CurrentWave - 1);
//}
//
//void AMyGameModeBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	
//	clock += DeltaTime;
//	
//	// If clock exeeds the right value, spawning of the acors will happen
//	if (clock > WaveSpawnFrequency*(CurrentWave - 1) && !GameWon)
//	{
//		//Clock resets
//		clock = 0.f;
//
//		// Sets the lo
//		FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));
//
//		//Spawns Alien Actors
//		AActor* Actor = GetWorld()->SpawnActor<AActor>(AAlien_Actor_BP, Location, FRotator::ZeroRotator);
//		AAlien_Actor* Alien_Actor = Cast<AAlien_Actor>(Actor);
//
//		//Reducing aliens that need to spawn
//		AliensToSpawn--;
//		if (AliensToSpawn <= 0)
//		{
//			ChangeWave(CurrentWave + 1);
//		}
//	}
//}
//
//void AMyGameModeBase::ChangeWave(int wave)
//{
//	if (WaveSize < wave)
//	{
//		// Wins Game
//		GameWon = true;
//		return;
//	}
//}
