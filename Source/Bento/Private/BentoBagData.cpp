#include "BentoBagData.h"

// ------------------------------------------------------------------
// ------------------------------------------------------------------
UBentoBagData::UBentoBagData()
{
	SlotInfo.SetNum(SlotCount);

	for (FBentoBagSlot& Slot : SlotInfo)
	{
		Slot.AllowedItemTypes = DefaultAllowedItemTypes;
	}	
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
void UBentoBagData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
	(PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UBentoBagData, SlotCount)))
	{
		int32 const iDiff = SlotCount - SlotInfo.Num();
		if( iDiff > 0 )
		{
			SlotInfo.Reserve(SlotCount);
			for( int32 i = SlotInfo.Num(); i < SlotCount; ++i )
			{
				SlotInfo.AddDefaulted_GetRef().AllowedItemTypes = DefaultAllowedItemTypes;
			}
		}
		else
		{
			SlotInfo.SetNumUninitialized(SlotCount);
		}
	}
}
