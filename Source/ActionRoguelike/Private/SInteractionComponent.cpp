// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"


// Sets default values
USInteractionComponent::USInteractionComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
void USInteractionComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
**/

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<USGameplayInterface>())
		{
			// Cast is safe.
			APawn* MyPawn = Cast<APawn>(MyOwner);
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
}

