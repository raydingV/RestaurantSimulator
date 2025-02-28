// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientActor.h"

#include "DynamicMesh/MeshTransforms.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIngredientActor::AIngredientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	InputEnable = true;
	AnimationFinish = false;
	Cost = 0;
	Profit = 0;
	
}

// Called when the game starts or when spawned
void AIngredientActor::BeginPlay()
{
	Super::BeginPlay();

	PawnActor = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(PawnActor);

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);
}

// Called every frame
void AIngredientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HaveAnimation == true && InputEnable == false)
	{
		PawnClass->InputEnable = InputEnable;

		if(IsDonerAnim == true)
		{
			PawnClass->InputDisable(-90);
		}
		else
		{
			PawnClass->InputDisable(90);
		}
	}

	if(AnimationFinish == true)
	{
		AnimationFinish = false;
		InputEnable = true;
		PawnClass->InputEnable = InputEnable;
	}
	
	takeAway = PawnClass->takeAway;
	
}

void AIngredientActor::AddInFood()
{
	if(GameManagerClass->ControlIngredients[thisFoodTag] == false)
	{
		FoodObjectActor = PawnClass->foodObject;
		GameManagerClass->ControlIngredients[thisFoodTag] = true;

		if(FoodObjectActor != nullptr)
		{
			FoodObjectClass = Cast<AFoodObject>(FoodObjectActor);	
		}

		if(FoodObjectClass != nullptr)
		{
			SpawnIngredientObject();

			GameManagerClass->Currency -= Cost;
			GameManagerClass->Profit += Profit;

			GameManagerClass->SpawnText(Cost, false, CostTextLocation, CostTextRotation, CostTextScale, FColor::Red);
		}	
	}
}

void AIngredientActor::SpawnIngredientObject()
{
	NewSpawnObject = GetWorld()->SpawnActor<AActor>(IngredientObject, GetActorLocation(), GetActorRotation(), SpawnParameters);
	NewSpawnObject->SetActorScale3D(ScaleSpawn);
	IngredientClass = Cast<AIngredientObject>(NewSpawnObject);
	IngredientClass->Mesh->SetStaticMesh(SpawnMesh);
	FoodObjectClass->IngredientAdderFunction(NewSpawnObject, NewSpawnLocation);

	if(PawnClass->FoodTag == 0)
	{
		NewSpawnObject->SetActorRotation(NewSpawnRotator);
	}
}



