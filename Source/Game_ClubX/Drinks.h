// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Drinks.generated.h"

UENUM(BlueprintType)
enum class EDrinksState : uint8
{
	EDS_Idle UMETA(DisplayName = "Idle"),
	EDS_BeingHold UMETA(DisplayName = "BeingHold"),
	EDS_Empty UMETA(DisplayName = "Empty"),

	EDS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class GAME_CLUBX_API ADrinks : public AItem
{
	GENERATED_BODY()

public:

   ADrinks();

   UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drinks")
   FString DrinkName;

   UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Drinks")
   EDrinksState DrinksState;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drinks")
   class UParticleSystemComponent* OnTakenParticle;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drinks")
   class USoundCue* OnTakenSound;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drinks")
   int DrinkAmount;

   virtual void OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
   virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

   void Equip(class AMainCharacter* MainChar);
   void Unequip(class AMainCharacter* MainChar);
   void Drink(class AMainCharacter* MainChar);

   FORCEINLINE void SetWeaponState(EDrinksState State) { DrinksState = State; }
   FORCEINLINE EDrinksState GetWeaponState() { return DrinksState; }
};
