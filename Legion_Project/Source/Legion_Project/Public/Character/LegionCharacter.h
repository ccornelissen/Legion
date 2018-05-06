// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LegionCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

USTRUCT(BlueprintType)
struct FPlayerVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerHeatlh = 150.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float fDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float fAttackResetTime = 0.6f;
};

UCLASS()
class LEGION_PROJECT_API ALegionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALegionCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float fBaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float fBaseLookUpRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//GETTERS
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraArm; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return PlayerCam; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Blueprint")
	void StartedAttack();

	UFUNCTION(BlueprintImplementableEvent, Category = "Blueprint")
	void FinishedAttack();

	void Attack();

	void ResetAttack();

	FTimerHandle AttackResetHandle;

	bool bCanAttack = true;

	/** Called for side to side input */
	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	UPROPERTY(EditDefaultsOnly, Category = "Player Variables")
	FPlayerVariables PlayerVariables;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm = nullptr;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCam = nullptr;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DamageZone = nullptr;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
