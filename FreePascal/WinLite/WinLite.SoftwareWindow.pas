unit WinLite.SoftwareWindow;

{$mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

interface

uses
  Windows,
  WinLite.Events,
  WinLite.MainWindow;

type
  TSoftwareWindow = class
  private
    FBitmapInfo: BITMAPINFO;
    FImpl: TMainWindow;

    constructor CreatePrivate(AImpl: TMainWindow);
  public
    class function Create(AWidth, AHeight: Integer; const ATitle: String; out AWindow: TSoftwareWindow; out AError: String): Boolean;
    
    destructor Destroy; override;

    function IsRunning: Boolean;
    procedure StopEvent;
    function GetEvent(out AEvent: TWinLiteEvent): Boolean;
    procedure Present(APixels: Pointer; ABytes: Byte; AWidth, AHeight: Integer);
  end;

implementation

{ TSoftwareWindow }

constructor TSoftwareWindow.CreatePrivate(AImpl: TMainWindow);
begin
  inherited Create;
  FImpl := AImpl;
  FillChar(FBitmapInfo, SizeOf(BITMAPINFO), 0);
end;

destructor TSoftwareWindow.Destroy;
begin
  if FImpl <> nil then
    FImpl.Free;
  inherited Destroy;
end;

class function TSoftwareWindow.Create(AWidth, AHeight: Integer; const ATitle: String; out AWindow: TSoftwareWindow; out AError: String): Boolean;
var
  MainWindowInstance: TMainWindow;
begin
  AWindow := nil;
  AError := '';

  if not TMainWindow.Create(AWidth, AHeight, ATitle, MainWindowInstance, AError) then
    Exit(False);

  AWindow := TSoftwareWindow.CreatePrivate(MainWindowInstance);
  Result := True;
end;

function TSoftwareWindow.IsRunning: Boolean;
begin
  Result := FImpl.IsRunning;
end;

procedure TSoftwareWindow.StopEvent;
begin
  FImpl.StopEvent;
end;

function TSoftwareWindow.GetEvent(out AEvent: TWinLiteEvent): Boolean;
begin
  Result := FImpl.GetEvent(AEvent);
end;

procedure TSoftwareWindow.Present(APixels: Pointer; ABytes: Byte; AWidth, AHeight: Integer);
begin
  FBitmapInfo.bmiHeader.biSize := SizeOf(BITMAPINFOHEADER);
  FBitmapInfo.bmiHeader.biWidth := AWidth;
  FBitmapInfo.bmiHeader.biHeight := -AHeight; // Отрицательная высота для Top-Down формата (0,0 в левом верхнем углу)
  FBitmapInfo.bmiHeader.biPlanes := 1;
  FBitmapInfo.bmiHeader.biBitCount := ABytes * 8;
  FBitmapInfo.bmiHeader.biCompression := BI_RGB;

  SetDIBitsToDevice(
    FImpl.GetHdc, 
    0, 0, 
    AWidth, AHeight, 
    0, 0, 
    0, AHeight, 
    APixels, 
    FBitmapInfo, 
    DIB_RGB_COLORS
  );
end;

end.
