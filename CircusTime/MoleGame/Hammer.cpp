#include "MoleGame/Hammer.h"

AHammer::AHammer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHammer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHammer::Init(AMoleGame* NewMoleGame)
{
	MoleGame = NewMoleGame;
}

void AHammer::Hit_Implementation()
{

}