// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyBase::ApplyDamage(float fDamageIn)
{
	EnemyVariables.fEnemyHealth = EnemyVariables.fEnemyHealth - fDamageIn;

	TookDamage();

	if (EnemyVariables.fEnemyHealth <= 0)
	{
		EnemyDeath();
	}
}

void AEnemyBase::EnemyWeak()
{
}

void AEnemyBase::EnemyDeath()
{
	Destroy();
}

void AEnemyBase::EnemyMove()
{
}

void AEnemyBase::EnemyAttack()
{
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




