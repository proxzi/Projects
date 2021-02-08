//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include "dmu.h"
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
	tc->TabPosition = TTabPosition::None;
    tc->ActiveTab = tilist;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::FormShow(TObject *Sender)
{
    dm->FDConnection->Connected = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buAddClick(TObject *Sender)
{
	dm->taNotes->Append();
}
//---------------------------------------------------------------------------
void __fastcall Tfm::lvItemClick(TObject *Sender)
{
	dm->taNotes->Edit();
	tc->GotoVisibleTab(tiItem->Index);

}
//---------------------------------------------------------------------------
void __fastcall Tfm::buSaveClick(TObject *Sender)
{
	dm->taNotes->Post();
	tc->GotoVisibleTab(tilist->Index);

}
//---------------------------------------------------------------------------
void __fastcall Tfm::buCancelClick(TObject *Sender)
{
	dm->taNotes->Cancel();
	tc->GotoVisibleTab(tilist->Index);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buDelClick(TObject *Sender)
{
    dm->taNotes->Delete();
	tc->GotoVisibleTab(tilist->Index);
}
