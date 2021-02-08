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
void __fastcall Tfm::Player_1Click(TObject *Sender)
{
	I_p1->Position->X += 5;
	Check();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Player_2Click(TObject *Sender)
{
	I_p2->Position->X += 5;
    Check();
}

void Tfm::Check()
{
	if((I_p1->Position->X + I_p1->Width) >= (this->Width)){
		ShowMessage(L"Победил зеленый");
		tc->ActiveTab = Start;
	}
	else if((I_p2->Position->X + I_p2->Width) >= (this->Width))
	{
		ShowMessage(L"Победил синий");
		tc->ActiveTab = Start;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->TabPosition = TTabPosition::None;
	tc->ActiveTab = Start;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::Button1Click(TObject *Sender)
{
	tc->ActiveTab = Game;
	Reset();
}

void Tfm::Reset()
{
	I_p1->Position->X = 0;
	I_p2->Position->X = 0;
}
//---------------------------------------------------------------------------

