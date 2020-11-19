#include "Arduino.h"
#include "ttype.h"

#define LED_BUILTIN 13
#define MIN_DELAY 2

//A pixel is to a stepper
struct Pixel{
	u32 delay = MIN_DELAY; 
	//TODO: compact this
	u32 pin;
	u32 state = 1;
	u32 dir; 
};


constexpr u8 ReverseBitOrder(u8 b){ // performs simple bit swapping
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

void WriteStep(u32 start_pin,u32 step){
	digitalWrite(start_pin, (step) & 1);
	digitalWrite(start_pin + 1,(step >> 1) & 1);
	digitalWrite(start_pin + 2,(step >> 2) & 1);
	digitalWrite(start_pin + 3,(step >> 3) & 1);
}


void UpdatePixel(Pixel* pixel){
	pixel->state <<= pixel->dir;
	pixel->state = (pixel->state >> 1) | (pixel->state); // cycles the bit back if we overflow

	WriteStep(pixel->pin,pixel->state);
}

void WriteToScreen(Pixel* buffer,u32 len){

	u32 start_pin = 0;

	//Using this in case we need to do things w the x and y coords
	for(u32 y = 0; y < len; y++){
		for(u32 x = 0; x < len; x++){
			//NOTE: Assumes a certain matrix setup
			Pixel* p = buffer + (y * len) + x;
			UpdatePixel(p);
		}
	}
}

extern "C" void __cxa_pure_virtual(void)
{
	// call to a pure virtual function happened ... wow, should never happen ... stop
	for(;;)
	{

	}
}


void Startup(){


	for(u32 i = 0; i < 53; i+=4){
		pinMode(i + 0,OUTPUT);
		pinMode(i + 1,OUTPUT);
		pinMode(i + 2,OUTPUT);
		pinMode(i + 3,OUTPUT);
	}

}

void Loop(){
	digitalWrite(13,HIGH);
	//digitalWrite(5,HIGH);
}



//NOTE: this just lights an LED for now
s32 main(s32 argc,s8** argv){

	init();
	//Serial.begin(9600);

	Startup();

	while(1){
		Loop();
	}

	return 0;
}
