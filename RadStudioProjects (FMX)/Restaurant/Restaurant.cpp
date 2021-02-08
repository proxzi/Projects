//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("fmuLogin.cpp", fmulog);
USEFORM("fmufornumbertable.cpp", ffnt);
USEFORM("dmu.cpp", dm); /* TDataModule: File Type */
USEFORM("fmu.cpp", fm);
USEFORM("fmuforAmount.cpp", ffa);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(Tfmulog), &fmulog);
		Application->CreateForm(__classid(Tfm), &fm);
		Application->CreateForm(__classid(Tdm), &dm);
		Application->CreateForm(__classid(Tffa), &ffa);
		Application->CreateForm(__classid(Tffnt), &ffnt);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
