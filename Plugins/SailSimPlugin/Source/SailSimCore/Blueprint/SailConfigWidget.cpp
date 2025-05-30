#include "SailConfigWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/ExpandableArea.h"
#include "Components/ScrollBox.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/SpinBox.h"
#include "Widgets/Input/SSpinBox.h"  // for SSpinBox<>::FOnValueChanged
#include "Components/Button.h"
#include <Components/CanvasPanel.h>


void USailConfigWidget::AddGrid(UWidget* Parent, const TArray<FFieldDef>& Fields)
{
    // Create a GridPanel and attach it
    UGridPanel* Grid = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass(), TEXT("GridPanel"));
    if (UPanelWidget* Panel = Cast<UPanelWidget>(Parent))
    {
        Panel->AddChild(Grid);
    }

    for (int32 Row = 0; Row < Fields.Num(); ++Row)
    {
        const FFieldDef& FD = Fields[Row];
        float* ValuePtr = static_cast<float*>(FD.Ptr);

        // --- Label ---
        UTextBlock* Label = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), *FString::Printf(TEXT("Label_%s"), *FD.Label));
        Label->SetText(FText::FromString(FD.Label));
        Grid->AddChildToGrid(Label, Row, 0);

        // --- SpinBox ---
        USpinBox* Spin = WidgetTree->ConstructWidget<USpinBox>(USpinBox::StaticClass(), *FString::Printf(TEXT("Spin_%s"), *FD.Label));
        Spin->SetMinValue(FD.Min);
        Spin->SetMaxValue(FD.Max);
        Spin->SetDelta(FD.Delta);
        Spin->SetValue(*ValuePtr);

        // Bind the *dynamic* delegate so each spinbox writes directly into your struct
        Spin->OnValueChanged.AddDynamic(this, &USailConfigWidget::OnSpinBoxValueChanged);

        Grid->AddChildToGrid(Spin, Row, 1);
    }
}

void USailConfigWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Super::NativeConstruct();

    // Now hook up any runtime-only events, e.g. your Generate button:
    if (UButton* Btn = Cast<UButton>(WidgetTree->FindWidget(TEXT("Btn_Generate"))))
    {
        Btn->OnClicked.AddDynamic(this, &USailConfigWidget::OnGenerateRequested);
    }

    // 1) Root Canvas
    UCanvasPanel* RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
    WidgetTree->RootWidget = RootCanvas;

    // 2) Sized container
    USizeBox* SB = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), TEXT("RootSizeBox"));
    SB->SetWidthOverride(1000.f);
    SB->SetHeightOverride(900.f);
    RootCanvas->AddChild(SB);

    // 3) Vertical flow
    UVerticalBox* VB = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("VB_Main"));
    SB->AddChild(VB);

    // 4) Helper: add an ExpandableArea + VerticalBox body
    auto AddSection = [&](FText Title, FName Name) {
        UExpandableArea* EA = WidgetTree->ConstructWidget<UExpandableArea>(UExpandableArea::StaticClass(), Name);
        EA->SetIsExpanded(true);
        VB->AddChildToVerticalBox(EA);
        // Create a vertical box for the body
        FName ContentName = FName(*(Name.ToString() + TEXT("_Content")));
        UVerticalBox* EAContent = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), ContentName);
        // Set as the body slot
        EA->SetContentForSlot("Body", EAContent);
        return EAContent;
    };

  
   
  
    UVerticalBox* MainsailBox = AddSection(FText::FromString("Mainsail Geometry"), TEXT("EA_Mainsail"));
    UVerticalBox* JibBox = AddSection(FText::FromString("Jib Geometry"), TEXT("EA_Jib"));
    UVerticalBox* ClothBox = AddSection(FText::FromString("Cloth Tweaks"), TEXT("EA_Cloth"));

    // 5) Grid of spin‐boxes
    TArray<FFieldDef> SailFields = {
        {TEXT("Luff Length (m)"),   &MainGeom.LuffLength,   0.f,20.f,0.01f},
        {TEXT("Foot Length (m)"),   &MainGeom.FootLength,   0.f,20.f,0.01f},
        // ... add more fields as needed ...
    };
   
    
    AddGrid(MainsailBox, SailFields);

    // ... repeat for JibBox and ClothBox as needed ...

    // 6) Generate button
    UButton* Btn = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Btn_Generate"));
    UTextBlock* Txt = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Txt->SetText(FText::FromString("Generate / Reimport"));
    Btn->AddChild(Txt);
    VB->AddChildToVerticalBox(Btn);
    Btn->OnClicked.AddDynamic(this, &USailConfigWidget::HandleGenerateClicked);
}

void USailConfigWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    // Build in the UMG Designer and once at runtime before Construct
    if (!bHasBuiltDesignerView)
    {
        BuildAllSections();
        bHasBuiltDesignerView = true;
    }
}


void USailConfigWidget::OnSpinBoxValueChanged(float NewValue)
{
    OnConfigChanged();
}

void USailConfigWidget::BuildAllSections()
{
    // 1) Clear any existing tree (designer reload can call this multiple times)
    if (WidgetTree->RootWidget)
    {
       // WidgetTree->RootWidget->ClearChildren();
    }

    // 2) Root Canvas
    UCanvasPanel* RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
    WidgetTree->RootWidget = RootCanvas;

    // 3) SizeBox
    USizeBox* SB = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), TEXT("RootSizeBox"));
    SB->SetWidthOverride(1000.f);
    SB->SetHeightOverride(900.f);
    RootCanvas->AddChild(SB);

    // 4) VerticalBox
    UVerticalBox* VB = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("VB_Main"));
    SB->AddChild(VB);

    // 5) Helper to add each section
    auto AddSection = [&](FText Title, const FName& Name) -> UScrollBox*
        {
            UExpandableArea* EA = WidgetTree->ConstructWidget<UExpandableArea>(UExpandableArea::StaticClass(), Name);
         //   EA->SetAreaTitle(Title);
            EA->SetIsExpanded(true);
            VB->AddChild(EA);

            UScrollBox* Scroll = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), (TEXT("_Scroll")));
         //   EA->SetBodyContent(Scroll);
            return Scroll;
        };

    UScrollBox* MainsailBox = AddSection(FText::FromString("Mainsail Geometry"), TEXT("EA_Mainsail"));
    UScrollBox* JibBox = AddSection(FText::FromString("Jib Geometry"), TEXT("EA_Jib"));
    UScrollBox* ClothBox = AddSection(FText::FromString("Cloth Tweaks"), TEXT("EA_Cloth"));

    // 6) Field definitions
    struct FFieldDef { FString Label; void* Ptr; float Min, Max, Delta; };
    TArray<FFieldDef> SailFields = {
        {TEXT("Luff Length (m)"),   &MainGeom.LuffLength,   0.f,20.f,0.01f},
        {TEXT("Foot Length (m)"),   &MainGeom.FootLength,   0.f,20.f,0.01f},
        /* … other mainsail fields … */
    };
    TArray<FFieldDef> JibFields = {
        {TEXT("Luff Length (m)"),   &JibGeom.LuffLength,     0.f,20.f,0.01f},
        /* … other jib fields … */
    };
    TArray<FFieldDef> ClothFields = {
        {TEXT("Bend Stiffness"),     &MainCloth.BendStiffness,    0.f,1.f,0.01f},
        /* … other cloth fields … */
    };

    auto AddGrid = [&](UPanelWidget* Parent, const TArray<FFieldDef>& Fields)
        {
            UGridPanel* Grid = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
            Parent->AddChild(Grid);

            for (int32 Row = 0; Row < Fields.Num(); ++Row)
            {
                const FFieldDef& FD = Fields[Row];
                float* ValuePtr = static_cast<float*>(FD.Ptr);

                // Label
                UTextBlock* TB = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
                TB->SetText(FText::FromString(FD.Label));
                Grid->AddChildToGrid(TB, Row, 0);

                // SpinBox
                USpinBox* SBx = WidgetTree->ConstructWidget<USpinBox>(USpinBox::StaticClass());
                SBx->SetMinValue(FD.Min);
                SBx->SetMaxValue(FD.Max);
                SBx->SetDelta(FD.Delta);
                SBx->SetValue(*ValuePtr);

                // Native delegate: write new value into your struct
             //   SBx->OnValueChanged(  // Note: this is the native SSpinBox delegate 
             //       SSpinBox<float>::FOnValueChanged::CreateLambda(
             //           [ValuePtr](float NewVal) { *ValuePtr = NewVal; }
             //       )
            //    );

                Grid->AddChildToGrid(SBx, Row, 1);
            }
        };

    AddGrid(MainsailBox, SailFields);
    AddGrid(JibBox, JibFields);
    AddGrid(ClothBox, ClothFields);

    // 7) Generate button
    UButton* Btn = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Btn_Generate"));
    UTextBlock* Txt = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
    Txt->SetText(FText::FromString("Generate / Reimport"));
    Btn->AddChild(Txt);
    VB->AddChild(Btn);
}

void USailConfigWidget::HandleGenerateClicked()
{
    OnGenerateRequested();
}
