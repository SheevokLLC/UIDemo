#include "DUIHealthComponent.h"
#include "GameFramework/Actor.h"

#if WITH_EDITOR
#include "ObjectEditorUtils.h"
#endif //WITH_EDITOR

void UDUIHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* const OwningActor = GetOwner();
	if (OwningActor)
	{
		OwningActor->OnTakeAnyDamage.AddDynamic(this, &ThisClass::HandleTakeAnyDamage);
	}
}

void UDUIHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor* const OwningActor = GetOwner();
	if (OwningActor)
	{
		OwningActor->OnTakeAnyDamage.RemoveDynamic(this, &ThisClass::HandleTakeAnyDamage);
	}

	Super::EndPlay(EndPlayReason);
}

#if WITH_EDITOR

void UDUIHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName MaxHitPointsPropertyName = GET_MEMBER_NAME_CHECKED(ThisClass, MaxHitPoints);
	const FName HitPointsPropertyName = GET_MEMBER_NAME_CHECKED(ThisClass, HitPoints);
	if (PropertyChangedEvent.Property == StaticClass()->FindPropertyByName(MaxHitPointsPropertyName))
	{
		FObjectEditorUtils::MigratePropertyValue(this, MaxHitPointsPropertyName, this, HitPointsPropertyName);
	}
}

#endif //WITH_EDITOR

void UDUIHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	AActor* const OwningActor = GetOwner();
	if (!ensure(DamagedActor == OwningActor))
	{
		return;
	}

	HitPoints = FMath::Clamp(HitPoints - Damage, 0.0f , MaxHitPoints);
	OnHitPointsChangedEvent.Broadcast();

	if (HitPoints <= 0.0f)
	{
		OwningActor->Destroy();
	}
}