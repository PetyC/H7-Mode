copy STM32H743_FreeRTOS\STM32H743_FreeRTOS.hex .\output.hex

hex2bin output.hex

for /f %%i in ('dir /b output.bin') do (
set indexdx=%%~zi
)
ECHO %indexdx%

srec_cat.exe output.bin -Binary -crop 0 %indexdx%  -STM32_Little_Endian %indexdx%  -o app.bin -Binary





