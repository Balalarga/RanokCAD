@echo off
pushd %~dp0%

cmake -B Build
mklink RanokCAD.sln Build\RanokCAD.sln

popd
pause