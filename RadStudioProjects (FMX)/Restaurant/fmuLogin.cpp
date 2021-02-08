//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmuLogin.h"
#include "dmu.h"
#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
Tfmulog *fmulog;
//---------------------------------------------------------------------------
__fastcall Tfmulog::Tfmulog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfmulog::btnCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfmulog::btnEnterClick(TObject *Sender)
{
// ����� ������ � ������� roles �� ���������� ������

	// ������� ������ � id �������
	Variant role = dm->Access->Lookup("Login", edLogin->Text, "Password; RoleID; AccessID");

	// ���� ������ ���, � role ������� null
	if (!role.IsNull()) {

		UnicodeString pass = role.GetElement(0);
        AccessID = role.GetElement(2);

		// ��������� ������ � ������

		// ���������� ���������� ������ � ��������� � (���� ������)
		if (pass == edPass->Text) {

			level = role.GetElement(1); // ������� �������
			fmulog->Hide();
			fm->Show();
			switch (level) {
			case 1:	
				fm->tbGeneral->ActiveTab = fm->tbMain;
				break;
			case 2:
				fm->tbGeneral->ActiveTab = fm->tbMain;
				break;
			case 3:
				fm->tbGeneral->ActiveTab = fm->tbMain;
				break;
			}

		}
		else {
			ShowMessage(L"������������ �� ������");
		}
	}
	else {
		ShowMessage(L"������������ �� ������");
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfmulog::FormShow(TObject *Sender)
{
	dm->Connect();
}
//---------------------------------------------------------------------------

void __fastcall Tfmulog::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
    if (Key == VK_RETURN) {

		btnEnterClick(Sender);
	}
}
//---------------------------------------------------------------------------

