#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollableDieActor.generated.h"

UCLASS()
class TTT_PROJECT_API ARollableDieActor : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	ARollableDieActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Rolls the die
	void RollDie();

	// Gets the face-up value of the die
	int GetFaceUpValue() const;

private:
	// Static mesh for the die
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* DieMesh;

	// Adjusts physics properties of the die
	void AdjustPhysicsProperties();

	// Calculates the face-up value based on orientation
	int CalculateFaceUpValue() const;

	// Current face-up value
	int FaceUpValue;
};
