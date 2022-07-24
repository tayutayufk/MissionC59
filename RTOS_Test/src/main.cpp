// #include <Arduino.h>
// #include <MPU9250.h>
// #include <SPICREATE.h>
// #include <SPIflash.h>
// #include <LPS22HB.h>
// #include <freertos/FreeRTOS.h>    /* FreeRTOSを用いるためのヘッダファイル */
// #include <freertos/timers.h>      /* タイマを用いるためのヘッダファイル */
// #include <SDIOLogWrapper.h>

// #define LEDPIN 5

// #define FLASHCS 33
// #define LPSCS 25
// #define MPUCS 26
// #define PITCS 21

// #define CLK 18
// #define MISO 19
// #define MOSI 23

// #define F100KHZ 100000
// #define F1MHZ 1000000
// #define F10MHZ 10000000
// #define F50MHZ 50000000

// SPICreate spi;

// Flash flash;LPS lps;MPU mpu;

// TimerHandle_t thand_test;
// SDIOLogWrapper SDIO;

// xTaskHandle xlogHandle;

// void IRAM_ATTR timer_handler( void *param )
// {
//   // Serial.print("timer_handler()\n");
//   Serial.println(millis());
// }


// IRAM_ATTR void logging(void *parameters)
// {
//   portTickType xLastWakeTime = xTaskGetTickCount();
//   for (;;)
//   {
//     char bfChar[128] = "very tekitou na data\n";

//     if (SDIO.appendQueue(bfChar) == 1)
//     {
//       vTaskDelete(&xlogHandle);
//       Serial.println("queue filled!");
//       ESP.restart();
//     }

//     vTaskDelayUntil(&xLastWakeTime, 1 / portTICK_PERIOD_MS);
//   }
// }

// void setup(){
//   pinMode(LEDPIN,OUTPUT);
//   Serial.begin(115200);
//   SDIO.makeQueue(64, 128);

//   //SPI setup
//   spi = SPICreate();
//   spi.begin(VSPI,CLK,MISO,MOSI,F1MHZ);

  

//   //flash setup
//   flash = Flash();
//   flash.begin(&spi,FLASHCS,F10MHZ);
//   delay(1);

//   //accerolometer setup
//   mpu = MPU();
//   mpu.begin(&spi,MPUCS,F1MHZ);
  
//   //barometer setup
//   lps = LPS();
//   lps.begin(&spi,LPSCS,F1MHZ);

//   //bulk erase
//   // Serial.println("erase");
//   // flash.erase();
//   // Serial.println("erase done");

//   //Sensors Who Am I
//   // Serial.print("mpu : \t");
//   // Serial.println((int)mpu.WhoAmI());

//   Serial.print("lps : \t");
//   Serial.println((int)lps.WhoAmI());


//   thand_test = xTimerCreate( "TIM_TEST",  /* タイマの名称 */
//                              100,        /* 500Hz 2ms */
//                              pdTRUE,      /* 自動繰り返しの有無 */
//                              NULL,        /* ID変数のポインタ */
//                              timer_handler ); /* タイマハンドラの関数名 */
// }

// uint32_t addr = 0;
// void loop(){


//   //Flash Sample Code
//   // uint8_t data[256];
//   // uint8_t rdata[256];
  
//   // for(int i = 0;i<256;i++){
//   //   data[i] = i*2;
//   // }
//   // flash.write(addr,data);

//   // delay(1);

//   // flash.read(addr,rdata);
//   // for(int i = 0;i<256;i++){
//   //   Serial.println(rdata[i]);
//   // }
//   // addr+=256;
  
//   // lps.begin(&spi,LPSCS,F1MHZ);

//   // Accelerometer Sample
//   int16_t accData[6];
//   mpu.Get(accData);
//   Serial.printf("Acc : x:%d\ty:%d\tz:%d\n",(int)accData[0],(int)accData[1],(int)accData[2]);
//   Serial.printf("Gyro : x:%d\ty:%d\tz:%d\n",(int)accData[3],(int)accData[4],(int)accData[5]);

//   Serial.print("mpu : \t");
//   Serial.println((int)mpu.WhoAmI());

//   //Barometer Sample

