//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "projectdim.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::БелыйClick(TObject *Sender)
{
	Cat->Visible = ! Cat->Visible;
	Label1->Text = "Меняем картинку...";
	Белый->Visible = false;
	Button2->Visible = false;
	Button3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Image2->Visible = ! Image2->Visible;
	Белый->Visible = false;
	Button1->Visible = false;
	Button2->Visible = false;
	Button3->Visible = true;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Image3->Visible = ! Image3->Visible;
	Белый->Visible = false;
	Button1->Visible = false;
	Button2->Visible = true;
	Button3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Image4->Visible = ! Image4->Visible;
	Белый->Visible = true;
	Button1->Visible = true;
	Button2->Visible = true;
	Button3->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Image4->Visible = true;
	Image2->Visible = true;
	Image3->Visible = true;
	Cat->Visible = true;
	Белый->Visible = true;
	Button1->Visible = true;
	Button2->Visible = true;
	Button3->Visible = true;
	Label1->Text = "ГОРОД ДОРОГ";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Image4->Visible = !Image4->Visible;
	Image2->Visible = !Image2->Visible;
	Image3->Visible = !Image3->Visible;
	Cat->Visible = !Cat->Visible;
}
//---------------------------------------------------------------------------

