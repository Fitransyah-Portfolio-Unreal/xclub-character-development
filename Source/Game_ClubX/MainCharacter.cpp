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

	FollowCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookupRate = 65.f;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 840.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsHappy = false;
	bIsSad = false;
	bIsDancing = false;
	bIsHoldingGlass = false;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsHappy || bIsSad)
	{
		GetCharacterMovement()->MaxWalkSpeed = 150.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 350.f;
	}

	CharacterVelocity = GetCharacterMovement()->GetLastUpdateVelocity();
	if (bIsDancing && CharacterVelocity != FVector::Zero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Is Moving"));
		bIsDancing = false;

		StopDancing();
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

	PlayerInputComponent->BindAction("HoldingGlass", IE_Pressed, this, &AMainCharacter::HoldingGlassActive);
	PlayerInputComponent->BindAction("HoldingGlass", IE_Released, this, &AMainCharacter::HoldingGlassInactive);

}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
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
	bIsHappy = true;
	bIsSad = false;
}

void AMainCharacter::HappyKeyUp()
{
	bIsHappy = false;
}

void AMainCharacter::SadKeyDown()
{
	bIsSad = true;
	bIsHappy = false;
}

void AMainCharacter::SadKeyUp()
{
	bIsSad = false;
}

void AMainCharacter::HoldingGlassActive()
{
	if(!bIsHoldingGlass) bIsHoldingGlass = true;
}

void AMainCharacter::HoldingGlassInactive()
{
	if (bIsHoldingGlass) bIsHoldingGlass = false;
}