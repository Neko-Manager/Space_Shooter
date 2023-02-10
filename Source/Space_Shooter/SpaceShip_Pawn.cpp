// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip_Pawn.h"
#include "Projectiles_Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Space_ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

//Inputs
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

// Sets default values
ASpaceShip_Pawn::ASpaceShip_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initializing the Space Ship.
	Space_Ship = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Space ship"));
	SetRootComponent(Space_Ship);

	//Initializing the spring arm.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Space_Ship);
	SpringArm->TargetArmLength = 250.f;
	SpringArm->SetRelativeLocation(FVector3d(0.f, 0.f, 50.f));
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true; //Gives tha camera physics when a collision or physical law is implemented.
	SpringArm->CameraLagSpeed = 0.f;

	//Initializing the camera.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	////////////////////////////////////////////////////////////////////////////////////
	//Setting default values for variables.
	MaxAmmo = 10;
	Ammo = 10;
	MovementSpeed =  1000.f;
	HealthPoints = 5;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}   


// Called when the game starts or when spawned
void ASpaceShip_Pawn::BeginPlay()
{
	Super::BeginPlay();

	//Getting the player controller with Cast.
	APlayerController* PlayerController = Cast<APlayerController>(GetController());


	//If statement to check if player 0 is playing.
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		//If the subsystem instance is true, then we point to which map and player we are.
		if(Subsystem)
		{
			Subsystem->AddMappingContext(IMC, 0);
		}

	}
}

// Called every frame
void ASpaceShip_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShip_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Checking if the playerInputComponent is true/ a PLayerInput or not. If yes, then we allow the action binding to succeed.
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Movement);
		EnhancedInputComponent->BindAction(IA_Look,ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Look);
		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Shoot);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Reload);

	}

}

void ASpaceShip_Pawn::Movement(const FInputActionValue& Value)
{
	//Checking i the controller is not a NullPointer and a Controller.
	if (Controller && (Value.IsNonZero())) 
	{
		//Creating a general const variable for the type of vector we want to recieve/work with.
		const FVector3d VectorMove = Value.Get<FVector3d>();

		//creating a new variable for each of the directions we want the movement to have access to. 
		const FVector3d Up_Down = GetActorUpVector();
		const FVector3d Forward_Backward = GetActorForwardVector();
		const FVector3d Right_Left = GetActorRightVector();

		//Adding the movement by defining what to update the received input, and where  to update it. (New vector, Old vector)
		AddMovementInput(Up_Down, VectorMove.Z);
		AddMovementInput(Forward_Backward, VectorMove.Y);
		AddMovementInput(Right_Left, VectorMove.X);
	}
}

void ASpaceShip_Pawn::Look(const FInputActionValue& Value)
{
	//Checking if the controller is received.
	if (GetController()) 
	{
		//Getting the general vector as in the MOvement function.
		const FVector2D LookAxisInput = Value.Get<FVector2D>();

		//Same principle as in Movement, but with 2 vectors.
		AddControllerYawInput(LookAxisInput.X);
		AddControllerPitchInput(LookAxisInput.Y);
	}

	
}

void ASpaceShip_Pawn::Shoot()
{
	if(Ammo > 0)
	{
		Ammo--;
		GetWorld()->SpawnActor<AProjectiles_Actor>(Projectiles_BP, GetActorLocation() + FVector(30.f, 0.f, 0.f), GetActorRotation());
	}
}

void ASpaceShip_Pawn::Reload()
{
	Ammo = MaxAmmo;
}


void ASpaceShip_Pawn::PlayerHit()
{
}

