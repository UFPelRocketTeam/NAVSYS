//altimetrotwks1.3
//alteraçao
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

#include "Arduino.h"
#include "SFE_BMP180.h"
//#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "SD.h"

#define SDFILE_PIN_CS  10
#define IGNITOR 7
#define LED 4
#define TIME 10000

double altura;
double alturamax;
double pressao;
double temperatura;
int i=0;
int flag=0;

int MAGx,GYRx,ACCx;
int MAGy,GYRy,ACCy;
int MAGz,GYRz,ACCz;

File sdFile;
SFE_BMP180 bmp180;
char filename[7]="00.TXT";  //nome do arquivo inicial

void setup()
{
  Serial.begin(9600);
  while (!Serial) ;
    Serial.println("Start");
    Serial.println("1");
    bmp180.begin();
    Serial.println("2");
    Wire.begin();
    Serial.println("3");
    pinMode(SDFILE_PIN_CS, OUTPUT);
    Serial.println("4");
    pinMode(IGNITOR, OUTPUT);
    Serial.println("5");
      pinMode(LED, OUTPUT);
    Serial.println("Foi!!! =D");
  if (!SD.begin())
  {
    Serial.println(F("KEBAB REMOVED"));
    while(1);
  }
  Serial.println(F("É HORA DO SHOW."));
  while(SD.exists(filename))
  {
    if(i<10)
    sprintf(filename,"0%d.TXT",i);
    else
    sprintf(filename,"%2d.TXT",i);
    i++;
  }
  sdFile = SD.open(filename, FILE_WRITE);
  digitalWrite(LED,HIGH);
    altura = bmp180.altitude();
    alturamax=altura;
    pressao = bmp180.getPressure();
    temperatura = bmp180.getTemperatureC();

  Wire.beginTransmission(ACCEL);

    Wire.write(0x2D); // modo medição
    Wire.write(8);
  Wire.endTransmission(); 
    
    Wire.beginTransmission(ACCEL);
    Wire.write(0x21); // desativa modo double tap
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(ACCEL);
    Wire.write(0x22); // idem
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(ACCEL);
    Wire.write(0x23); // idem
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(ACCEL);
    Wire.write(0x31); // resolução completa, escala +/- 16g
    Wire.write(0x0B);  // 0.004 g por LSB
    Wire.endTransmission();


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
   altura = bmp180.altitude();
    pressao = bmp180.getPressure();
    temperatura = bmp180.getTemperatureC();
   
        if(altura<(alturamax-10.0f) && !flag)
        {
            digitalWrite(IGNITOR,HIGH);//abre o paraquedas
            flag=1;
        sdFile.print(millis());
        sdFile.print(", ");
        sdFile.println("abriu");
        }

 	if(altura > alturamax){
      alturamax = altura;
    }
// ------------------ LER MAGNETOMETRO -----------------------------
  
  Wire.beginTransmission(MAGNT);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
  Wire.requestFrom(MAGNT, 6);

  if(6==Wire.available()){

    MAGx = Wire.read()<<8; //MSB  x 
    MAGx |= Wire.read(); //LSB  x
    MAGy = Wire.read()<<8; //MSB  z
    MAGy |= Wire.read(); //LSB z
    MAGz = Wire.read()<<8; //MSB y
    MAGz |= Wire.read(); //LSB y
  }
//--------------------------------------------------

// ------------------ LER GYROS -----------------------------

  Wire.beginTransmission(GYROS);
  Wire.write(GYR_R); //start with register 3.
  Wire.endTransmission();
  
  Wire.requestFrom(GYROS, 8);

  if(Wire.available() == 8){

    int temp = Wire.read()<<8; //MSB  x 
    temp |= Wire.read(); //LSB  x
    GYRx = Wire.read()<<8; //MSB  z
    GYRx |= Wire.read(); //LSB z
    GYRy = Wire.read()<<8; //MSB y
    GYRy |= Wire.read(); //LSB y
    GYRz = Wire.read()<<8; //MSB y
    GYRz |= Wire.read(); //LSB y

  }

  
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
  
//--------------------------------------------------

  sdFile.print(millis());
  sdFile.print(", ");
  sdFile.print(altura);
  sdFile.print(", ");
  sdFile.print(pressao);
  sdFile.print(", ");
  sdFile.print(temperatura);
  sdFile.print(",");
  sdFile.print(ACCx);
  sdFile.print(",");
  sdFile.print(ACCy);
  sdFile.print(",");
  sdFile.print(ACCz);
  sdFile.print(",");
  sdFile.print(GYRx);
  sdFile.print(",");
  sdFile.print(GYRy);
  sdFile.print(",");
  sdFile.print(GYRz);
  sdFile.print(",");
  sdFile.print(MAGx);
  sdFile.print(",");
  sdFile.print(MAGy);
  sdFile.print(",");
  sdFile.print(MAGz);
  sdFile.println();
  sdFile.flush();
  /*
      if(millis()>TIME)
    {
       sdFile.close();
       digitalWrite(LED,LOW);
    }
    */
}
