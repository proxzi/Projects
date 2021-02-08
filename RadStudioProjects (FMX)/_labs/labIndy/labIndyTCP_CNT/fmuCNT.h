//---------------------------------------------------------------------------

#ifndef fmuCNTH
#define fmuCNTH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ActnList.hpp>
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
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <System.Actions.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TButton *buConnect;
	TButton *buDisconnect;
	TButton *buTime;
	TButton *buStr;
	TButton *buImage;
	TLayout *Layout1;
	TEdit *edHost;
	TEdit *edPort;
	TImage *im;
	TIdTCPClient *IdTCPClient;
	TActionList *al;
	TAction *acConnect;
	TAction *acDisconnect;
	TAction *acGetTime;
	TAction *acGetStr;
	TAction *acGetImage;
	TMemo *me;
	TStyleBook *StyleBook1;
	TButton *buVer;
	TAction *acGetVersion;
	TButton *buFile;
	TAction *acGetFile;
	void __fastcall acConnectExecute(TObject *Sender);
	void __fastcall acDisconnectExecute(TObject *Sender);
	void __fastcall acGetTimeExecute(TObject *Sender);
	void __fastcall acGetStrExecute(TObject *Sender);
	void __fastcall acGetImageExecute(TObject *Sender);
	void __fastcall alUpdate(TBasicAction *Action, bool &Handled);
	void __fastcall acGetVersionExecute(TObject *Sender);
	void __fastcall buFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
