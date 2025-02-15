// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaterpillarCaveFollowPoint.generated.h"

UCLASS()
class CATASTROPHE_API ACaterpillarCaveFollowPoint : public AActor
{
	GENERATED_BODY()
	
private:

	/** The trigger box that detect overlap with player character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultRoot;

	/** The trigger box that detect overlap with player character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EditorMesh;

public:	
	// Sets default values for this actor's properties
	ACaterpillarCaveFollowPoint();

protected:

	/**  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Gameplay | Cave", meta = (MakeEditWidget = "true"))
	TArray<FVector> CaterpillarFollowPoints;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Getter */
	FORCEINLINE TArray<FVector> GetCaterpillarFollowPoints() const { return CaterpillarFollowPoints; }

	/** Getter End */
};
