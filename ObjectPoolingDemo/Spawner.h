#pragma once

#include "PoolableActor.h"
#include "ObjectPoolerComponent.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class OBJECTPOOLINGDEMO_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();
	virtual void BeginPlay() override;

private:
	FVector GetRandomPointInVolume();
	float GetLifespan();

	/* spawner's bounding box */
	class UBoxComponent* SpawnVolume;

	/* object pooler component */
	UPROPERTY(EditAnywhere, Category = "Spawner")	
	UObjectPoolerComponent* ObjectPooler;

	/* pooled objects lifespan properties */
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float LifespanMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float LifespanMax  = 5.0f;

	/* time between spawns */
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;

	/* turns spawner into a crude 'firework / sparkler' system */
	UPROPERTY(EditAnywhere, Category = "Spawner")
	bool SparklingMode = false;

	/* sparkles velocity */
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SparklesVelocity = 100.f;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();
};
