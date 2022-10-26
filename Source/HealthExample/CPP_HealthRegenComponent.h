#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_HealthRegenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHEXAMPLE_API UCPP_HealthRegenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_HealthRegenComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHealthComponentDamageTaken(float amount);

	UPROPERTY()
	class UCPP_HealthComponent* healthComponent = nullptr;

	// Variable That Ticks Down
	float DelayBeforeHealing = 0.0f;

	UPROPERTY(EditAnywhere)
	float MaxDelayBeforeHealing = 1.0f;

	UPROPERTY(EditAnywhere)
	float HealPerSecond = 10.0f;
};
