// Copyright Grant Windes 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	FHitResult GetFirstPhsyicsBodyInReach();

private:
	UPROPERTY(EditAnywhere)
	float Reach = 150.f;

	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * InputComponent = nullptr;

	// ray-cast & grab what's in reach
	void Grab();
	void Release();

	void SetupInputComponent();
	void FindPhysicsHandleComponent();
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	
};
