// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Beacon_Actor.generated.h"

UCLASS()
class SPACE_SHOOTER_API ABeacon_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeacon_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Main collection for Beacon mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		class UCapsuleComponent* Colision_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		UStaticMeshComponent* Beacon;

	////////////////////////////////////////////////////////////////////////////////////
	//Collision control.
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	////////////////////////////////////////////////////////////////////////////////////
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int BeaconHealth;
};
