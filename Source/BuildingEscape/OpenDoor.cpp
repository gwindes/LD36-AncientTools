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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	if (!isOpen) {
		AActor * Owner = GetOwner();
		FRotator CurrentRot = Owner->GetActorRotation();

		CurrentRot.Yaw += 60.f;

		//FRotator NewRotation = FRotator(CurrentRot.Pitch, CurrentRot.Yaw + 60.f, CurrentRot.Roll);
		Owner->SetActorRotation(CurrentRot);

		isOpen = true;
	}
}

void UOpenDoor::CloseDoor()
{
	if (isOpen) {
		AActor * Owner = GetOwner();
		FRotator CurrentRot = Owner->GetActorRotation();

		CurrentRot.Yaw -= 60.f;

		//FRotator NewRotation = FRotator(CurrentRot.Pitch, CurrentRot.Yaw + 60.f, CurrentRot.Roll);
		Owner->SetActorRotation(CurrentRot);

		isOpen = false;
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll Trigger every frame
	// if actor that opens in trig volume then open door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (isOpen == true && GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay){
		CloseDoor();
	}
}

