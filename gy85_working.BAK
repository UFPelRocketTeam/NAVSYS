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

//REGMAP MAGNETOMETRO
#define MAGXHI 0x03
#define MAGXLO 0x04
#define MAGYHI 0x05
#define MAGYLO 0x06
#define MAGZHI 0x07
#define MAGZLO 0x08

//REGMAP GYROS
#define TEMPHI 0X1B
#define TEMPLO 0X1C
#define GYRXHI 0X1D
#define GYRXLO 0X2E
#define GYRYHI 0X1F
#define GYRYLO 0X20
#define GYRZHI 0X21
#define GYRZLO 0X22

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

#include <Wire.h>
#include <stdio.h>
#include <math.h>


/*
 
	Are you proposing to slaughter our tennants?

*/

unsigned long int TF, T0, DT; // comentar fora, apenas pra debug
int MAGx, MAGxLSB, MAGxMSB;
int MAGy, MAGyLSB, MAGyMSB;
int MAGz, MAGzLSB, MAGzMSB;

int GYRx, GYRxLSB, GYRxMSB;
int GYRy, GYRyLSB, GYRyMSB;
int GYRz, GYRzLSB, GYRzMSB;
int TEMP, TLO, THI;

int ACCx, ACCxLSB, ACCxMSB;
int ACCy, ACCyLSB, ACCyMSB;
int ACCz, ACCzLSB, ACCzMSB;
//double XADJ, YADJ, ZADJ;

void setup(){
	
	Wire.begin(9600);        // join i2c bus (address optional for master)
	Serial.begin(9600);  // start serial for output

	int i = ACCEL_SETUP();
	(i == 0)? Serial.println("ACCEL ARM") : Serial.println("ACCEL FAIL"); //diag acc
	delay(500);
	
	int j = MAGNT_SETUP();
	(j == 0)? Serial.println("MAGNT ARM") : Serial.println("MAGNT FAIL"); //diag gyro
	delay(500);

	int k = GYROS_SETUP();
	(k == 0)? Serial.println("GYROS ARM") : Serial.println("GYROS FAIL"); //diag gyro
	delay(500);

	//Serial.println("\tACC X\tACC Y\tACC Z\tMAG X\tMAG Y\tMAG Z\tGYR X\tGYR Y\tGYR Z\tTEMP\tREQTIME");
}

