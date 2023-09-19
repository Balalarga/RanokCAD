@echo off
pushd %~dp0%

cmake -B Debug
mklink RanokCAD.sln Build\RanokCAD.sln

popd
pause