// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_CC.h"

// Sets default values
ABoss_CC::ABoss_CC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss_CC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss_CC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss_CC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

