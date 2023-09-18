@echo off
pushd %~dp0%

cmake -B Debug
mklink RanokCAD.sln Debug\RanokCAD.sln

popd
pause