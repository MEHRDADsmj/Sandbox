// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "CharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SANDBOX_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	// CTOR/DTOR & VIRTUAL FUNCTIONS
public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Equivalent of ConstructionScript in blueprint
	virtual void OnConstruction(const FTransform& Transform) override;

	// FUNCTIONS
public:
	UFUNCTION(Category= "Input")
	void MoveForward(float InVal);

	UFUNCTION(Category= "Input")
	void MoveRight(float InVal);

	UFUNCTION(Category= "Input")
	void TargetLock();

	// PROPERTIES
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	float TargetDetectionRange = 1000.0f;

	bool IsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	TSubclassOf<AActor> TargetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties")
	FRotator RotRate = FRotator{0.0f, 720.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components")
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Components")
	USphereComponent* TargetDetector;
};
