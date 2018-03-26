//ENDEREÇOS I2C
#define ACCEL 0x53
#define GYROS 0x68
#define MAGNT 0x1E

//REGMAP ACELEROMETRO
#define ACCXLO 0X32
#define ACCXHI 0x33
#define ACCYLO 0x34
#define ACCYHI 0x35
#define ACCZLO 0x36
#define ACCZHI 0x37
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

	Wire.beginTransmission(ACCEL);

		Wire.write(0x2D); // modo medição
		Wire.write(8);
		
		Wire.write(0x21); // desativa modo double tap
		Wire.write(0);
		Wire.write(0x22); // idem
		Wire.write(0);
		Wire.write(0x23); // idem
		Wire.write(0);
		Wire.write(0x31); // resolução completa, escala +/- 2g
		Wire.write(0x08);  

	Wire.endTransmission();
}


void loop(){
// ------------------ LER MAGNETOMETRO -----------------------------

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


// ------------------ LER ACELEROMETRO -----------------------------

	Wire.beginTransmission(ACCEL);
	Wire.write(ACCXLO);
	Wire.write(ACCXHI);
	Wire.endTransmission();
	
	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCx = Wire.read() ;
		ACCx |= Wire.read()<< 8;
	}
	
	// LER ACCEL EIXO Y
	
	Wire.beginTransmission(ACCEL);
	Wire.write(ACCYLO);
	Wire.write(ACCYHI);
	Wire.endTransmission();
	
	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCy = Wire.read();
		ACCy |= Wire.read() << 8;
	}
	
	
	// LER ACCEL EIXO Z

	Wire.beginTransmission(ACCEL);
	Wire.write(ACCZLO);
	Wire.write(ACCZHI);
	Wire.endTransmission();
	
	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCz = Wire.read();
		ACCz |= Wire.read()<<8;
	}




// --------------------------------- Cuspir resultados


	Serial.print(MAGx);
	Serial.print(" ");
	Serial.print(MAGy);
	Serial.print(" ");
	Serial.print(MAGz);
	Serial.print(" ");
	Serial.print(ACCx);
	Serial.print(" ");
	Serial.print(ACCy);
	Serial.print(" ");
	Serial.print(ACCz);
	Serial.println(" ");

}

