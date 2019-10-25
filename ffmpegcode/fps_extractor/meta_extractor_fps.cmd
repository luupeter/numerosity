echo off
ECHO 'hello world'
SET mypath=%~dp0
echo %mypath%

ruby %mypath%meta_extractor_fps.rb %*

pause
