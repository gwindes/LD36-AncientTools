// Copyright Grant Windes 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate not found on %s"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	if (!isOpen) {
		OnOpen.Broadcast();

		isOpen = true;
	}
}

void UOpenDoor::CloseDoor()
{
	if (isOpen) {
		OnClose.Broadcast();

		isOpen = false;
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll Trigger every frame
	// if actor that opens in trig volume then open door
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
		OpenDoor();
	}
	else 
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;
	
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++) {
		auto Actor = OverlappingActors[i];
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}

