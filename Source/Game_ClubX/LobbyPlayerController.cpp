// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "CharactersStorage.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h" 


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
			SetFirstActor();
		}
	}
}

void ALobbyPlayerController::SetFirstActor()
{
	if (CharStorage)
	{
		FString  Bob = "LobbyChar1";
		if (CharStorage->LobbyCharMap.Contains(Bob))
		{
			ActiveDisplayedActor = GetWorld()->SpawnActor<AActor>(CharStorage->LobbyCharMap[Bob]);

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

