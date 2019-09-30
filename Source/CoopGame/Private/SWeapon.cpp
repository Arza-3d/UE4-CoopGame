#include "..\Public\SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
//#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles\WorldPSCPool.h"
#include "Particles\ParticleSystemComponent.h"

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

void ASWeapon::Fire(FHitResult& Hit)
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

			bool hitSomething = GetWorld()->LineTraceSingleByChannel(Hit, start, end, ECC_Visibility, params, responseParam);
			if (hitSomething)
			{
				AActor* hitActor = Hit.GetActor();

				UGameplayStatics::ApplyPointDamage(hitActor, 20.0f, shotDirection, Hit, owner->GetInstigatorController(), this, DamageType);

				if (HitEffect)
				{	
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), FVector(1.f), true);
				}

				if (MuzzleEffect)
				{
					UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
				}
			}

			//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0f, 0, 1.0f);
			if (TracerEffect)
			{
				FVector muzzleSocketLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

				UParticleSystemComponent* tracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, muzzleSocketLocation);
				if (tracerComp)
				{
					FVector target = (hitSomething) ? Hit.ImpactPoint : end;
					tracerComp->SetVectorParameter(TracerTargetName, target);
				}
			}
		}
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

