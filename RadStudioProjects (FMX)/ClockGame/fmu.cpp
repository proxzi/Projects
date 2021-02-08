//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfm *fm;

using namespace std;
typedef std::list<Mobile*>::iterator moIt;

UnicodeString txt(char * str, int n)
{
	return Format(str, ARRAYOFCONST((n)));
}

//---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tc->TabPosition = TTabPosition::None;
	tc->ActiveTab = menu;
	up = 3;
	Attempt = 5;
		////////////MOBILE///////
	for (int i = 0; i < 10; i++) {
		int Size_m = (int)RandomRange(30,80);
		float Rnd = Random(2) ? 5 : (recbackground->Width - Size_m);
		mobiles.push_back(new Mobile(Size_m,Rnd, Height+Size_m,recbackground,imList));
		moIt it= mobiles.end();
		(*(--it))->speed = RandomRange(3,8);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfm::buStartClick(TObject *Sender)
{



	for(int i = 1; i < 11; i++){
		TRectangle * Rect = (TRectangle*) fm->FindComponent("Rectangle" + IntToStr(i));
		Rect->HitTest = false;
		Rect->Fill->Color = claHoneydew;
	}
	tc->ActiveTab = game;
	GameTimer->Enabled = true;
	rdyAnim->Enabled = true;
	laAttempt->Text = txt("Осталось попыток: %d", Attempt);
}
//---------------------------------------------------------------------------
void __fastcall Tfm::RectClick(TObject *Sender)
{
	rdyAnim->Enabled = false;
    keyAnim->Enabled = false;
	if (RectGlobal->Fill->Color == claLightsalmon) {
		RectGlobal->Fill->Color = claAliceblue;
		delay->Enabled = false;
	}
	RepeatAnswer++;
	TRectangle * currentRect = (TRectangle*)Sender;
	RectGlobal = currentRect;
	RectGlobal->Fill->Color = claLightsalmon;
	delay->Enabled = true;
	str += IntToStr(currentRect->Tag + 1);
	laAnswer->Text = str;
	if (RepeatAnswer == Repeat) {

		if (StrToInt(str) == StrToInt(Answer)) {
			Score += 10 * up;
            up++;
			gl->ImageIndex = 0;
            keyAnim->Enabled = true;
			laAnswer->Text = "";
			RepeatAnswer = 0;
			Repeat = 0;
			str = "";
			Answer = "";
			GameTimer->Enabled = true;
			for(int i = 1; i < 11; i++){
				TRectangle * Rect = (TRectangle*) fm->FindComponent("Rectangle" + IntToStr(i));
				Rect->HitTest = false;
			}
			rdyAnim->Enabled = true;
			pg->Value = 0;
			TimeUp->Enabled = false;
			laScore->Text = txt("Счет: %d", Score);
		}
		else {
			Attempt--;
			if (Attempt == -1) {
				ShowMessage("Вы проиграли");
				buBackmenuClick(NULL);
			}
			laAttempt->Text = txt("Осталось попыток: %d", Attempt);
            gl->ImageIndex = 1;
            keyAnim->Enabled = true;
			for(int i = 1; i < 11; i++){
				laAnswer->Text = "";
				RepeatAnswer = 0;
				Repeat = 0;
				str = "";
				Answer = "";
				GameTimer->Enabled = true;
				TRectangle * Rect = (TRectangle*) fm->FindComponent("Rectangle" + IntToStr(i));
				Rect->HitTest = false;
			}

			rdyAnim->Enabled = true;
			pg->Value = 0;
			TimeUp->Enabled = false;
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall Tfm::delayTimer(TObject *Sender)
{
	RectGlobal->Fill->Color = claAliceblue;
	delay->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::GameTimerTimer(TObject *Sender)
{
	TimerWait->Enabled = true;
	int RandomRect = RandomRange(1,10);
	RectGlobal = (TRectangle*) fm->FindComponent("Rectangle" + IntToStr(RandomRect));
	RectGlobal->Fill->Color = claLightsalmon;
	Repeat++;
	Answer += IntToStr(RectGlobal->Tag + 1);
	if (Repeat == up) {
		for(int i = 1; i < 11; i++){
				TRectangle * Rect = (TRectangle*) fm->FindComponent("Rectangle" + IntToStr(i));
				Rect->HitTest = true;
		}
		GameTimer->Enabled = false;
		TimeUp->Enabled = true;
	}

}
//---------------------------------------------------------------------------


void __fastcall Tfm::TimerWaitTimer(TObject *Sender)
{
	RectGlobal->Fill->Color = claAliceblue;
	TimerWait->Enabled = false;
	if (Repeat == up) {
        TimerWait->Enabled = false;
	}
}

void __fastcall Tfm::TimeUpTimer(TObject *Sender)
{
	pg->Value += 1;
	if (pg->Value == 100) {
		TimeUp->Enabled = false;
		ShowMessage("Вы проиграли!");
        buBackmenuClick(NULL);
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfm::buSettingsClick(TObject *Sender)
{
	tc->ActiveTab = settings;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buInClick(TObject *Sender)
{
	tc->ActiveTab = instruction;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buBackClick(TObject *Sender)
{
    tc->ActiveTab = menu;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buSaveClick(TObject *Sender)
{
	tc->ActiveTab = menu;
    laName->Text = eName->Text;
	if (rb1->IsChecked == true) {
		up = 3;
	}
	else if (rb2->IsChecked == true) {
		up = 5;
	}
	else{
        up = 7;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfm::buBackmenuClick(TObject *Sender)
{
	tc->ActiveTab = menu;
    GameTimer->Enabled = false;
	delay->Enabled = false;
	TimerWait->Enabled = false;
	laAnswer->Text = "";
	RepeatAnswer = 0;
	Repeat = 0;
	str = "";
	Answer = "";
	rdyAnim->Enabled = false;
	keyAnim->Enabled = false;
	TimeUp->Enabled = false;
	pg->Value = 0;
	Attempt = 5;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::buAboutClick(TObject *Sender)
{
    ShowMessage("Created by Dmitry Yakuba");
}
//---------------------------------------------------------------------------

Mobile::Mobile(int size, float x, float y, TComponent * parent, TImageList * il)
	:moGl(new TGlyph(NULL)){
	moGl->Parent = (TFmxObject*)parent;
	moGl->Height = size;
	moGl->Width = size;
	moGl->Position->X = x;
	moGl->Position->Y = y;
	moGl->Images = il;
	moGl->ImageIndex = 2;
}

void __fastcall Tfm::renderMobileTimer(TObject *Sender)
{
	for (moIt mi = mobiles.begin(); mi != mobiles.end(); ++mi) {
		(*mi)->moGl->Position->Y -= (*mi)->speed;
		if((*mi)->moGl->Position->Y <= -(*mi)->moGl->Height){
            (*mi)->moGl->Position->Y = Height;
	}
	}

}
//---------------------------------------------------------------------------

