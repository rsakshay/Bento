#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BentoItemType.h"
#include "BentoBagData.generated.h"

// ------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FBentoBagSlot
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bento|Bag", meta = (Bitmask, BitmaskEnum = "EBentoItemType"))
	int32 AllowedItemTypes = static_cast<int32>(EBentoItemType::All);
};

// ------------------------------------------------------------------
UCLASS(BlueprintType)
class BENTO_API UBentoBagData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UBentoBagData();
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	// Unique ID for this bag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bento|Bag")
	FName BagId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bento|Bag", meta = (ClampMin = "1"))
	int32 SlotCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bento|Bag", meta = (Bitmask, BitmaskEnum = "EBentoItemType"))
	int32 DefaultAllowedItemTypes = static_cast<int32>(EBentoItemType::All);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bento|Bag")
	TArray<FBentoBagSlot> SlotInfo;
};