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

	AActor * Owner = GetOwner();
	FRotator CurrentRot = Owner->GetActorRotation();

	CurrentRot.Yaw += 60.f;

	//FRotator NewRotation = FRotator(CurrentRot.Pitch, CurrentRot.Yaw + 60.f, CurrentRot.Roll);
	Owner->SetActorRotation(CurrentRot);
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

