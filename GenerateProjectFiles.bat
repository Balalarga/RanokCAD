@echo off
pushd %~dp0%

cmake -B Build -G "Visual Studio 17 2022" -DVCPKG_TARGET_TRIPLET=x64-windows-static
mklink RanokCAD.sln Build\RanokCAD.sln

popd
pause
