object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 718
  ClientWidth = 725
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 160
    Top = 20
    Width = 87
    Height = 13
    Caption = #1058#1077#1082#1089#1090' '#1087#1088#1086#1075#1088#1072#1084#1084#1099
  end
  object Label2: TLabel
    Left = 488
    Top = 21
    Width = 107
    Height = 13
    Caption = #1054#1073#1098#1077#1082#1090#1085#1099#1077' '#1082#1086#1084#1072#1085#1076#1099
  end
  object Label3: TLabel
    Left = 8
    Top = 380
    Width = 138
    Height = 13
    Caption = #1058#1072#1073#1083#1080#1094#1072' '#1080#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088#1086#1074
  end
  object Label4: TLabel
    Left = 175
    Top = 380
    Width = 174
    Height = 13
    Caption = #1058#1072#1073#1083#1080#1094#1072' '#1094#1077#1083#1086#1095#1080#1089#1083#1077#1085#1085#1099#1093' '#1082#1086#1085#1089#1090#1072#1085#1090
  end
  object Memo1: TMemo
    Left = 8
    Top = 40
    Width = 369
    Height = 313
    Lines.Strings = (
      '')
    TabOrder = 0
  end
  object Begin: TButton
    Left = 302
    Top = 8
    Width = 75
    Height = 25
    Caption = #1053#1072#1095#1072#1090#1100
    TabOrder = 1
    OnClick = BeginClick
  end
  object Identifiers: TStringGrid
    Left = 8
    Top = 399
    Width = 137
    Height = 313
    ColCount = 2
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object Integers: TStringGrid
    Left = 184
    Top = 399
    Width = 137
    Height = 313
    ColCount = 2
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object Memo: TMemo
    Left = 8
    Top = 39
    Width = 393
    Height = 313
    Lines.Strings = (
      '')
    ScrollBars = ssVertical
    TabOrder = 4
  end
  object TranslationRes: TMemo
    Left = 456
    Top = 40
    Width = 201
    Height = 313
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 5
  end
end
