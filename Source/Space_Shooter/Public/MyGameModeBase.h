// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/GameModeBase.h"
////#include "Alien_Actor.h"
//#include "MyGameModeBase.generated.h"
//
//class AAlien_Actor;
//
//UCLASS()
//class SPACE_SHOOTER_API AMyGameModeBase : public AGameModeBase
//{
//	GENERATED_BODY()
//	
//public:
//	AMyGameModeBase();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

//	//Location constants
//	// -------- X Axis -------
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MinX;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MaxX;
//
//	// -------- Y Axis -------
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MinY;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MaxY;
//
//	// -------- Z Axis -------
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MinZ;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	float MaxZ;
//
//	//Game constants
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	int CurrentWave;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	int MaxWaves;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	int WaveSize;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	int WaveSpawnFrequency;
//
//	//Sets Alien as blueprint value
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
//	TSubclassOf<AAlien_Actor> AAlien_Actor_BP;
//
//private:
//	int AliensToSpawn;
//	float clock;
//	bool GameWon;
//
//	void ChangeWave(int wave);
//
//};
