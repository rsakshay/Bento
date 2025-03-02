// Copyright Epic Games, Inc. All Rights Reserved.

#include "Bento.h"

#define LOCTEXT_NAMESPACE "FBentoModule"

// ------------------------------------------------------------------
// ------------------------------------------------------------------
void FBentoModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("Bento Module Started!"));
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
void FBentoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Warning, TEXT("Bento Module Started!"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBentoModule, Bento)