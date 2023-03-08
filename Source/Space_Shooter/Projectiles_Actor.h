// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectiles_Actor.generated.h"

UCLASS()
class SPACE_SHOOTER_API AProjectiles_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectiles_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Projectile components.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Component")
		class USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Component")
		UStaticMeshComponent* Projectile;

	////////////////////////////////////////////////////////////////////////////////////
	///Collision control.
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	////////////////////////////////////////////////////////////////////////////////////
	///Projectile functions.
	UFUNCTION(BlueprintCallable)
		void DespawnProjectile();


	////////////////////////////////////////////////////////////////////////////////////
	//Projectile variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile variable")
	    int ProjectileDespawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile variable")
		float ProjectileSpeed;



	////////////////////////////////////////////////////////////////////////////////////
private:
	//Private variables.
	float ProjectileTime;

};
