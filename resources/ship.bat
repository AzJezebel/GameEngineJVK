@echo Should copy necessary directories near .exe
SET mypath=%~dp0

@echo %mypath%

call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
devenv %mypath%/../Build/JVKEngine.sln /build Shipping
robocopy %mypath%/ %mypath%/../Build/bin/Shipping/resources /E /mt /z
robocopy %mypath%/../Assets/ %mypath%/../Build/bin/Shipping/Assets /E /mt /z

#pause
