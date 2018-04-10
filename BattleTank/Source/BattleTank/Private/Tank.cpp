// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Projectile.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {

	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation) {

	// Added Pointer Protection here becauase it crashes the UE4 Editor.
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
}
void ATank::Fire() {
	//UE_LOG(LogTemp, Warning, TEXT("Tank Fired"));
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded) {
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	return;
}
