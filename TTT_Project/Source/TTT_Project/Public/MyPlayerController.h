#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ARollableDieActor;

UCLASS()
class TTT_PROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	// Correct override of SetupInputComponent
	virtual void SetupInputComponent() override;

	// Function to roll the die when pressing a key
	void RollDie();

private:
	// Reference to the die actor in the level
	UPROPERTY()
	ARollableDieActor* DieActor;
};
