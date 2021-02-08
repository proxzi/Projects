//---------------------------------------------------------------------------

#ifndef fmufinishH
#define fmufinishH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "fmu.h"
//---------------------------------------------------------------------------
class Tfmf : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfmf(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfmf *fmf;
//---------------------------------------------------------------------------
#endif
