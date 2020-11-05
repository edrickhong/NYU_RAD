avrdude -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:$1:i
