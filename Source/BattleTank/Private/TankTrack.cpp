// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}



void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	// Drive tracks apply side ways force
	DriveTrack();
	ApplySidewaysForce();
	//Reset Throttle
	CurrentThrottle = 0.0f;
}


void UTankTrack::ApplySidewaysForce()
{
	// Calculate Slippage Speed Sideways friction prolly use cross product
	// Work-out the required acceleration this frame to correct
	// Apply a force in that direction
	// Splipage speed should be when cos (0) = 1 which is the dot product between the velocity vector and sideways vector.
	
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());


	// Acceleration = V/T
	auto CorrectionAcceleration = (-SlippageSpeed / (DeltaTime)) * GetRightVector();

	// F = MA
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto Correctionforce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks
	TankRoot->AddForce(Correctionforce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle),-1,1);
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}