// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Components/AudioComponent.h"
#include "SpaceShip_Pawn.generated.h"

//Calling Projectiles class.
class AProjectiles_Actor;
class USoundCue;

UCLASS()
class SPACE_SHOOTER_API ASpaceShip_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ------------- Verriables --------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		float RelativeDistanceForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		float RelativeDistanceSide;

	//Collision health variable. Must be accessed in Alien to subtract health.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int ShipHealth;

	// ------------- Components --------------

	//Main collection for SpaceShip mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		UStaticMeshComponent* Space_Ship;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		class USpringArmComponent* SpringArm;

	
	//Subclasses (Class of another class)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship SubClass")
		TSubclassOf<AProjectiles_Actor> Projectiles_BP;

		//Audio Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundCue* ReloadSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundCue* ShootingSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundCue* AmmoEmptySoundCue;

	//Innput Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem")
		class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Move")
		class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Look")
		class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Shoot")
		class UInputAction* IA_Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Reload")
		class UInputAction* IA_Reload;

	// ------------- Functions --------------

	//Movement and vision to declare what will happen if the Triggered InputAction is met.
	UFUNCTION(BlueprintCallable, Category = "Spaceship Movement")
		void Movement(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Spaceship Look")
		void Look(const FInputActionValue& Value);


private:
	
	// ------------- Private Verriables --------------

	UAudioComponent* ShootAudioComponent;

	UAudioComponent* ReloadAudioComponent;

	UAudioComponent* EmptyShotAudioComponent;


	// ------------- Private Functions --------------

	//Private functions for variable management.
	UFUNCTION(BlueprintCallable, Category = "Spaceship Look")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Spaceship Reload")
	void Reload();





};
