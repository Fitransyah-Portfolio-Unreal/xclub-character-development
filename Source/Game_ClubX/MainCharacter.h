// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GAME_CLUBX_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------- Cameras and movement

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookupRate;

	// Called for forward/backwards input
	void MoveForward(float Value);

	// Called for side to side input
	void MoveRight(float Value);

	/** Called via input to turn at a given rate
	* @param Rate this is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @param Rate this is a normalized rate, i.e. 1.0 means 100% of desired look up/down rate
	*/
	void LookUpRate(float Rate);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//------------------ WALK MODE

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WalkMode")
	bool bIsHappy;

	void HappyKeyDown();

	void HappyKeyUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WalkMode")
	bool bIsSad;

	void SadKeyDown();

	void SadKeyUp();

	//------------------ DANCE MODE

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DanceMode | Sounds")
	class USoundCue* DancingSound;

	FVector CharacterVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DanceMode")
	bool bIsDancing;

	UFUNCTION(BlueprintImplementableEvent, Category = "DanceMode")
	void StartDancing();

	UFUNCTION(BlueprintImplementableEvent, Category = "DanceMode")
	void StopDancing();

	//------------------ DANCE MODE

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HoldingGlass")
	bool bIsHoldingGlass;

	UFUNCTION(BlueprintCallable, Category = "HoldingGlass")
	void HoldingGlassActive();

	UFUNCTION(BlueprintCallable, Category = "HoldingGlass")
	void HoldingGlassInactive();

};
