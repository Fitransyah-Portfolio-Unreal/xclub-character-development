// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "CharactersStorage.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h" 
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"


void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidget)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidget);
	}
	MainMenu->AddToViewport(-20);
	MainMenu->SetVisibility(ESlateVisibility::Visible);
	MainMenu->bIsEnabled = true;

	if (SettingMenuWidget)
	{
		SettingMenu = CreateWidget<UUserWidget>(this,SettingMenuWidget);
	}
	SettingMenu->AddToViewport(-10);
	SettingMenu->SetVisibility(ESlateVisibility::Hidden);
	SettingMenu->bIsEnabled = false;

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	bShowMouseCursor= true;

	AActor* CharStorageActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACharactersStorage::StaticClass());
	CharStorage = Cast<ACharactersStorage>(CharStorageActor);

	TArray <AActor*, FDefaultAllocator> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "Placement", OutActors);
	if (OutActors.Num() > 0)
	{
		PlacementPointActor = OutActors[0];
		
		if (CharStorage != nullptr)
		{
			ActiveDisplayedActorName = "Bob";
			SetFirstActor();
		}
	}

	
}

void ALobbyPlayerController::SetFirstActor()
{
	if (CharStorage)
	{
		FString  FirstCharacter = ActiveDisplayedActorName;
		if (CharStorage->LobbyCharMap.Contains(ActiveDisplayedActorName))
		{
			ActiveDisplayedActor = GetWorld()->SpawnActor<AActor>(CharStorage->LobbyCharMap[ActiveDisplayedActorName]);

			if (PlacementPointActor)
			{
				ActiveDisplayedActor->SetActorLocation(PlacementPointActor->GetActorLocation());
				ActiveDisplayedActor->SetActorRotation(PlacementPointActor->GetActorRotation());
			}

		}
	}
}

void ALobbyPlayerController::SetActiveDisplayerdActor(FString NewActiveDisplayedActor)
{
	DestroyActiveDisplayedActor();
	if (CharStorage)
	{
		if (CharStorage->LobbyCharMap.Contains(NewActiveDisplayedActor))
		{
			ActiveDisplayedActor = GetWorld()->SpawnActor<AActor>(CharStorage->LobbyCharMap[NewActiveDisplayedActor]);

			if (PlacementPointActor)
			{
				ActiveDisplayedActor->SetActorLocation(PlacementPointActor->GetActorLocation());
				ActiveDisplayedActor->SetActorRotation(PlacementPointActor->GetActorRotation());

				ActiveDisplayedActorName = NewActiveDisplayedActor;
			}
		}
	}
}

void ALobbyPlayerController::DestroyActiveDisplayedActor()
{
	if (ActiveDisplayedActor)
	{
		ActiveDisplayedActor->Destroy();
	}
	else
	{
		return;
	}
}

void ALobbyPlayerController::DisplaySettingMenu()
{
	if (SettingMenu)
	{
		bSettingMenuVisible = true;
		SettingMenu->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void ALobbyPlayerController::RemoveSettingMenu()
{
	if (SettingMenu)
	{
		bSettingMenuVisible = false;
		SettingMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ALobbyPlayerController::ToggleSettingMenu()
{
	if (bSettingMenuVisible)
	{
		RemoveSettingMenu();
	}
	else
	{
		DisplaySettingMenu();
	}
}



