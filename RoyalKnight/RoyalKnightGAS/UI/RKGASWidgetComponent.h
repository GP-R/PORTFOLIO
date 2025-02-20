#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "RKGASWidgetComponent.generated.h"

UCLASS()
class ROYALKNIGHTGAS_API URKGASWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
