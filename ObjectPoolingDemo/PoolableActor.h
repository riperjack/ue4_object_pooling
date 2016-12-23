#pragma once

#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

UCLASS()
class OBJECTPOOLINGDEMO_API APoolableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APoolableActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetLifeSpan(float InLifespan) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return StaticMesh; }

	void SetActive(bool InpActive);
	bool IsActive();

	/* velocity and direction for 'sparkling mode' */
	void SetVelocity(float InVelocity);
	void SetDirection(FVector InDirection);

protected:
	/* actor's visual representation */
	class UStaticMeshComponent* StaticMesh;
	float Lifespan = 5.0f;
	FTimerHandle LifespanTimer;
	bool Active;
	float Velocity = 100.0f;
	FVector Direction;

	void Deactivate();
};