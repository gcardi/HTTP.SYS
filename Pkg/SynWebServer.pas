{ *************************************************************************** }
{  SynWebReqRes.pas is the 3rd file of SynBroker Project                      }
{  by c5soft@189.cn  Version 0.9.0.0  2018-5-27                               }
{ *************************************************************************** }

unit SynWebServer;

interface

uses SysUtils, Classes, {IniFiles,} HTTPApp, Contnrs, WebReq, SynCommons,
  SynCrtSock, SynWebEnv;

type
  TSynWebRequestHandler = class(TWebRequestHandler);

  TSynWebServer = class
  private
    FOwner: TObject;
    {FIniFile: TIniFile;}
    FActive, FHttps: Boolean;
    FRoot, FPort, FDomainName: string;
    FHttpServer: THttpApiServer;
    FReqHandler: TWebRequestHandler;
    function Process(AContext: THttpServerRequest): cardinal;
    function WebBrokerDispatch(const AEnv: TSynWebEnv): Boolean;
  public
    property Active: Boolean read FActive;
    property Port: string read FPort;
    {constructor Create(AOwner: TComponent = nil);}
    //constructor Create(AOwner: TComponent; ARoot: string; APort: string; Https: boolean );
    constructor Create( AOwner: TComponent; const aRoot, aPort: string;
                        Https: boolean=false; const aDomainName: string='*';
                        aRegisterURI: boolean=false; aContext: Int64=0);
    destructor Destroy; override;
  end;

  TSynHTTPWebBrokerBridge = TSynWebServer;

implementation

uses SynZip, SynWebReqRes;

var
  RequestHandler: TWebRequestHandler = nil;

function GetRequestHandler: TWebRequestHandler;
begin
  if RequestHandler = nil then
    RequestHandler := TSynWebRequestHandler.Create(nil);
  Result := RequestHandler;
end;

{ TSynWebServer }

//constructor TSynWebServer.Create(AOwner: TComponent; ARoot: string; APort: string; Https: boolean );

constructor TSynWebServer.Create(AOwner: TComponent;
                                 const aRoot, aPort: string; Https: boolean;
                                 const aDomainName: string;
                                 aRegisterURI: boolean;
                                 aContext: Int64);
begin
  inherited Create;
  FActive := False;
  FOwner := AOwner;
  if (FOwner <> nil) and (FOwner.InheritsFrom(TWebRequestHandler)) then
    FReqHandler := TWebRequestHandler(FOwner)
  else
    FReqHandler := GetRequestHandler;
{
  FIniFile := TIniFile.Create(ChangeFileExt(ParamStr(0), '.ini'));
  FRoot := FIniFile.ReadString('Server', 'Root', '');
  FPort := FIniFile.ReadString('Server', 'Port', '8080');
  }
  FRoot := ARoot;
  FPort := APort;
  FHttps := Https;
  FDomainName := aDomainName;
  FHttpServer := THttpApiServer.Create(False);
  //FHttpServer.AddUrl(StringTOUTF8(FRoot), StringTOUTF8(FPort), Https,
  //  '+', true);

  FHttpServer.AddUrl(StringTOUTF8(FRoot), StringTOUTF8(FPort), Https,
    StringTOUTF8(aDomainName), aRegisterURI, aContext );

  FHttpServer.RegisterCompress(CompressDeflate);
  // our server will deflate html :)
  FHttpServer.OnRequest := Process;
  FHttpServer.Clone(31); // will use a thread pool of 32 threads in total
  FActive := true;
end;

destructor TSynWebServer.Destroy;
begin
//  FHttpServer.RemoveUrl(StringTOUTF8(FRoot), StringTOUTF8(FPort), False, '+');
  FHttpServer.RemoveUrl(StringTOUTF8(FRoot), StringTOUTF8(FPort), FHttps,
    StringTOUTF8(FDomainName) );
  FHttpServer.Free;
  {FIniFile.Free;}
  inherited;
end;

function TSynWebServer.Process(AContext: THttpServerRequest)
  : cardinal;
var
  FEnv: TSynWebEnv;
begin
  try
    FEnv := TSynWebEnv.Create(AContext);
    try
      if WebBrokerDispatch(FEnv) then
        Result := 200
      else
        Result := 404;
    finally
      FEnv.Free;
    end;
  except
    on e: Exception do begin
      AContext.OutContent := StringTOUTF8('<HTML><BODY>' + '<H1>服务器运行出错</H1>' +
        '<P>' +
        UTF8ToString(AContext.Method + ' ' + AContext.URL) + '</P>' + '<P>' +
        e.Message + '</P>' + '</HTML></BODY>');
      AContext.OutContentType := HTML_CONTENT_TYPE;
      Result := 500;
    end;
  end;
end;

function TSynWebServer.WebBrokerDispatch(const AEnv: TSynWebEnv): Boolean;
var
  HTTPRequest: TSynWebRequest;
  HTTPResponse: TSynWebResponse;
begin
  HTTPRequest := TSynWebRequest.Create(AEnv);
  try
    HTTPResponse := TSynWebResponse.Create(HTTPRequest);
    try
      Result := TSynWebRequestHandler(FReqHandler).HandleRequest(HTTPRequest, HTTPResponse);
    finally
      HTTPResponse.Free;
    end;
  finally
    HTTPRequest.Free;
  end;
end;
initialization

  WebReq.WebRequestHandlerProc := GetRequestHandler;

finalization

  if RequestHandler <> nil then
    FreeAndNil(RequestHandler);

end.