void loop(){
 T0 = micros();
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H                                                           H
// H        				ACCELEROMETER  					   H
// H                                                           H
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

	Wire.beginTransmission(ACCEL);
	Wire.write(ACCXLO);
	Wire.write(ACCXHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCxLSB = Wire.read();
		ACCxMSB = Wire.read();

		ACCx = ((ACCxMSB << 8) + ACCxLSB);
	}

	// LER ACCEL EIXO Y

	Wire.beginTransmission(ACCEL);
	Wire.write(ACCYLO);
	Wire.write(ACCYHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCyLSB = Wire.read();
		ACCyMSB = Wire.read();

		ACCy = ((ACCyMSB << 8) + ACCyLSB);
	}


	// LER ACCEL EIXO Z

	Wire.beginTransmission(ACCEL);
	Wire.write(ACCZLO);
	Wire.write(ACCZHI);
	Wire.endTransmission();

	Wire.requestFrom(ACCEL, 2);
	if (Wire.available() <= 2){
		ACCzLSB = Wire.read();
		ACCzMSB = Wire.read();

		ACCz = ((ACCzMSB << 8) + ACCzLSB);
	}

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H                                                           H
// H        				GYROSCOPE   					   H
// H                                                           H
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

	Wire.beginTransmission(GYROS);
	Wire.write(GYRXLO);
	Wire.write(GYRXHI);
	Wire.endTransmission();

	Wire.requestFrom(GYROS, 2);
	if (Wire.available() <= 2){
		GYRxLSB = Wire.read();
		GYRxMSB = Wire.read();

		GYRx = ((GYRxMSB << 8) + GYRxLSB);
	}

	// LER GYROS EIXO Y

	Wire.beginTransmission(GYROS);
	Wire.write(GYRYLO);
	Wire.write(GYRYHI);
	Wire.endTransmission();

	Wire.requestFrom(GYROS, 2);
	if (Wire.available() <= 2){
		GYRyLSB = Wire.read();
		GYRyMSB = Wire.read();

		GYRy = ((GYRyMSB << 8) + GYRyLSB);
	}


	// LER GYROS EIXO Z

	Wire.beginTransmission(GYROS);
	Wire.write(GYRZLO);
	Wire.write(GYRZHI);
	Wire.endTransmission();

	Wire.requestFrom(GYROS, 2);
	if (Wire.available() <= 2){
		GYRzLSB = Wire.read();
		GYRzMSB = Wire.read();

		GYRz = ((GYRzMSB << 8) + GYRzLSB);
	}

	Wire.beginTransmission(GYROS);
	Wire.write(TEMPLO);
	Wire.write(TEMPHI);
	Wire.endTransmission();

	Wire.requestFrom(GYROS, 2);
	if (Wire.available() <= 2){
		TLO = Wire.read();
		THI = Wire.read();

		TEMP = ((THI << 8) + TLO);
	}

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H                                                           H
// H        				MAGNETOMETER   					   H
// H                                                           H
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

	Wire.beginTransmission(MAGNT);
	Wire.write(MAGXLO);
	Wire.write(MAGXHI);
	Wire.endTransmission();

	Wire.requestFrom(MAGNT, 2);
	if (Wire.available() <= 2){
		MAGxLSB = Wire.read();
		MAGxMSB = Wire.read();

		MAGx = ((MAGxMSB << 8) + MAGxLSB);
	}

	// LER MAGNT EIXO Y

	Wire.beginTransmission(MAGNT);
	Wire.write(MAGYLO);
	Wire.write(MAGYHI);
	Wire.endTransmission();

	Wire.requestFrom(MAGNT, 2);
	if (Wire.available() <= 2){
		MAGyLSB = Wire.read();
		MAGyMSB = Wire.read();

		MAGy = ((MAGyMSB << 8) + MAGyLSB);
	}


	// LER MAGNT EIXO Z

	Wire.beginTransmission(MAGNT);
	Wire.write(MAGZLO);
	Wire.write(MAGZHI);
	Wire.endTransmission();

	Wire.requestFrom(MAGNT, 2);
	if (Wire.available() <= 2){
		MAGzLSB = Wire.read();
		MAGzMSB = Wire.read();

		MAGz = ((MAGzMSB << 8) + MAGzLSB);
	}

	


// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
	Serial.print(MAGx);
	Serial.print(" ");
	Serial.print(MAGy);
	Serial.print(" ");
	Serial.print(MAGz);
	Serial.println(" ");
	TF = micros();	
	DT = (TF - T0)/4;
//Serial.println("ACC X, ACC Y, ACC Z, MAG X, MAG Y, MAG Z, GYR X, GYR Y, GYR Z, TEMP");
/*
	Serial.print(ACCx);
	Serial.print(" ");
	Serial.print(ACCy);
	Serial.print(" ");
	Serial.print(ACCz);
	Serial.print(" ");
	Serial.print(GYRx);
	Serial.print(" ");
	Serial.print(GYRy);
	Serial.print(" ");
	Serial.print(GYRz);
	Serial.print(" ");
	Serial.print(DT);
	Serial.println();
*/	
}

// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H                                                           H
// H        				SETUPS       					   H
// H                                                           H
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

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
		case 0: Serial.println("ACCEL OK"); break;
		case 1: Serial.println("ACCEL TRANSMIT BUFFER OVF"); break;
		case 2: Serial.println("ACCEL ADDR NACK"); break;
		case 3: Serial.println("ACCEL DATA NACK"); break;
		case 4: Serial.println("ACCEL BELGIUM"); break;
	}	

	return i;

}
int MAGNT_SETUP(){
	
	Wire.beginTransmission(MAGNT); //open communication with HMC5883
	Wire.write(0x02); //select mode register
	Wire.write(0x00); //continuous measurement mode
	Wire.write(0x00); //reg de conf
	Wire.write(0x78); // 75hz output rate, 8 medidas por amostra
	int i = Wire.endTransmission();
	switch (i){ // case switch pra debugar
		case 0: Serial.println("MAGNT OK"); break;
		case 1: Serial.println("MAGNT TRANSMIT BUFFER OVF"); break;
		case 2: Serial.println("MAGNT ADDR NACK"); break;
		case 3: Serial.println("MAGNT DATA NACK"); break;
		case 4: Serial.println("MAGNT BELGIUM"); break;
	}	

	return i;

}

int GYROS_SETUP(){

	Wire.beginTransmission(GYROS); //open communication with HMC5883
	Wire.write(0x16); //select mode register
	Wire.write(0x19); //2000deg/s LPF 188hz BW, 1khz rate
	int i = Wire.endTransmission();
	switch (i){ // case switch pra debugar
		case 0: Serial.println("GYROS OK"); break;
		case 1: Serial.println("GYROS TRANSMIT BUFFER OVF"); break;
		case 2: Serial.println("GYROS ADDR NACK"); break;
		case 3: Serial.println("GYROS DATA NACK"); break;
		case 4: Serial.println("GYROS BELGIUM"); break;
	}	

	return i;

	
}
