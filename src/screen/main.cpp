#include "WProgram.h"
#include "ttype.h"

#define LED_BUILTIN 13

constexpr u8 ReverseBitOrder(u8 b){ // performs simple bit swapping
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

enum StepperState : u8{
	STEPPER_NONE = 0,
	STEPPER_L1 = 1,
	STEPPER_L2 = 2,
	STEPPER_L3 = 4,

	STEPPER_R1 = ReverseBitOrder(STEPPER_L1),
	STEPPER_R2 = ReverseBitOrder(STEPPER_L2),
	STEPPER_R3 = ReverseBitOrder(STEPPER_L3),
};

void WriteStep(u32 start_pin,StepperState step){
	digitalWrite(start_pin, (step) ^ 1);
	digitalWrite(start_pin + 1,(step >> 1) ^ 1);
	digitalWrite(start_pin + 2,(step >> 2) ^ 1);
	digitalWrite(start_pin + 3,(step >> 3) ^ 1);
}

void WriteToScreen(u8* buffer,u32 len){

	u32 start_pin = 0;

	//Using this in case we need to do things w the x and y coords
	for(u32 y = 0; y < len; y++){
		for(u32 x = 0; x < len; x++){
			//NOTE: Assumes a certain matrix setup
			WriteStep(start_pin,(StepperState)buffer[ (y * len) + x]); 
			start_pin += 4;
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
	//		Serial.println("Hello world");
}



//NOTE: this just lights an LED for now
s32 main(s32 argc,s8** argv){

	init();
	Serial.begin(9600);

	Startup();

	while(1){
		Loop();
	}

	return 0;
}
