// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle)
	auto ForceApplied = GetForwardVector() * FMath::Clamp<float> (Throttle , -0.5f,0.5f) * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	// We cast to a Primitive Component because the pointer returned is a scene component and we cannot add forces on that type.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
	
}

