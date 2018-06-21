// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
	
	PawnThatOpensTheDoor =  GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}

void UDoorOpener::OpenDoor()
{
	FRotator DoorAngle = FRotator(0.0F, 80.0F, 0.0F);
	this->GetOwner()->SetActorRotation(DoorAngle);
}

// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume
	//If the PawnThatOpensTheDoor is in the presure plate
	if (PressurePlate->IsOverlappingActor(PawnThatOpensTheDoor)) {
		OpenDoor();
	}

	// ...
}

