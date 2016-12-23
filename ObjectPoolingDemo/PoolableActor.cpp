#include "ObjectPoolingDemo.h"
#include "PoolableActor.h"

APoolableActor::APoolableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Create and position a mesh component for actor's visual representation */
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
	if (SphereVisualAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(SphereVisualAsset.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMesh->SetWorldScale3D(FVector(0.5f));
		StaticMesh->SetSimulatePhysics(false);
	}
	RootComponent = StaticMesh;
	SetActorEnableCollision(false);
}

void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
}

void APoolableActor::Tick(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + Velocity * Direction * DeltaTime);
	Super::Tick(DeltaTime);
}

void APoolableActor::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer, this, &APoolableActor::Deactivate, Lifespan, false);
}

bool APoolableActor::IsActive() {
	return Active;
}

void APoolableActor::SetActive(bool InpActive) {
	Active = InpActive;
	SetActorHiddenInGame(!InpActive);
}

/* workaround for lifespan timer callback not handling passing arguments */
void APoolableActor::Deactivate() {
	SetActive(false);
}

void APoolableActor::SetVelocity(float InVelocity)
{
	Velocity = InVelocity;
}

void APoolableActor::SetDirection(FVector InDirection)
{
	Direction = InDirection;
}