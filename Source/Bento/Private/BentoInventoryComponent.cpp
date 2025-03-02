// ReSharper disable CppUseStructuredBinding
#include "BentoInventoryComponent.h"

// ------------------------------------------------------------------
// ------------------------------------------------------------------
UBentoInventoryComponent::UBentoInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
void UBentoInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// ------------------------------------------------------------------
// ------------------------------------------------------------------
bool UBentoInventoryComponent::AddBag(UBentoBagData* BagAsset)
{
	if (!BagAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bento] AddBag failed: Invalid bag asset."));
		return false;
	}

	FBentoBagInstance& NewBag = Bags.AddDefaulted_GetRef();
	if (BagAsset)
	{
		NewBag.BagAsset = BagAsset;
		NewBag.Slots.SetNum(BagAsset->SlotCount);
	}

	UE_LOG(LogTemp, Log, TEXT("[Bento] Added bag: %s"), *BagAsset->GetName());
	return true;
}


// ------------------------------------------------------------------
// ------------------------------------------------------------------
bool UBentoInventoryComponent::RemoveBag(int32 BagIndex)
{
	if (!Bags.IsValidIndex(BagIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bento] RemoveBag failed: Bag Index was Invalid."));
		return false;
	}

	Bags.RemoveAt(BagIndex);

	UE_LOG(LogTemp, Log, TEXT("[Bento] Removed bag at index: %d"), BagIndex);
	return true;
}


// ------------------------------------------------------------------
// ------------------------------------------------------------------
EBentoInventoryAddResult UBentoInventoryComponent::AddItem(UBentoItemData* Item, int32 const Amount)
{
	ensureAlwaysMsgf(Item, TEXT("[Bento] Removing Item but Item was Invalid"));
	if (!Item)
	{
		return EBentoInventoryAddResult::Failure_InvalidItem;
	}

	check(Amount > 0);
	int32 AmountLeft = Amount;

	auto AddAmountToSlot = [&AmountLeft, &Item](FBentoItemStack& Slot)
	{
		if(Slot.Quantity + AmountLeft > Item->MaxStackSize)
		{
			Slot.Quantity = Item->MaxStackSize;
			AmountLeft -= Item->MaxStackSize;
		}
		else
		{
			Slot.Quantity += AmountLeft;
			AmountLeft -= 0;
		}	
	};
	
	for(FBentoBagInstance& Bag : Bags)
	{
		FBentoItemStack* SlotWithItem = nullptr;
    	for(FBentoItemStack& Slot : Bag.Slots)
    	{
    		UBentoItemData const* SlotItemData = Slot.ItemData.Get();
    		if(SlotItemData != Item)
    			continue;
    		SlotWithItem = &Slot;
    	}
		if(SlotWithItem)
		{
			AddAmountToSlot(*SlotWithItem);
			break;
		}
	}

	if(AmountLeft)
	{
		for(FBentoBagInstance& Bag : Bags)
		{
			for(FBentoItemStack& Slot : Bag.Slots)
			{
				if(!Slot.ItemData)
				{
					Slot.ItemData = Item;
					AddAmountToSlot(Slot);
					break;
				}
			}
		}
	}

	if(AmountLeft == Amount) return EBentoInventoryAddResult::Failure_OutOfSpace;
	
	return AmountLeft ? EBentoInventoryAddResult::Success_PartialAdds : EBentoInventoryAddResult::Success;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
EBentoInventoryRemoveResult UBentoInventoryComponent::RemoveItem(int32 const BagIndex, int32 const SlotIndex,
	EBentoInventoryRemoveOption const RemoveOption)
{
	if (!Bags.IsValidIndex(BagIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bento] RemoveItem failed: Bag Index was Invalid."));
		return EBentoInventoryRemoveResult::Failure_InvalidBagIndex;
	}

	if(!Bags[BagIndex].Slots.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bento] RemoveItem failed: Slot Index was Invalid."));
		return EBentoInventoryRemoveResult::Failure_InvalidSlotIndex;
	}

	FBentoItemStack& Slot = Bags[BagIndex].Slots[SlotIndex];
	switch(RemoveOption)
	{
		case EBentoInventoryRemoveOption::RemoveSingle:
		{
			if(--Slot.Quantity == 0)
			{
				Slot.ItemData = nullptr;
			}
		} break;
		
		case EBentoInventoryRemoveOption::RemoveStack:
		{
			Slot.Quantity = 0;
			Slot.ItemData = nullptr;
		} break;
	}

	return EBentoInventoryRemoveResult::Success;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
TArray<FBentoBagInstance> UBentoInventoryComponent::GetBags() const
{
	return Bags;
}