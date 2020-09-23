object Form1: TForm1
  Left = 271
  Top = 114
  Caption = 'Form1'
  ClientHeight = 235
  ClientWidth = 399
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    399
    235)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 124
    Width = 20
    Height = 13
    Caption = 'Port'
  end
  object Label2: TLabel
    Left = 24
    Top = 78
    Width = 23
    Height = 13
    Caption = 'Root'
  end
  object Label3: TLabel
    Left = 168
    Top = 78
    Width = 35
    Height = 13
    Caption = 'Domain'
  end
  object lblURI: TLabel
    Left = 24
    Top = 55
    Width = 25
    Height = 13
    Caption = 'URI: '
  end
  object ButtonStart: TButton
    Left = 24
    Top = 16
    Width = 75
    Height = 25
    Action = actStart
    TabOrder = 0
  end
  object ButtonStop: TButton
    Left = 128
    Top = 16
    Width = 75
    Height = 25
    Action = actStop
    TabOrder = 1
  end
  object EditPort: TEdit
    Left = 24
    Top = 139
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '10443'
  end
  object ButtonOpenBrowser: TButton
    Left = 24
    Top = 184
    Width = 353
    Height = 25
    Action = actOpenBrowser
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 3
  end
  object EditRoot: TEdit
    Left = 24
    Top = 93
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object checkboxHTTPS: TCheckBox
    Left = 168
    Top = 141
    Width = 97
    Height = 17
    Caption = 'HTTPS'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object EditDomainName: TEdit
    Left = 168
    Top = 93
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '+'
  end
  object ActionList1: TActionList
    Left = 320
    Top = 64
    object actStart: TAction
      Caption = 'Start'
      OnExecute = actStartExecute
      OnUpdate = EnabledIfNotRunning
    end
    object actStop: TAction
      Caption = 'Stop'
      OnExecute = actStopExecute
      OnUpdate = EnabledIfRunning
    end
    object actOpenBrowser: TAction
      Caption = 'Open Browser'
      OnExecute = actOpenBrowserExecute
      OnUpdate = EnabledIfRunning
    end
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = ApplicationEvents1Idle
    Left = 320
    Top = 128
  end
end
