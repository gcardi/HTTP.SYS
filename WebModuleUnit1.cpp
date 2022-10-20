
#pragma hdrstop
#include <tchar.h>

#include <Web.WebReq.hpp>

#include "WebModuleUnit1.h"
#include "ServerMethodsUnit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"

TComponentClass WebModuleClass = __classid(TWebModule1);
TComponent *FModule;
TDSServer *FDSServer;
TDSAuthenticationManager *FDSAuthenticationManager;

//---------------------------------------------------------------------------

extern bool HTTPSEnabled;

__fastcall TWebModule1::TWebModule1(TComponent* Owner)
	: TWebModule(Owner)
{
	if ( HTTPSEnabled ) {
		WSDLHTMLPublish1->PublishOptions =
			WSDLHTMLPublish1->PublishOptions << poPublishLocationAsSecure;
	}
	else {
		WSDLHTMLPublish1->PublishOptions =
			WSDLHTMLPublish1->PublishOptions >> poPublishLocationAsSecure;
	}

}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1DefaultHandlerAction(TObject *Sender,
	  TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
//	 WSDLHTMLPublish1->ServiceInfo(Sender, Request, Response, Handled);
  if (Request->InternalPathInfo == "" || Request->InternalPathInfo == "/")
	Response->Content = ReverseString->Content();
  else
	Response->SendRedirect(Request->InternalScriptName + "/");
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebFileDispatcher1BeforeDispatch(TObject *Sender, const UnicodeString AFileName,
		  TWebRequest *Request, TWebResponse *Response, bool &Handled)

{
	Handled = false;
	if ( SameFileName(ExtractFileName( AFileName ), _T( "serverfunctions.js" ) ) ) {
		TDateTime D1, D2;
		if ( FileAge( AFileName, D1 ) && FileAge( WebApplicationFileName(), D2 ) && ( D1 < D2 ) ) {
			DSProxyGenerator1->TargetDirectory = ExtractFilePath(AFileName);
			DSProxyGenerator1->TargetUnitName = ExtractFileName(AFileName);
			DSProxyGenerator1->Write();
		}
	}

}
//---------------------------------------------------------------------------

/*
static void freeWebModules()
{
	FreeWebModules();
}
#pragma exit freeWebModules 33
*/

//---------------------------------------------------------------------------

void __fastcall TWebModule1::DSServerClass1GetClass(TDSServerClass *DSServerClass,
		  TPersistentClass &PersistentClass)
{
	PersistentClass = __classid( TServerMethods1 );
}
//---------------------------------------------------------------------------


void __fastcall TWebModule1::ServerFunctionInvokerHTMLTag(TObject *Sender, TTag Tag,
          const UnicodeString TagString, TStrings *TagParams, UnicodeString &ReplaceText)

{
	if (SameText(TagString, "urlpath"))
		ReplaceText = (Request->InternalScriptName);
	else if (SameText(TagString, "port"))
		ReplaceText = IntToStr(Request->ServerPort);
	else if (SameText(TagString, "host"))
		ReplaceText = (Request->Host);
	else if (SameText(TagString, "classname"))
		ReplaceText = __classid(TServerMethods1)->ClassName();
	else if (SameText(TagString, "loginrequired"))
	{
    /*
		if (DSHTTPWebDispatcher1->AuthenticationManager != NULL)
			ReplaceText = "true";
		else
			ReplaceText = "false";
        */
	}
	else if (SameText(TagString, "serverfunctionsjs"))
		ReplaceText = Request->InternalScriptName + "/js/serverfunctions.js";
	else if (SameText(TagString, "servertime"))
		ReplaceText = DateTimeToStr(Now());
	else if  (SameText(TagString, "serverfunctioninvoker"))
	{
		if (AllowServerFunctionInvoker())
			ReplaceText =
			"<div><a href='" + Request->InternalScriptName +
			"/ServerFunctionInvoker' target='_blank'>Server Functions</a></div>";
	}
	else
		ReplaceText = "";
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModuleBeforeDispatch(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled)
{
	if (FServerFunctionInvokerAction != NULL)
	{
		FServerFunctionInvokerAction->Enabled = AllowServerFunctionInvoker();
	}

}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModuleCreate(TObject *Sender)
{
	FServerFunctionInvokerAction = ActionByName("ServerFunctionInvokerAction");
	DSServerMetaDataProvider1->Server = DSServer1;
	DSHTTPWebDispatcher1->Server = DSServer1;
	if (DSServer1->Started)
	{
		DSHTTPWebDispatcher1->DbxContext = DSServer1->DbxContext;
		DSHTTPWebDispatcher1->Start();
	}
	DSHTTPWebDispatcher1->AuthenticationManager = DSAuthenticationManager1;

}
//---------------------------------------------------------------------------

bool __fastcall TWebModule1::AllowServerFunctionInvoker(void)
{
	return Request->RemoteAddr == "127.0.0.1" ||
		Request->RemoteAddr == "0:0:0:0:0:0:0:1" || Request->RemoteAddr == "::1";
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::DSAuthenticationManager1UserAuthenticate(TObject *Sender,
		  const UnicodeString Protocol, const UnicodeString Context, const UnicodeString User,
		  const UnicodeString Password, bool &valid, TStrings *UserRoles)
{
	/* TODO : Validate the client user and password.
	If role-based authorization is needed, add role names to the UserRoles parameter  */
	valid = true;
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::DSAuthenticationManager1UserAuthorize(TObject *Sender,
		  TDSAuthorizeEventObject *AuthorizeEventObject, bool &valid)
{
	/* TODO : Authorize a user to execute a method.
	Use values from eventObject such as UserName, UserRoles, AuthorizedRoles and DeniedRoles.
	Use DSAuthenticationManager1.Roles to define Authorized and Denied roles
	for particular server methods. */
	valid = true;
}
//---------------------------------------------------------------------------

