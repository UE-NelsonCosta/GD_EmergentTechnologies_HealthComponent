#include "CPP_HealthComponent.h"

UCPP_HealthComponent::UCPP_HealthComponent()
{
	// This is a component that doesn't need a tick so lets disable it
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UCPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// This is here for now, but if you ever do anything serialization related you might not want this.
	Health = MaxHealth;
}

float UCPP_HealthComponent::GetHealth() const
{
	return Health;
}

float UCPP_HealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UCPP_HealthComponent::GetHealthAsPercentage() const
{
	return Health / MaxHealth;
}

void UCPP_HealthComponent::ModifyHealth(const float Amount)
{
	if(Amount == 0)
		return;
	
	Health += Amount;

	Amount > 0 ? OnDamageHealedEvent.Broadcast(Amount) : OnDamageTakenEvent.Broadcast(Amount);
}

void UCPP_HealthComponent::TakeDamage(const float Amount)
{
	if(Amount > 0)
	{
		Health -= Amount;

		OnDamageTakenEvent.Broadcast(Amount);
	}
}

void UCPP_HealthComponent::RecoverHealth(const float Amount)
{
	if(Amount > 0)
	{
		Health += Amount;

		OnDamageHealedEvent.Broadcast(Amount);
	}
}
