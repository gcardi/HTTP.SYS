
//---------------------------------------------------------------------------
#include "WebModuleUnit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"

TComponentClass WebModuleClass = __classid(TWebModule1);

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
     WSDLHTMLPublish1->ServiceInfo(Sender, Request, Response, Handled);
}
//---------------------------------------------------------------------------


