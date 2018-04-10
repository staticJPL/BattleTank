// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	//TODO need to remove once firing is moved.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000; // 1000 m/s ;)

	// Tank needs to know something about the projectile which is C++ and a Blueprint
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// Set a projectile blueprint on every instance of Tank
	TSubclassOf<AProjectile> ProjectileBlueprint;
	// Could do this too  UClass* ProjectileBlueprint but TSubclass is cleaner for drop down in the blueprint setup;
	//Local Barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr;
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

};
