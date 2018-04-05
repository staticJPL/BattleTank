// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw) {

	UE_LOG(LogTemp, Warning, TEXT("Intend Move forward throw: %f"), Throw)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void  UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveRight(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
