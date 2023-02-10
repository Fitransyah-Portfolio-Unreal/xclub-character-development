// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"
#include "ClubberAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API UClubberAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	class AClubber* Clubber;

	UPROPERTY(BlueprintReadOnly, Category = "ClubberAnimInstance")
	EDrunknessLevel PlayerDrunkState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	FVector TargetLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	bool bLookAtTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	bool bPlayerIsDancing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ClubberAnimInstance")
	bool bKeepLooing;

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "ClubberAnimInstance")
	void UpdateAnimationProperties();
	
};
