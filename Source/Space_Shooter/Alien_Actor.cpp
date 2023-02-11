// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_Actor.h"

#include "Components/BoxComponent.h"

// Sets default values
AAlien_Actor::AAlien_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colision_2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Collison_2 component"));
	SetRootComponent(Colision_2);

	Alien = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Alien Component"));

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

}

void AAlien_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

