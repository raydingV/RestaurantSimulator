// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockFood.h"

// Sets default values
AUnlockFood::AUnlockFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	DisableActorRecursive(this, false);
}

// Called when the game starts or when spawned
void AUnlockFood::BeginPlay()
{
	Super::BeginPlay();
	GameManagerClass = Cast<AGameManager>(GameManager);
	DisableActorRecursive(this, true);
}

// Called every frame
void AUnlockFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GameManagerClass != nullptr)
	{
		UnlockFood(GameManagerClass->DayCounter);
	}
}

void AUnlockFood::UnlockFood(int day)
{
	switch (day)
	{
	case 3:
		if(UnlockDay == day)
		{
			UE_LOG(LogTemp, Error, TEXT("NEW UNLCOK FODD COMING GOTCHA POKEOMONYEENENE"));
			DisableActorRecursive(this, false);
			GameManagerClass->OrderLenght++;
			UnlockDay = 0;	
		}
	break;

	case 6:
		if(UnlockDay == day)
		{
			UE_LOG(LogTemp, Error, TEXT("NEW UNLCOK FODD COMING GOTCHA POKEOMONYEENENE"));
			DisableActorRecursive(this, false);
			GameManagerClass->OrderLenght++;
			UnlockDay = 0;	
		}
		break;

	case 9:
		if(UnlockDay == day)
		{
			UE_LOG(LogTemp, Error, TEXT("NEW UNLCOK FODD COMING GOTCHA POKEOMONYEENENE"));
			DisableActorRecursive(this, false);
			GameManagerClass->OrderLenght++;
			UnlockDay = 0;	
		}
		break;
	}
}

void AUnlockFood::DisableActorRecursive(AActor* Actor, bool Hide)
{
	TArray<AActor*> AttachedActors;
	Actor->GetAttachedActors(AttachedActors);

	for (AActor* AttachedActor : AttachedActors)
	{
		DisableActorRecursive(AttachedActor, Hide);
	}

	Actor->SetActorHiddenInGame(Hide);
	Actor->SetActorEnableCollision(!Hide);
}
