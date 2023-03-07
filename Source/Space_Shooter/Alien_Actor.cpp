// Fill out your copyright notice in the Description page of Project Settings.

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


// Sets default values
AAlien_Actor::AAlien_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colision_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Colision_2);
	Colision_2->InitBoxExtent(FVector(150, 150, 150));
	Colision_2->OnComponentBeginOverlap.AddDynamic(this, &AAlien_Actor::OnOverlap);

	Alien = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Alien->SetupAttachment(Alien);

	//Overides Basic mesh and selects a model from the file system
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("StaticMesh'/Game/Assets/Models/Mesh/Spaceinvader'"));

	if (Model3D.Succeeded()) {
		Alien->SetStaticMesh(Model3D.Object);
	}

	MovementSpeed = 500.f;

	score = 0;

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


	// Move

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	// Score

	//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Black, "score";
		
	//Rotate
	//SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));

	//SetActorRotation(GetActorRotation() + FRotator(0, 0, 0));
	//SetActorRotation(FRotator(LookAxisInput.X));

	//Same principle as in Movement, but with 2 vectors.

	GetActorRotation();
	
}

void AAlien_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<ABeacon_Actor>() || OtherActor->IsA<ASpaceShip_Pawn>())
	{
		DestroyAlien();
	}
}

void AAlien_Actor::DestroyAlien()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();

	score += 10;
}

