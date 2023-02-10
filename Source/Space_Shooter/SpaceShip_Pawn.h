// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SpaceShip_Pawn.generated.h"

//Calling Projectiles class.
class AProjectiles_Actor;

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

	//Main collection for SpaceShip mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		UMeshComponent* Space_Ship;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Mesh")
		class USpringArmComponent* SpringArm;


	////////////////////////////////////////////////////////////////////////////////////
	//Main collection for variables.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship Variables")
		int HealthPoints;


	////////////////////////////////////////////////////////////////////////////////////
	//Subclasses (Class of another class)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space ship SubClass")
		TSubclassOf<AProjectiles_Actor> Projectiles_BP;


	////////////////////////////////////////////////////////////////////////////////////
	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundBase* ShootingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Space Ship Sound")
		USoundBase* AmmoEmptySound;


	////////////////////////////////////////////////////////////////////////////////////
	//Input Controller to define InputAction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem")
		class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Move")
		class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputsystem Look")
		class UInputAction* IA_Look;


	////////////////////////////////////////////////////////////////////////////////////
	//Movement and vision to declare what will happen if the Triggered InputAction is met.
	UFUNCTION(BlueprintCallable, Category = "Spaceship Movement")
		void Movement(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Spaceship Look")
		void Look(const FInputActionValue& Value);

	////////////////////////////////////////////////////////////////////////////////////
private:
	//Private variables.


	////////////////////////////////////////////////////////////////////////////////////
private:
	//Private functions for control.

	//Private functions for variable management.
	void Shoot();
	void Reload();
	void PlayerHit();


};
