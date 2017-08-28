// Corpyright Caveman Games 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TotalMass = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TriggerMassToOpenDoor = 30.f;

private:	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* WinLine = nullptr;

	AActor* Owner;
	float GetTotalMassOfActorsOnPlate();
	void GetPlayerWin();
};
