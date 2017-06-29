// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) {return;}
    
    auto PlayerTank = Cast<ATank>(PlayerPawn);
    auto ControlledTank = Cast<ATank>(GetPawn());

    if (PlayerTank)
    {
        // Move towards the player
        
        // Aim towards the player
        
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        
        // fire if ready
        ControlledTank->Fire(); // TODO limit firing rate
        
    }
}



