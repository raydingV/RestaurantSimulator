// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerPawn.h"

// Sets default values
APlayerControllerPawn::APlayerControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	newRotationSet = false;

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
	
}

// Called to bind functionality to input
void APlayerControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerControllerPawn::CameraInput(float rotation)
{
	// FText keyDisplay = key.GetDisplayName();
	//
	// FString keyName = keyDisplay.ToString();

	if(rotation <= 0.00f)
	{
		targetRotationZ = -90;
		TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
		UE_LOG(LogTemp, Warning, TEXT("%s"), rotation);
		newRotationSet = true;	
	}

	if(rotation >= 0.00f)
	{
		targetRotationZ = 90;
		TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
		UE_LOG(LogTemp, Warning, TEXT("%s"), rotation);
		newRotationSet = true;	
	}

	// if (keyName == TEXT("A"))
	// {
	// 	targetRotationZ = -90;
	// 	TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
	// 	UE_LOG(LogTemp, Warning, TEXT("Input"));
	// 	newRotationSet = true;
	// }
	//
	// if (keyName == TEXT("D"))
	// {
	// 	targetRotationZ = 90;
	// 	TargetRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + targetRotationZ, GetActorRotation().Roll);
	// 	UE_LOG(LogTemp, Warning, TEXT("Input"));
	// 	newRotationSet = true;
	// }
	
}

