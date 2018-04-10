// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "BattleTank.h"
#include "Engine/World.h"
void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	//BroadCasts the event that we found the component
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

	auto ControlledTank = GetControlledTank();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() {

	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation; // Out Parameter
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString());
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect, and is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	// Get world location if lintrace through crosshair
	// If it hits the landscape
// Tell controlled tank to aim at this point
}

//Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	
	// Find Crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector LookDirection;
	// Calculate Screen Location
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	// De-Project the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		// Line-Trace Through along that LookDirection, and see what is hit (to a limited range)
		GetLookVectorHitLocation(LookDirection,HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X,ScreenLocation.Y,CameraWorldLocation,LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}