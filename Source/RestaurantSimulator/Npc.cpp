// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ANpc::ANpc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(Pawn);

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);

	TargetLocation = FVector3d(-700, 480, 30);
	
	if(GameManagerClass->CounterNPC >= 1)
	{
		TargetLocation = FVector3d(TargetLocation.X + 150, 480, 30);
	}

	OrderFoodTag = FMath::RandRange(0, GameManagerClass->OrderLenght);

	UE_LOG(LogTemp, Warning, TEXT("%d"), OrderFoodTag);
	
	TargetRotation = FRotator3d(0,90,0);
	SetActorRotation(TargetRotation);
}

// Called every frame
void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(GameManagerClass->CounterNPC == 1)
	{
		TargetLocation = FVector3d(-700, 480, 30);
	}

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, 0.5f);
	SetActorLocation(NewLocation);

}

void ANpc::OrderTake()
{
	if(PawnClass->takeAway == false && PawnClass->FoodTag == OrderFoodTag)
	{
		GameManagerClass->Money += 100;
		UE_LOG(LogTemp, Warning, TEXT("%d"), GameManagerClass->Money);
		PawnClass->foodObject->Destroy();
		PawnClass->CountFood--;
		GameManagerClass->CounterNPC--;
		this->Destroy();
	}
}


