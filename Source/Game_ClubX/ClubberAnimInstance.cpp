// Fill out your copyright notice in the Description page of Project Settings.


#include "ClubberAnimInstance.h"
#include "Clubber.h"
#include "MainCharacter.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

void UClubberAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

		if (Pawn)
		{
			Clubber = Cast<AClubber>(Pawn);
		}
	}

	PlayerDrunkState = EDrunknessLevel::EDL_MAX;
	bLookAtTarget = false;
	bKeepLooing = false;
}

void UClubberAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		if (Clubber != nullptr)
		{
			Clubber = Cast<AClubber>(Pawn);
			if (Clubber->bPlayerIsExist)
			{
				PlayerDrunkState = Clubber->GetTargetedPlayer()->GetDrunkState();

				bLookAtTarget = Clubber->bPlayerIsExist;
				bPlayerIsDancing = Clubber->GetTargetedPlayer()->bIsDancing;

				ACharacter* Main = Cast<ACharacter>(Clubber->GetTargetedPlayer());
				if (Main)
				{
					USkeletalMeshComponent* Mesh =  Main->GetMesh();
					TargetLocation = Mesh->GetSocketLocation("HeadSocket");
				}
			}
			else
			{
				PlayerDrunkState = EDrunknessLevel::EDL_MAX;
				bLookAtTarget = false;
			}

		}
	}
}
