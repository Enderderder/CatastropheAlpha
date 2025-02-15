// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UseableItem.generated.h"

UCLASS()
class CATASTROPHE_API AUseableItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUseableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Called to use item
	 * @author James Johnstone
	 */
	UFUNCTION(BlueprintCallable)
	virtual void UseAbility();
};
