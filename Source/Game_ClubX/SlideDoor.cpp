// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ASlideDoor::ASlideDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetBoxExtent(FVector(80.f, 80.f, 80.f));

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor->SetupAttachment(GetRootComponent());
	LeftDoor->SetupAttachment(GetRootComponent());

	CloseTime = 4.f;
	bCharNearDoor = false;
	bDoorIsOpen = false;

	DoorOpeningSound = nullptr;
}

// Called when the game starts or when spawned
void ASlideDoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASlideDoor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASlideDoor::OnOverlapEnd);
	
	InitialRightDoorLocation = RightDoor->GetComponentLocation();
	InitialLeftDoorLocation = LeftDoor->GetComponentLocation();
}

// Called every frame
void ASlideDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlideDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString OtherName = OtherActor->GetActorNameOrLabel();
	UE_LOG(LogTemp, Warning, TEXT("%s In the trigger area"), *OtherName);

	if (!bCharNearDoor) bCharNearDoor = true;
	

	SlideOpenRightDoor();
	SlideOpenLeftDoor();

	if (DoorOpeningSound && !bDoorIsOpen)
	{
		UGameplayStatics::PlaySound2D(this, DoorOpeningSound);
		bDoorIsOpen = true;
	}

}


void ASlideDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FString OtherName = OtherActor->GetActorNameOrLabel();
	UE_LOG(LogTemp, Warning, TEXT("%s Out of the trigger box"), *OtherName);

	if (bCharNearDoor) bCharNearDoor = false;

	GetWorldTimerManager().SetTimer(ClosingHandle, this, &ASlideDoor::CloseDoor, CloseTime);
}

void ASlideDoor::UpdateRightDoorLocation(float OpenDirection)
{
	FVector NewLocation = InitialRightDoorLocation;
	NewLocation.X += OpenDirection;
	RightDoor->SetWorldLocation(NewLocation);
}


void ASlideDoor::UpdateLefttDoorLocation(float OpenDirection)
{
	FVector NewLocation = InitialLeftDoorLocation;
	NewLocation.X += OpenDirection;
	LeftDoor->SetWorldLocation(NewLocation);
}

void ASlideDoor::CloseDoor()
{
	if (!bCharNearDoor)
	{
		SlideCloseRightDoor();
		SlideCloseLeftDoor();

		if (DoorClosingSound && bDoorIsOpen)
		{
			UGameplayStatics::PlaySound2D(this, DoorClosingSound);
			bDoorIsOpen = false;
		}

		
	}
}

