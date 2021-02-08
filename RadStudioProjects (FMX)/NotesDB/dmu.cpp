//---------------------------------------------------------------------------


#pragma hdrstop

#include "dmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma resource "*.dfm"
Tdm *dm;
//---------------------------------------------------------------------------
__fastcall Tdm::Tdm(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tdm::FDConnectionAfterConnect(TObject *Sender)
{
	FDConnection->ExecSQL(
		" CREATE TABLE IF NOT EXISTS [Notes]("
		" [Caption] VARCHAR(50) NOT NULL,"
		" [Priority] SMALLINT NOT NULL,"
		" [Detail] VARCHAR(500))"
	);
	taNotes->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tdm::FDConnectionBeforeConnect(TObject *Sender)
{
#ifdef _Windows
	"..\\..\\" + cNameDB;
#else
	Ioutils::TPath::GetDocumentsPath() + PathDelim + cNameDB;
#endif
}
//---------------------------------------------------------------------------

