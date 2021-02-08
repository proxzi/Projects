//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "fmu.h"
#include "dmu.h"
#include "fmuforAmount.h"
#include "fmufornumbertable.h"
#include "fmuLogin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX.frxClass"
#pragma link "FMX.frxDBSet"
#pragma resource "*.fmx"
Tfm *fm;
//---------------------------------------------------------------------------
__fastcall Tfm::Tfm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void Tfm::TabControlsOff(){
	tbGeneral->TabPosition = TTabPosition::None;
	tb->TabPosition = TTabPosition::None;
	tb2->TabPosition = TTabPosition::None;
	tb3->TabPosition = TTabPosition::None;
    tbProd->TabPosition = TTabPosition::None;
	tb->ActiveTab = TabItem1;
	tb3->ActiveTab = TabItem5;
    tbProd->ActiveTab = TabItem4;
}
void __fastcall Tfm::FormCreate(TObject *Sender)
{
	tbGeneral->ActiveTab = tbMain;
	TabControlsOff();
}

//---------------------------------------------------------------------------
void __fastcall Tfm::FormShow(TObject *Sender)
{
	dm->Connect();
	Fullname = dm->Access->Lookup("AccessID", fmulog->AccessID, "Fullname");
	if (fmulog->level == 2) {
		btnMainAccess->Enabled = false;
		dm->Orders->Filter = "Fullname = '" + Fullname + "'";
		dm->Orders->Filtered = true;
		btnMainOrder->Enabled = false;
	}
	else {
		btnMainAccess->Enabled = true;
        btnMainOrder->Enabled = true;
		dm->Orders->Filtered = false;
	}
	orderId = (dm->Orders->FieldByName("OrderID")->AsInteger);
	dm->orderSql->Filter = "OrderID = " + IntToStr(orderId);
	dm->orderSql->Filtered = true;

}
//---------------------------------------------------------------------------
void __fastcall Tfm::btnSaveClientClick(TObject *Sender)
{
	dm->Menu->Append();
	tb->ActiveTab = TabItem2;
}
void __fastcall Tfm::btnEditMenuClick(TObject *Sender)
{
	dm->Menu->Edit();
	tb->ActiveTab = TabItem2;
}
//---------------------------------------------------------------------------
void __fastcall Tfm::btnSavePostClick(TObject *Sender)
{
	dm->Menu->Post();
	tb->ActiveTab = TabItem1;
}
//---------------------------------------------------------------------------
//int cost = dm->Menu->Lookup("Name", "55", "Cost"); // 1-� ������� 2-� ������������ 3-� ����� ������ �����
//---------------------------------------------------------------------------
void __fastcall Tfm::appendClick(TObject *Sender)
{
	dm->Orders->Append();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::editClick(TObject *Sender)
{
	dm->Orders->Edit();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btndeleteClick(TObject *Sender)
{
    dm->Orders->Delete();
}
//---------------------------------------------------------------------------


void __fastcall Tfm::btnDeleteMenuClick(TObject *Sender)
{
    dm->Menu->Delete();
}
//---------------------------------------------------------------------------

bool Run(){
}


void __fastcall Tfm::MenuOrderSaveClick(TObject *Sender)
{
	dm->MenuOrder->FieldByName("MenuID")->AsInteger = menuId;
	dm->MenuOrder->Post();
	tb2->ActiveTab = TabItem3;
}
//---------------------------------------------------------------------------


void __fastcall Tfm::Grid4CellDblClick(TColumn * const Column, const int Row)
{
	menuId = dm->Menu->FieldByName("MenuID")->AsInteger;
	Variant menuName = dm->Menu->FieldByName("Name")->AsString;
	Variant NameMenu = dm->orderSql->Lookup("Name", menuName,"Name");
	if (NameMenu.IsNull()) {
		dm->MenuOrder->Append();
		dm->MenuOrder->FieldByName("OrderID")->AsInteger = orderId;
		dm->MenuOrder->FieldByName("MenuID")->AsInteger = menuId;
		ffa->ShowModal();
		dm->MenuOrder->Post();
		dm->orderSql->Refresh();
	}
	else ShowMessage(L"�� �������� �����, ������� ��� ���������� � ������, �������� ������!");

}
//---------------------------------------------------------------------------

void __fastcall Tfm::Grid2SelChanged(TObject *Sender)
{
	orderId = dm->Orders->FieldByName("OrderID")->AsInteger;
	dm->orderSql->Filter = "OrderID = " + IntToStr(orderId);
}
//---------------------------------------------------------------------------


void __fastcall Tfm::btnMenuOrderAppendClick(TObject *Sender)
{
	dm->Orders->Append();
	ffnt->ShowModal();
	dm->Orders->FieldByName("Datatime")->AsString = Now().DateString();
	dm->Orders->FieldByName("Time")->AsString = Now().TimeString();
    dm->Orders->FieldByName("Fullname")->AsString = Fullname;
	dm->Orders->Post();
	dm->Orders->Refresh();
    orderId = (dm->Orders->FieldByName("OrderID")->AsInteger);
	dm->orderSql->Filter = "OrderID = " + IntToStr(orderId);
//	dm->orderSql->Refresh();
//    dm->Menu->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::Grid3CellDblClick(TColumn * const Column, const int Row)
{

	dm->MenuOrder->Locate("MenuOrderID", dm->orderSql->FieldByName("MenuOrderID")->AsInteger);
	dm->MenuOrder->Delete();
	dm->orderSql->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnOrderDeleteClick(TObject *Sender)
{
    dm->Orders->Delete();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnAppendAccessClick(TObject *Sender)
{
	dm->Access->Append();
	tb3->ActiveTab = TabItem6;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnAccessEditClick(TObject *Sender)
{
    dm->Access->Locate("AccessID", dm->AccessSql->FieldByName("AccessID")->AsInteger);
	dm->Access->Edit();
	tb3->ActiveTab = TabItem6;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnAccessDeleteClick(TObject *Sender)
{
	dm->Access->Locate("AccessID", dm->AccessSql->FieldByName("AccessID")->AsInteger);
	dm->Access->Delete();
	dm->AccessSql->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnSaveAccessClick(TObject *Sender)
{
	int AccessLevel = dm->Role->Lookup("Title", cbAccessRole->Selected->Text, "RoleId");
	dm->Access->FieldByName("RoleID")->AsInteger = AccessLevel;
	dm->Access->Post();
    dm->AccessSql->Refresh();
	tb3->ActiveTab = TabItem5;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnAppendMenuClick(TObject *Sender)
{
	dm->Menu->Append();
    tb->ActiveTab = TabItem2;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnSaveMenuClick(TObject *Sender)
{
	dm->Menu->Post();
    tb->ActiveTab = TabItem1;
}
//---------------------------------------------------------------------------




void __fastcall Tfm::btnMainMenuClick(TObject *Sender)
{
	tbGeneral->ActiveTab = tbMenuOrder;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnMainOrderClick(TObject *Sender)
{
	tbGeneral->ActiveTab = tbMenu;
    tb->ActiveTab = TabItem1;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnMainAccessClick(TObject *Sender)
{
	tbGeneral->ActiveTab = tbAccess;

}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnMainProductsClick(TObject *Sender)
{
	tbGeneral->ActiveTab = tbProducts;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnReturnClick(TObject *Sender)
{
    tbGeneral->ActiveTab = tbMain;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::FormClose(TObject *Sender, TCloseAction &Action)
{
	fmulog->Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfm::btnChangeUserClick(TObject *Sender)
{
	Hide();
	fmulog->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnProductsSaveClick(TObject *Sender)
{
	dm->Products->Post();
	tbProd->ActiveTab = TabItem4;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnProductsAppendClick(TObject *Sender)
{
	dm->Products->Append();
	tbProd->ActiveTab = TabItem7;
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnProductsEditClick(TObject *Sender)
{
    dm->Products->Edit();
	tbProd->ActiveTab = TabItem7;
}
//---------------------------------------------------------------------------



void __fastcall Tfm::btnReturnAccessClick(TObject *Sender)
{
	tb3->ActiveTab = TabItem5;
	if(Edit1->Text == ""){
		dm->Access->Delete();
	}
	else dm->Access->Post();

}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnReturnProductsClick(TObject *Sender)
{
	tbProd->ActiveTab = TabItem4;
	if(Edit4->Text == ""){
		dm->Products->Delete();
	}
	else dm->Products->Post();
}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnReturnMenuClick(TObject *Sender)
{
	tb->ActiveTab = TabItem1;
	if(edNameMenu->Text == ""){
		dm->Menu->Delete();
	}
	else dm->Menu->Post();

}
//---------------------------------------------------------------------------

void __fastcall Tfm::btnProductsDeleteClick(TObject *Sender)
{
    dm->Products->Delete();
}
//---------------------------------------------------------------------------

