#include "ObjectPoolingDemo.h"
#include "ObjectPoolerComponent.h"

UObjectPoolerComponent::UObjectPoolerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UObjectPoolerComponent::BeginPlay()
{
	if (PooledObjectSubclass != NULL)
	{
		/* Check for a valid World */
		UWorld* const World = GetWorld();
		if (World) {
			/* Spawn objects, make them 'inactive' and add them to pool */
			for (int i = 0; i < PoolSize; i++) {
				APoolableActor* PoolableActor = World->SpawnActor<APoolableActor>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
			}
		}
	}
	Super::BeginPlay();
}

APoolableActor * UObjectPoolerComponent::GetPooledObject()
{
	for (APoolableActor* PoolableActor : Pool)
	{
		if ( ! PoolableActor->IsActive()) {
			return PoolableActor;
		}
	}
	/* pool is drained, no inactive objects found */
	return nullptr;
}

