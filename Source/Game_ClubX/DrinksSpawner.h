// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrinksSpawner.generated.h"

UCLASS()
class GAME_CLUBX_API ADrinksSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrinksSpawner();

	UPROPERTY(EditDefaultsOnly, Category = "DrinksSpawner")
	FString SpawnerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DrinksSpawner")
	class USphereComponent* CollisionVolume;
	
	UPROPERTY(EditDefaultsOnly, Category = "DrinksSpawner")
	TMap<FString, TSubclassOf<class ADrinks>> DrinksMap;

	ADrinks* Drink;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

// This need to have sphere volume
// Once player on overlap 
// Check spawner name with drinks map, store it
// set overlapping actor in player as stored variable

// deactivate the 
};
