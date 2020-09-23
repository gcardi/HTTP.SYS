
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <SynCrtSock.hpp>

#include <memory>

#include "FormMain.h"

using std::make_unique;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment( lib, "PkgHttpSysBridge" )
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool HTTPSEnabled {};

void TForm1::StartServer()
{
    HTTPSEnabled = checkboxHTTPS->Checked;

    FServer =
        make_unique<TSynHTTPWebBrokerBridge>(
            this,
            EditRoot->Text,           // aRoot
            EditPort->Text,           // aPort
            checkboxHTTPS->Checked,   // Https
            DomainName,               // aDomainName
            true,                     // aRegisterURI
            0                         // aContext
        );
}
//---------------------------------------------------------------------------

void TForm1::StopServer()
{
    FServer.reset();
    WebRequestHandler()->FreeModules();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonStopClick(TObject *Sender)
{
    FServer.reset();
}
//---------------------------------------------------------------------------

bool TForm1::IsRunning() const
{
    return FServer && FServer->Active;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EnabledIfNotRunning(TObject *Sender)
{
    auto& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = !IsRunning();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EnabledIfRunning(TObject *Sender)
{
    auto& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = IsRunning();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actStartExecute(TObject *Sender)
{
    StartServer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actStopExecute(TObject *Sender)
{
    StopServer();
}
//---------------------------------------------------------------------------

String TForm1::GetDomainName() const
{
    return EditDomainName->Text;
}
//---------------------------------------------------------------------------

void TForm1::SetDomainName( String Val )
{
    EditDomainName->Text = Val;
}
//---------------------------------------------------------------------------

String TForm1::GetHName() const
{
    if ( DomainName.IsEmpty() || DomainName == _D( "+" ) ) {
        return _D( "localhost" );
    }
    return DomainName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actOpenBrowserExecute(TObject *Sender)
{
    ::ShellExecuteW(
        {},
        nullptr,
        launchURL_.c_str(),
        nullptr,
        nullptr,
        SW_SHOWNOACTIVATE
    );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
    auto const NotRunning = !IsRunning();
    EditRoot->Enabled = NotRunning;
    EditDomainName->Enabled = NotRunning;
    EditPort->Enabled = NotRunning;
    checkboxHTTPS->Enabled = NotRunning;
    if ( NotRunning ) {
        lblURI->Caption =
            Format(
                _D( "URI: %s" ),
                ARRAYOFCONST((
                    ToURI(
                        EditRoot->Text,           // aRoot
                        EditPort->Text,           // aPort
                        checkboxHTTPS->Checked,   // Https
                        EditDomainName->Text      // aDomainName
                    )
                ))
            );

        launchURL_ =
            ToURI(
                {},                       // aRoot
                EditPort->Text,           // aPort
                checkboxHTTPS->Checked,   // Https
                GetHName()                // aDomainName
            );

        actOpenBrowser->Caption =
            Format( _D( "Launch \'%s\'" ), ARRAYOFCONST(( launchURL_ )) );
    }

}
//---------------------------------------------------------------------------


