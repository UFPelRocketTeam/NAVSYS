//ENDEREÇOS I2C
#define ACCEL 0x53
#define GYROS 0x68
#define MAGNT 0x1E

#include <Wire.h>

/*
 
	Are you proposing to slaughter our tennants?

*/

int MAGx,GYRx,ACCx;
int MAGy,GYRy,ACCy;
int MAGz,GYRz,ACCz;



void setup(){
  Serial.begin(9600);
  Wire.begin();
  
  
  Wire.beginTransmission(MAGNT); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}


void loop(){
	Wire.beginTransmission(MAGNT);
	Wire.write(0x03); //start with register 3.
	Wire.endTransmission();
	
	Wire.requestFrom(MAGNT, 6);

	if(6<=Wire.available()){

		MAGx = Wire.read()<<8; //MSB  x 
		MAGx |= Wire.read(); //LSB  x
		MAGz = Wire.read()<<8; //MSB  z
		MAGz |= Wire.read(); //LSB z
		MAGy = Wire.read()<<8; //MSB y
		MAGy |= Wire.read(); //LSB y
 	}

	Serial.print(MAGx);
	Serial.print(" ");
	Serial.print(MAGy);
	Serial.print(" ");
	Serial.print(MAGz);
	Serial.println(" ");

}
