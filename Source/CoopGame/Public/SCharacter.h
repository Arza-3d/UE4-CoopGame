// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
//class USkeletalMeshComponent;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	float ZoomFOV = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming", Meta = (ClampMin = "0.1", ClampMax = "100"))
	float ZoomInterpSpeed = 3.f;

	float DefaultFOV;

private:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void StopCrouch();

	void BeginZoom();

	void EndZoom();
};
