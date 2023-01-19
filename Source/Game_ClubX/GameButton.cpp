// Fill out your copyright notice in the Description page of Project Settings.


#include "GameButton.h"
#include "Components/Button.h"
#include "MainCharacter.h"

bool UGameButton::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &ThisClass::ActionButtonPressed);
	}

	if (DanceButton)
	{
		DanceButton->OnClicked.AddDynamic(this, &ThisClass::DanceButtonPressed);
	}


	return true;
}


