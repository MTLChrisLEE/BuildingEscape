// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"




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
	
	//PawnThatOpensTheDoor =  GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...

	if (!PressurePlate) {
		UE_LOG(LogTemp,Warning,TEXT("%s is missing"),*(GetOwner()->GetName()))
	}

}

void UDoorOpener::OpenDoor()
{
	/*FRotator DoorAngle = FRotator(0.0F, 80.0F, 0.0F);
	this->GetOwner()->SetActorRotation(DoorAngle);*/

	OnOpenRequest.Broadcast();
}

void UDoorOpener::CloseDoor()
{
	FRotator DoorAngle = FRotator(0.0F, 0.0F, 0.0F);
	this->GetOwner()->SetActorRotation(DoorAngle);
}

// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume
	//If the PawnThatOpensTheDoor is in the presure plate
	if (GetTotalMassofActorOnPlate()>=50.F) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDealy) {
		CloseDoor();
	}
	// ...
}

float UDoorOpener::GetTotalMassofActorOnPlate() {

	float total = 0.0F;
	TArray<AActor*> OverlappingActors;
	
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		total+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return total;
}



