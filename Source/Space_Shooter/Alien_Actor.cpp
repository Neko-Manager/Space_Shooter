// ------------- Includes --------------

//Our classes
#include "Alien_Actor.h"
#include "SpaceShip_Pawn.h"
#include "Projectiles_Actor.h"
#include "Beacon_Actor.h"

//Components
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

//Other
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

//Inputs
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

class ABeacon_Actor;

// Sets default values
AAlien_Actor::AAlien_Actor()
{
	// ------------- Initializations --------------
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colision_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Colision_2);
	Colision_2->InitBoxExtent(FVector(150, 150, 150));
	Colision_2->OnComponentBeginOverlap.AddDynamic(this, &AAlien_Actor::OnOverlap);

	Alien = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Alien->SetupAttachment(Colision_2);

	//Overides Basic mesh and selects a model from the file system
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("StaticMesh'/Game/Assets/Models/Mesh/Spaceinvader'"));

	if (Model3D.Succeeded()) {
		Alien->SetStaticMesh(Model3D.Object);
	}

	MovementSpeed = 500.f;
}

// Called when the game starts or when spawned
void AAlien_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlien_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ------------- Move Toward Beacon --------------
	//Gets Beacon position
	FVector Origo = FVector(0.f, 0.f, 0.f);

	//Find Vector between alien and Beacon
	FVector AB = FVector(Origo.X - GetActorLocation().X, Origo.Y - GetActorLocation().Y, Origo.Z - GetActorLocation().Z);

	//Normalize Vector to a value of 1 and inverse it
	AB.Normalize();

	//Gets Current Location
	FVector NewLocation = GetActorLocation();

	//Moves current location along Vector betwen current location and Beacon
	NewLocation += AB * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AAlien_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ------------- Collision Logic --------------

	if(OtherActor->IsA<ABeacon_Actor>())
	{
		DestroyAlien();
	}
	else if(OtherActor->IsA<ASpaceShip_Pawn>())
	{
		DestroyAlien();
		Cast<ASpaceShip_Pawn>(OtherActor)->ShipHealth--;
		//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Yellow, "Spaceship health minus 1");
	}
}

void AAlien_Actor::DestroyAlien()
{
	// ------------- Destroy Alien --------------

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

