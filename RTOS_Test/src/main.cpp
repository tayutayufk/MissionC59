#include <Arduino.h>

#include <MPU9250.h>
#include <SPICREATE.h>
#include <SPIflash.h>
#include <LPS22HB.h>

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h> 


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

SPICreate spi;

Flash flash;LPS lps;MPU mpu;

void setup() {
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(115200);

  //SPI setup
  spi = SPICreate();
  spi.begin(VSPI,CLK,MISO,MOSI,F1MHZ);

  //flash setup
  flash = Flash();
  flash.begin(&spi,FLASHCS,F10MHZ);
  delay(1);

  //accerolometer setup
  mpu = MPU();
  mpu.begin(&spi,MPUCS,F10MHZ);
  delay(1);

  //barometer setup
  lps = LPS();
  lps.begin(&spi,LPSCS,F1MHZ);
  delay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
}