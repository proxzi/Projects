//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmufornumbertable.h"
#include "fmu.h"
#include "dmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tffnt *ffnt;
//---------------------------------------------------------------------------
__fastcall Tffnt::Tffnt(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tffnt::FormShow(TObject *Sender)
{
	dm->Connect();
}
//---------------------------------------------------------------------------
void __fastcall Tffnt::btnokeyClick(TObject *Sender)
{
	dm->Orders->FieldByName("NumberTable")->AsInteger = StrToInt(edAmount->Text);
    edAmount->Text = 1;
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tffnt::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
    if (Key == VK_RETURN) {

		btnokeyClick(Sender);
	}
}
//---------------------------------------------------------------------------

