// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"


UENUM(BlueprintType)
enum class EDrunknessLevel : uint8
{
	EDL_Normal UMETA(DisplayName = "Normal"),
	EDL_Typsy UMETA(DisplayName = "Typsy"),
	EDL_Drunk UMETA(DisplayName = "Drunk"),
	EDL_Wasted UMETA(DisplayName = "Wasted"),

	EDL_MAX UMETA(DisplayName = "DefaultMAX")
};

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
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	// Called for side to side input
	UFUNCTION(BlueprintCallable)
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WalkMode")
	float NormalWalkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WalkMode")
	float EmoteWalkSpeed;

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

	//------------------ DRINK MECHANIC

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drinking")
	bool bIsHoldingGlass;

	
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Drinking")
	class ADrinks* HoldedDrink;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drinking")
	class ADrinks* ActiveOverlappingItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Drinking")
	class UAnimMontage* DrinkingMontage;

	UPROPERTY(VisibleAnywhere, Category = "Drinking")
	bool bIsDrinking;

	bool bLMBDown;

	void SetHoldedDrink(ADrinks* DrinkToHold);
	void LMBDown();
	void LMBUp();
	void Drinking();

	UFUNCTION(BlueprintCallable)
	void DrinkingEnd();

	// Setter for overlapping item
	FORCEINLINE void SetActiveOverlappingItem(ADrinks* ItemToSet) { ActiveOverlappingItem = ItemToSet; }

	// Getter to weapon
	FORCEINLINE ADrinks* GetEquippedWeapon() { return HoldedDrink; }

	// Getter for overlapping item
	FORCEINLINE ADrinks* GetActiveOverlappingItem() { return ActiveOverlappingItem; }

	//------------------ DRUNK MECHANIC
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float MaxDrunkness;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float TypsyLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float DrunkLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float WastedLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float AlcoholDrainRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float IntoxicationRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float TypsyWalkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drunk")
	float DrunkWalkSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Drunk")
	float Drunkness;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Drunk")
	EDrunknessLevel DrunkState;

	void SetDrunkState(EDrunknessLevel NewState);
	EDrunknessLevel GetDrunkState() { return DrunkState;}

	//------------------ FIRST  PERSON

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* HeadCamera;

	void ToggleCamera();

	void SetCameraPitchLimits(float Min, float Max);

	//------------------ Clubber Idle Collision
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Clubber")
	class USphereComponent* ClubberSphere;

	//-------------------------- Live Link

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Live Link")
	bool bFaceLiveLinkEnabled;
	
};
