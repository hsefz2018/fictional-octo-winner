@echo off
if "%1"=="" goto loop
copy num%1.in num.in>nul
echo num TEST
echo Data %1
time<enter
num
time<enter
fc num%1.out num.out
pause
del num.in
del num.out
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
