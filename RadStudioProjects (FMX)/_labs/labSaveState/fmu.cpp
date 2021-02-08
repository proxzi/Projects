//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;
//---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	TBinaryReader* x;
	if (SaveState->Stream->Size > 0) {
		x = new TBinaryReader(SaveState->Stream, TEncoding::UTF8, false);
		try {
		Edit1->Text = x->ReadString();
		DateEdit1->Date = x->ReadDouble();
		TimeEdit1->Time = x->ReadDouble();
		TrackBar1->Value = x->ReadDouble();
		Switch1->IsChecked = x->ReadDouble();
		TabControl1->ActiveTab = TabControl1->Tabs[x->ReadDouble()];
		}
		__finally{
            x->DisposeOf();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormSaveState(TObject *Sender)
{
	TBinaryReader* x;
	SaveState->Stream->Clear();
	x = new TBinaryWritet(SaveState->Stream);
	try {
		x->Write(Edit1->Text);
        x->Write(DateEdit1->Date.Val);
	}
}
//---------------------------------------------------------------------------
