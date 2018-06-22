// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("GRABBER REPORT FOR DUTY"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	//Draw a red trace line
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	FString location = Location.ToString();
	FString rotation = Rotation.ToString();

	FVector LineTraceEnd = Location + Rotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), Location, LineTraceEnd, FColor(255,0,0),false,0,0,3.0);

	UE_LOG(LogTemp, Warning, TEXT("Location is %s, Rotation is %s"), *location, *rotation);



	//Line-trace

	FHitResult Result;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Result,
		Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Result.GetActor();

	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *(ActorHit->GetName()))

	}

	

}

