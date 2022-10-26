#include "CPP_HealthRegenComponent.h"

#include "CPP_HealthComponent.h"

UCPP_HealthRegenComponent::UCPP_HealthRegenComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCPP_HealthRegenComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!GetOwner())
		return;
	
	healthComponent = Cast<UCPP_HealthComponent>(GetOwner()->GetComponentByClass(UCPP_HealthComponent::StaticClass()));
	if(!healthComponent)
	{
		// TODO: Log Of Some Sort
		PrimaryComponentTick.bCanEverTick = false;
		return;
	}

	healthComponent->OnDamageTakenEvent.AddUFunction(this, "OnHealthComponentDamageTaken");
}


// Called every frame
void UCPP_HealthRegenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(DelayBeforeHealing > 0)
	{
		FString output = " Delaying Heal! Timer: " + FString::SanitizeFloat( DelayBeforeHealing );
		GEngine->AddOnScreenDebugMessage(10,1,FColor::Red, output );
		
		DelayBeforeHealing -= DeltaTime;
		return;
	}

	if(healthComponent)
	{
		healthComponent->RecoverHealth(HealPerSecond * DeltaTime);

		FString output = " Applying Heal Of: " + FString::SanitizeFloat( HealPerSecond * DeltaTime );
		GEngine->AddOnScreenDebugMessage(11,1,FColor::Green, output );
	}
}

void UCPP_HealthRegenComponent::OnHealthComponentDamageTaken(float amount)
{
	DelayBeforeHealing = MaxDelayBeforeHealing;
}

