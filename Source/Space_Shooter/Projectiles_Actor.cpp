// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles_Actor.h"
#include "Alien_Actor.h"
#include "Beacon_Actor.h"
#include "SpaceShip_Pawn.h"
#include "Components/SphereComponent.h"


// Sets default values
AProjectiles_Actor::AProjectiles_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ------------- Initializing and activating all class meshes and variables --------------
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collission Component"));
	SetRootComponent(Collision);
	Collision->InitSphereRadius(10.f);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectiles_Actor::OnOverlap);

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Component"));
	Projectile->SetupAttachment(Collision);

	////////////////////////////////////////////////////////////////////////////////////
	//Initializing default values for variables.
	ProjectileDespawnTime = 10.f;
	ProjectileSpeed = 5000.f;
	score = 0;

}

// Called when the game starts or when spawned
void AProjectiles_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectiles_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ------------- Updating actorlocation --------------
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * ProjectileSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	ProjectileTime += DeltaTime;
	if(ProjectileTime > ProjectileDespawnTime)
	{
		DespawnProjectile();
	}
}

void AProjectiles_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ------------- Collision between Projectile and other classes --------------
	if(OtherActor->IsA<AAlien_Actor>())
	{
		//Cast<ASpaceShip_Pawn>(OtherActor)->score += 10;
		Cast<AAlien_Actor>(OtherActor)->Destroy();
		DespawnProjectile();
		score++;
		/*GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, "Score+10" + score);*/
	}

	else if(OtherActor->IsA<ABeacon_Actor>())
	{
		DespawnProjectile();
	}

}

void AProjectiles_Actor::DespawnProjectile()
{
	// ------------- Despawn projectile --------------
	//Makes the bullet invisible due to load-lag. While this is true, the actor should also not be able to collide.
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

