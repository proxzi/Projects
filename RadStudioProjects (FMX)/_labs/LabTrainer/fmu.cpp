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
void Tfm::DoReset()
{
	FCountCorrect = 0;
	FCountWrong = 0;
	DoContinue();

}
void Tfm::DoContinue(){
	laCorrect->Text = Format(L"Верно = %d", ARRAYOFCONST((FCountCorrect)));
	laWrong->Text = Format(L"Неверно = %d", ARRAYOFCONST((FCountWrong)));

	int xValue1 = Random(20);
	int xValue2 = Random(20);
	int xSign = (Random(2) == 1) ? 1 : -1;
	int xResult = xValue1 + xValue2;
	int xResultNew = (Random(2) == 1) ? xResult : xResult + (Random(7) * xSign);

	FAnswerCorrect = (xResult == xResultNew);
	laCode->Text = Format("%d +%d = %d",
	ARRAYOFCONST((xValue1,xValue2,xResultNew)));
}
void Tfm::DoAnswer(bool aValue)
{
	(aValue == FAnswerCorrect) ? FCountCorrect ++ : FCountWrong++;
	DoContinue();

}
void __fastcall Tfm::buResetClick(TObject *Sender)
{
	DoReset();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buYesClick(TObject *Sender)
{
	DoAnswer(true);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buNoClick(TObject *Sender)
{
	DoAnswer(false);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage(L"labTrainer - Yakuba Dmitry");
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	Randomize();
    DoReset();
}
//---------------------------------------------------------------------------
