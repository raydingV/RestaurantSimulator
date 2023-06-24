// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	CounterNPC = 0;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CountDownTimer -= DeltaTime * 300;

	if(CounterNPC >= 2)
	{
		CountDownTimer = 1000.0f;
	}
	
	if (NpcSpawn != nullptr && CountDownTimer <= 0)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(NpcSpawn, GetActorLocation() , GetActorRotation(), SpawnParams);
		CountDownTimer = 1000.0f;
		CounterNPC++;
	}  
}

