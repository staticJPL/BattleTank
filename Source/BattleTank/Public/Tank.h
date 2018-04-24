// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Returns current health as a percentage of starting health between 0 and 1

	UFUNCTION(BlueprintPure,Category="Health")
	float GetHealthPercent() const;

	// This blueprint is a const fucntion that doesnt modify the object it's accociated with.

	// Called by engine.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 CurrentHealth; // Initialised in begin play
};
