#include "SailConfigWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/ExpandableArea.h"
#include "Components/ScrollBox.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/SpinBox.h"
#include "Components/Button.h"
#include <Components/CanvasPanel.h>



void USailConfigWidget::NativeConstruct()
{
    Super::NativeConstruct();

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

    // Helper: add a grid of fields to a vertical box
    auto AddGrid = [&](UVerticalBox* Container, const TArray<FFieldDef>& Fields) {
        UGridPanel* Grid = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
        Container->AddChildToVerticalBox(Grid);
        for (int32 Row = 0; Row < Fields.Num(); ++Row)
        {
            const FFieldDef& FD = Fields[Row];
            // Label
            UTextBlock* TB = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
            TB->SetText(FText::FromString(FD.Label));
            Grid->AddChildToGrid(TB, Row, 0);
            // SpinBox
            USpinBox* SBx = WidgetTree->ConstructWidget<USpinBox>(USpinBox::StaticClass());
            SBx->SetMinValue(FD.Min);
            SBx->SetMaxValue(FD.Max);
            SBx->SetDelta(FD.Delta);
            SBx->SetValue(*static_cast<float*>(FD.Ptr));
            SBx->OnValueChanged.AddDynamic(this, &USailConfigWidget::OnSpinBoxValueChanged);
            Grid->AddChildToGrid(SBx, Row, 1);
        }
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

template<typename T>
void USailConfigWidget::BindSpinBox(USpinBox* Spin, T* ValuePtr)
{
    // Initialize
    Spin->SetValue(*ValuePtr);
    // When user changes value, write back to the struct
  //  Spin->OnValueChanged.AddLambda([ValuePtr](float NewVal) {
  //      *ValuePtr = NewVal;
  //      });
}

void USailConfigWidget::OnSpinBoxValueChanged(float NewValue)
{
    OnConfigChanged();
}

void USailConfigWidget::HandleGenerateClicked()
{
    OnGenerateRequested();
}
