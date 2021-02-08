//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmuforAmount.h"
#include "dmu.h"
#include "fmu.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tffa *ffa;
//---------------------------------------------------------------------------
__fastcall Tffa::Tffa(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tffa::FormShow(TObject *Sender)
{
	dm->Connect();
}
//---------------------------------------------------------------------------
void __fastcall Tffa::btnokeyClick(TObject *Sender)
{
	dm->MenuOrder->FieldByName("Amount")->AsInteger = StrToInt(edAmount->Text);
    edAmount->Text = 1;
	Close();


}
//---------------------------------------------------------------------------

void __fastcall Tffa::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
    if (Key == VK_RETURN) {

		btnokeyClick(Sender);
	}
}
//---------------------------------------------------------------------------

