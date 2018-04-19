// NAVSYS 1.2 
// enjOy[dream]	ver 1.2 apr 2018

#define GYR_R 0x1B

#define ACCEL 0x53
#define GYROS 0x68
#define MAGNT 0x1E
#include <bool.h>
#include "Arduino.h"
#include "SFE_BMP180.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "SD.h"

#define SDFILE_PIN_CS  10
#define IGNITOR 7
#define LED 4
#define TIME 300000
/*
 
	Are you proposing to slaughter our tennants?
	fafafa
*/

volatile double[13] data;

/*
	indices do buffer

	data[0] - tempo
	data[1] - temperatura
	data[2] - altura
	data[3] - altura max
	data[4] - pressao
	data[5], [6], [7] - Acelerometro (X, Y, Z)
	data[8], [9], [10] - Giroscópio	(X, Y, Z)
	data[11], [12], [13] - Magnetometro (X, Y, Z)
*/

void setup (){
    
	Wire.begin();
	Serial.begin(9600);
	// HARDWARE IRR

	//input PB0 PB1 PB2, PCINT0, PCINT1, PCINT2
	EICRA = (1 << ISC00);
	PCICR = (1 << PCIE0); // PCINT 0 
	PCMSK0 = (1 << PCINT0)|(1 << PCINT1)|(1 << PCINT2); // INT PB0 PB1 PB2
	 __asm__("nop\n\t"); 

	bmp180.begin();
	pinMode(SDFILE_PIN_CS, OUTPUT);
	pinMode(IGNITOR, OUTPUT);
	pinMode(LED, OUTPUT);

	if (!SD.begin())
	{
	    //Serial.println(F("não funciona ou não está presente"));
	    while(1);
	}
	 //Serial.println(F("Cartão de memória inicializado."));
	while(SD.exists(filename)){

	  if(i<10)
	    sprintf(filename,"0%d.TXT",i);
	  
	  else
	  sprintf(filename,"%2d.TXT",i);
	  i++;

	}
    
    sdFile = SD.open(filename, FILE_WRITE); // seta altitude inicial
    digitalWrite(LED,HIGH);
	data[2] = bmp180.altitude();
	data[3] =  data[];
	data[4] = bmp180.getPressure();
	data[1] = bmp180.getTemperatureC();


	gyros_setup();
	accel_setup();

}


void gyros_setup(){

	Wire.begin();
	Wire.beginTransmission(GYROS);
	
		Wire.write(0x17); // interr config
		Wire.write(0x01); // raw rdy enable

	int a = Wire.endTransmission();
	switch (b){
		case 0: Serial.println("GYROS INT SETUP OK"); break;
		case 1: Serial.println("GYROS INT SETUP TRANSMIT BUFF OVF"); break;
		case 2: Serial.println("GYROS INT SETUP ADDRESS NACK"); break;
		case 3: Serial.println("GYROS INT SETUP DATA NACK"); break;
		case 4: Serial.println("GYROS INT SETUP BELGIUM"); break;
	}

}

void accel_setup(){
	
	Wire.beginTransmission(ACCEL);

		Wire.write(0x2C); // modo medição
		Wire.write(0x0c);

	int a = Wire.endTransmission();
 
	Wire.beginTransmission(ACCEL);

		Wire.write(0x2D); // modo medição
		Wire.write(0x08);

	int b = Wire.endTransmission();

	Wire.beginTransmission(ACCEL);
	
		Wire.write(0x31); // resolução completa, escala +/- 2g
		Wire.write(0x0F);  

	int c = Wire.endTransmission();

	Wire.beginTransmission(ACCEL);

		Wire.write(0x2e); //enable irr
		Wire.write(0x80); //drdy

	int d = Wire.endTransmission();

	Wire.beginTransmission(ACCEL):

		Wire.write(0x2F); //map irr
		Wire.write(0x80); //irr drdy1

	int e = Wire.endTransmission();

	Wire.beginTransmission(ACCEL);

		Wire.write(0x30) //irr source
		Wire.write(0x80) //irr drdy

	int f = Wire.endTransmission()

	int status = a+b+c+d+e+f;

	status ==0 ? return true : return false;

}

