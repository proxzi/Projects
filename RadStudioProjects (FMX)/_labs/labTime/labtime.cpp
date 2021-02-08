//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "labtime.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BustartClick(TObject *Sender)
{
	if (t == 0) {
		FTimeStart = Now();
		Tm->Enabled = true;
		Bustop->Text = "Пауза";
	}
	if (t == 1) {
	  Tm->Enabled = true;
	  Bustop->Text = "Пауза";
      t = 0;
	}


}
//---------------------------------------------------------------------------
void __fastcall TForm1::BustopClick(TObject *Sender)
{
	Bustop->Text = "Стоп";
	t+=1;
	Tm->Enabled = false;
	if (t == 2) {
		t = 0;
		Latime->Text = "0:00:00";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TmTimer(TObject *Sender)
{
	//Latime->Text = TimeToStr(Now() - FTimeStart);
	UnicodeString x;
	DateTimeToString(x, L"h:nn:ss.zzz", Now() - FTimeStart);
	Latime->Text = x.Delete(x.Length() - 1,2);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



