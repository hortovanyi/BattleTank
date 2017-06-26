// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank *ControlledTank = GetContolledTank();
    
    if (ControlledTank == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing tank: %s"), *(ControlledTank->GetName()));
    }
    
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    
//    UE_LOG(LogTemp, Warning, TEXT("PlayerController tick DeltaTime: %f"), DeltaTime);
}

ATank* ATankPlayerController::GetContolledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!GetContolledTank()) {return;}
    
    FVector HitLocation; // Out Parameter
    if (GetSightRayHitLocation(HitLocation))
    {
//        UE_LOG(LogTemp, Warning, TEXT("Hit location : %s"), *HitLocation.ToString());
        // tell controlled tank to aim at this point
        GetContolledTank()->AimAt(HitLocation);
    }
}

// get world location of linetrace through crosshair, true it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
//    UE_LOG(LogTemp, Warning, TEXT("Screen location: %s"), *ScreenLocation.ToString());
    
    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to max range)
//        UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
        
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector WorldLocation; // to be discarded
    
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    // if line trace succeeds
    if (GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility)
        )
    {
        // set hit location
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    
    return false;
}
