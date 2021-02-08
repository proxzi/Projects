//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmuCNT.h"
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



void __fastcall Tfm::acConnectExecute(TObject *Sender)
{
	IdTCPClient->Host = edHost->Text;
	IdTCPClient->Port = StrToInt(edPort->Text);
	IdTCPClient->Connect();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::acDisconnectExecute(TObject *Sender)
{
	IdTCPClient->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::acGetTimeExecute(TObject *Sender)
{
	IdTCPClient->Socket->WriteLn("time");
	UnicodeString x;
	x = IdTCPClient->Socket->ReadLn();
	me->Lines->Add(x);
}
//---------------------------------------------------------------------------

void __fastcall Tfm::acGetStrExecute(TObject *Sender)
{
	IdTCPClient->Socket->WriteLn("str");
	UnicodeString x;
	x = IdTCPClient->Socket->ReadLn(IndyTextEncoding_UTF8());
	me->Lines->Add(x);
}
//---------------------------------------------------------------------------


void __fastcall Tfm::acGetImageExecute(TObject *Sender)
{
	IdTCPClient->Socket->WriteLn("image");
	TMemoryStream *x = new TMemoryStream();
	try {
		int xSize = IdTCPClient->Socket->ReadInt64();
		IdTCPClient->Socket->ReadStream(x, xSize);
        im->Bitmap->LoadFromStream(x);
	}
	__finally{
        delete x;
    }

}
//---------------------------------------------------------------------------
void __fastcall Tfm::acGetVersionExecute(TObject *Sender)
{
	IdTCPClient->Socket->WriteLn("ver");
	UnicodeString x;
	x = IdTCPClient->Socket->ReadLn();
	me->Lines->Add(x);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buFileClick(TObject *Sender)
{
						   //

}
//---------------------------------------------------------------------------

void __fastcall Tfm::alUpdate(TBasicAction *Action, bool &Handled)
{
	edHost->Enabled = ! IdTCPClient->Connected();
	edPort->Enabled = ! IdTCPClient->Connected();
	acConnect->Enabled = ! IdTCPClient->Connected();
	acDisconnect->Enabled = IdTCPClient->Connected();
	acGetTime->Enabled = IdTCPClient->Connected();
	acGetStr->Enabled = IdTCPClient->Connected();
	acGetImage->Enabled = IdTCPClient->Connected();
	acGetVersion->Enabled = IdTCPClient->Connected();
}
//---------------------------------------------------------------------------


