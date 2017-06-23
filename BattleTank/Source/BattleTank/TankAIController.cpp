// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    // Controlled Tank
    ATank *ControlledTank = GetContolledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController has no controlled tank!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController controlled tank: %s"), *(ControlledTank->GetName()));
    }
    
    // Player Tank
    ATank* PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController %s unable to find player tank"),*(ControlledTank->GetName()));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController %s found player tank: %s "),
               *ControlledTank->GetName(), *PlayerTank->GetName());
    }
    
}

ATank* ATankAIController::GetContolledTank() const
{
    return Cast<ATank>(GetPawn());
}

 ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) {return nullptr;}
    
    return Cast<ATank>(PlayerPawn);
}

