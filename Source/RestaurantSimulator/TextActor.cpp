// Fill out your copyright notice in the Description page of Project Settings.


#include "TextActor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ATextActor::ATextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextObject = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextObject"));

	RootComponent = TextObject;
}

// Called when the game starts or when spawned
void ATextActor::BeginPlay()
{
	Super::BeginPlay();
	
	TargetLocation = FVector3d(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 40);
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetActorLocation();
	
	Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	NewLocation = CurrentLocation + (Direction * 50 * DeltaTime);
	SetActorLocation(NewLocation);

	if(CurrentLocation.Z + 5 >= TargetLocation.Z)
	{
		this->Destroy();
	}

	TextObject->SetTextRenderColor(TextColor);
	
	TextObject->Text = FText::Format(FText::FromString("{0} $"), FText::AsNumber(Value));
	TextObject->SetWorldScale3D(Scale);
}

