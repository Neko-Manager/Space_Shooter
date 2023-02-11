// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Alien_Actor.generated.h"

UCLASS()
class SPACE_SHOOTER_API AAlien_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Main collection for Alien
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alien component")

		class UBoxComponent* Colision_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alien component")
		UStaticMeshComponent* Alien;

	////////////////////////////////////////////////////////////////////////////////////
	//Collision control.
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
