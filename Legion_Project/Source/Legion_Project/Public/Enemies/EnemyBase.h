// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

USTRUCT(BlueprintType)
struct FEnemyVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float fEnemyHealth = 150.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float fDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float fAttackResetTime = 0.6f;
};

UCLASS()
class LEGION_PROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ApplyDamage(float fDamageIn);

	UFUNCTION(BlueprintCallable, Category = "Blueprint")
	FORCEINLINE float GetEnemyHealth() const { return EnemyVariables.fEnemyHealth; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EnemyWeak();

	UFUNCTION(BlueprintImplementableEvent, Category = "Blueprint")
	void TookDamage();

	virtual void EnemyDeath();

	virtual void EnemyMove();

	virtual void EnemyAttack();

	UPROPERTY(EditDefaultsOnly, Category = "EnemyVariables")
	FEnemyVariables EnemyVariables;
	
};
