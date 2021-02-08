//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FMMenu.h"
#include "FMGame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TmenuForm *menuForm;
//---------------------------------------------------------------------------
__fastcall TmenuForm::TmenuForm(TComponent* Owner)
	: TForm(Owner)
	, fieldNumber(9)
{
}
//---------------------------------------------------------------------------
void __fastcall TmenuForm::trbChangeFieldSizeChange(TObject *Sender)
{
	#ifdef _WIN32
		fieldNumber = trbChangeFieldSize->Value * 3 + 9;
	#else
		fieldNumber = trbChangeFieldSize->Value + 9;
	#endif

	lblShowFieldSize->Text = Format( "%d X %d", ARRAYOFCONST((fieldNumber,fieldNumber)));
}
//----------------------------+-----------------------------------------------

int TmenuForm::getFieldNumber()
{
	return fieldNumber;
}

bool TmenuForm::getPlayerStatus()
{
	return rbPlayer->IsChecked;
}

void __fastcall TmenuForm::btnStartClick(TObject *Sender)
{
	gameForm->Show();
}
void __fastcall TmenuForm::FormShow(TObject *Sender)
{
	gameForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TmenuForm::FormCreate(TObject *Sender)
{
	#ifdef _WIN32
		rbPlayer->IsChecked = false;
		rbClick->IsChecked = true;
		StyleBook = sbWin;
	#else
		rbPlayer->IsChecked = false;
		rbPlayer->Visible = false;
		rbClick->Visible = false;
		StyleBook = sbAndroid;
	#endif
}
//---------------------------------------------------------------------------

