#include "beaglebone.h"
#include "FreeRTOS.h"
#include "task.h"
#include "debug.h"

HAL_StatusTypeDef beagleboneOff()
{
    PP_BB_DISABLE;
    PP_5V0_DISABLE;

    return HAL_OK;
}

HAL_StatusTypeDef beaglebonePower(bool enable)
{
  if (enable) {
    PP_5V0_ENABLE;
    vTaskDelay(100);
    PP_BB_ENABLE;
  } else {
    //TODO: send shutdown message to BB
    PP_BB_DISABLE;
    vTaskDelay(100);
    PP_5V0_DISABLE;
  }

  return HAL_OK;
}

void bbTask(void *pvParameters)
{
  HAL_StatusTypeDef rc;

  // power on beaglebone
  // Make sure you have the beaglebone battery connected when powering the
  // beaglebone on, to ensure it safely shuts down when the VCU is powered
  // off

  DEBUG_PRINT("Powering on beaglebone, make sure beaglebone battery is plugged in!!\n");
  rc = beaglebonePower(true);
  if (rc != HAL_OK) {
    ERROR_PRINT("Failed to power on beaglebone!\n");
  }

  while (1) {
    vTaskDelay(10000);
  }
}