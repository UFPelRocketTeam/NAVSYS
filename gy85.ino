#define ACCEL 0x53 // ADDR ACELEROMETRO
#define GYROS 0x69
#define MAGNT 0x1E
#define XLO 0X32 //REGS ACELEROMETRO
#define XHI 0x33
#define YLO 0x34
#define YHI 0x35
#define ZLO 0x36
#define ZHI 0x37
#include <Wire.h>
#include <stdio.h>



/*
  ADXL345 Datasheet: https://goo.gl/uOZc2b
  Table 16. Register Map Address
  Hex   Dec Name  Type  Reset_Value   Description
  0x2D  45 POWER_CTL  R/W   00000000  Power-saving features control.
  (...)
  0x32  50 DATAX0  X-Axis Data 0. EIXO X LSB
  0x33  51 DATAX1  X-Axis Data 1. EIXO X MSB
  0x34  52 DATAY0  Y-Axis Data 0. EIXO Y LSB
  0x35  53 DATAY1  Y-Axis Data 1. EIXO Y MSB
  0x36  54 DATAZ0  Z-Axis Data 0. EIXO Z LSB
  0x37  55 DATAZ1  Z-Axis Data 1. EIXO Z MSB

*/

int x, xLSB, xMSB;
int y, yLSB, yMSB;
int z, zLSB, zMSB;


void setup(){
	
	Wire.begin(9600);        // join i2c bus (address optional for master)
	Serial.begin(9600);  // start serial for output

	int i = ACCEL_SETUP();
	(i == 0)? Serial.println("ACCEL ARM") : Serial.println("ACCEL FAIL"); //diag gyro

	//MAGNT_SETUP();
	//GYROS_SETUP();
}

void loop(){

	// LER ACCEL EIXO X
	Wire.beginTransmission(ACCEL);
	Wire.write(XLO);
	Wire.write(XHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		xLSB = Wire.read();
		xMSB = Wire.read();

		x = (xMSB << 8) + xLSB;
	}

	// LER ACCEL EIXO Y

	Wire.beginTransmission(ACCEL);
	Wire.write(YLO);
	Wire.write(YHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		yLSB = Wire.read();
		yMSB = Wire.read();

		y = (yMSB << 8) + yLSB;
	}


	// LER ACCEL EIXO Z

	Wire.beginTransmission(ACCEL);
	Wire.write(ZLO);
	Wire.write(ZHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		zLSB = Wire.read();
		zMSB = Wire.read();

		z = (zMSB << 8) + zLSB;
	}


	Serial.print("X = ");
	Serial.print(x);
	Serial.print("\t");
	Serial.print("\t Y = ");
	Serial.print(y);
	Serial.print("\t");
	Serial.print("\t Z = ");
	Serial.print(z);
	Serial.println("\t");

}

int ACCEL_SETUP(){
	
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

	int i = Wire.endTransmission();
	switch (i){ // case switch pra debugar
		case 0: Serial.println("OK"); break;
		case 1: Serial.println("TRANSMIT BUFFER OVF"); break;
		case 2: Serial.println("ADDR NACK"); break;
		case 3: Serial.println("DATA NACK"); break;
		case 4: Serial.println("BELGIUM"); break;
	}	

	return i;

}

/* void MAGNT_SETUP(){

}

void GYROS_SETUP(){

} */