void loop(){

	bool buff_rdy = false;
	bool gy_rdy = false;
	bool bmp_rdy = false;

	if (G_INT){gyro_read();}
	if (A_INT){accel_read();}
	if (M_INT){mag_read();}

	bmp_rdy = bmp_read();

	if(data[2]<(data[3]-10.0f) && !flag)
		{
		   	digitalWrite(IGNITOR,HIGH);//abre o paraquedas
		   	flag=1;
        sdFile.print(millis());
        sdFile.print(", ");
        sdFile.println("abriu");
	}

	if (bmp_rdy & gy_rdy){
		file_out();
	}
}

bool gyro_read(){
	cli();

	G_INT = false;

	Wire.beginTransmission(GYROS);
	Wire.write(GYR_R); //start with register 3.
	Wire.endTransmission();
	
	Wire.requestFrom(GYROS, 8);

	if(Wire.available() == 8){

		temp = Wire.read()<<8; //MSB t 
		temp |= Wire.read(); //LSB  t
		data[8] = Wire.read()<<8; //MSB  x
		data[8] |= Wire.read(); //LSB x
		data[9] = Wire.read()<<8; //MSB y
		data[9] |= Wire.read(); //LSB y
		data[10] = Wire.read()<<8; //MSB z
		data[10] |= Wire.read(); //LSB z
	}

	sei();
	return true;

}

bool mag_read(){ // leitura atomizada LE
	cli();
	M_INT = false;
	Wire.beginTransmission(MAGNT);
	Wire.write(0x03); //start with register 3.
	Wire.endTransmission();
	
	Wire.requestFrom(MAGNT, 6);

	if(6<=Wire.available()){

		data[11] = Wire.read()<<8; //MSB  x 
		data[11] |= Wire.read(); //LSB  x
		data[12] = Wire.read()<<8; //MSB  y
		data[12] |= Wire.read(); //LSB y
		data[13] = Wire.read()<<8; //MSB z
		data[13] |= Wire.read(); //LSB z
	}
	sei();
	return true;
}

bool acc_read(){
	
	cli();
	A_INT = false;
	Wire.beginTransmission(ACCEL);
	Wire.write(0x32); //start with register 3.
	Wire.endTransmission();
	
	Wire.requestFrom(ACC, 6);

	if(6<=Wire.available()){

		data[5] = Wire.read(); //MSB  x 
		data[5] |= Wire.read()<<8; //LSB  x
		data[6] = Wire.read(); //MSB  y
		data[6] |= Wire.read()<<8; //LSB y
		data[7] = Wire.read(); //MSB z
		data[7] |= Wire.read()<<8; //LSB z
	}
	sei();
	return true;


}

void file_out(){
	cli();
	sdFile.print(millis());
	sdFile.print(", ");
	
	for (int i = 0; i < 14; i++){
		sdFile.print(data[i]);
		sdFile.print(",");
	}

	sdfile.println();
	sdfile.flush()
	sei();

}

bool bmp_read(){
	cli();
	data[2] = bmp180.altitude();
    data[4] = bmp180.getPressure();
    data[1] = bmp180.getTemperatureC();
    
    if(data[2]>data[3]){
	  	data[3]=data[2];
	}


	if(altura<(alturamax-10.0f) && !flag){
	   	digitalWrite(IGNITOR,HIGH);//abre o paraquedas
	   	flag=1;
       sdFile.print(millis());
       sdFile.print(", ");
       sdFile.println("abriu");
	}

	sei();
	return true;
}

ISR___ (PCINT0){
	PINB0? G_INT=true:G_INT=false;
	PINB1? M_INT=true:M_INT=false;
	PINB2? A_INT=true:A_INT=false;

}