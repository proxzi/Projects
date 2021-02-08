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
void __fastcall TForm1::angryClick(TObject *Sender)
{
	FCountAngry ++;
	LaAngry->Text = "Angry = " + IntToStr(FCountAngry);
	FloatAnimationCountCat->Start();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LaCleaverClick(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lynaClick(TObject *Sender)
{
	FCountLyna++;
	LaCleaver->Text = "Cleaver = " + IntToStr(FCountLyna);
	FloatAnimationCountLyna->Start();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
	FloatAnimationCat->StopValue = this->Width - angry->Width;
    FloatAnimationLyna->StopValue = this->Width - lyna->Width;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FloatAnimationCatProcess(TObject *Sender)
{
	if ((angry->Position->X == FloatAnimationCat->StartValue)
	||(angry->Position->X == FloatAnimationCat->StopValue) ) {
	angry->Bitmap->FlipHorizontal();

	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FloatAnimationLynaProcess(TObject *Sender)
{
	if ((lyna->Position->X == FloatAnimationCat->StartValue)
	||(lyna->Position->X == FloatAnimationCat->StopValue) ) {
	lyna->Bitmap->FlipHorizontal();

	}
}
//---------------------------------------------------------------------------

