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

#define F1MHZ 1000000
#define F10MHZ 10000000

Flash flash;
SPICreate spi;

void setup(){
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(115200);

  //SPI setup
  spi = SPICreate();
  spi.begin(VSPI,CLK,MISO,MOSI,F1MHZ);
  

  //flash setup
  flash = Flash();
  flash.begin(&spi,FLASHCS,F1MHZ);

  //bulk erase
  Serial.println("erase");
  //flash.erase();
  Serial.println("erase done");
}

uint32_t addr = 0;
void loop(){

  
  // uint8_t data[256];
  // uint8_t rdata[256];
  
  // for(int i = 0;i<256;i++){
  //   data[i] = i*2;
  // }
  // flash.write(addr,data);

  // delay(10000);

  // flash.read(addr,rdata);
  // for(int i = 0;i<256;i++){
  //   Serial.println(rdata[i]);
  // }
  // addr+=256;
  
  Serial.println("fuck the world");
  digitalWrite(LEDPIN,HIGH);
  delay(100);
  digitalWrite(LEDPIN,LOW);
  delay(100);

}