// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Actor.h"
#include "Components/BoxComponent.h"
//#include "SpaceShip_Pawn.h"

// Sets default values
ABoss_Actor::ABoss_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(10, 50, 50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABoss_Actor::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, .1f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50));

	MovementSpeed = 350;
	RotationSpeed = 1.f;
	XKillPosition = -100.f;
}

// Called when the game starts or when spawned
void ABoss_Actor::BeginPlay()
{
	Super::BeginPlay();
	

	RotationSpeed = FMath::RandRange(0.5f, 1.5f);
	MovementSpeed += FMath::RandRange(0, 250);
}

// Called every frame
void ABoss_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move
	FVector NewLocation = GetActorLocation();
	NewLocation += FVector(-1, 0, 0) * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	//rotate
	SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));


	//kill
	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}

}

void ABoss_Actor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherActor->IsA<ASpaceShip_Pawn>())
	{
		Cast<ASpaceShip_Pawn>(OtherActor)->HitByTarget();
		DestroyTarget();
	}*/
}

void ABoss_Actor::DestroyTarget()
{

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();

}


