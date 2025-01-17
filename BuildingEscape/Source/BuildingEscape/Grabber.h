// Corpyright Caveman Games 2017

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float LineLength = 100.f;

	UPROPERTY(EditAnywhere)
		FColor LineColor;
private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	FVector PlayerViewPointLocation;

	// Ray-cast and grab what's in reach
	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void FindInputComponent();
	FVector GetPReachLineEnd();
	FHitResult GetFirstPhysicsBodyInReach();
};
