#-b115200 
avrdude -patmega2560 -cwiring -P/dev/ttyACM0 -D -Uflash:w:$1:i
