#include "ObjectPoolingDemo.h"
#include "Spawner.h"
#include "Kismet/KismetMathLibrary.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Spawner's extents */
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	/* Object pooler component */
	ObjectPooler = CreateDefaultSubobject<UObjectPoolerComponent>(TEXT("ObjectPooler"));
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawner::Spawn, SpawnCooldown, false);
}

/* find random point within the collision box extents */
FVector ASpawner::GetRandomPointInVolume() {
	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

float ASpawner::GetLifespan() {
	return UKismetMathLibrary::RandomFloatInRange(LifespanMin, LifespanMax);
}

void ASpawner::Spawn()
{
	APoolableActor* PoolableActor = ObjectPooler->GetPooledObject();
	
	/* pool is drained */
	if (PoolableActor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawner::Spawn, SpawnCooldown, false);
		return;
	}
	
	FVector ActorLocation;
	float SparklesVelocityTmp;
	FVector SparklesDirectionTmp;

	/* if sparkling mode is enabled all objects would spawn from the center of the spawner and will have a velocity outwards*/
	if (SparklingMode) {
		ActorLocation = SpawnVolume->Bounds.Origin;
		SparklesVelocityTmp = SparklesVelocity;
		SparklesDirectionTmp = UKismetMathLibrary::RandomUnitVector();
	}
	/* otherwise objects should spawn randomly within the spawn box extents */
	else {
		ActorLocation = GetRandomPointInVolume();
		SparklesVelocityTmp = 0;
		SparklesDirectionTmp = FVector().ZeroVector;
	}

	PoolableActor->SetActorLocation(ActorLocation);
	PoolableActor->SetLifeSpan(GetLifespan());
	PoolableActor->SetActive(true);
	PoolableActor->SetVelocity(SparklesVelocity);
	PoolableActor->SetDirection(SparklesDirectionTmp);

	/* setup next spawn call within a given cooldown */
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawner::Spawn, SpawnCooldown, false);
}
