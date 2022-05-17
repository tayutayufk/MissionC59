/*
 Author : Yuta Takayasu
 Date : 2022/5/14

    Library for operating SDCard with ESP32.
*/


#pragma once


#ifndef _SDLOG_H_
#define _SDLOG_H_
 

#include <Arduino.h>

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

class SD{
    sdmmc_host_t host;
    sdmmc_slot_config_t slot_config;
    esp_vfs_fat_sdmmc_mount_config_t mount_config;
    sdmmc_card_t *card;
public:
    void begin(int CMD,int D0,int D1,int D2,int D3);
};


void SD::begin(int CMD=15,int D0=2,int D1=4,int D2=12,int D3=13){
    host = SDMMC_HOST_DEFAULT();
    slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    pinMode(CMD, PULLUP);   // CMD, needed in 4- and 1- line modes
    pinMode(D0, PULLUP);    // D0, needed in 4- and 1-line modes
    pinMode(D1, PULLUP);    // D1, needed in 4-line mode only
    pinMode(D2, PULLUP);   // D2, needed in 4-line mode only
    pinMode(D3, PULLUP);   // D3, needed in 4- and 1-line modes

    mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    
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
    }
}


 
#endif // _CALC_H_