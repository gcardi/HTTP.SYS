
//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.AppEvnts.hpp>
//#include <IdHTTPWebBrokerBridge.hpp>
#include <SynWebServer.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>

#include <memory>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonOpenBrowser;
	TEdit *EditPort;
	TButton *ButtonStop;
	TButton *ButtonStart;
	TLabel *Label1;
    TLabel *Label2;
    TEdit *EditRoot;
    TCheckBox *checkboxHTTPS;
    TLabel *Label3;
    TEdit *EditDomainName;
    TActionList *ActionList1;
    TAction *actStart;
    TAction *actStop;
    TAction *actOpenBrowser;
    TApplicationEvents *ApplicationEvents1;
    TLabel *lblURI;
    void __fastcall ButtonStopClick(TObject *Sender);
    void __fastcall EnabledIfNotRunning(TObject *Sender);
    void __fastcall EnabledIfRunning(TObject *Sender);
    void __fastcall actStartExecute(TObject *Sender);
    void __fastcall actStopExecute(TObject *Sender);
    void __fastcall actOpenBrowserExecute(TObject *Sender);
    void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
private:	// User declarations
//    TIdHTTPWebBrokerBridge *FServer;
    std::unique_ptr<TSynHTTPWebBrokerBridge> FServer;
    String launchURL_;

    bool IsRunning() const;
    String GetHName() const;

    void StartServer();
    void StopServer();
    String GetDomainName() const;
    void SetDomainName( String Val );

    __property String DomainName = { read = GetDomainName, write = SetDomainName };
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif


