@echo off
pushd %~dp0%

cmake -B Build -G "Visual Studio 17 2022"
mklink RanokCAD.sln Build\RanokCAD.sln

popd
pause