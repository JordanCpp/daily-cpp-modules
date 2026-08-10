unit WinLite.Queue;

{$mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

interface

uses
  gqueue,
  WinLite.Events;

type
  TEventInterfaceQueue = specialize TQueue<TWinLiteEvent>;

  TWinLiteQueue = record
  private
    FRunning: Boolean;
    FEvents: TEventInterfaceQueue;
    FInitialized: Boolean;
    
    procedure CheckInit; inline;
  public
    procedure Init;
    procedure Clear;

    function Empty: Boolean;
    procedure Push(const AEvent: TWinLiteEvent);
    function Pop(out AEvent: TWinLiteEvent): Boolean;
    
    function IsRunning: Boolean;
    procedure Stop;
  end;

implementation

{ TWinLiteQueue }

procedure TWinLiteQueue.CheckInit;
begin
  if not FInitialized then
  begin
    FEvents := TEventInterfaceQueue.Create;
    FRunning := True;
    FInitialized := True;
  end;
end;

procedure TWinLiteQueue.Init;
begin
  CheckInit;
end;

procedure TWinLiteQueue.Clear;
begin
  if FInitialized then
  begin
    FEvents.Free;
    FInitialized := False;
  end;
end;

function TWinLiteQueue.Empty: Boolean;
begin
  CheckInit;
  Result := FEvents.IsEmpty;
end;

procedure TWinLiteQueue.Push(const AEvent: TWinLiteEvent);
begin
  CheckInit;
  FEvents.Push(AEvent);
end;

function TWinLiteQueue.Pop(out AEvent: TWinLiteEvent): Boolean;
begin
  CheckInit;
  if not FEvents.IsEmpty then
  begin
    AEvent := FEvents.Front;
    FEvents.Pop;
    Exit(True);
  end;
  Result := False;
end;

function TWinLiteQueue.IsRunning: Boolean;
begin
  CheckInit;
  Result := FRunning;
end;

procedure TWinLiteQueue.Stop;
begin
  CheckInit;
  FRunning := False;
end;

end.
