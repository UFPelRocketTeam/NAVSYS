//altimetrotwks1.3

#include "Arduino.h"
#include "SFE_BMP180.h"
//#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "SD.h"

#define SDFILE_PIN_CS  10
#define IGNITOR 7
#define LED 4
#define TIME 300000

double altura;
double alturamax;
double pressao;
double temperatura;
int i=0;
int flag=0;

File sdFile;
SFE_BMP180 bmp180;
char filename[7]="00.TXT";  //nome do arquivo inicial

void setup() 
{
    Serial.begin(9600);
    while (!Serial) ;
    //Serial.println("Start");
    //Serial.println("1");
    bmp180.begin();
    //Serial.println("2");
    Wire.begin();
    //Serial.println("3");
    pinMode(SDFILE_PIN_CS, OUTPUT);
    //Serial.println("4");
  	pinMode(IGNITOR, OUTPUT);
    //Serial.println("5");
	  pinMode(LED, OUTPUT);
    //Serial.println("Foi!!! =D");
	
    if (!SD.begin()) 
    {
        //Serial.println(F("não funciona ou não está presente")); 
        while(1);
    }
     //Serial.println(F("Cartão de memória inicializado.")); 
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
	
}

void loop()
{
    while(millis()<=TIME)
    {
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
    if(altura>alturamax)
	  alturamax=altura;    
    if (sdFile) 
    {
        sdFile.print(millis());
        sdFile.print(", ");
        sdFile.print(altura);
        sdFile.print(", ");
        sdFile.print(pressao);
        sdFile.print(", ");
        sdFile.println(temperatura);
        sdFile.print("\n");
     } 
    else 
    {
       Serial.println(F("Erro no arquivo."));
    }
 }
    if(millis()>TIME)
    {
       sdFile.close();
       digitalWrite(LED,LOW);
    }
}

