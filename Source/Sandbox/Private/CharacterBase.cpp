// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

// Sets default values
ACharacterBase::ACharacterBase() : TargetClass{nullptr}, Target{nullptr}, CameraSpringArm{nullptr}, Camera{nullptr}, TargetDetector{nullptr}, LeftPunch{nullptr}, RightFoot{nullptr}
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);
	Camera->bUsePawnControlRotation = false;

	TargetDetector = CreateDefaultSubobject<USphereComponent>(TEXT("TargetSphere"));
	TargetDetector->SetupAttachment(RootComponent);

	LeftPunch = CreateDefaultSubobject<USphereComponent>(TEXT("LeftPunch"));
	LeftPunch->SetupAttachment(GetMesh());

	RightFoot = CreateDefaultSubobject<USphereComponent>(TEXT("RightFoot"));
	RightFoot->SetupAttachment(GetMesh());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocked)
		if (Target)
		{
			if ((Target->GetActorLocation() - GetActorLocation()).Size() > TargetDetectionRange)
				TargetLock();
			else
			{
				const FVector TargetLocation = Target->GetActorLocation();
				const FRotator Direction = (TargetLocation - this->GetActorLocation()).ToOrientationRotator();
				Controller->SetControlRotation(Direction);
			}
		}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::Jump);
	PlayerInputComponent->BindAction("TargetLock", IE_Pressed, this, &ACharacterBase::TargetLock);
	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &ACharacterBase::LightAttack);
	PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &ACharacterBase::HeavyAttack);
}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
	TargetDetector->SetSphereRadius(TargetDetectionRange);
	GetCharacterMovement()->RotationRate = RotRate;

	LeftPunch->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("LeftPunch"));
	RightFoot->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightFoot"));
}

// FUNCTIONS

void ACharacterBase::MoveForward(float InVal)
{
	if (Controller && InVal != 0.0f)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator Yaw = FRotator{0.0f, ControlRotation.Yaw, 0.0f};
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, InVal);
	}
}

void ACharacterBase::MoveRight(float InVal)
{
	if (Controller && InVal != 0.0f)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator Yaw = FRotator{0.0f, ControlRotation.Yaw, 0.0f};
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, InVal);
	}
}

void ACharacterBase::TargetLock()
{
	if (IsLocked)
	{
		IsLocked = false;
		Target = nullptr;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	if (TargetClass)
	{
		TArray<AActor*> ActorsInRange;
		TargetDetector->GetOverlappingActors(ActorsInRange, TargetClass);

		for (uint8 Index = 0; Index < ActorsInRange.Num(); Index++)
			if (ActorsInRange[Index] != this && ActorsInRange[Index]->ActorHasTag(FName("PossibleTarget")))
			{
				//TODO: When the Sphere components of two base characters collide, the rotation of the player would change and that's a bug
				Target = ActorsInRange[Index];
				IsLocked = true;
				GetCharacterMovement()->bOrientRotationToMovement = false;
				bUseControllerRotationYaw = true;
				break;
			}
	}
}

void ACharacterBase::DoLightDamage()
{
	TArray<AActor*> Actors;
	LeftPunch->GetOverlappingActors(Actors);
	const TSubclassOf<UDamageType> DamageType;	
	UE_LOG(LogTemp, Warning, TEXT("%d"), Actors.Num());
	if (Actors.Num() > 1 && Actors[1] && Actors[1] != this)
		UGameplayStatics::ApplyDamage(Actors[1], LightDamage, GetController(), this, DamageType);
}

void ACharacterBase::DoHeavyDamage()
{
	TArray<AActor*> Actors;
	RightFoot->GetOverlappingActors(Actors);
	const TSubclassOf<UDamageType> DamageType;
	if (Actors.Num() > 1 && Actors[1] && Actors[1] != this)
		UGameplayStatics::ApplyDamage(Actors[1], LightDamage * 3, GetController(), this, DamageType);
}
