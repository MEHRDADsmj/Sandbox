// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// CTOR/DTOR & VIRTUAL FUNCTIONS

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = RotRate;
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
}

void ACharacterBase::MoveForward(float InVal)
{
	if (Controller && InVal != 0.0f)
	{
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator Yaw = FRotator{0.0f, ControlRotation.Yaw, 0.0f};
		FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, InVal);
	}
}

void ACharacterBase::MoveRight(float InVal)
{
	if (Controller && InVal != 0.0f)
	{
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator Yaw = FRotator{0.0f, ControlRotation.Yaw, 0.0f};
		FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, InVal);
	}
}
