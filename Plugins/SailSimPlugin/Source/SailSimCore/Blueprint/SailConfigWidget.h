#pragma once

#include "CoreMinimal.h"                        // always first
#include "Blueprint/UserWidget.h"               // for UUserWidget
#include "SailConfigWidget.generated.h"         // must exactly match this filename



USTRUCT(BlueprintType)
struct FSailGeometrySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "4", ClampMin = "4"))
    int32 HorizontalSegs = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "4", ClampMin = "4"))
    int32 VerticalPanels = 12;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LuffLength = 9.20f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FootLength = 2.65f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "0.5"))
    float HeadWidthRatio = 0.15f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.05", ClampMax = "0.25"))
    float MaxDraftPct = 0.12f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.2", ClampMax = "0.6"))
    float MaxDraftPos = 0.40f;
};

USTRUCT(BlueprintType)
struct FClothTweakSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1"))
    float BendStiffness = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1"))
    float StretchStiffness = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "10"))
    float AirDrag = 1.0f;
};

UCLASS(Abstract, Blueprintable)
class SAILSIMCORE_API USailConfigWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /** Called whenever the user changes a value in the UI */
    UFUNCTION(BlueprintImplementableEvent, Category = "Sail")
    void OnConfigChanged();

    /** How tight the sail should be, 0–1 in the UI slider */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sail",
        meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
    float SailTension = 0.5f;

    // mainsail + jib settings exposed to Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sail")
    FSailGeometrySettings MainGeom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sail")
    FSailGeometrySettings JibGeom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth")
    FClothTweakSettings  MainCloth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth")
    FClothTweakSettings  JibCloth;

    /** BlueprintImplementable – called when “Generate” pressed */
    UFUNCTION(BlueprintImplementableEvent, Category = "Sail")
    void OnGenerateRequested();
};
