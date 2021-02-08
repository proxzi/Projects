//---------------------------------------------------------------------------

#ifndef dmuH
#define dmuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.FMXUI.Wait.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
//---------------------------------------------------------------------------
class Tdm : public TDataModule
{
__published:	// IDE-managed Components
	TFDConnection *Connection;
	TFDTable *Menu;
	TFDGUIxWaitCursor *FDGUIxWaitCursor1;
	TFDPhysSQLiteDriverLink *FDPhysSQLiteDriverLink1;
	TFDAutoIncField *MenuMenuID;
	TStringField *MenuName;
	TWideStringField *MenuWeight;
	TIntegerField *MenuCost;
	TFDTable *Access;
	TFDTable *Products;
	TFDTable *Role;
	TFDAutoIncField *ProductsProductsID;
	TStringField *ProductsName;
	TFloatField *ProductsAmount;
	TStringField *ProductsDimension;
	TFDAutoIncField *RoleRoleID;
	TStringField *RoleTitle;
	TFDTable *MenuOrder;
	TFDAutoIncField *MenuOrderMenuOrderID;
	TIntegerField *MenuOrderOrderID;
	TIntegerField *MenuOrderMenuID;
	TFDTable *Orders;
	TFDAutoIncField *OrdersOrderID;
	TStringField *OrdersFullname;
	TStringField *OrdersDatatime;
	TIntegerField *OrdersNumberTable;
	TFDQuery *orderSql;
	TStringField *orderSqlName;
	TIntegerField *orderSqlCost;
	TIntegerField *orderSqlAmount;
	TIntegerField *MenuOrderAmount;
	TStringField *OrdersTime;
	TIntegerField *orderSqlOrderID;
	TFDAutoIncField *orderSqlMenuOrderID;
	TFDAutoIncField *AccessAccessID;
	TStringField *AccessFullName;
	TStringField *AccessLogin;
	TStringField *AccessPassword;
	TStringField *AccessRoleID;
	TStringField *AccessPosition;
	TFDQuery *AccessSql;
	TStringField *AccessSqlFullName;
	TStringField *AccessSqlLogin;
	TStringField *AccessSqlPassword;
	TStringField *AccessSqlTitle;
	TFDAutoIncField *AccessSqlAccessID;
	void __fastcall ConnectionBeforeConnect(TObject *Sender);
	void __fastcall ConnectionAfterConnect(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tdm(TComponent* Owner);

    void Connect();
};
//---------------------------------------------------------------------------
extern PACKAGE Tdm *dm;
//---------------------------------------------------------------------------
#endif