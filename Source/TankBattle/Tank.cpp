// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->TanAimingCompo = CreateDefaultSubobject<UAimingComponent>(FName("AimingCompo"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATank::AimAt(FVector HitLocation)
{
	this->TanAimingCompo->AimAt(HitLocation, LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReferrence(UTankBarrel * BarrelFromOutSide)
{
	TanAimingCompo->SetBarrelReferrenceFromOwner(BarrelFromOutSide);
}

void ATank::SetTurretRefferrence(UTankTurret * TurretFromOutside)
{
	TanAimingCompo->SetTurretreferrenceFromOwner(TurretFromOutside);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire in The Hole!!"));
}
