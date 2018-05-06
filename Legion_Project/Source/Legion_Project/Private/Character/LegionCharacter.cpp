// Fill out your copyright notice in the Description page of Project Settings.

#include "LegionCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.h"

// Sets default values
ALegionCharacter::ALegionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set base numbers for variables
	fBaseTurnRate = 45.0f;
	fBaseLookUpRate = 45.0f;

	//Detach player rotation from camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Setup Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 0.0f; //Can't jump
	GetCharacterMovement()->AirControl = 0.0f;

	// Create a camera arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.0f;
	CameraArm->bUsePawnControlRotation = true; 

	//Create the Player camera
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	PlayerCam->bUsePawnControlRotation = false;

	//Create damage box
	DamageZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageZone"));
	DamageZone->SetupAttachment(RootComponent);
	DamageZone->bGenerateOverlapEvents = false;
	DamageZone->SetCollisionObjectType(ECC_WorldDynamic);
	DamageZone->SetCollisionResponseToAllChannels(ECR_Overlap);
	DamageZone->OnComponentBeginOverlap.AddDynamic(this, &ALegionCharacter::OnOverlapBegin);

}

// Called to bind functionality to input
void ALegionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALegionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALegionCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALegionCharacter::TurnAtRate);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALegionCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Attack",IE_Pressed, this, &ALegionCharacter::Attack);
}

// Called when the game starts or when spawned
void ALegionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALegionCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALegionCharacter::Attack()
{
	if (bCanAttack)
	{
		if (DamageZone)
		{
			DamageZone->bGenerateOverlapEvents = true;
		}

		StartedAttack();
		
		GetWorld()->GetTimerManager().SetTimer(AttackResetHandle, this, &ALegionCharacter::ResetAttack, PlayerVariables.fAttackResetTime, false);

		bCanAttack = false;
	}
}

void ALegionCharacter::ResetAttack()
{
	if (DamageZone)
	{
		DamageZone->bGenerateOverlapEvents = false;
	}

	FinishedAttack();

	bCanAttack = true;
}

void ALegionCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ALegionCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * fBaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALegionCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * fBaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALegionCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AActor* HitActor = OtherActor;

	AEnemyBase* Enemy = Cast<AEnemyBase>(HitActor);

	if (Enemy)
	{
		DamageZone->bGenerateOverlapEvents = false;

		Enemy->ApplyDamage(PlayerVariables.fDamage);
	}
}

// Called every frame
void ALegionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



