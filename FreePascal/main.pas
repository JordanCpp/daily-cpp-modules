program main;

{$mode ObjFPC}{$H+}

uses
  WinLite.SoftwareWindow,
  WinLite.Events,
  SoftwareRender;

var
  Window: TSoftwareWindow;
  Renderer: TSoftwareRender;
  ErrStr: String;
  Event: TWinLiteEvent;
  PixelBuffer: array[0..800 * 600 - 1] of LongWord; 
begin
  if not TSoftwareWindow.Create(800, 600, 'Software Renderer Window', Window, ErrStr) then
  begin
    Writeln('Error: ', ErrStr);
    Exit;
  end;

  Renderer.Init(800, 600, 4, PByte(@PixelBuffer[0]), SizeOf(PixelBuffer));

  while Window.IsRunning do
  begin
    while Window.GetEvent(Event) do
    begin
      if Event.Type_ = etQuit then
        Window.StopEvent;
    end;

    Renderer.SetColor(TColor.Create(40, 40, 50));
    Renderer.Clear;

    Renderer.SetColor(TColor.Create(255, 0, 0));
    Renderer.Fill(100, 100, 200, 200);

    Renderer.SetColor(TColor.Create(0, 255, 0));
    Renderer.Line(0, 0, 800, 600);

    Window.Present(@PixelBuffer[0], 4, 800, 600);
  end;

  Window.Free;
end.
