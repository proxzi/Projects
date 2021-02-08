//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *angry;
	TFloatAnimation *FloatAnimationCat;
	TImage *lyna;
	TFloatAnimation *FloatAnimationLyna;
	TLabel *LaAngry;
	TLabel *LaCleaver;
	TFloatAnimation *FloatAnimationCountCat;
	TFloatAnimation *FloatAnimationCountLyna;
	TBitmapListAnimation *BitmapListAnimation1;
	TFloatAnimation *FloatAnimationCaty;
	TFloatAnimation *FloatAnimation1;
	void __fastcall angryClick(TObject *Sender);
	void __fastcall LaCleaverClick(TObject *Sender);
	void __fastcall lynaClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FloatAnimationCatProcess(TObject *Sender);
	void __fastcall FloatAnimationLynaProcess(TObject *Sender);
private:	// User declarations
	int FCountAngry;
    int FCountLyna;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
