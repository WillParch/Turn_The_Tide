#include "RollableDieActor.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "PhysicsEngine/PhysicalMaterial.h"

// Sets default values
ARollableDieActor::ARollableDieActor()
{
    // Enable Tick function
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach a Static Mesh Component
    DieMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DieMesh"));
    RootComponent = DieMesh;

    // Enable physics for the die
    DieMesh->SetSimulatePhysics(true);

    // Adjust physics properties using Chaos Physics Material
    AdjustPhysicsProperties();

    // Initialize face-up value
    FaceUpValue = 1;
}

// Called when the game starts or when spawned
void ARollableDieActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ARollableDieActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the face-up value each frame (optional, can be triggered manually)
    FaceUpValue = CalculateFaceUpValue();
}

// Rolls the die by applying a random force and torque
void ARollableDieActor::RollDie()
{
    // Generate random forces to simulate rolling
    FVector RandomForce = FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), FMath::RandRange(500, 1000));
    FVector RandomTorque = FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), FMath::RandRange(-500, 500));

    // Apply the impulse and torque
    DieMesh->AddImpulse(RandomForce, NAME_None, true);
    DieMesh->AddTorqueInRadians(RandomTorque, NAME_None, true);
}

// Gets the current face-up value of the die
int ARollableDieActor::GetFaceUpValue() const
{
    return FaceUpValue;
}

// Adjusts the physics properties of the die using Chaos Physics Material
void ARollableDieActor::AdjustPhysicsProperties()
{
    if (!DieMesh) return;

    // Create a new Chaos Physics Material
    UPhysicalMaterial* PhysicsMaterial = NewObject<UPhysicalMaterial>();
    if (PhysicsMaterial)
    {
        PhysicsMaterial->Friction = 1.0f;      // Higher friction to reduce sliding
        PhysicsMaterial->Restitution = 0.1f;   // Lower restitution for reduced bounciness

        // Assign the material to the static mesh
        DieMesh->SetPhysMaterialOverride(PhysicsMaterial);
    }
}

// Calculates the face-up value based on the die's orientation
int ARollableDieActor::CalculateFaceUpValue() const
{
    // Get the die's "up" vector
    FVector UpVector = DieMesh->GetUpVector();

    // Map the orientation to a face number
    if (FVector::DotProduct(UpVector, FVector::UpVector) > 0.9f) return 1;   // Top face is 1
    if (FVector::DotProduct(UpVector, -FVector::UpVector) > 0.9f) return 6;  // Bottom face is 6
    if (FVector::DotProduct(UpVector, FVector::RightVector) > 0.9f) return 3;  // Right face is 3
    if (FVector::DotProduct(UpVector, -FVector::RightVector) > 0.9f) return 4; // Left face is 4
    if (FVector::DotProduct(UpVector, FVector::ForwardVector) > 0.9f) return 2; // Forward face is 2
    if (FVector::DotProduct(UpVector, -FVector::ForwardVector) > 0.9f) return 5; // Back face is 5

    return -1; // Error case
}

