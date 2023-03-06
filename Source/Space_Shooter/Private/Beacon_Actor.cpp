// Fill out your copyright notice in the Description page of Project Settings.

//Our classes
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
#include "Components/CapsuleComponent.h"
#include "Space_Shooter/Alien_Actor.h"

// Sets default values
ABeacon_Actor::ABeacon_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colision_3 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	SetRootComponent(Colision_3);
	Colision_3->InitCapsuleSize(150,300);
	Colision_3->OnComponentBeginOverlap.AddDynamic(this, &ABeacon_Actor::OnOverlap);


	Beacon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beacon"));
	Beacon->SetupAttachment(Colision_3);

	//Overides Basic mesh and selects a model from the file system
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Model3D(TEXT("/Script/CoreUObject.Class'/Script/Space_Shooter.Beacon_Actor'"));

	if (Model3D.Succeeded()) {
		Beacon->SetStaticMesh(Model3D.Object);
	}

	//Variables
	BeaconHealth = 100;
}

// Called when the game starts or when spawned
void ABeacon_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeacon_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeacon_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AAlien_Actor>())
	{
		BeaconHealth--;
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, "Beacon minus 1");
	}

	/*else if(BeaconHealth == 0)
	{
		
	}*/
}

