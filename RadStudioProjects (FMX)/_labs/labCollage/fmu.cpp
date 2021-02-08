// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;

// ---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------
void Tfm::SelectionAll(TObject *Sender) {
	if (FSel != NULL) {
		FSel->HideSelection = true;
	}
	FSel = dynamic_cast<TSelection*>(Sender);
	if (FSel != NULL) {
		FSel->HideSelection = false;
	}
	tbOptions->Visible = (FSel != NULL);
	if (tbOptions->Visible) {
		trRotation->Value = FSel->RotationAngle;
	}
	tbImage->Visible = (FSel != NULL) && (dynamic_cast<TGlyph*>(FSel->Controls->Items[0]));

	tbRect->Visible = (FSel != NULL) && (dynamic_cast<TRectangle*>(FSel->Controls->Items[0]));
	if (tbRect->Visible) {
		ComboColorBoxRect->Color = ((TRectangle*)FSel->Controls->Items[0])->Fill->Color;
		trRectRadius->Value = ((TRectangle*)FSel->Controls->Items[0])->XRadius;
	}


}

void __fastcall Tfm::SelectionAllMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, float X, float Y) {
	SelectionAll(Sender);
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void __fastcall Tfm::FormCreate(TObject *Sender) {
	FSel = NULL;
    SelectionAll(ly);
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::buToFrontClick(TObject *Sender) {
	FSel->BringToFront();
	FSel->Repaint();

}
// ---------------------------------------------------------------------------

void __fastcall Tfm::buToBackClick(TObject *Sender) {
	FSel->SendToBack();
	FSel->Repaint();

}
// ---------------------------------------------------------------------------
void __fastcall Tfm::buDeleteClick(TObject *Sender)
{
	FSel->DisposeOf();
	FSel = NULL;
	SelectionAll(ly);
}
//----------------------------------------------------------------------------
void __fastcall Tfm::trRotationChange(TObject *Sender) {
	FSel->RotationAngle = trRotation->Value;
}
// ---------------------------------------------------------------------------
void __fastcall Tfm::buRNDClick(TObject *Sender)
{
	TGlyph *tmp = (TGlyph*)FSel->Controls->Items[0];
	tmp->ImageIndex = Random(il->Count);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buPrevClick(TObject *Sender)
{
	TGlyph *tmp = (TGlyph*)FSel->Controls->Items[0];
	tmp->ImageIndex = (tmp->ImageIndex <= 0) ? il->Count -1 : tmp->ImageIndex - 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNextClick(TObject *Sender)
{
	TGlyph *tmp = (TGlyph*)FSel->Controls->Items[0];
	tmp->ImageIndex = (tmp->ImageIndex >= il->Count - 1) ? 0 : tmp->ImageIndex + 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buNewImageClick(TObject *Sender)
{
	TSelection *me = new TSelection(ly);
	me->Parent = ly;
	me->GripSize = 8;
	me->Width = 50 + Random(100);
	me->Height = 50 + Random(100);
	me->Position->X = Random(ly->Width - me->Width);
	me->Position->Y = Random(ly->Height - me->Height);
	me->RotationAngle = Random(100) - 50;
	me->OnMouseDown = SelectionAllMouseDown;
	TGlyph *xGlyph = new TGlyph(me);
	xGlyph->Parent = me;
	xGlyph->Align = TAlignLayout::Client;
	xGlyph->Images = il;
	xGlyph->ImageIndex = Random(il->Count);
	SelectionAll(me);

	}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall Tfm::ComboColorBoxRectChange(TObject *Sender)
{
	TRectangle *tmp = static_cast<TRectangle *>(FSel->Controls->Items[0]);
	tmp->Fill->Color = ComboColorBoxRect->Color;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::trRectRadiusChange(TObject *Sender)
{
	TRectangle *tmp = static_cast<TRectangle *>(FSel->Controls->Items[0]);
	tmp->XRadius = trRectRadius->Value;
    tmp->YRadius = tmp->XRadius;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buClearClick(TObject *Sender)
{
	SelectionAll(ly);
	for (int i = ly->ControlsCount-1; i >= 0; i--) {
		if (dynamic_cast<TSelection *>(ly->Controls->Items[i])) {
			ly->RemoveObject(i);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buNewRectClick(TObject *Sender)
{
	TSelection *me = new TSelection(ly);
	me->Parent = ly;
	me->GripSize = 8;
	me->Width = 50 + Random(100);
	me->Height = 50 + Random(100);
	me->Position->X = Random(ly->Width - me->Width);
	me->Position->Y = Random(ly->Height - me->Height);
	me->RotationAngle = Random(100) - 50;
	me->OnMouseDown = SelectionAllMouseDown;
	TRectangle *xRect = new TRectangle(me);
	xRect->Parent = me;
	xRect->Align = TAlignLayout::Client;
	xRect->HitTest = false;
	xRect->XRadius = (float)Random(50);
	xRect->YRadius = xRect->XRadius;
	xRect->Fill->Color =
	TAlphaColorF::Create((float)Random(256), (float)Random(256),(float)Random(256)).ToAlphaColor();
	SelectionAll(me);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage(L"Created by Dmitry Yakuba");
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buLabelClick(TObject *Sender)
{
	UnicodeString nR[] = {"a","b","c","d","e","f","g"};
	TSelection *me = new TSelection(ly);
	me->Parent = ly;
	me->GripSize = 8;
	me->Width = 50 + Random(100);
	me->Height = 50 + Random(100);
	me->Position->X = Random(ly->Width - me->Width);
	me->Position->Y = Random(ly->Height - me->Height);
	me->RotationAngle = Random(100) - 50;
	me->OnMouseDown = SelectionAllMouseDown;
	TLabel * newLabel = new TLabel(me);
	newLabel->Parent = me;
	newLabel->RotationAngle = me->RotationAngle;
	newLabel->Align = TAlignLayout::Client;
	int Rand = Random(20);
	newLabel->TextSettings->Font->Size = 25;
	for (int i = Rand; i < Rand ; i++) {
		newLabel->Text += nR[RandomRange(0,8)];
	}

}
//---------------------------------------------------------------------------

