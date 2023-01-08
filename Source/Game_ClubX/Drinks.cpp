// Fill out your copyright notice in the Description page of Project Settings.


#include "Drinks.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"

ADrinks::ADrinks()
{
	DrinksState = EDrinksState::EDS_Idle;

	bIdleParticleActive = true;
	bOverlapParticleActive = false;
	bRotate = false;

	DrinkAmount = 3;
}

void ADrinks::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverLapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if ((DrinksState == EDrinksState::EDS_Idle) && OtherActor)
	{
		AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
		if (MainChar)
		{
			MainChar->SetActiveOverlappingItem(this);
		}
	}
}

void ADrinks::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
		if (MainChar)
		{
			MainChar->SetActiveOverlappingItem(nullptr);
		}
	}
}

void ADrinks::Equip(class AMainCharacter* MainChar)
{
	if (MainChar)
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* LeftHandSocket = MainChar->GetMesh()->GetSocketByName("LeftHandSocket");
		if (LeftHandSocket)
		{
			LeftHandSocket->AttachActor(this, MainChar->GetMesh());

			MainChar->SetHoldedDrink(this);
			MainChar->SetActiveOverlappingItem(nullptr);
			MainChar->bIsHoldingGlass = true;

			DrinksState = EDrinksState::EDS_BeingHold;
			CollisionVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

	}
}

void ADrinks::Unequip(AMainCharacter* MainChar)
{
	MainChar->SetHoldedDrink(nullptr);
	MainChar->bIsHoldingGlass = false;

	Destroy();
}

void ADrinks::Drink(AMainCharacter* MainChar)
{
	if (DrinksState == EDrinksState::EDS_BeingHold &&
	(MainChar->bIsDrinking == false)
	)
	{
		DrinkAmount --;
		if (OnTakenSound)
		{
			UGameplayStatics::PlaySound2D(this, OnTakenSound);
		}
	}
	
	if (DrinkAmount <= 0)
	{
		DrinksState = EDrinksState::EDS_Empty;
	}
}