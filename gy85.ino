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

#define GYROS 0x68
#define GYR_R 0x1B


#include <Wire.h>

/*
 
	Are you proposing to slaughter our tennants?

*/

int MAGx,GYRx,ACCx;
int MAGy,GYRy,ACCy;
int MAGz,GYRz,ACCz;
int temp;
float tempC;



void setup(){
	Serial.begin(9600);
	Wire.begin();
    
	Wire.beginTransmission(MAGNT); //start talking
  	
	Wire.write(0x02); // Set the Register
	Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  
	int j = Wire.endTransmission();
		switch (j){
		case 0: Serial.println("MAGNT SETUP OK"); break;
		case 1: Serial.println("MAGNT SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("MAGNT SETUP ADDRESS NACK"); break;
		case 3: Serial.println("MAGNT SETUP DATA NACK"); break;
		case 4: Serial.println("MAGNT SETUP BELGIUM"); break;
	}

// ====================================================================

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

		int k = Wire.endTransmission();
		switch (k){
		case 0: Serial.println("ACCEL SETUP OK"); break;
		case 1: Serial.println("ACCEL SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("ACCEL SETUP ADDRESS NACK"); break;
		case 3: Serial.println("ACCEL SETUP DATA NACK"); break;
		case 4: Serial.println("ACCEL SETUP BELGIUM"); break;
	}

// ===================================================================


	Wire.beginTransmission(GYROS);
		Wire.write(0x16);
		Wire.write(0x1C);
	int i = Wire.endTransmission();
	switch (i){
		case 0: Serial.println("GYROS SETUP OK"); break;
		case 1: Serial.println("GYROS SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("GYROS SETUP ADDRESS NACK"); break;
		case 3: Serial.println("GYROS SETUP DATA NACK"); break;
		case 4: Serial.println("GYROS SETUP BELGIUM"); break;
	}

}


void loop(){
	unsigned long int t0 = micros();
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
//--------------------------------------------------

// ------------------ LER GYROS -----------------------------

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

	tempC = temp/280 + 82.142857;
//--------------------------------------------------

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
unsigned long int tf = micros();

	unsigned long int dt = (tf - t0);




// --------------------------------- Cuspir resultados
	Serial.print(ACCx);
	Serial.print(",");
	Serial.print(ACCy);
	Serial.print(",");
	Serial.print(ACCz);
	Serial.print(",");
	Serial.print(GYRx);
	Serial.print(",");
	Serial.print(GYRy);
	Serial.print(",");
	Serial.print(GYRz);
	Serial.print(",");
	Serial.print(MAGx);
	Serial.print(",");
	Serial.print(MAGy);
	Serial.print(",");
	Serial.print(MAGz);
	Serial.print(",");
	Serial.print(dt);
	Serial.print(",");
	Serial.print(tempC);
	Serial.println(" ");

}

