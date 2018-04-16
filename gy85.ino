//SKETCHING
#define ACCEL 0x53
#define GYROS 0x68
#define MAGNT 0x1E
#include <bool.h>
#include <Wire.h>

bool M_INT, A_INT, G_INT;

void setup(){
	Serial.begin(115200);
	Wire.begin();

	// IRR uc

	//input PB0 PB1 PB2, PCINT0, PCINT1, PCINT2
	EICRA = (1 << ISC00);
	PCICR = (1 << PCIE0); // PCINT 0 
	PCMSK0 = (1 << PCINT0)|(1 << PCINT1)|(1 << PCINT2); // INT PB0 PB1 PB2
	 __asm__("nop\n\t"); 
	// IRR sensor

	
	
	Wire.beginTransmission(ACCEL);

		Wire.write(0x2E); //int enable
		Wire.write(0x80); // DRDY INT
		Wire.write(0x2F); //int_map 
		Wire.write(0x80); //manda pro pino de int do gy85
		//instr
		Wire.write(0x30); //int source
		//instr

	a = Wire.endTransmission();
	switch (a){
		case 0: Serial.println("ACCEL INT SETUP OK"); break;
		case 1: Serial.println("ACCEL INT SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("ACCEL INT SETUP ADDRESS NACK"); break;
		case 3: Serial.println("ACCEL INT SETUP DATA NACK"); break;
		case 4: Serial.println("ACCEL INT SETUP BELGIUM"); break;
	}

	Wire.begin();
	Wire.beginTransmission(GYROS);
	
		Wire.write(0x17); // interr config
		Wire.write(0x01); // raw rdy enable

	b = Wire.endTransmission();
	switch (b){
		case 0: Serial.println("GYROS INT SETUP OK"); break;
		case 1: Serial.println("GYROS INT SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("GYROS INT SETUP ADDRESS NACK"); break;
		case 3: Serial.println("GYROS INT SETUP DATA NACK"); break;
		case 4: Serial.println("GYROS INT SETUP BELGIUM"); break;
	}



	sei();
}

void loop() {
	check IRR

}

void data_read(){
	if(G_INT){
		cli();
		G_INT = false;
		Wire.beginTransmission(GYROS);
		Wire.write(GYR_R); //start with register 3.
		Wire.endTransmission();
		
		Wire.requestFrom(GYROS, 8);
	
			if(Wire.available() == 8){
	
				temp = Wire.read()<<8; //MSB  x 
				temp |= Wire.read(); //LSB  x
				GYRx = Wire.read()<<8; //MSB  z
				GYRx |= Wire.read(); //LSB z
				GYRy = Wire.read()<<8; //MSB y
				GYRy |= Wire.read(); //LSB y
				GYRz = Wire.read()<<8; //MSB y
				GYRz |= Wire.read(); //LSB y
	}
}

void buffer_assemble(){ 

}

void info_broadcast() {}

ISR___ (PCINT0){
	PINB0? G_INT=true:G_INT=false;
	PINB1? M_INT=true:M_INT=false;
	PINB2? A_INT=true:A_INT=false;

}