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
        UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
        // tell controlled tank to aim at this point
        
    }
}

// get world location of linetrace through crosshair, true it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    HitLocation = FVector(1.0);
    return true;
}
