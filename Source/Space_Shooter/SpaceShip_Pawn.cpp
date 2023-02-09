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
	SpringArm->TargetArmLength = 200.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true; //Gives tha camera physics when a collision or physical law is implemented.
	SpringArm->CameraLagSpeed = 0.f;

	//Initializing the camera.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	////////////////////////////////////////////////////////////////////////////////////
	//Setting default values for variables.
	MaxAmmo = 10;
	MovementSpeed =  1000.f;
	HealthPoints = 5;


	AutoPossessPlayer = EAutoReceiveInput::Player0;
}   


// Called when the game starts or when spawned
void ASpaceShip_Pawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

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

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASpaceShip_Pawn::Movement);
	}

}

void ASpaceShip_Pawn::Movement(const FInputActionValue& Value)
{
	const FVector3d VectorMove = Value.Get<FVector3d>();

	const FVector3d Up_Down = GetActorUpVector();
	const FVector3d Forward_Backward = GetActorForwardVector();
	const FVector3d Right_Left = GetActorRightVector();

	AddMovementInput(Up_Down, VectorMove.Z);
	AddMovementInput(Forward_Backward, VectorMove.Y);
	AddMovementInput(Right_Left, VectorMove.X);

}

