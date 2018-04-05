// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Public/Tank.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	// Move the Barrel the right amount this frame
	
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ElevationClamp = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	// Need to clamp the Elevation
	SetRelativeRotation(FRotator(ElevationClamp, 0, 0));
}
