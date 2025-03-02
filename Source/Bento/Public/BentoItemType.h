#pragma once

#include "CoreMinimal.h"
#include "BentoItemType.generated.h"

/** Bitfield enum representing item types */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBentoItemType : uint8
{
	None          = 0 UMETA(Hidden),
	Consumable    = 1 << 0 UMETA(DisplayName = "Consumable"),
	Equipment     = 1 << 1 UMETA(DisplayName = "Equipment"),
	Material      = 1 << 2 UMETA(DisplayName = "Material"),
	Miscellaneous = 1 << 3 UMETA(DisplayName = "Miscellaneous"),
	All           = Consumable | Equipment | Material | Miscellaneous UMETA(Hidden)
};
ENUM_CLASS_FLAGS(EBentoItemType);