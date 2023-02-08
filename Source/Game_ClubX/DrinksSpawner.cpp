// Fill out your copyright notice in the Description page of Project Settings.


#include "DrinksSpawner.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "Drinks.h"

// Sets default values
ADrinksSpawner::ADrinksSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetSphereRadius(90, true);
	CollisionVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionVolume->SetCollisionResponseToChannel( ECollisionChannel::ECC_Pawn ,ECollisionResponse::ECR_Overlap);
	RootComponent = CollisionVolume;

	SpawnerName = TEXT("");

}

// Called when the game starts or when spawned
void ADrinksSpawner::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADrinksSpawner::OnOverLapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADrinksSpawner::OnOverlapEnd);
}

void ADrinksSpawner::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FString Name = GetActorNameOrLabel();
	FString OtherName = OtherActor->GetActorLabel();
	UE_LOG(LogTemp, Warning, TEXT("%s begin overlapped outside by: %s"), *Name, *OtherName);
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar)
	{
		if (DrinksMap.Contains(SpawnerName))
		{
			Drink = GetWorld()->SpawnActor<ADrinks>(DrinksMap[SpawnerName]);		
			Drink->SetActorLocation(GetActorLocation());

			//FString Name = GetActorNameOrLabel();
			//FString OtherName = OtherActor->GetActorLabel();
			//UE_LOG(LogTemp, Warning, TEXT("%s begin overlapped inside by: %s"), *Name, *OtherName);

			MainChar->SetActiveOverlappingItem(Drink);
			
		}
	}
}

void ADrinksSpawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar)
	{
		if (MainChar->GetEquippedWeapon() == Drink)
		{
			Drink = nullptr;
		}
		else 
		{
			if (MainChar->GetActiveOverlappingItem())
			{
				MainChar->SetActiveOverlappingItem(nullptr);
			}
			Drink->Destroy();
		}
	}
}



