// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss_Actor.generated.h"


//decleriations
class UBoxComponent;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS()
class SPACE_SHOOTER_API ABoss_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss_Actor();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Collider {
		nullptr
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DestroyTarget();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//Public Variables
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float XKillPosition;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
