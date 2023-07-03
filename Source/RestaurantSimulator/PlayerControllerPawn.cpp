// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerPawn.h"

// Sets default values
APlayerControllerPawn::APlayerControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	newRotationSet = false;
	takeAway = true;
	CountFood = 0;
}

// Called when the game starts or when spawned
void APlayerControllerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	StartRotation = GetActorRotation();

	if(newRotationSet)
	{
		NewRotation = FMath::Lerp(StartRotation, TargetRotation,  0.2f);
		SetActorRotation(NewRotation);
		
		if(GetActorRotation().Yaw == TargetRotation.Yaw)
		{
			newRotationSet = false;
		}
	}
	
	if(CountFood >= 1)
	{
		takeAway = false;
	}
	else
	{
		takeAway = true;
	}
	
}

// Called to bind functionality to input
void APlayerControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerControllerPawn::CameraInput(float rotation)
{
	if(rotation != 0)
	{
		if(rotation < 6.0f && rotation >= 2.0f)
		{
			targetRotationZ = -90;
			TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
			newRotationSet = true;	
		}
	
		if(rotation >= 6.0f)
		{
			targetRotationZ = 90;
			TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
			newRotationSet = true;	
		}	
	}
}

