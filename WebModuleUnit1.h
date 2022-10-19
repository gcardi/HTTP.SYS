
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
#include <Datasnap.DSClientMetadata.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSHTTP.hpp>
#include <Datasnap.DSHTTPWebBroker.hpp>
#include <Datasnap.DSMetadata.hpp>
#include <Datasnap.DSProxyJavaScript.hpp>
#include <Datasnap.DSServer.hpp>
#include <Datasnap.DSServerMetadata.hpp>
#include <IPPeerServer.hpp>
#include <Web.HTTPProd.hpp>
#include <Datasnap.DSAuth.hpp>
//---------------------------------------------------------------------------
class TWebModule1 : public TWebModule
{
__published:	// IDE-managed Components
        THTTPSoapDispatcher *HTTPSoapDispatcher1;
        THTTPSoapCppInvoker *HTTPSoapCppInvoker1;
        TWSDLHTMLPublish *WSDLHTMLPublish1;
	TPageProducer *PageProducer1;
	TDSProxyGenerator *DSProxyGenerator1;
	TWebFileDispatcher *WebFileDispatcher1;
	TDSHTTPWebDispatcher *DSHTTPWebDispatcher1;
	TDSServer *DSServer1;
	TDSServerClass *DSServerClass1;
	TDSServerMetaDataProvider *DSServerMetaDataProvider1;
	TPageProducer *ReverseString;
	TPageProducer *ServerFunctionInvoker;
	TDSAuthenticationManager *DSAuthenticationManager1;
        void __fastcall WebModule1DefaultHandlerAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
	void __fastcall WebFileDispatcher1BeforeDispatch(TObject *Sender, const UnicodeString AFileName,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
	void __fastcall DSServerClass1GetClass(TDSServerClass *DSServerClass, TPersistentClass &PersistentClass);
	void __fastcall ServerFunctionInvokerHTMLTag(TObject *Sender, TTag Tag, const UnicodeString TagString,
          TStrings *TagParams, UnicodeString &ReplaceText);
	void __fastcall WebModuleBeforeDispatch(TObject *Sender, TWebRequest *Request, TWebResponse *Response,
          bool &Handled);
	void __fastcall WebModuleCreate(TObject *Sender);
	void __fastcall DSAuthenticationManager1UserAuthenticate(TObject *Sender, const UnicodeString Protocol,
          const UnicodeString Context, const UnicodeString User,
          const UnicodeString Password, bool &valid, TStrings *UserRoles);
	void __fastcall DSAuthenticationManager1UserAuthorize(TObject *Sender, TDSAuthorizeEventObject *AuthorizeEventObject,
		  bool &valid);

private:	// User declarations
	TWebActionItem* FServerFunctionInvokerAction;
	bool __fastcall AllowServerFunctionInvoker(void);
public:		// User declarations
	__fastcall TWebModule1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWebModule1 *WebModule1;
//---------------------------------------------------------------------------
#endif



