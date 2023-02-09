// Fill out your copyright notice in the Description page of Project Settings.


#include "ClubberAnimInstance.h"
#include "Clubber.h"

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
		}
		
	}
}
