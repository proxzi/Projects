//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Tr->Value = 30;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Tr->Value = 60;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Tr->Value = 120;
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Tr->Value = 180;
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Tr->Value -=10;
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Tr->Value +=10;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::TrChange(TObject *Sender)
{
	im->RotationAngle = Tr->Value;
	la->Text = FloatToStr(Tr->Value);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Tr_oChange(TObject *Sender)
{
	im->Opacity = Tr_o->Value;
    la_o->Text = FloatToStr(Tr_o->Value);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HClick(TObject *Sender)
{
	im->Bitmap->FlipHorizontal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VClick(TObject *Sender)
{
    im->Bitmap->FlipVertical();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::la_oClick(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::laClick(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------
