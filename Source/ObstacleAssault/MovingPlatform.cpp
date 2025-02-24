// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	
	SetActorLocation(CurrentLocation);

	//Send platform back if gone too far		
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);
		//Reverse direction of motion if gone too far	
		if (DistanceMoved > MoveDistance)
		{			
			FString Name = GetName();
			float OverShoot = DistanceMoved - MoveDistance;
			UE_LOG(LogTemp, Warning, TEXT("%s OverShoot by %f"), *Name ,OverShoot);

			FVector MoveDirection = PlatformVelocity.GetSafeNormal();
			StartLocation = StartLocation + MoveDirection * MoveDistance;
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity;
		}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("Rotating!"));
}