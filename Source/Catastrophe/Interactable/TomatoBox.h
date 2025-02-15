// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TomatoBox.generated.h"

/**
 * This is an interactable object that allow player grab a tomato in his hand
 */
UCLASS()
class CATASTROPHE_API ATomatoBox : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TomatoBoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ItemSack")
	TSubclassOf<class ATomatoSack> TomatoSackClass;

public:
	// Sets default values for this actor's properties
	ATomatoBox();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TomatoBox")
	bool bRestoreAllTomatoOneTime = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called when the player interact, restore tomato to the player */
	UFUNCTION()
	void PickUpTomato(class APlayerCharacter* _playerCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "TomatoBox", meta = (DisplayName = "OnPickupTomato"))
	void Receive_PickUpTomato();
};
