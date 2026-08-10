{
  Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or copy at
  https://boost.org)
}

unit WinLite.Events;

{$mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

interface

type
  TButtonState = (bsReleased = 0, bsPressed = 1);
  TMouseButton = (mbLeft = 1, mbRight = 2, mbMiddle = 3);
  TMouseScroll = (msVertical = 1, msHorizontal = 2);
  
  TEventType = (
    etNone = 0,
    etQuit = 1,
    etMouseMove,
    etMouseClick,
    etResize,
    etKeyboard,
    etGainedFocus,
    etLostFocus,
    etMouseScroll
  );
  
  TGainedFocus = record
    Type_: TEventType;
  end;

  TLostFocus = record
    Type_: TEventType;
  end;

  TQuit = record
    Type_: TEventType;
  end;

  TKeyboard = record
    Type_: TEventType;
    State: TButtonState;
    Key: Byte;
  end;

  TResize = record
    Type_: TEventType;
    Width: Integer;
    Height: Integer;
  end;

  TMouse = record
    Type_: TEventType;
    State: TButtonState;
    Button: TMouseButton;
    Scroll: TMouseScroll;
    PosX: Integer;
    PosY: Integer;
    PosRelX: Integer;
    PosRelY: Integer;
    Delta: Integer;
  end;

  TWinLiteEvent = record
  public
    function IsKeyPressed(AKey: Byte): Boolean;
    function IsKeyReleased(AKey: Byte): Boolean;
    function IsMousePressed(AButton: TMouseButton): Boolean;
    function IsMouseReleased(AButton: TMouseButton): Boolean;
  public
    case Type_: TEventType of
      etNone: ();
      etQuit: (Quit: TQuit);
      etMouseMove, etMouseClick, etMouseScroll: (Mouse: TMouse);
      etResize: (Resize: TResize);
      etKeyboard: (Keyboard: TKeyboard);
      etGainedFocus: (GainedFocus: TGainedFocus);
      etLostFocus: (LostFocus: TLostFocus);
  end;

implementation

{ TWinLiteEvent }

function TWinLiteEvent.IsKeyPressed(AKey: Byte): Boolean;
begin
  Result := (Type_ = etKeyboard) and 
            (Keyboard.Key = AKey) and 
            (Keyboard.State = bsPressed);
end;

function TWinLiteEvent.IsKeyReleased(AKey: Byte): Boolean;
begin
  Result := (Type_ = etKeyboard) and 
            (Keyboard.Key = AKey) and 
            (Keyboard.State = bsReleased);
end;

function TWinLiteEvent.IsMousePressed(AButton: TMouseButton): Boolean;
begin
  Result := (Type_ = etMouseClick) and 
            (Mouse.Button = AButton) and 
            (Mouse.State = bsPressed);
end;

function TWinLiteEvent.IsMouseReleased(AButton: TMouseButton): Boolean;
begin
  Result := (Type_ = etMouseClick) and 
            (Mouse.Button = AButton) and 
            (Mouse.State = bsReleased);
end;

end.
