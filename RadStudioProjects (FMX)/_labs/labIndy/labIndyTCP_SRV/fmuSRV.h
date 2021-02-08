//---------------------------------------------------------------------------

#ifndef fmuSRVH
#define fmuSRVH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TLayout *Layout1;
	TButton *buStop;
	TButton *buStart;
	TEdit *edStr;
	TImage *im;
	TMemo *me;
	TIdTCPServer *IdTCPServer;
	TStyleBook *StyleBook1;
	TButton *buClear;
	void __fastcall buStartClick(TObject *Sender);
	void __fastcall buStopClick(TObject *Sender);
	void __fastcall IdTCPServerConnect(TIdContext *AContext);
	void __fastcall IdTCPServerDisconnect(TIdContext *AContext);
	void __fastcall IdTCPServerExecute(TIdContext *AContext);
	void __fastcall buClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
