#include <Arduino.h>
#include <MPU9250.h>
#include <SPICREATE.h>
#include <SPIflash.h>
#include <LPS22HB.h>


#define LEDPIN 5

#define FLASHCS 33
#define LPSCS 25
#define MPUCS 26
#define PITCS 21

#define CLK 18
#define MISO 19
#define MOSI 23

#define F100KHZ 100000
#define F1MHZ 1000000
#define F10MHZ 10000000
#define F50MHZ 50000000

SPICreate spi;

Flash flash;LPS lps;MPU mpu;

void setup(){
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(115200);

  //SPI setup
  spi = SPICreate();
  spi.begin(VSPI,CLK,MISO,MOSI,F1MHZ);

  

  //flash setup
  // flash = Flash();
  // flash.begin(&spi,FLASHCS,F10MHZ);
  // delay(1);

  //accerolometer setup
  mpu = MPU();
  mpu.begin(&spi,MPUCS,F10MHZ);
  delay(1);

  //barometer setup
  lps = LPS();
  lps.begin(&spi,LPSCS,F10MHZ);
  delay(1);

  //bulk erase
  // Serial.println("erase");
  // flash.erase();
  // Serial.println("erase done");

  //Sensors Who Am I
  // Serial.print("mpu : \t");
  // Serial.println((int)mpu.WhoAmI());

  Serial.print("lps : \t");
  Serial.println((int)lps.WhoAmI());

}

uint32_t addr = 0;
void loop(){


  //Flash Sample Code
  // uint8_t data[256];
  // uint8_t rdata[256];
  
  // for(int i = 0;i<256;i++){
  //   data[i] = i*2;
  // }
  // flash.write(addr,data);

  // delay(1);

  // flash.read(addr,rdata);
  // for(int i = 0;i<256;i++){
  //   Serial.println(rdata[i]);
  // }
  // addr+=256;
  
  // lps.begin(&spi,LPSCS,F1MHZ);

  //Accelerometer Sample
  int16_t accData[6];
  mpu.Get(accData);
  Serial.printf("Acc : x:%d\ty:%d\tz:%d\n",(int)accData[0],(int)accData[1],(int)accData[2]);
  Serial.printf("Gyro : x:%d\ty:%d\tz:%d\n",(int)accData[3],(int)accData[4],(int)accData[5]);

  Serial.print("mpu : \t");
  Serial.println((int)mpu.WhoAmI());

  //Barometer Sample

  int barData;
  lps.Get(&barData);
  Serial.printf("barometer : %d\n",barData);


  Serial.print("lps : \t");
  Serial.println((int)lps.WhoAmI());

  delay(20);


  // Serial.println("fuck the world");
  // digitalWrite(LEDPIN,HIGH);
  // delay(100);
  // digitalWrite(LEDPIN,LOW);
  // delay(100);

}