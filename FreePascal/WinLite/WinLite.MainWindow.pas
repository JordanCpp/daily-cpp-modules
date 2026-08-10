unit WinLite.MainWindow;

{$mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

interface

uses
  Windows, 
  WinLite.Events, 
  WinLite.Queue;

const
  CLASS_NAME = 'MainWindow';

type
  TMainWindow = class
  private
    FHwnd: HWND;
    FHdc: HDC;
    FEvents: TWinLiteQueue;

    function Handler(AMessage: UINT; AWParam: WPARAM; ALParam: LPARAM): LRESULT;
  public
    constructor CreateWithHwnd(AHwnd: HWND);
    
    class function Create(AWidth, AHeight: Integer; const ATitle: String; out AWindow: TMainWindow; out AError: String): Boolean;
    
    destructor Destroy; override;

    procedure PollEvents;
    function GetEvent(out AEvent: TWinLiteEvent): Boolean;
    procedure StopEvent;
    function IsRunning: Boolean;
    function GetHdc: HDC;
  end;

function WndProc(AHwnd: HWND; AMessage: UINT; AWParam: WPARAM; ALParam: LPARAM): LRESULT; stdcall;

implementation

function WndProc(AHwnd: HWND; AMessage: UINT; AWParam: WPARAM; ALParam: LPARAM): LRESULT; stdcall;
var
  WindowInstance: TMainWindow;
begin
  WindowInstance := TMainWindow(GetWindowLongPtrA(AHwnd, GWLP_USERDATA));
  
  if WindowInstance <> nil then
    Exit(WindowInstance.Handler(AMessage, AWParam, ALParam));

  Result := DefWindowProcA(AHwnd, AMessage, AWParam, ALParam);
end;

{ TMainWindow }

constructor TMainWindow.CreateWithHwnd(AHwnd: HWND);
begin
  inherited Create;
  FHwnd := AHwnd;
  FEvents.Init;
end;

destructor TMainWindow.Destroy;
begin
  FEvents.Clear;
  
  if (FHdc <> 0) and (FHwnd <> 0) then
    ReleaseDC(FHwnd, FHdc);

  if FHwnd <> 0 then
    DestroyWindow(FHwnd);

  inherited Destroy;
end;

class function TMainWindow.Create(AWidth, AHeight: Integer; const ATitle: String; out AWindow: TMainWindow; out AError: String): Boolean;
var
  Instance: HMODULE;
  WindowClass: TWndClassExA;
  WindowRect: Windows.RECT;
  Style: DWORD;
  FinalWidth, FinalHeight: Integer;
  ScreenWidth, ScreenHeight: Integer;
  PosX, PosY: Integer;
  Hwnd: Windows.HWND;
  SetWindowRet: PtrInt;
begin
  AWindow := nil;
  AError := '';

  Instance := GetModuleHandleA(nil);
  if Instance = 0 then
  begin
    AError := 'GetModuleHandleA failed';
    Exit(False);
  end;

  FillChar(WindowClass, SizeOf(TWndClassExA), 0);
  WindowClass.cbSize := SizeOf(TWndClassExA);
  WindowClass.hInstance := Instance;
  WindowClass.lpszClassName := CLASS_NAME;
  WindowClass.lpfnWndProc := @WndProc;
  WindowClass.style := CS_HREDRAW or CS_VREDRAW;
  WindowClass.hbrBackground := GetStockObject(BLACK_BRUSH);
  WindowClass.hIcon := LoadIconA(0, IDI_APPLICATION);
  WindowClass.hCursor := LoadCursorA(0, IDC_ARROW);

  if not GetClassInfoExA(Instance, CLASS_NAME, @WindowClass) then
  begin
    if RegisterClassExA(@WindowClass) = 0 then
    begin
      AError := 'RegisterClassExA failed';
      Exit(False);
    end;
  end;

  WindowRect.Left := 0;
  WindowRect.Top := 0;
  WindowRect.Right := AWidth;
  WindowRect.Bottom := AHeight;
  Style := WS_OVERLAPPED or WS_SYSMENU or WS_CAPTION or WS_MINIMIZEBOX;

  AdjustWindowRect(WindowRect, Style, False);

  FinalWidth := WindowRect.Right - WindowRect.Left;
  FinalHeight := WindowRect.Bottom - WindowRect.Top;

  ScreenWidth := GetSystemMetrics(SM_CXSCREEN);
  ScreenHeight := GetSystemMetrics(SM_CYSCREEN);

  PosX := (ScreenWidth - FinalWidth) div 2;
  PosY := (ScreenHeight - FinalHeight) div 2;

  Hwnd := CreateWindowA(CLASS_NAME, PChar(ATitle), WS_OVERLAPPED or WS_SYSMENU, PosX, PosY, FinalWidth, FinalHeight, 0, 0, Instance, nil);

  if Hwnd = 0 then
  begin
    AError := 'CreateWindowA failed';
    Exit(False);
  end;

  AWindow := TMainWindow.CreateWithHwnd(Hwnd);

  SetLastError(0);
  SetWindowRet := SetWindowLongPtrA(Hwnd, GWLP_USERDATA, PtrInt(AWindow));
  
  if (SetWindowRet = 0) and (GetLastError() <> 0) then
  begin
    AWindow.Free;
    AWindow := nil;
    AError := 'SetWindowLongPtrA failed';
    Exit(False);
  end;

  AWindow.FHdc := GetDC(Hwnd);
  if AWindow.FHdc = 0 then
  begin
    AWindow.Free;
    AWindow := nil;
    AError := 'GetDC failed';
    Exit(False);
  end;

  ShowWindow(Hwnd, SW_SHOW);
  UpdateWindow(Hwnd);

  Result := True;
end;

procedure TMainWindow.PollEvents;
var
  Msg: TMSG;
begin
  while PeekMessageA(@Msg, 0, 0, 0, PM_REMOVE) do
  begin
    TranslateMessage(@Msg);
    DispatchMessageA(@Msg);
  end;
end;

function TMainWindow.GetEvent(out AEvent: TWinLiteEvent): Boolean;
begin
  if not FEvents.Empty then
    Exit(FEvents.Pop(AEvent));

  PollEvents;

  if not FEvents.Empty then
    Exit(FEvents.Pop(AEvent));

  Result := False;
end;

procedure TMainWindow.StopEvent;
begin
  FEvents.Stop;
end;

function TMainWindow.IsRunning: Boolean;
begin
  Result := FEvents.IsRunning;
end;

function TMainWindow.GetHdc: HDC;
begin
  Result := FHdc;
end;

function TMainWindow.Handler(AMessage: UINT; AWParam: WPARAM; ALParam: LPARAM): LRESULT;
var
  Event: TWinLiteEvent;
begin
  FillChar(Event, SizeOf(TWinLiteEvent), 0);

  case AMessage of
    WM_PAINT:
      begin
      end;

    WM_DESTROY:
      begin
      end;

    WM_MOUSEMOVE:
      begin
        Event.Type_ := etMouseMove;
        Event.Mouse.PosX := LoWord(ALParam);
        Event.Mouse.PosY := HiWord(ALParam);
        FEvents.Push(Event);
      end;

    WM_LBUTTONDOWN, WM_LBUTTONUP,
    WM_RBUTTONDOWN, WM_RBUTTONUP,
    WM_MBUTTONDOWN, WM_MBUTTONUP:
      begin
        Event.Type_ := etMouseClick;
        Event.Mouse.PosX := LoWord(ALParam);
        Event.Mouse.PosY := HiWord(ALParam);

        if (AMessage = WM_LBUTTONDOWN) or (AMessage = WM_RBUTTONDOWN) or (AMessage = WM_MBUTTONDOWN) then
          Event.Mouse.State := bsPressed
        else
          Event.Mouse.State := bsReleased;

        if (AMessage = WM_LBUTTONDOWN) or (AMessage = WM_LBUTTONUP) then
          Event.Mouse.Button := mbLeft
        else if (AMessage = WM_RBUTTONDOWN) or (AMessage = WM_RBUTTONUP) then
          Event.Mouse.Button := mbRight
        else
          Event.Mouse.Button := mbMiddle;

        FEvents.Push(Event);
      end;

    WM_SIZE:
      begin
        Event.Type_ := etResize;
        Event.Resize.Width := LoWord(ALParam);
        Event.Resize.Height := HiWord(ALParam);
        FEvents.Push(Event);
      end;

    WM_CLOSE:
      begin
        Event.Type_ := etQuit;
        FEvents.Push(Event);
        PostQuitMessage(0);
      end;

    WM_KEYDOWN, WM_SYSKEYDOWN:
      begin
        Event.Type_ := etKeyboard;
        Event.Keyboard.State := bsPressed;
        Event.Keyboard.Key := Byte(AWParam);
        FEvents.Push(Event);
      end;

    WM_KEYUP, WM_SYSKEYUP:
      begin
        Event.Type_ := etKeyboard;
        Event.Keyboard.State := bsReleased;
        Event.Keyboard.Key := Byte(AWParam);
        FEvents.Push(Event);
      end;

    WM_SETFOCUS:
      begin
        Event.Type_ := etGainedFocus;
        FEvents.Push(Event);
      end;

    WM_KILLFOCUS:
      begin
        Event.Type_ := etLostFocus;
        FEvents.Push(Event);
      end;

    WM_MOUSEWHEEL, WM_MOUSEHWHEEL:
      begin
        Event.Type_ := etMouseScroll;
        Event.Mouse.PosX := LoWord(ALParam);
        Event.Mouse.PosY := HiWord(ALParam);
        Event.Mouse.Delta := SmallInt(HiWord(AWParam));
        
        if AMessage = WM_MOUSEWHEEL then
          Event.Mouse.Scroll := msVertical
        else
          Event.Mouse.Scroll := msHorizontal;
          
        FEvents.Push(Event);
      end;
  end;

  Result := DefWindowProcA(FHwnd, AMessage, AWParam, ALParam);
end;

end.
