// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockFood.h"

// Sets default values
AUnlockFood::AUnlockFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UnlockQue = 0;
}

// Called when the game starts or when spawned
void AUnlockFood::BeginPlay()
{
	Super::BeginPlay();
	GameManagerClass = Cast<AGameManager>(GameManager);
}

// Called every frame
void AUnlockFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnlockFood::UnlockFood()
{
	if (GameManagerClass != nullptr)
	{
		if (GameManagerClass->Money >= 300 && UnlockQue == GameManagerClass->OrderLenght)
		{
			this->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("NewFoodUnlocked!"));
			GameManagerClass->OrderLenght++;
		}
	}
}
