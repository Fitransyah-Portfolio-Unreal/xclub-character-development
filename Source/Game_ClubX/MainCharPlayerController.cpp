// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainCharPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}
	HUDOverlay->AddToViewport(-20);

	HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	HUDOverlay->bIsEnabled = true;
}
