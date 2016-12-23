#pragma once

#include "PoolableActor.h"

#include "Components/ActorComponent.h"
#include "ObjectPoolerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTPOOLINGDEMO_API UObjectPoolerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectPoolerComponent();
	virtual void BeginPlay() override;

	APoolableActor* GetPooledObject();

private:
	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	TSubclassOf<class APoolableActor> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	int PoolSize = 200;

	TArray<APoolableActor*> Pool;
};
