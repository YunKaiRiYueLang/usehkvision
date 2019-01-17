@echo off

cd /d %~dp0

vc_redist.x86.exe /install /quiet /norestart

VC_x86Runtime.exe /q

