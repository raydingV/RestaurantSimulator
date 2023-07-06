// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AIngredientActor::AIngredientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AIngredientActor::BeginPlay()
{
	Super::BeginPlay();

	PawnActor = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(PawnActor);
}

// Called every frame
void AIngredientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredientActor::AddInFood()
{
	FoodObjectActor = PawnClass->foodObject;
	FoodObjectClass = Cast<AFoodObject>(FoodObjectActor);

	if(FoodObjectActor != nullptr)
	{
		NewSpawnObject = GetWorld()->SpawnActor<AActor>(IngredientObject, GetActorLocation(), GetActorRotation(), SpawnParameters);
		NewSpawnObject->SetActorScale3D(FVector3d(ScaleSpawn, ScaleSpawn, ScaleSpawn));
		IngredientClass = Cast<AIngredientObject>(NewSpawnObject);
		IngredientClass->Mesh->SetStaticMesh(SpawnMesh);
		FoodObjectClass->IngredientAdderFunction(NewSpawnObject, NewSpawnLocation);
		NewSpawnObject->SetActorRotation(NewSpawnRotator);
	}
}


