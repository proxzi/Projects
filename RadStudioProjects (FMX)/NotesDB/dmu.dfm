object dm: Tdm
  OldCreateOrder = False
  Height = 353
  Width = 498
  object FDConnection: TFDConnection
    Params.Strings = (
      'Database=C:\Users\VD\Documents\projradstudio\labNotesDB\Notes.db'
      'DriverID=SQLite')
    LoginPrompt = False
    AfterConnect = FDConnectionAfterConnect
    BeforeConnect = FDConnectionBeforeConnect
    Left = 240
    Top = 80
  end
  object taNotes: TFDTable
    Connection = FDConnection
    UpdateOptions.UpdateTableName = 'Notes'
    TableName = 'Notes'
    Left = 296
    Top = 192
  end
  object FDGUIxWaitCursor1: TFDGUIxWaitCursor
    Provider = 'FMX'
    Left = 96
    Top = 216
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 184
    Top = 272
  end
end
