// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles_Actor.h"

// Sets default values
AProjectiles_Actor::AProjectiles_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

