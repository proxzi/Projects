//---------------------------------------------------------------------------

#ifndef fmuH
#define fmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Objects.hpp>
#include "FMX.frxClass.hpp"
#include "FMX.frxDBSet.hpp"
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class Tfm : public TForm
{
__published:	// IDE-managed Components
	TGrid *gridmenu;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB1;
	TButton *btnAppendMenu;
	TEdit *edNameMenu;
	TEdit *edWeightMenu;
	TEdit *edCostMenu;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TTabControl *tb;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TButton *btnEditMenu;
	TButton *btnSaveMenu;
	TTabControl *tbGeneral;
	TTabItem *tbMenu;
	TTabItem *tbMenuOrder;
	TTabItem *tbAccess;
	TTabItem *tbProducts;
	TGrid *Grid1;
	TBindSourceDB *BindSourceDB4;
	TButton *btnAppendAccess;
	TButton *btnDeleteMenu;
	TBindSourceDB *BindSourceDB2;
	TBindSourceDB *BindSourceDB3;
	TBindSourceDB *BindSourceDB5;
	TGrid *Grid3;
	TGrid *Grid2;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB32;
	TTabControl *tb2;
	TTabItem *TabItem3;
	TGrid *Grid4;
	TLabel *Label2;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB12;
	TLabel *Label3;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB5;
	TButton *btnMenuOrderAppend;
	TButton *btnOrderDelete;
	TLabel *Label1;
	TLabel *Label4;
	TLabel *Label5;
	TBindSourceDB *BindSourceDB6;
	TTabControl *tb3;
	TTabItem *TabItem5;
	TTabItem *TabItem6;
	TButton *btnAccessEdit;
	TButton *btnAccessDelete;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label6;
	TLabel *vds;
	TLabel *Label8;
	TEdit *Edit3;
	TButton *btnSaveAccess;
	TLabel *Label7;
	TComboBox *cbAccessRole;
	TBindSourceDB *BindSourceDB7;
	TLinkListControlToField *LinkListControlToField1;
	TLinkControlToField *LinkControlToField5;
	TLinkControlToField *LinkControlToField6;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TTabItem *tbMain;
	TButton *btnMainAccess;
	TButton *btnMainOrder;
	TButton *btnMainMenu;
	TButton *btnMainProducts;
	TButton *btnReturn;
	TButton *Button2;
	TButton *Button1;
	TButton *Button3;
	TLinkControlToField *LinkControlToField4;
	TBindSourceDB *BindSourceDB8;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB8;
	TButton *btnChangeUser;
	TGrid *Grid5;
	TButton *btnProductsAppend;
	TButton *btnProductsEdit;
	TButton *btnProductsDelete;
	TBindSourceDB *BindSourceDB9;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB9;
	TTabControl *tbProd;
	TTabItem *TabItem4;
	TTabItem *TabItem7;
	TEdit *Edit4;
	TLabel *Label9;
	TLabel *Label13;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label14;
	TButton *btnProductsSave;
	TLinkControlToField *LinkControlToField7;
	TLinkControlToField *LinkControlToField8;
	TLinkControlToField *LinkControlToField9;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TButton *btnReturnAccess;
	TButton *btnReturnMenu;
	TButton *btnReturnProducts;
	void __fastcall btnSaveClientClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnEditMenuClick(TObject *Sender);
	void __fastcall btnSavePostClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall appendClick(TObject *Sender);
	void __fastcall editClick(TObject *Sender);
	void __fastcall btndeleteClick(TObject *Sender);
	void __fastcall btnDeleteMenuClick(TObject *Sender);
	void __fastcall MenuOrderSaveClick(TObject *Sender);
	void __fastcall Grid4CellDblClick(TColumn * const Column, const int Row);
	void __fastcall Grid2SelChanged(TObject *Sender);
	void __fastcall btnMenuOrderAppendClick(TObject *Sender);
	void __fastcall Grid3CellDblClick(TColumn * const Column, const int Row);
	void __fastcall btnOrderDeleteClick(TObject *Sender);
	void __fastcall btnAppendAccessClick(TObject *Sender);
	void __fastcall btnAccessEditClick(TObject *Sender);
	void __fastcall btnAccessDeleteClick(TObject *Sender);
	void __fastcall btnSaveAccessClick(TObject *Sender);
	void __fastcall btnAppendMenuClick(TObject *Sender);
	void __fastcall btnSaveMenuClick(TObject *Sender);
	void __fastcall btnMainMenuClick(TObject *Sender);
	void __fastcall btnMainOrderClick(TObject *Sender);
	void __fastcall btnMainAccessClick(TObject *Sender);
	void __fastcall btnMainProductsClick(TObject *Sender);
	void __fastcall btnReturnClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnChangeUserClick(TObject *Sender);
	void __fastcall btnProductsSaveClick(TObject *Sender);
	void __fastcall btnProductsAppendClick(TObject *Sender);
	void __fastcall btnProductsEditClick(TObject *Sender);
	void __fastcall btnReturnAccessClick(TObject *Sender);
	void __fastcall btnReturnProductsClick(TObject *Sender);
	void __fastcall btnReturnMenuClick(TObject *Sender);
	void __fastcall btnProductsDeleteClick(TObject *Sender);
private:	// User declarations
    void TabControlsOff();
public:		// User declarations
	__fastcall Tfm(TComponent* Owner);
	int orderId;
	int menuId;
	UnicodeString Fullname;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfm *fm;
//---------------------------------------------------------------------------
#endif
