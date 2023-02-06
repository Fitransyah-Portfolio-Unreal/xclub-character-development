// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Drinks.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 400.f;

	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookupRate = 65.f;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	NormalWalkSpeed = 150.f;
	EmoteWalkSpeed = 100.f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 840.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;

	Drunkness = 0.f;
	MaxDrunkness = 175.f;
	TypsyLimit = 50.f;
	DrunkLimit = 100.f;
	AlcoholDrainRate = 0.075f;
	IntoxicationRate = 12.5f;
	WastedLimit = 145.f;
	TypsyWalkSpeed = 100.f;
	DrunkWalkSpeed = 65.f;

	bFaceLiveLinkEnabled = false;
	
	// First Person Mode
	HeadCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeadCamera"));
	HeadCamera->SetupAttachment(GetMesh(), FName("HeadSocket"));
	HeadCamera->bAutoActivate = false;
	HeadCamera->bUsePawnControlRotation = true;
	HeadCamera->SetWorldLocation(FVector(0.f, 0.f, 25.f));
	HeadCamera->SetWorldRotation(FRotator(0.f, 90.f, 90.f));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsHappy = false;
	bIsSad = false;
	bIsDancing = false;
	bIsHoldingGlass = false;

	SetCameraPitchLimits(-89.f, 89.f);

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Walk Mode and Emote
	if (bIsHappy || bIsSad)
	{
		GetCharacterMovement()->MaxWalkSpeed = EmoteWalkSpeed;
	}
	else if (DrunkState == EDrunknessLevel::EDL_Normal)
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
	}

	CharacterVelocity = GetCharacterMovement()->GetLastUpdateVelocity();
	if (bIsDancing && CharacterVelocity != FVector::Zero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Moving"));
		bIsDancing = false;

		StopDancing();
	}

	// Drunk Mechanic
	float DeltaAlcoholDrainRate = AlcoholDrainRate * DeltaTime;

	switch (DrunkState)
	{
		case EDrunknessLevel::EDL_Normal:
		if (Drunkness > TypsyLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Typsy);
		}
		break;
		case EDrunknessLevel::EDL_Typsy:
		if (Drunkness > DrunkLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Drunk);
		}
		else if (Drunkness < TypsyLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Normal);
		}
		break;
		case EDrunknessLevel::EDL_Drunk:
		if (Drunkness > WastedLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Wasted);
		}
		else if (Drunkness < DrunkLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Typsy);
		}
		break;
		case EDrunknessLevel::EDL_Wasted:
		if (Drunkness < WastedLimit)
		{
			SetDrunkState(EDrunknessLevel::EDL_Drunk);
		}
		break;
	}

	if (Drunkness > 0.f)
	{
		Drunkness -= DeltaAlcoholDrainRate;
	}
	else if (Drunkness < 0.f)
	{
		Drunkness = -0.001f;
	}
	if (Drunkness > MaxDrunkness)
	{
		Drunkness = MaxDrunkness;
	}
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);


	// Camera code
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpRate);

	PlayerInputComponent->BindAction("Happy", IE_Pressed, this, &AMainCharacter::HappyKeyDown);
	PlayerInputComponent->BindAction("Happy", IE_Released, this, &AMainCharacter::HappyKeyUp);

	PlayerInputComponent->BindAction("Sad", IE_Pressed, this, &AMainCharacter::SadKeyDown);
	PlayerInputComponent->BindAction("Sad", IE_Released, this, &AMainCharacter::SadKeyUp);

	PlayerInputComponent->BindAction("Dance", IE_Pressed, this, &AMainCharacter::StartDancing);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);

	PlayerInputComponent->BindAction("ToggleCamera", IE_Pressed, this, &AMainCharacter::ToggleCamera);
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDrinking) && (DrunkState != EDrunknessLevel::EDL_Wasted))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && (!bIsDrinking) && (DrunkState != EDrunknessLevel::EDL_Wasted))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::HappyKeyDown()
{
	if (DrunkState == EDrunknessLevel::EDL_Normal)
	{
		bIsHappy = true;
		bIsSad = false;
	}
}

void AMainCharacter::HappyKeyUp()
{
	bIsHappy = false;
}

void AMainCharacter::SadKeyDown()
{
	if (DrunkState == EDrunknessLevel::EDL_Normal)
	{
		bIsSad = true;
		bIsHappy = false;
	}
}

void AMainCharacter::SadKeyUp()
{
	bIsSad = false;
}

void AMainCharacter::LMBDown()
{
	bLMBDown = true;

	if (ActiveOverlappingItem && !bIsHoldingGlass)
	{
		ADrinks* DrinkToHold = Cast<ADrinks>(ActiveOverlappingItem);
		if (DrinkToHold)
		{
			bIsHoldingGlass = true;
			DrinkToHold->IdleParticleComponent->Deactivate();
			DrinkToHold->Equip(this);
		}
	}
	else if (bIsHoldingGlass && HoldedDrink)
	{
		Drinking();
	}
}

void AMainCharacter::LMBUp()
{
	bLMBDown = false;
}

void AMainCharacter::SetHoldedDrink(ADrinks* DrinkToHold)
{
	if (HoldedDrink)
	{
		HoldedDrink->Destroy();
	}

	HoldedDrink = DrinkToHold;
}

void AMainCharacter::Drinking()
{
	if (!bIsDrinking && HoldedDrink)
	{
		HoldedDrink->Drink(this);
		bIsDrinking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && DrinkingMontage)
		{
			AnimInstance->Montage_Play(DrinkingMontage, 1.5f);
			Drunkness += IntoxicationRate;
		}
	}
}

void AMainCharacter::DrinkingEnd()
{
	bIsDrinking = false;

	if (HoldedDrink->DrinksState == EDrinksState::EDS_Empty)
	{
		HoldedDrink->Unequip(this);
	}
}

void AMainCharacter::SetDrunkState(EDrunknessLevel NewState)
{
	DrunkState = NewState;
	switch (DrunkState)
	{
		case EDrunknessLevel::EDL_Normal:
		GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
		break;
		case EDrunknessLevel::EDL_Typsy:
		GetCharacterMovement()->MaxWalkSpeed = TypsyWalkSpeed;
		break;
		case EDrunknessLevel::EDL_Drunk:
		GetCharacterMovement()->MaxWalkSpeed = DrunkWalkSpeed;
		break;
		case EDrunknessLevel::EDL_Wasted:
		GetCharacterMovement()->MaxWalkSpeed = 0.001f;
		break;
	}
}

void AMainCharacter::ToggleCamera()
{
	if (FollowCamera->IsActive())
	{
		FollowCamera->SetActive(false);
		HeadCamera->SetActive(true);
		bUseControllerRotationYaw = true;
		SetCameraPitchLimits(-70.f, 90.f);
	}
	else
	{
		FollowCamera->SetActive(true);
		HeadCamera->SetActive(false);
		bUseControllerRotationYaw = false;
		SetCameraPitchLimits(-89.f, 89.f);
	}
}

void AMainCharacter::SetCameraPitchLimits(float Min, float Max)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->PlayerCameraManager->ViewPitchMin = Min;
	PlayerController->PlayerCameraManager->ViewPitchMax = Max;
}
