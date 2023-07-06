// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActor.h"

// Sets default values
AInteractionActor::AInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComponent;

	FoodTag = 0;

}

// Called when the game starts or when spawned
void AInteractionActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractionActor::FoodObjectCreate()
{
	FActorSpawnParameters SpawnParameters;

	if(FoodObject != nullptr)
	{
		NewFoodObject = GetWorld()->SpawnActor<AActor>(FoodObject, FVector3d(GetActorLocation().X + FoodSpawnLocation.X, GetActorLocation().Y + FoodSpawnLocation.Y, GetActorLocation().Z + FoodSpawnLocation.Z) , FoodSpawnRotation, SpawnParameters);
		FoodObjectClass = Cast<AFoodObject>(NewFoodObject);
		FoodObjectClass->FoodTag = FoodTag;
		FoodObjectClass->Mesh->SetStaticMesh(MeshFood);
	}
}

void AInteractionActor::FoodMakeAnimation()
{
	
}



