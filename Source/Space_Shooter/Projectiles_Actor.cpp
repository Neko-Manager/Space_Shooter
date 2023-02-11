// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles_Actor.h"
#include "Alien_Actor.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectiles_Actor::AProjectiles_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if(OtherActor->IsA<AAlien_Actor>())
	{
		Cast<AAlien_Actor>(OtherActor)->Destroy();
		DespawnProjectile();
	}

}

void AProjectiles_Actor::DespawnProjectile()
{
	//Makes the bullet invisible due to load-lag. While this is true, the actor should also not be able to collide.
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

