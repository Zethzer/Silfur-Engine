@echo off
rem Compile shaders from the root of the project
rem and let the bytecode next to the corresponding shader
rem NOTE : Names must be unique between different shaders
echo Compile shaders...
pushd %~dp0\..\
(for /r %%i in (*.frag, *.vert, *.tesc, *.tese, *.geom, *.comp) do (
	%VULKAN_SDK%/Bin/glslangvalidator -V "%%i" -o "%%~dpi/%%~nxi.spv"
))
popd
pause