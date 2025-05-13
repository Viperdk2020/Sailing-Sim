// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SailClothSimulation/Public/SailClothComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSailClothComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector3f();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent_NoRegister();
SAILCLOTHSIMULATION_API UClass* Z_Construct_UClass_USailClothComponent();
SAILCLOTHSIMULATION_API UClass* Z_Construct_UClass_USailClothComponent_NoRegister();
SAILCLOTHSIMULATION_API UScriptStruct* Z_Construct_UScriptStruct_FSailStrip();
UPackage* Z_Construct_UPackage__Script_SailClothSimulation();
// End Cross Module References

// Begin Class USailClothComponent Function GetSailStrips
struct Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics
{
	struct SailClothComponent_eventGetSailStrips_Parms
	{
		TArray<FSailStrip> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Sail Cloth" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * Get the current aerodynamic strips for debug or analysis.\n     */" },
#endif
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the current aerodynamic strips for debug or analysis." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSailStrip, METADATA_PARAMS(0, nullptr) }; // 0
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SailClothComponent_eventGetSailStrips_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 0
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USailClothComponent, nullptr, "GetSailStrips", nullptr, nullptr, Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::PropPointers), sizeof(Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::SailClothComponent_eventGetSailStrips_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::Function_MetaDataParams), Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::SailClothComponent_eventGetSailStrips_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USailClothComponent_GetSailStrips()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USailClothComponent_GetSailStrips_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USailClothComponent::execGetSailStrips)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FSailStrip>*)Z_Param__Result=P_THIS->GetSailStrips();
	P_NATIVE_END;
}
// End Class USailClothComponent Function GetSailStrips

// Begin Class USailClothComponent
void USailClothComponent::StaticRegisterNativesUSailClothComponent()
{
	UClass* Class = USailClothComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetSailStrips", &USailClothComponent::execGetSailStrips },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USailClothComponent);
UClass* Z_Construct_UClass_USailClothComponent_NoRegister()
{
	return USailClothComponent::StaticClass();
}
struct Z_Construct_UClass_USailClothComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Physics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Sail Cloth Simulation Component\n * Handles GPU-based cloth simulation and aerodynamic processing for sails.\n */" },
#endif
		{ "DisplayName", "Sail Cloth Simulation" },
		{ "IncludePath", "SailClothComponent.h" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sail Cloth Simulation Component\nHandles GPU-based cloth simulation and aerodynamic processing for sails." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProcMesh_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Procedural mesh component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Procedural mesh component" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProcMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USailClothComponent_GetSailStrips, "GetSailStrips" }, // 2137055701
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USailClothComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USailClothComponent_Statics::NewProp_ProcMesh = { "ProcMesh", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USailClothComponent, ProcMesh), Z_Construct_UClass_UProceduralMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProcMesh_MetaData), NewProp_ProcMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USailClothComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USailClothComponent_Statics::NewProp_ProcMesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USailClothComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USailClothComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_SailClothSimulation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USailClothComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USailClothComponent_Statics::ClassParams = {
	&USailClothComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USailClothComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USailClothComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USailClothComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_USailClothComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USailClothComponent()
{
	if (!Z_Registration_Info_UClass_USailClothComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USailClothComponent.OuterSingleton, Z_Construct_UClass_USailClothComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USailClothComponent.OuterSingleton;
}
template<> SAILCLOTHSIMULATION_API UClass* StaticClass<USailClothComponent>()
{
	return USailClothComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USailClothComponent);
USailClothComponent::~USailClothComponent() {}
// End Class USailClothComponent

// Begin ScriptStruct FSailStrip
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_SailStrip;
class UScriptStruct* FSailStrip::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_SailStrip.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_SailStrip.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSailStrip, (UObject*)Z_Construct_UPackage__Script_SailClothSimulation(), TEXT("SailStrip"));
	}
	return Z_Registration_Info_UScriptStruct_SailStrip.OuterSingleton;
}
template<> SAILCLOTHSIMULATION_API UScriptStruct* StaticStruct<FSailStrip>()
{
	return FSailStrip::StaticStruct();
}
struct Z_Construct_UScriptStruct_FSailStrip_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Aerodynamic strip data structure for VLM and debugging.\n */" },
#endif
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Aerodynamic strip data structure for VLM and debugging." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Normal_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Chord_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gamma_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cl_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Cd_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TwistAngleDeg_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SailTrimAngleDeg_MetaData[] = {
		{ "Category", "Sail Strip" },
		{ "ModuleRelativePath", "Public/SailClothComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Normal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Chord;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Gamma;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Cl;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Cd;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TwistAngleDeg;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SailTrimAngleDeg;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSailStrip>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Position), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Normal = { "Normal", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Normal), Z_Construct_UScriptStruct_FVector3f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Normal_MetaData), NewProp_Normal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Chord = { "Chord", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Chord), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Chord_MetaData), NewProp_Chord_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Gamma = { "Gamma", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Gamma), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gamma_MetaData), NewProp_Gamma_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Cl = { "Cl", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Cl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cl_MetaData), NewProp_Cl_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Cd = { "Cd", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, Cd), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Cd_MetaData), NewProp_Cd_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_TwistAngleDeg = { "TwistAngleDeg", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, TwistAngleDeg), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TwistAngleDeg_MetaData), NewProp_TwistAngleDeg_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_SailTrimAngleDeg = { "SailTrimAngleDeg", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSailStrip, SailTrimAngleDeg), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SailTrimAngleDeg_MetaData), NewProp_SailTrimAngleDeg_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSailStrip_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Normal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Chord,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Gamma,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Cl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_Cd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_TwistAngleDeg,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSailStrip_Statics::NewProp_SailTrimAngleDeg,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSailStrip_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSailStrip_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_SailClothSimulation,
	nullptr,
	&NewStructOps,
	"SailStrip",
	Z_Construct_UScriptStruct_FSailStrip_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSailStrip_Statics::PropPointers),
	sizeof(FSailStrip),
	alignof(FSailStrip),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSailStrip_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSailStrip_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSailStrip()
{
	if (!Z_Registration_Info_UScriptStruct_SailStrip.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_SailStrip.InnerSingleton, Z_Construct_UScriptStruct_FSailStrip_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_SailStrip.InnerSingleton;
}
// End ScriptStruct FSailStrip

// Begin Registration
struct Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FSailStrip::StaticStruct, Z_Construct_UScriptStruct_FSailStrip_Statics::NewStructOps, TEXT("SailStrip"), &Z_Registration_Info_UScriptStruct_SailStrip, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSailStrip), 827082293U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USailClothComponent, USailClothComponent::StaticClass, TEXT("USailClothComponent"), &Z_Registration_Info_UClass_USailClothComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USailClothComponent), 3078863675U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_1314122158(TEXT("/Script/SailClothSimulation"),
	Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Unreal_Projects_Sailing_Plugins_SailClothSimulation_Source_SailClothSimulation_Public_SailClothComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
