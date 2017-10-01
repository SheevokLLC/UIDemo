#pragma once

#include "DelegateCombinations.h"
#include "Components/ActorComponent.h"
#include "DUIHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FDUIOnHitPointsChanged)

UCLASS(BlueprintType, Meta = (BlueprintSpawnableComponent))
class UDUIHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR

private:
	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHitPoints;

	FDUIOnHitPointsChanged OnHitPointsChangedEvent;
};