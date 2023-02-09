// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_Actor.h"

// Sets default values
AAlien_Actor::AAlien_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

