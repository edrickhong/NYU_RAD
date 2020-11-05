#include "WProgram.h"
#include "ttype.h"

#define LED_BUILTIN 13

extern "C" void __cxa_pure_virtual(void)
{
	// call to a pure virtual function happened ... wow, should never happen ... stop
	for(;;)
	{

	}
}



//NOTE: this just lights an LED for now
s32 main(s32 argc,s8** argv){

	init();

	Serial.begin(9600);
	pinMode(LED_BUILTIN,OUTPUT);

	s32 state = HIGH;

	while(1){

		Serial.println("Hello world");
		digitalWrite(LED_BUILTIN,state);

		(state == HIGH) ? (state = LOW) : (state = HIGH);
		delay(1000);
	}

	return 0;
}
