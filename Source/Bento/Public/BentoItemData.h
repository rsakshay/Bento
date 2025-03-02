#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BentoItemType.h" 
#include "BentoItemData.generated.h"

// ------------------------------------------------------------------
// Data Asset representing an item in the inventory system.
// ------------------------------------------------------------------
UCLASS(BlueprintType)
class BENTO_API UBentoItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Unique identifier for the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item")
	FName ItemId = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "EBentoItemType"), Category = "Bento|Item")
	int32 ItemType = static_cast<int32>(EBentoItemType::None);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item")
	bool bUnlimitedStack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item", meta = (EditCondition = "!bUnlimitedStack", ClampMin = 1))
	int32 MaxStackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item")
	TObjectPtr<UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bento|Item")
	FText ItemDescription;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("BentoItem"), ItemId);
	}
};