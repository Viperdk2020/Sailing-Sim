#pragma once

#include "Blueprint/UserWidget.h"

#include "SailConfigWidget.generated.h"

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
class USailConfigWidget : public UUserWidget
{
    GENERATED_BODY()

public:
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
