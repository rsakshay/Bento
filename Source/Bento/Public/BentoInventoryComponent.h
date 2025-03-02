#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BentoItemData.h"
#include "BentoBagData.h"
#include "BentoInventoryComponent.generated.h"

// ------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FBentoItemStack
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bento|Inventory")
    TObjectPtr<UBentoItemData> ItemData = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bento|Inventory")
    int32 Quantity = 0;
};

// ------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FBentoBagInstance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBentoBagData> BagAsset = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FBentoItemStack> Slots;
};

// ------------------------------------------------------------------
UENUM(BlueprintType)
enum class EBentoInventoryAddResult : uint8
{
    Success                UMETA(DisplayName = "Success"),
    Success_PartialAdds    UMETA(DisplayName = "Partial Success"),
    Failure_OutOfSpace     UMETA(DisplayName = "Out of Space"),
    Failure_InvalidItem    UMETA(DisplayName = "Invalid Item"),
};

// ------------------------------------------------------------------
UENUM(BlueprintType)
enum class EBentoInventoryRemoveResult : uint8
{
    Success                     UMETA(DisplayName = "Success"),
    Failure_InvalidBagIndex     UMETA(DisplayName = "Invalid Bag"),
    Failure_InvalidSlotIndex    UMETA(DisplayName = "Invalid Bag slot"),
};

// ------------------------------------------------------------------
UENUM(BlueprintType)
enum class EBentoInventoryRemoveOption : uint8
{
    RemoveSingle            UMETA(DisplayName = "Remove Single"),
    RemoveStack             UMETA(DisplayName = "Remove Stack"),
};

// ------------------------------------------------------------------
// Inventory manager component
// ------------------------------------------------------------------
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BENTO_API UBentoInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBentoInventoryComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Bento|Inventory")
    bool AddBag(UBentoBagData* BagAsset);

    UFUNCTION(BlueprintCallable, Category = "Bento|Inventory")
    bool RemoveBag(int32 BagIndex);
    
    UFUNCTION(BlueprintCallable, Category = "Bento|Inventory")
    EBentoInventoryAddResult AddItem(UBentoItemData* Item, int32 const Amount);

    UFUNCTION(BlueprintCallable, Category = "Bento|Inventory")
    EBentoInventoryRemoveResult RemoveItem(int32 const BagIndex, int32 const SlotIndex,
        EBentoInventoryRemoveOption const RemoveOption);
    
    UFUNCTION(BlueprintCallable, Category = "Bento|Inventory")
    TArray<FBentoBagInstance> GetBags() const;
private:
    UPROPERTY()
    TArray<FBentoBagInstance> Bags;
};