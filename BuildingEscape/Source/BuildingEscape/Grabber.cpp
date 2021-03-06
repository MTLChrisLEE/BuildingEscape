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

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Error, TEXT("GRAB PRESSED"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) {
		PhysicsHandler->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ActorHit->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Error, TEXT("RELEASED"));

	PhysicsHandler->ReleaseComponent();

}


void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()))
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Input component found"))
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component handle component"), *(GetOwner()->GetName()))
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PhysicsHandler) {
		return;
	}
	if (PhysicsHandler && PhysicsHandler->GrabbedComponent)
	{
		PhysicsHandler->SetTargetLocation(GetLineTraceEnd());
	}
	
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{	
	FHitResult Result;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Result,
		Location,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Result.GetActor();

	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *(ActorHit->GetName()))
	}
	
	return Result;
}

FVector UGrabber::GetLineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	FString location = Location.ToString();
	FString rotation = Rotation.ToString();

	LineTraceEnd = Location + Rotation.Vector() * Reach;

	return LineTraceEnd;
}

