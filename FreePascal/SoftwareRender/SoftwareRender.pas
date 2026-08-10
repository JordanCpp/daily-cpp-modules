{
  Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or copy at
  https://boost.org)
}

unit SoftwareRender;

{$mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

interface

uses
  SysUtils, Math;

type
  TColor = record
    r: Byte;
    g: Byte;
    b: Byte;
    a: Byte;
    
    constructor Create(ARed, AGreen, ABlue: Byte; AAlpha: Byte = 255);
  end;

  TSoftwareRender = record
  private
    FColor: TColor;
    FWidth: PtrUInt;
    FHeight: PtrUInt;
    FBytesPerPixel: PtrUInt;
    FPixels: PByte;        
    FPixelCount: PtrUInt;  
  public
    procedure Init(AW, AH, ABytesPerPixel: PtrUInt; APixels: PByte; APixelCount: PtrUInt);
    
    procedure SetColor(AColor: TColor);
    function GetColor: TColor;
    
    procedure Clear;
    procedure Pixel(AX, AY: PtrUInt);
    procedure Line(AX0, AY0, AX1, AY1: Integer);
    procedure Fill(AX, AY, AWidth, AHeight: Integer);
    
    function GetWidth: PtrUInt;
    function GetHeight: PtrUInt;
    function GetBytesPerPixel: PtrUInt;
  end;

implementation

{ TColor }

constructor TColor.Create(ARed, AGreen, ABlue: Byte; AAlpha: Byte = 255);
begin
  r := ARed;
  g := AGreen;
  b := ABlue;
  a := AAlpha;
end;

{ TSoftwareRender }

procedure TSoftwareRender.Init(AW, AH, ABytesPerPixel: PtrUInt; APixels: PByte; APixelCount: PtrUInt);
begin
  if (ABytesPerPixel <> 3) and (ABytesPerPixel <> 4) then
    raise EInvalidArgument.Create('Only 3 or 4 bytes per pixel are supported.');

  FWidth := AW;
  FHeight := AH;
  FBytesPerPixel := ABytesPerPixel;
  FPixels := APixels;
  FPixelCount := APixelCount;
  
  // Явно инициализируем дефолтный цвет непрозрачным черным
  FColor.r := 0;
  FColor.g := 0;
  FColor.b := 0;
  FColor.a := 255;
end;

procedure TSoftwareRender.SetColor(AColor: TColor);
begin
  FColor := AColor;
end;

function TSoftwareRender.GetColor: TColor;
begin
  Result := FColor;
end;

procedure TSoftwareRender.Clear;
var
  I: PtrUInt;
begin
  if (FColor.r = FColor.g) and (FColor.g = FColor.b) and ((FBytesPerPixel = 3) or (FColor.g = FColor.a)) then
  begin
    FillChar(FPixels^, FPixelCount, FColor.r);
    Exit;
  end;

  if FBytesPerPixel = 4 then
  begin
    I := 0;
    while I < FPixelCount do
    begin
      FPixels[I + 0] := FColor.r;
      FPixels[I + 1] := FColor.g;
      FPixels[I + 2] := FColor.b;
      FPixels[I + 3] := FColor.a;
      Inc(I, 4);
    end;
  end
  else
  begin
    I := 0;
    while I < FPixelCount do
    begin
      FPixels[I + 0] := FColor.r;
      FPixels[I + 1] := FColor.g;
      FPixels[I + 2] := FColor.b;
      Inc(I, 3);
    end;
  end;
end;

procedure TSoftwareRender.Pixel(AX, AY: PtrUInt);
var
  Index: PtrUInt;
begin
  if (AX >= FWidth) or (AY >= FHeight) then
    Exit;

  Index := (AY * FWidth + AX) * FBytesPerPixel;

  FPixels[Index + 0] := FColor.r;
  FPixels[Index + 1] := FColor.g;
  FPixels[Index + 2] := FColor.b;

  if FBytesPerPixel = 4 then
    FPixels[Index + 3] := FColor.a;
end;

procedure TSoftwareRender.Line(AX0, AY0, AX1, AY1: Integer);
var
  Dx, Dy, Sx, Sy, Err, E2: Integer;
  Index: PtrUInt;
begin
  Dx := Abs(AX1 - AX0);
  Dy := Abs(AY1 - AY0);
  
  if AX0 < AX1 then Sx := 1 else Sx := -1;
  if AY0 < AY1 then Sy := 1 else Sy := -1;
  
  Err := Dx - Dy;

  while True do
  begin
    if (AX0 >= 0) and (PtrUInt(AX0) < FWidth) and
       (AY0 >= 0) and (PtrUInt(AY0) < FHeight) then
    begin
      Index := (PtrUInt(AY0) * FWidth + PtrUInt(AX0)) * FBytesPerPixel;
      FPixels[Index + 0] := FColor.r;
      FPixels[Index + 1] := FColor.g;
      FPixels[Index + 2] := FColor.b;

      if FBytesPerPixel = 4 then
        FPixels[Index + 3] := FColor.a;
    end;

    if (AX0 = AX1) and (AY0 = AY1) then
      Break;

    E2 := 2 * Err;
    if E2 > -Dy then
    begin
      Dec(Err, Dy);
      Inc(AX0, Sx);
    end;
    if E2 < Dx then
    begin
      Inc(Err, Dx);
      Inc(AY0, Sy);
    end;
  end;
end;

procedure TSoftwareRender.Fill(AX, AY, AWidth, AHeight: Integer);
var
  X0, Y0, X1, Y1, CurrX, CurrY: PtrUInt;
  RowStart: PtrUInt;
begin
  if (AWidth <= 0) or (AHeight <= 0) then
    Exit;

  X0 := PtrUInt(Max(0, AX));
  Y0 := PtrUInt(Max(0, AY));
  X1 := Min(FWidth, PtrUInt(AX + AWidth));
  Y1 := Min(FHeight, PtrUInt(AY + AHeight));

  if (X0 >= X1) or (Y0 >= Y1) then
    Exit;

  if FBytesPerPixel = 4 then
  begin
    for CurrY := Y0 to Y1 - 1 do
    begin
      RowStart := (CurrY * FWidth + X0) * 4;
      for CurrX := X0 to X1 - 1 do
      begin
        FPixels[RowStart + 0] := FColor.r;
        FPixels[RowStart + 1] := FColor.g;
        FPixels[RowStart + 2] := FColor.b;
        FPixels[RowStart + 3] := FColor.a;
        Inc(RowStart, 4);
      end;
    end;
  end
  else
  begin
    for CurrY := Y0 to Y1 - 1 do
    begin
      RowStart := (CurrY * FWidth + X0) * 3;
      for CurrX := X0 to X1 - 1 do
      begin
        FPixels[RowStart + 0] := FColor.r;
        FPixels[RowStart + 1] := FColor.g;
        FPixels[RowStart + 2] := FColor.b;
        Inc(RowStart, 3);
      end;
    end;
  end;
end;

function TSoftwareRender.GetWidth: PtrUInt;
begin
  Result := FWidth;
end;

function TSoftwareRender.GetHeight: PtrUInt;
begin
  Result := FHeight;
end;

function TSoftwareRender.GetBytesPerPixel: PtrUInt;
begin
  Result := FBytesPerPixel;
end;

end.
