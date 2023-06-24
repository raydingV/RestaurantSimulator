// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"


UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		// Tıklama olayını dinlemek istediğiniz bileşenleri buraya ekleyin, örneğin:
		UStaticMeshComponent* MeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();
		if (MeshComponent)
		{
			MeshComponent->OnClicked.AddDynamic(this, &UMyActorComponent::OnClicked);
			MeshComponent->SetGenerateOverlapEvents(true); // Etkileşimli bileşenlerde çakışma etkinleştirme
		}
	}
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyActorComponent::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	// Tıklama olayını ele almak için gereken kodu buraya ekleyin
	UE_LOG(LogTemp, Warning, TEXT("Tıklandı!"));
}

