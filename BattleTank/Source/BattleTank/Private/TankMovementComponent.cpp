// Fill out your copyright notice in the Description page of Project Settings.
#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// No need for super here as we are replaceing the functionality.
	//auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto MoveRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveForward(ForwardThrow);
	IntendMoveRight(MoveRightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	//UE_LOG(LogTemp, Warning, TEXT("Intend Move forward throw: %f"), Throw)
	if (!ensure(LeftTrack && RightTrack)) { return; }
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
}

void  UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveRight(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
