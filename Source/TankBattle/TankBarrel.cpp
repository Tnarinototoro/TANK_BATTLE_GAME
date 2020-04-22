// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Eleate(float RelativeSpeed)
{
	//Clamp Relative Speed from -1 to +1;
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPersecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation=FMath::Clamp<float>(RawNewElevation,MinElevationDegrees,MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0,0));
}