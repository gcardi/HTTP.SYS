{ *************************************************************************** }
{  SynWebEnv.pas is the 1st file of SynBroker Project                         }
{  by c5soft@189.cn  Version 0.9.0.0  2018-5-27                               }
{ *************************************************************************** }
unit SynWebEnv;

interface
uses Classes, SynCommons, SynCrtSock;
type
  TSynWebEnv = class
  protected
    FHost, FMethod, FURL, FPathInfo, FQueryString, FAnchor: RawUTF8;
    FRemoteIP: string;
    FContext: THttpServerRequest;
    function PrepareURL: RawUTF8; virtual;
  public
    property Context: THttpServerRequest read FContext;
    property Host: RawUTF8 read FHost;
    property Method: RawUTF8 read FMethod;
    property URL: RawUTF8 read FURL;
    property PathInfo: RawUTF8 read FPathInfo;
    property QueryString: RawUTF8 read FQueryString;
    property Anchor: RawUTF8 read FAnchor;
    property RemoteIP: string read FRemoteIP;
    function GetHeader(const AUpKey: RawUTF8; const ASource: RawUTF8 = ''; const Sep: AnsiChar = #13): RawUTF8;
    constructor Create(const AContext: THttpServerRequest);
    procedure OutStream(const AStream: TStream);
    procedure OutFile(const AFileName: string);
    procedure OutHeader(const ANewHeaderAppended: RawUTF8);
    procedure OutJSon(const AOutput: PDocVariantData); overload;
    procedure OutJSon(const AOutput: RawUTF8); overload;
{$IFDEF UNICODE}
    procedure OutHtml(const AOutput: RawUTF8); overload;
    procedure OutHtml(const AOutput: string); overload;
    procedure OutXML(const AOutput: RawUTF8); overload;
    procedure OutXML(const AOutput: string); overload;
{$ELSE}
    procedure OutHtml(const AOutput: string); overload;
    procedure OutXML(const AOutput: string); overload;
{$ENDIF}

  end;

implementation

{ TSynWebEnv }

function InferContentType(const AFileName: string): RawUTF8;
var
  pFileName: PUTF8Char;
begin
  Result := '';
  pFileName := PUTF8Char(StringToUTF8(AFileName));
  if IdemFileExt(pFileName, '.HTML') or IdemFileExt(pFileName, '.HTM') then Result := HTML_CONTENT_TYPE
  else if IdemFileExt(pFileName, '.JPG') then Result := JPEG_CONTENT_TYPE
  else if IdemFileExt(pFileName, '.PNG') then Result := 'image/png'
  else if IdemFileExt(pFileName, '.GIF') then Result := 'image/gif'
  else if IdemFileExt(pFileName, '.ICO') then Result := 'image/x-icon'
  else if IdemFileExt(pFileName, '.JS') then Result := 'application/x-javascript'
  else if IdemFileExt(pFileName, '.CSS') then Result := 'text/css'
  else Result := 'application/octet-stream';
end;


{$IFDEF UNICODE}

procedure TSynWebEnv.OutHtml(const AOutput: string);
begin
  OutHtml(StringToUTF8(AOutput));
end;

procedure TSynWebEnv.OutHtml(const AOutput: RawUTF8);
begin
  Context.OutContent := AOutput;
  Context.OutContentType := 'text/html; charset=utf-8';
end;

procedure TSynWebEnv.OutXML(const AOutput: string);
begin
  OutXML(StringToUTF8(AOutput));
end;

procedure TSynWebEnv.OutXML(const AOutput: RawUTF8);
begin
  Context.OutContent := AOutput;
  Context.OutContentType := 'text/xml; charset=utf-8';
end;
{$ELSE}

procedure TSynWebEnv.OutHtml(const AOutput: string);
begin
  Context.OutContent := StringToUTF8(AOutput);
  Context.OutContentType := 'text/html; charset=utf-8';
end;

procedure TSynWebEnv.OutXML(const AOutput: string);
begin
  Context.OutContent := StringToUTF8(AOutput);
  Context.OutContentType := 'text/xml; charset=utf-8';
end;

{$ENDIF}

procedure TSynWebEnv.OutJSon(const AOutput: PDocVariantData);
begin
  OutJSon(AOutput.ToJson);
end;

procedure TSynWebEnv.OutJSon(const AOutput: RawUTF8);
begin
  Context.OutContent := AOutput;
  Context.OutContentType := 'application/json; charset=utf-8';
end;

procedure TSynWebEnv.OutHeader(const ANewHeaderAppended: RawUTF8);
begin
  if Length(ANewHeaderAppended) > 0 then begin
    with FContext do begin
      if Length(OutCustomHeaders) > 0 then OutCustomHeaders := OutCustomHeaders + #13#10;
      OutCustomHeaders := OutCustomHeaders + ANewHeaderAppended;
    end;
  end;
end;

procedure TSynWebEnv.OutFile(const AFileName: string);
var
  ContentType: RawUTF8;
begin
  Context.OutContent := StringToUTF8(AFileName);
  Context.OutContentType := HTTP_RESP_STATICFILE;
  ContentType := InferContentType(AFileName);
  if Length(ContentType) > 0 then OutHeader(HEADER_CONTENT_TYPE + ContentType);
end;

function TSynWebEnv.GetHeader(const AUpKey: RawUTF8; const ASource: RawUTF8 = ''; const Sep: AnsiChar = #13): RawUTF8;
var
  P, pUpKey, pSource: PUTF8Char;
  cVal: RawUTF8;
begin
  pUpKey := PUTF8Char(AUpKey);
  if ASource = '' then pSource := PUTF8Char(FContext.InHeaders)
  else pSource := PUTF8Char(ASource);
  P := StrPosI(pUpKey, pSource);
  if IdemPCharAndGetNextItem(P, pUpKey, cVal, Sep) then Result := Trim(cVal)
  else Result := '';
end;

constructor TSynWebEnv.Create(const AContext: THttpServerRequest);
var
  nQPos, nAPos: Integer;
begin
  FContext := AContext;
  FHost := GetHeader('HOST:');
  FRemoteIP := UTF8ToString(GetHeader('REMOTEIP:'));
  FMethod := FContext.Method;
  FURL := PrepareURL;
  nAPos := {$IFDEF UNICODE}SynCommons.Pos{$ELSE}Pos{$ENDIF}('#', FURL);
  nQPos := {$IFDEF UNICODE}SynCommons.Pos{$ELSE}Pos{$ENDIF}('?', FURL);
  if nQPos > 0 then begin
    FPathInfo := copy(FURL, 1, nQPos - 1);
    if nAPos > nQPos then begin
      FQueryString := copy(FURL, nQPos + 1, nAPos - nQPos - 1);
      FAnchor := copy(FURL, nAPos + 1, Length(FURL) - nAPos);
    end else begin
      FQueryString := copy(FURL, nQPos + 1, Length(FURL) - nQPos);
      FAnchor := '';
    end;
  end else begin
    FQueryString := '';
    if nAPos > 0 then begin
      FPathInfo := copy(FURL, 1, nAPos - 1);
      FAnchor := copy(FURL, nAPos + 1, Length(FURL) - nAPos);
    end else begin
      FPathInfo := FURL;
      FAnchor := '';
    end;
  end;
end;

function TSynWebEnv.PrepareURL: RawUTF8;
begin
  Result := Context.URL;
end;

procedure TSynWebEnv.OutStream(const AStream: TStream);
var
  Buffer: SockString;
begin
  SetLength(Buffer, AStream.Size);
  AStream.Read(Buffer[1], AStream.Size);
  Context.OutContent := Buffer;
end;

end.

