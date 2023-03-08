// Fill out your copyright notice in the Description page of Project Settings.

// ------------- Includes --------------

//Our classes
#include "SpaceShip_Pawn.h"
#include "Projectiles_Actor.h"
#include "Alien_Actor.h"

//Audio


//Components
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/AudioComponent.h"


//Other
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"

//Inputs
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

//Initializing Sound Cue and component
USoundCue* ShootAudioCue;
UAudioComponent* ShootAudioComponent;

// Sets default values
ASpaceShip_Pawn::ASpaceShip_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ------------- Initializations --------------

	//Initializing the Space Ship
	Space_Ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Space ship"));
	SetRootComponent(Space_Ship);

	//Initializing the spring arm.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Space_Ship);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeLocation(FVector3d(0.f, 0.f, 50.f));
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true; //Gives tha camera physics when a collision or physical law is implemented.
	SpringArm->CameraLagSpeed = 1.f;

	//Initializing the camera.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//Overides Basic mesh and selects a model from the file system
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("StaticMesh'/Game/Assets/Models/Mesh/PlayerShip'"));


	if (Model3D.Succeeded()) {
		Space_Ship->SetStaticMesh(Model3D.Object);
	}

	//Setting default values for variables.
	MaxAmmo = 20;
	Ammo = 20;
	MovementSpeed =  1000.f;
	ShipHealth = 5;
	RelativeDistanceForward = 100.f,
	RelativeDistanceSide = 100.f;
	Score = 0;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//---------------- Audio ----------------- 

	//Loads soundque object
	static ConstructorHelpers::FObjectFinder<USoundCue> ShootSoundCueObject(TEXT("/Script/Engine.SoundCue'/Game/Audio/SoundCues/Shoot_SQ.Shoot_SQ'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ReloadSoundCueObject(TEXT("/Script/Engine.SoundCue'/Game/Audio/SoundCues/Reload_AQ.Reload_AQ'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AmmoEmptySoundCueObject(TEXT("/Script/Engine.SoundCue'/Game/Audio/SoundCues/AmmoEmptyShoot_AQ.AmmoEmptyShoot_AQ'"));

	//Checks if loading worked	
	if (ShootSoundCueObject.Succeeded()) {
		ShootingSoundCue = ShootSoundCueObject.Object;
		//initialize audio component
		ShootAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootAudioComponent"));
		//Attatch to root component
		ShootAudioComponent->SetupAttachment(RootComponent);
		}

	if (ReloadSoundCueObject.Succeeded()) {
		ReloadSoundCue = ReloadSoundCueObject.Object;
		ReloadAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadAudioComponent"));
		ReloadAudioComponent->SetupAttachment(RootComponent);
	}

	if (AmmoEmptySoundCueObject.Succeeded()) {
		AmmoEmptySoundCue = AmmoEmptySoundCueObject.Object;
		EmptyShotAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EmptyShotAudioComponent"));
		EmptyShotAudioComponent->SetupAttachment(RootComponent);
	}
}   


// Called when the game starts or when spawned
void ASpaceShip_Pawn::BeginPlay()
{
	Super::BeginPlay();

	// ------------- Begin Play Controller Setup --------------

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

	// ------------- Audio Setup --------------

	//Attatch sound cue to audio component
	if (ShootAudioComponent && ShootingSoundCue)
		ShootAudioComponent->SetSound(ShootingSoundCue);

	if (ReloadAudioComponent && ReloadSoundCue)
		ReloadAudioComponent->SetSound(ReloadSoundCue);

	if (EmptyShotAudioComponent && AmmoEmptySoundCue)
		EmptyShotAudioComponent->SetSound(AmmoEmptySoundCue);

}

// Called every frame
void ASpaceShip_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer = DeltaTime;
	Timer += DeltaTime;
	Delay += 5;
	Reload();
}

// Called to bind functionality to input
void ASpaceShip_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ------------- Input components for Spaceship actions --------------
	//Checking if the playerInputComponent is true/ a PLayerInput or not. If yes, then we allow the action binding to succeed.
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Movement);
		EnhancedInputComponent->BindAction(IA_Look,ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Look);
		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Shoot);
		EnhancedInputComponent->BindAction(IA_Beam, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Shoot);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Reload);

	}

}

void ASpaceShip_Pawn::Movement(const FInputActionValue& Value)
{
	// ------------- Movement For player Ship --------------
	
	//Checking i the controller is not a NullPointer and a Controller.
	if (Controller && Value.IsNonZero()) 
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
	// ------------- Mouse Direction Control for player Ship --------------

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
	// ------------- Player Shooting --------------
	
	//Play Audio when Shooting
	if (ShootAudioComponent && ShootingSoundCue && Ammo >= 0)
		ShootAudioComponent->Play(0.f);

	//Checking if ammo is greater than zero.
	if(Ammo > 0)
	{
		//play Audio
		if (EmptyShotAudioComponent && AmmoEmptySoundCue)
			EmptyShotAudioComponent->Play();

		//If check is yes, then minus one ammo per trigger action to keep the information displayed correct, and removing the infinite ammo.
		Ammo--;

		//Creating floats for relative Distance; both directions.
		FVector ProjectilePos1 = GetActorLocation() + GetActorForwardVector() * RelativeDistanceForward + GetActorRightVector() * RelativeDistanceSide;
		FVector ProjectilePos2 = GetActorLocation() + GetActorForwardVector() * RelativeDistanceForward + GetActorRightVector() * -RelativeDistanceSide;

		//Need to fix relative spawn for bullets.
		GetWorld()->SpawnActor<AProjectiles_Actor>(Projectiles_BP, ProjectilePos1, GetActorRotation());
		GetWorld()->SpawnActor<AProjectiles_Actor>(Projectiles_BP, ProjectilePos2, GetActorRotation());
	}
}

void ASpaceShip_Pawn::Reload()
{
	// ------------- Player Reloading --------------

		//play Audio
	if (ReloadAudioComponent && ReloadSoundCue)
		ReloadAudioComponent->Play();

	//Reloads ammo to max ammo
	if (Delay == Timer) 
	{
		Ammo = MaxAmmo;
	}
}




