 
// stSOAPWebModuleIntf
//---------------------------------------------------------------------------
#ifndef WebModuleUnit1H
#define WebModuleUnit1H
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.SOAPHTTPDisp.hpp>
#include <Soap.SOAPHTTPPasInv.hpp>
#include <Soap.SOAPPasInv.hpp>
#include <Soap.WebBrokerSOAP.hpp>
#include <Soap.WebServExp.hpp>
#include <Soap.WSDLBind.hpp>
#include <Soap.WSDLIntf.hpp>
#include <Soap.WSDLPub.hpp>
#include <System.TypInfo.hpp>
#include <Xml.XMLSchema.hpp>
//---------------------------------------------------------------------------
class TWebModule1 : public TWebModule
{
__published:	// IDE-managed Components
        THTTPSoapDispatcher *HTTPSoapDispatcher1;
        THTTPSoapCppInvoker *HTTPSoapCppInvoker1;
        TWSDLHTMLPublish *WSDLHTMLPublish1;
        void __fastcall WebModule1DefaultHandlerAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
private:	// User declarations
public:		// User declarations
	__fastcall TWebModule1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWebModule1 *WebModule1;
//---------------------------------------------------------------------------
#endif