//   // int barData;
//   // lps.Get(&barData);
//   // Serial.printf("barometer : %d\n",barData);


//   // Serial.print("lps : \t");
//   // Serial.println((int)lps.WhoAmI());


//   // Serial.println("fuck the world");
//   // digitalWrite(LEDPIN,HIGH);
//   // delay(100);
//   // digitalWrite(LEDPIN,LOW);
//   // delay(100);


  
//   SDIO.initSD();
//   SDIO.openFile();
//   SDIO.writeTaskCreate(APP_CPU_NUM);
//   xTaskCreateUniversal(logging, "logging", 8192, NULL, 1, &xlogHandle, PRO_CPU_NUM);

//   xTimerStart( thand_test, 0 ); /* タイマの開始 */

//   delay(10000);

//   SDIO.writeTaskDelete();
//   SDIO.closeFile();
//   SDIO.deinitSD();


// }
#include <Arduino.h>
#include <SPICREATE.h>
#include <SDIOLogWrapper.h>

#include <MPU9250.h>
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
#define loggingPeriod 1

SPICreate spi;

Flash flash;LPS lps;MPU mpu;

TimerHandle_t thand_test;


SDIOLogWrapper SDIO;

xTaskHandle xlogHandle;

IRAM_ATTR void logging(void *parameters)
{
  portTickType xLastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    char bfChar[128] = "very tekitou na data\n";

    if (SDIO.appendQueue(bfChar) == 1)
    {
      vTaskDelete(&xlogHandle);
      Serial.println("queue filled!");
      ESP.restart();
    }

    vTaskDelayUntil(&xLastWakeTime, loggingPeriod / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);

  SDIO.makeQueue(64, 128);

  pinMode(LEDPIN,OUTPUT);

  //SPI setup
  spi = SPICreate();
  spi.begin(VSPI,CLK,MISO,MOSI,F10MHZ);

  //flash setup
  flash = Flash();
  flash.begin(&spi,FLASHCS,F50MHZ);

  //accerolometer setup
  mpu = MPU();
  mpu.begin(&spi,MPUCS,F10MHZ);
  
  //barometer setup
  lps = LPS();
  lps.begin(&spi,LPSCS,F10MHZ);

  //bulk erase
  Serial.println("erase");
  flash.erase();
  Serial.println("erase done");


  
  // Flash Sample Code
  
  uint32_t addr = 0;
  uint8_t data[256];
  uint8_t rdata[256];
  
  for(int i = 0;i<256;i++){
    data[i] = i*2;
  }
  flash.write(addr,data);

  delay(1);

  flash.read(addr,rdata);
  for(int i = 0;i<256;i++){
    Serial.println(rdata[i]);
  }
  addr+=256;



  //Sensors Who Am I
  Serial.print("mpu : \t");
  Serial.println((int)mpu.WhoAmI());

  Serial.print("lps : \t");
  Serial.println((int)lps.WhoAmI());

  
  //Barometer Sample

  int barData;
  lps.Get(&barData);
  Serial.printf("barometer : %d\n",barData);

  
  // Accelerometer Sample
  int16_t accData[6];
  mpu.Get(accData);
  Serial.printf("Acc : x:%d\ty:%d\tz:%d\n",(int)accData[0],(int)accData[1],(int)accData[2]);
  Serial.printf("Gyro : x:%d\ty:%d\tz:%d\n",(int)accData[3],(int)accData[4],(int)accData[5]);


}

void loop()
{
  // put your main code here, to run repeatedly:
  while (Serial.available())
  {
    char cmd = Serial.read();

    if (cmd == 'r')
    {
      ESP.restart();
    }

    if (cmd == 'a')
    {
      SDIO.initSD();
      SDIO.openFile();
      SDIO.writeTaskCreate(APP_CPU_NUM);
      xTaskCreateUniversal(logging, "logging", 8192, NULL, 1, &xlogHandle, PRO_CPU_NUM);
    }

    if (cmd == 'g')
    {
      vTaskDelete(xlogHandle);
      delay(1000);
      SDIO.writeTaskDelete();
      SDIO.closeFile();
      SDIO.deinitSD();
      Serial.println("File Save");
    }
  }
  delay(100);
}