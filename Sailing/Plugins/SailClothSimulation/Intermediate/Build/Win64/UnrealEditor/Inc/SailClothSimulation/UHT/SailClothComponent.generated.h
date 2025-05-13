// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SailClothComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FSailStrip;
#ifdef SAILCLOTHSIMULATION_SailClothComponent_generated_h
#error "SailClothComponent.generated.h already included, missing '#pragma once' in SailClothComponent.h"
#endif
#define SAILCLOTHSIMULATION_SailClothComponent_generated_h

#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetSailStrips);


#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSailClothComponent(); \
	friend struct Z_Construct_UClass_USailClothComponent_Statics; \
public: \
	DECLARE_CLASS(USailClothComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SailClothSimulation"), NO_API) \
	DECLARE_SERIALIZER(USailClothComponent)


#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USailClothComponent(USailClothComponent&&); \
	USailClothComponent(const USailClothComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USailClothComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USailClothComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USailClothComponent) \
	NO_API virtual ~USailClothComponent();


#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_14_PROLOG
#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAILCLOTHSIMULATION_API UClass* StaticClass<class USailClothComponent>();

#define FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_75_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FSailStrip_Statics; \
	static class UScriptStruct* StaticStruct();


template<> SAILCLOTHSIMULATION_API UScriptStruct* StaticStruct<struct FSailStrip>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
