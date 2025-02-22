#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BentoItemData.generated.h"


UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBentoItemType : uint8
{
	None        = 0 UMETA(Hidden),  // Default empty state
	Consumable  = 1 << 0 UMETA(DisplayName = "Consumable"),
	Equipment   = 1 << 1 UMETA(DisplayName = "Equipment"),
	Material    = 1 << 2 UMETA(DisplayName = "Material"),

	All         = Consumable | Equipment | Material  UMETA(Hidden) // Convenience value
};
ENUM_CLASS_FLAGS(EBentoItemType);

UCLASS(BlueprintType)
class BENTO_API UBentoItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemId = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "EBentoItemType"), Category = "Item")
	int32 ItemType = static_cast<int32>(EBentoItemType::None);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 MaxStackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;
};
