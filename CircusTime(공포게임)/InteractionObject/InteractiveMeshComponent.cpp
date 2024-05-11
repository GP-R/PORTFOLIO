// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveMeshComponent.h"

#include "Kismet/GameplayStatics.h"

UInteractiveMeshComponent::UInteractiveMeshComponent()
{
    bInteractLock = true;
    this->SetCollisionProfileName(TEXT("InteractiveActor"));

    FScriptDelegate HighLightDelegate;
    FScriptDelegate EndHighLightDelegate;

    HighLightDelegate.BindUFunction(this, "HighLightMesh");
    EndHighLightDelegate.BindUFunction(this, "EndHighLightMesh");

    OnHighLight.Add(HighLightDelegate);
    OnEndHighLight.Add(EndHighLightDelegate);
}

void UInteractiveMeshComponent::HighLightMesh()
{
    if (bInteractLock)
    {
        return;
    }
}

void UInteractiveMeshComponent::EndHighLightMesh()
{
    if (bInteractLock)
    {
        return;
    }
}

bool UInteractiveMeshComponent::GetInteractLockState()
{
    return bInteractLock;
}

void UInteractiveMeshComponent::SetInteractLockState(bool bValue)
{
    bInteractLock = bValue;
}