// Corpyright Caveman Games 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "EngineMinimal.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *Owner->GetName());
	}

	if (!WinLine)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Win Line"), *Owner->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate) { return; }

	if (!WinLine) { return; }

	if (GetTotalMassOfActorsOnPlate() > TriggerMassToOpenDoor)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

	GetPlayerWin();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	// Clear TotalMass to Pass to Blueprint else the value Incremento forever
	TotalMass = 0.0f;

	//Find All the Overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Interate through them adding their masses
	if (OverlappingActors.Num() > 0)
	{
		for (const auto& Overlapped : OverlappingActors)
		{
			TotalMass += Overlapped->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			UE_LOG(LogTemp, Warning, TEXT("Name of Object: %s and the mass is: %f"), *Overlapped->GetName(), TotalMass);
		}
	}
	return TotalMass;
}

void UOpenDoor::GetPlayerWin()
{
	TArray<AActor*> OverlappingActors;
	WinLine->GetOverlappingActors(OUT OverlappingActors);

	if (OverlappingActors.Num() > 0)
	{
		OnWin.Broadcast();
	}
}