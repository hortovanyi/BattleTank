// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5;
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.3;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000;

private:

    ATank* GetContolledTank() const;
    
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersect the world
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
