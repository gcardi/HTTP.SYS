object WebModule1: TWebModule1
  OnCreate = WebModuleCreate
  Actions = <
    item
      Name = 'ReverseStringAction'
      PathInfo = '/ReverseString'
    end
    item
      Name = 'ServerFunctionInvokerAction'
      PathInfo = '/ServerFunctionInvoker'
    end
    item
      Default = True
      Name = 'DefaultHandler'
      PathInfo = '/'
      OnAction = WebModule1DefaultHandlerAction
    end>
  BeforeDispatch = WebModuleBeforeDispatch
  Height = 369
  Width = 545
  object HTTPSoapDispatcher1: THTTPSoapDispatcher
    Dispatcher = HTTPSoapCppInvoker1
    WebDispatch.PathInfo = 'soap*'
    Left = 60
    Top = 11
  end
  object HTTPSoapCppInvoker1: THTTPSoapCppInvoker
    Converter.Options = [soSendMultiRefObj, soTryAllSchema, soUTF8InHeader]
    Left = 60
    Top = 67
  end
  object WSDLHTMLPublish1: TWSDLHTMLPublish
    WebDispatch.MethodType = mtAny
    WebDispatch.PathInfo = 'wsdl*'
    TargetNamespace = 'http://tempuri.org/'
    PublishOptions = [poPublishLocationAsSecure, poUTF8ContentType]
    Left = 60
    Top = 123
  end
  object PageProducer1: TPageProducer
    Left = 56
    Top = 192
  end
  object DSProxyGenerator1: TDSProxyGenerator
    ExcludeClasses = 'DSMetadata'
    MetaDataProvider = DSServerMetaDataProvider1
    Writer = 'Java Script REST'
    Left = 200
    Top = 192
  end
  object WebFileDispatcher1: TWebFileDispatcher
    WebFileExtensions = <
      item
        MimeType = 'text/css'
        Extensions = 'css'
      end
      item
        MimeType = 'text/javascript'
        Extensions = 'js'
      end
      item
        MimeType = 'image/x-png'
        Extensions = 'png'
      end
      item
        MimeType = 'text/html'
        Extensions = 'htm;html'
      end
      item
        MimeType = 'image/jpeg'
        Extensions = 'jpg;jpeg;jpe'
      end
      item
        MimeType = 'image/gif'
        Extensions = 'gif'
      end>
    BeforeDispatch = WebFileDispatcher1BeforeDispatch
    WebDirectories = <
      item
        DirectoryAction = dirInclude
        DirectoryMask = '*'
      end
      item
        DirectoryAction = dirExclude
        DirectoryMask = '\templates\*'
      end>
    RootDirectory = '.'
    VirtualPath = '/'
    Left = 200
    Top = 120
  end
  object DSHTTPWebDispatcher1: TDSHTTPWebDispatcher
    Server = DSServer1
    Filters = <>
    WebDispatch.PathInfo = 'datasnap*'
    Left = 200
    Top = 64
  end
  object DSServer1: TDSServer
    Left = 200
    Top = 8
  end
  object DSServerClass1: TDSServerClass
    OnGetClass = DSServerClass1GetClass
    Server = DSServer1
    Left = 344
    Top = 8
  end
  object DSServerMetaDataProvider1: TDSServerMetaDataProvider
    Server = DSServer1
    Left = 344
    Top = 192
  end
  object ReverseString: TPageProducer
    HTMLFile = 'templates\ReverseString.html'
    OnHTMLTag = ServerFunctionInvokerHTMLTag
    Left = 320
    Top = 104
  end
  object ServerFunctionInvoker: TPageProducer
    HTMLFile = 'Templates\ServerFunctionInvoker.html'
    OnHTMLTag = ServerFunctionInvokerHTMLTag
    Left = 432
    Top = 96
  end
  object DSAuthenticationManager1: TDSAuthenticationManager
    OnUserAuthenticate = DSAuthenticationManager1UserAuthenticate
    OnUserAuthorize = DSAuthenticationManager1UserAuthorize
    Roles = <>
    Left = 212
    Top = 261
  end
end
