// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    
    auto NewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
