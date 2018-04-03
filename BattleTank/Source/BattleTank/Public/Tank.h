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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000; // 1000 m/s ;)

	// Tank needs to know something about the projectile which is C++ and a Blueprint
	UPROPERTY(EditAnywhere, Category = Setup)
	// Set a projectile blueprint on every instance of Tank
	TSubclassOf<AProjectile> ProjectileBlueprint;
	// Could do this too  UClass* ProjectileBlueprint but TSubclass is cleaner for drop down in the blueprint setup;
	//Local Barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr;

};
