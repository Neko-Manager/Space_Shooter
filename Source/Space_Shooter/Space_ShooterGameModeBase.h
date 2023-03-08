#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Alien_Actor.h"
#include "Space_ShooterGameModeBase.generated.h"

//Forward decleared Alien Actor
class AAlien_Actor;

UCLASS()
class SPACE_SHOOTER_API ASpace_ShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpace_ShooterGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ------------- Verriables --------------

	// -------- X Axis -------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MaxX;

	// -------- Y Axis -------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MinY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MaxY;

	// -------- Z Axis -------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MinZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1-SpawnPositions")
		float MaxZ;

	// Game constants
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		int CurrentWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		int MaxWaves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		int LeftToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		int WaveSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		int WaveSpawnFrequency;

	//Sets Alien as blueprint value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2-WaveConsts")
		TSubclassOf<AAlien_Actor> AAlien_Actor_BP;

	// ------------- Private Verriables --------------

private:
	int AliensToSpawn;
	float clock;
	bool GameWon;

	// ------------- Private Functions --------------

	void ChangeWave(int wave);

};

