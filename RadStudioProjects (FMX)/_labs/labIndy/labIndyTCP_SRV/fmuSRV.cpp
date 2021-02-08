// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmuSRV.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;

// ---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::buStartClick(TObject *Sender) {
	IdTCPServer->Active = true;
	me->Lines->Add("Active = true");
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::buStopClick(TObject *Sender) {
	IdTCPServer->Active = false;
	me->Lines->Add("Active = false");
}

// ---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerConnect(TIdContext *AContext) {
	me->Lines->Add(Format("[%s] - Client Connected",
		ARRAYOFCONST((AContext->Connection->Socket->Binding->PeerIP))));
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerDisconnect(TIdContext *AContext) {
	me->Lines->Add(Format("[%s] - Client Disconnected",
		ARRAYOFCONST((AContext->Connection->Socket->Binding->PeerIP))));
}
// ---------------------------------------------------------------------------

void __fastcall Tfm::IdTCPServerExecute(TIdContext *AContext) {

	UnicodeString x = AContext->Connection->Socket->ReadLn();
	me->Lines->Add("Input = " + x);
	//
	if (x == "time") {
		AContext->Connection->Socket->WriteLn(TimeToStr(Now()));
	}

	if (x == "str") {
		AContext->Connection->Socket->WriteLn(edStr->Text,
			IndyTextEncoding_UTF8());
	}

	if (x == "image") {
		TMemoryStream *x = new TMemoryStream();
		try {
			im->Bitmap->SaveToStream(x);
			x->Seek(0, 0);
			AContext->Connection->Socket->Write(x->Size);
			AContext->Connection->Socket->Write(x);
		}
		__finally {
			delete x;
		}
	}

	if (x == "ver") {
		AContext->Connection->Socket->WriteLn("v20.0.1");

	}
	if (x == "file") {

	}
}

// ---------------------------------------------------------------------------
void __fastcall Tfm::buClearClick(TObject *Sender)
{
    me->Lines->Clear();
}

//---------------------------------------------------------------------------

