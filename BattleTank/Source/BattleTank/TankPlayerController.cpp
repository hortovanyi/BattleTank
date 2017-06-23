// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank *ControlledTank = GetContolledTank();
    
    if (ControlledTank == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController has no controlled tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController controlled tank: %s"), *(ControlledTank->GetName()));
    }
    
}


ATank* ATankPlayerController::GetContolledTank() const
{
    return Cast<ATank>(GetPawn());
}
