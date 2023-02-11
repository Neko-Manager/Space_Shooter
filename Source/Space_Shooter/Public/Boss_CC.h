// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Boss_CC.generated.h"

UCLASS()
class SPACE_SHOOTER_API ABoss_CC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoss_CC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
