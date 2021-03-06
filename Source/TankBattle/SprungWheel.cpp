// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);


	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Constraint);


	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleConstraint"));
	AxleConstraint->SetupAttachment(Axle);
}

void ASprungWheel::AddDriveForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}
}
void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector()*TotalForceMagnitudeThisFrame);
}
// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetUpConstraint();
	
}
void ASprungWheel::SetUpConstraint()
{
	if (!GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning,
			L"sprung wheel not Working!");
		return;
	}
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;

	Constraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
 }

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit)
{
	ApplyForce();
	UE_LOG(LogTemp, Warning, L"Hitting the tank wheel");
}
