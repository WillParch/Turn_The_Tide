#include "MyPlayerController.h"
#include "RollableDieActor.h"
#include "GameFramework/InputSettings.h" // Include for input binding
#include "Engine/World.h"
#include "GameFramework/PlayerInput.h"
#include "EngineUtils.h"
// Constructor
AMyPlayerController::AMyPlayerController()
{
	// Default constructor
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent(); // Call parent function to ensure proper initialization

	// Ensure InputComponent exists before binding
	if (InputComponent)
	{
		// Bind the RollDie function to the "R" key
		InputComponent->BindAction("RollDie", IE_Pressed, this, &AMyPlayerController::RollDie);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent is NULL!"));
	}
}

void AMyPlayerController::RollDie()
{
	if (!DieActor)
	{
		// Find the first die in the level
		for (TActorIterator<ARollableDieActor> It(GetWorld()); It; ++It)
		{
			DieActor = *It;
			break;
		}
	}

	// If we have a valid die, roll it
	if (DieActor)
	{
		DieActor->RollDie();

		// Log the face-up value
		int FaceValue = DieActor->GetFaceUpValue();
		UE_LOG(LogTemp, Log, TEXT("Face-Up Value: %d"), FaceValue);
	}
}

