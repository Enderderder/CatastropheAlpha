// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "Guard.generated.h"


class UPrimitiveComponent;
class APlayerCharacter;

/**
 * The enum that stores the state of the guard character
 */
UENUM(BlueprintType)
enum class EGuardState : uint8 
{
	STATIONARY = 0,
	SLEEPING,
	WAKEUP_STAGEONE,
	WAKEUP_STAGETWO,
	PATROLLING,
	INVESTATING,
	CHASING,
	SEARCHING,
	STUNED,
};

/**
 * This character is the main enemy that trying to guard around places and catches the player
 */
UCLASS()
class CATASTROPHE_API AGuard : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HeadHitbox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HeadShotTargetAnchor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HeadShotTargetMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BodyHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CatchHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HearingTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* AlertMarkMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* QuestionMarkMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ZzzMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponents", meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* HeadLight;

public:
	// Sets default values for this character's properties
	AGuard();
	
	/** The default state of the guard when it spawns in to the world */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guard | Behaviour | General")
	EGuardState PreferNeutralState = EGuardState::STATIONARY;

	/** Determine if the guard will walk around in his patrol location */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guard | Behaviour | Patrol")
	bool bHasPatrolBehaviour = true;

	/** The patrol way points of the guard, need to enable PatrolBehaviour to use them */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Guard | Behaviour | Patrol", meta = (MakeEditWidget = "true"))
	TArray<FVector> PatrolLocations;

	/** Previous state of the vision on player */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Guard | Behaviour | General")
	bool bPlayerWasInSight = false;

	/** Vision is on the player */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Guard | Behaviour | General")
	bool bPlayerInSight = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Guard | Behaviour | Sleep")
	bool bPlayerInSleepDetectRange = false;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Guard | Controller")
	class AGuardAiController* GuardController;

	UPROPERTY(BlueprintReadWrite, Category = "Guard | Animation")
	class UGuardAnimInstance* GuardAnimInstance;

	UPROPERTY(BlueprintReadWrite, Category = "Guard | References")
	class APlayerCharacter* PlayerRef;

	UPROPERTY(BlueprintReadOnly, Category = "Guard | References")
	class ACatastropheMainGameMode* CatastropheGameMode;

	UPROPERTY(BlueprintReadOnly, Category = "Guard | General")
	FTransform DefaultTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Movement")
	float PatrolSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Movement")
	float ChaseSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Perception")
	float PatrolSightRange = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Perception")
	float ChasingSightRange = 2500.0f;
	
	/** This is the range on top of the sight range */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Perception")
	float LosingSightRange = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Chase")
	float TimeToFullyAlert = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Stun")
	float MaxStunTime = 5.0f;

	/** This is the min radius each time when the guard perform a random location search  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Searching")
	float SearchRadiusMin = 100.0f;

	/** This is the max radius each time when the guard perform a random location search  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | Stats | Searching")
	float SearchRadiusMax = 150.0f;

	/** Head light color at normal state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | General")
	FColor NormalHeadLightColor = FColor::White;

	/** Head light color at alert state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | General")
	FColor AlertedHeadLightColor = FColor::Yellow;

	/** Head light color at spotted state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Guard | General")
	FColor SpottedHeadLightColor = FColor::Red;

private:

	/** Store the state of the guard */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Guard | Behaviour | General", meta = (AllowPrivateAccess = "true"))
	EGuardState GuardState;

	/** The timer handle for stun mechanic */
	UPROPERTY(BlueprintReadWrite, Category = "Guard | Behaviour | Stun", meta = (AllowPrivateAccess = "true"))
	FTimerHandle StunTimerHnadle;
	
	/** The timer handle for wake up stage one */
	UPROPERTY(BlueprintReadWrite, Category = "Guard | Behaviour | Sleep", meta = (AllowPrivateAccess = "true"))
	FTimerHandle WakeUpStageOneTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** BlueprintNativeEvent that gets the perception location and rotation of the character */
	UFUNCTION(BlueprintNativeEvent, Category = "AIPerception | Character")
	void GetPerceptionLocRot(FVector& Location, FRotator& Rotation) const;
	virtual void GetPerceptionLocRot_Implementation(FVector& Location, FRotator& Rotation) const;

	/** Called when the state of the guard changes */
	UFUNCTION(BlueprintNativeEvent, Category = "Guard | Behaviour | General")
	void OnGuardStateChange(EGuardState _oldState, EGuardState _newState);
	virtual void OnGuardStateChange_Implementation(EGuardState _oldState, EGuardState _newState);

	/** Called when guard state switch to stun */
	UFUNCTION()
	virtual void OnStunBegin();
	UFUNCTION(BlueprintImplementableEvent, Category = "Guard | Behaviour | Stun", meta = (DisplayName = "OnStunBegin"))
	void Receive_OnStunBegin();

	/** Called when guard state switch to stun */
	UFUNCTION()
	virtual void OnStunEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "Guard | Behaviour | Stun", meta = (DisplayName = "OnStunEnd"))
	void Receive_OnStunEnd();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Guard | General", meta = (DisplayName = "OnSendingPlayerToJail"))
	void Receive_OnSendingPlayerToJail();

	/** Called when the catch hit box overlap */
	UFUNCTION()
	virtual void OnCatchHitBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called  when actor is detroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Called to get the eye view point of the character */
	virtual void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;

	/**
	 * Sets the state of the guard then modify the character value base on the state
	 * @author Richard Wulansari
	 * @param The new state of the guard
	 */
	UFUNCTION(BlueprintCallable, Category = "Guard | Behaviour | General")
	void SetGuardState(EGuardState _newState);

	/**
	 * Sets the guards maximum walk speed
	 * @note This will overwrite the character movement component MaxWalkSpeed
	 */
	UFUNCTION(BlueprintCallable, Category = "Guard | Stats")
	void SetGuardMaxSpeed(float _speed);

	/** BLueprint function, Show the alert indicator or not */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Guard | Animation")
	void ToggleAlertIndicator(bool _b);

	/** BLueprint function, Show the  question mark indicator or not */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Guard | Animation")
	void ToggleQuestionIndicator(bool _b);

	/** Blueprint function, Show the Zzz indicator or not */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Guard | Animation")
	void ToggleZzzIndicator(bool _b);

	/** Stops all the montages that this character is playing */
	UFUNCTION(BlueprintCallable, Category = "Guard | Animation")
	void StopAllMontages();

	/** Look around behaviour */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Guard | Animation")
	void LookAround(float& out_montageTime);
	virtual void LookAround_Implementation(float& out_montageTime);

	/** Called when the guard caught the player */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Guard | General")
	void OnCatchPlayer(APlayerCharacter* _player);
	virtual void OnCatchPlayer_Implementation(APlayerCharacter* _player);

	/**
	 * Called the guard successfully caught the player
	 * @author Richard Wualansari
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Guard | General")
	void OnCatchPlayerSuccess();
	virtual void OnCatchPlayerSuccess_Implementation();

	/**
	 * Called the guard failed to catch the player
	 * @author Richard Wulansari
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Guard | General")
	void OnCatchPlayerFailed();
	virtual void OnCatchPlayerFailed_Implementation();

	/** Called to reset everything of the guard */
	UFUNCTION(BlueprintCallable, Category = "Guard | General")
	void ResetGuard();

	/**
	 * Sets the controller reference of the guard
	 * @author Richard Wulansari
	 * @param _controller The Ai controller that possesing the guard
	 */
	void SetGuardControllerRef(class AGuardAiController* _controller) {
		GuardController = _controller;
	}

	/** Sets the prefered neutral state of the guard */
	void SetPreferNeutralState(EGuardState _state) { PreferNeutralState = _state; }

	/** Getter */
	FORCEINLINE EGuardState GetGuardState() const { return GuardState; }
	FORCEINLINE EGuardState GetPreferNeutralState() const { return PreferNeutralState; }
	FORCEINLINE class AGuardAiController* GetGuardController() const { return GuardController; }
	/** Getter End */

private:
	
	/**
	 * Delegate bind function called whenever player is aiming and un-aim
	 */
	UFUNCTION()
	void OnPlayerAimingBegin();
	UFUNCTION()
	void OnPlayerAimingEnd();

};
