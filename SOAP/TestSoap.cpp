// ************************************************************************ //
// Implementation class for interface ITestSoap
// ************************************************************************ //
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#if !defined(__TestSoap_h__)
#include "TestSoap.h"
#endif

// ************************************************************************ //
//  TTestSoapImpl implements interface ITestSoap
// ************************************************************************ //
class TTestSoapImpl : public TInvokableClass, public ITestSoap
{
public:
    /* Sample methods of ITestSoap */
  SampleEnum     echoEnum(SampleEnum eValue);
  TDoubleArray   echoDoubleArray(const TDoubleArray daValue);
  TSampleStruct* echoStruct(const TSampleStruct* pStruct);
  double         echoDouble(double dValue);

  /* IUnknown */
  HRESULT STDMETHODCALLTYPE QueryInterface(const GUID& IID, void **Obj)
                        { return GetInterface(IID, Obj) ? S_OK : E_NOINTERFACE; }
  ULONG STDMETHODCALLTYPE AddRef() { return TInvokableClass::_AddRef();  }
  ULONG STDMETHODCALLTYPE Release() { return TInvokableClass::_Release();  }
};


SampleEnum TTestSoapImpl::echoEnum(SampleEnum eValue)
{
  /* TODO : Implement method echoEnum */
  return eValue;
}

TDoubleArray TTestSoapImpl::echoDoubleArray(TDoubleArray daValue)
{
  /* TODO : Implement method echoDoubleArray */
  return daValue;
}

TSampleStruct* TTestSoapImpl::echoStruct(const TSampleStruct* pEmployee)
{
  /* TODO : Implement method echoMyEmployee */
  return new TSampleStruct();
}

double TTestSoapImpl::echoDouble(const double dValue)
{
  /* TODO : Implement method echoDouble */
  return dValue;
}


static void __fastcall TestSoapFactory(System::TObject* &obj)
{
  static _di_ITestSoap iInstance;
  static TTestSoapImpl *instance = 0;
  if (!instance)
  {
    instance = new TTestSoapImpl();
    instance->GetInterface(iInstance);
  }
  obj = instance;
}

// ************************************************************************ //
//  The following routine registers the interface and implementation class
//  as well as the type used by the methods of the interface
// ************************************************************************ //
static void RegTypes()
{
  InvRegistry()->RegisterInterface(__delphirtti(ITestSoap));
  InvRegistry()->RegisterInvokableClass(__classid(TTestSoapImpl), TestSoapFactory);
}
#pragma startup RegTypes 32

