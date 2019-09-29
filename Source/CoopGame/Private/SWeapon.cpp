#include "..\Public\SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	AActor* owner = GetOwner();

	if (owner)
	{
		FVector start, end;
		{
			FVector eyeLocation;
			FRotator eyeRotator;
			owner->GetActorEyesViewPoint(eyeLocation, eyeRotator);

			start = eyeLocation;
			end = eyeLocation + (eyeRotator.Vector() * 10000.0f);
		}

		{
			FHitResult hitResult;
			
			{
				FCollisionQueryParams params;
				FCollisionResponseParams responseParam;
				params.AddIgnoredActor(owner);
				params.AddIgnoredActor(this);
				params.bTraceComplex = true;

				if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params, responseParam))
				{

				}
			}
			
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 8.0f, 0, 3.0f);
		}
		
	}

	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

