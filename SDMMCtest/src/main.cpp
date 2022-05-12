#include <Arduino.h>
#include <MPU9250.h>
#include <SPICREATE.h>
#include <SPIflash.h>
#include <LPS22HB.h>

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
 
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"


static const char *TAG = "example";

#define MOUNT_POINT "/sdcard"

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
  Serial.println("system begin");

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

  pinMode(15, PULLUP);   // CMD, needed in 4- and 1- line modes
  pinMode(2, PULLUP);    // D0, needed in 4- and 1-line modes
  pinMode(4, PULLUP);    // D1, needed in 4-line mode only
  pinMode(12, PULLUP);   // D2, needed in 4-line mode only
  pinMode(13, PULLUP);   // D3, needed in 4- and 1-line modes

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };
  
  sdmmc_card_t *card;
  esp_err_t ret;
  ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
        Serial.println("Failed to mount filesystem. "
            "If you want the card to be formatted, set format_if_mount_failed = true.");
    } else {
        Serial.println("Failed to initialize the card  "
            "Make sure SD card lines have pull-up resistors in place.");
    }
    return;
  }


  

}



uint32_t addr = 0;
//uint8_t writeData[256];
char writeData[1024];

void loop(){
  
  digitalWrite(LEDPIN,HIGH);
  FILE* f = fopen("/sdcard/hello.txt", "w");
  if (f == NULL) {
      ESP_LOGE(TAG, "Failed to open file for writing");
      return;
  }
  //make write Data
  //strcpy(writeData,"hello\n");

  char data[1024] = "hello,";
  for(int i = 0;i < 100;i++){
    fwrite(data,1,5,f);
  }
  fclose(f);
  Serial.println("write hello !");
  digitalWrite(LEDPIN,LOW);
  delay(10000);
}