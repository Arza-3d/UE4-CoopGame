#include "..\Public\SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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

void ASWeapon::Fire(FHitResult& HitResult)
{
	AActor* owner = GetOwner();

	if (owner)
	{
		FVector start, end, shotDirection;
		{
			FVector eyeLocation;
			FRotator eyeRotator;
			owner->GetActorEyesViewPoint(eyeLocation, eyeRotator);

			start = eyeLocation;
			shotDirection = eyeRotator.Vector();
			end = eyeLocation + (shotDirection * 10000.0f);
		}

		{
			FCollisionQueryParams params;
			FCollisionResponseParams responseParam;
			params.AddIgnoredActor(owner);
			params.AddIgnoredActor(this);
			params.bTraceComplex = true;

			if (GetWorld()->LineTraceSingleByChannel(HitResult, start, end, ECC_Visibility, params, responseParam))
			{
				AActor* hitActor = HitResult.GetActor();

				UGameplayStatics::ApplyPointDamage(hitActor, 20.0f, shotDirection, HitResult, owner->GetInstigatorController(), this, DamageType);
			}

			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0f, 0, 1.0f);
		}
		
	}

	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

