
@echo off
Setlocal EnableDelayedExpansion
 
Call :Timer Start
FOR /L %%i IN (1,1,10) DO (
    make_mat.exe 2.jpg 2_.f
)
Call :Timer End
 
pause>nul
goto :eof
 
:Timer
  if "%~1"=="Start" (
    Set StartTime=%time%
    Echo Время запуска    !StartTime!
  ) else (
    Set EndTime=%time%
    Echo Время завершения !EndTime!
    Call :TimeElapsed "%StartTime%" "!EndTime!" ret
    Echo Прошло                  !ret! c.
  )
exit /B
 
:TimeElapsed %1-StartTime %2-EndTime %3-var_result
  Call :TimeToMSec "%~1" TimeS_ms
  Call :TimeToMSec "%~2" TimeE_ms
  Set /A diff=TimeE_ms-TimeS_ms
  Set /A diffSS=diff/100
  Set /A diffms=%diff% %% 100
  if "%diffms:~1%"=="" Set diffms=0%diffms%
  Set %3=%diffSS%,%diffms%
Exit /B
 
:TimeToMSec %1-Time 2-var_mSec
  For /F "Tokens=1-4 Delims=,:" %%A in ("%~1") do (
    Set /A HH=%%A
    Set MM=1%%B& Set /A MM=!MM!-100
    Set SS=1%%C& Set /A SS=!SS!-100
    Set mS=1%%D& Set /A mS=!mS!-100
  )
  Set /A %~2=(HH*60*60+MM*60+SS)*100+mS
Exit /B