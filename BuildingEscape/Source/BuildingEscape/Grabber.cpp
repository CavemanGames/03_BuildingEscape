// Corpyright Caveman Games 2017

#include "Grabber.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	FindInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetPReachLineEnd());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (!ComponentToGrab && !ActorHit) { return; }
	if (!PhysicsHandle) { return; }

	// If we Hit something then attach a physics Handle
	PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		/// Physics Handle Message Error
		UE_LOG(LogTemp, Error, TEXT("Error on try Find the Physics Handle Component in the BeginPlay of the %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		/// Input Message Error
		UE_LOG(LogTemp, Error, TEXT("Error on try Find the Input Component in the BeginPlay of the %s"), *GetOwner()->GetName());
	}
}

FVector UGrabber::GetPReachLineEnd()
{
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	/// Create a Line Trace
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * LineLength);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector LineTraceEnd = GetPReachLineEnd();
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	/// Ray-Cast (AKA ray-cast) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	/// See what we hit
	AActor* ActorHit = LineTraceHit.GetActor();

	return LineTraceHit;
}