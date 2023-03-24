// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "CharactersStorage.h"
#include "GameFramework/Character.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "XClub_GameInstance.h"
#include "Containers/Array.h" 


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

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	bShowMouseCursor = false;

	AActor* CharStorageActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACharactersStorage::StaticClass());
	CharStorage = Cast<ACharactersStorage>(CharStorageActor);

	TArray <AActor*, FDefaultAllocator> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "Placement", OutActors);
	if (OutActors.Num() > 0)
	{
		PlacementPointActor = OutActors[0];

		if (CharStorage != nullptr)
		{
			// TO DO
			//SetCharacter("Bob");
			UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
			UXClub_GameInstance* XclubGameInstance = Cast<UXClub_GameInstance>(GameInstance);
			SetCharacter(XclubGameInstance->SelectedCharacter);
		}
	}
	
}

void AMainCharPlayerController::SetCharacter(FString SelectedCharacter)
{
	if (SelectedCharacter == "")
	{
		SelectedCharacter = "Bob";
	}
	if (CharStorage)
	{
		if (CharStorage->MainCharMap.Contains(SelectedCharacter))
		{
			ActiveDisplayedCharacter = GetWorld()->SpawnActor<AMainCharacter>(CharStorage->MainCharMap[SelectedCharacter]);

			if (PlacementPointActor)
			{
				ActiveDisplayedCharacter->SetActorLocation(PlacementPointActor->GetActorLocation());
				ActiveDisplayedCharacter->SetActorRotation(PlacementPointActor->GetActorRotation());

				Possess(ActiveDisplayedCharacter);
			}
		}
	}
}
