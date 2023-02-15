// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"
#include "Kismet/GameplayStatics.h"

bool UBaseUserWidget::Initialize()
{
	Super::Initialize();

	APlayerController* Localcontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Localcontroller)
	{
		LocalPlayerController = Cast<APlayerController>(Localcontroller);
	}
	return true;
}
