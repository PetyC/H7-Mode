/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "../../lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void encoder_init(void);
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t *indev_encoder;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
  static lv_indev_drv_t indev_drv;

  /*------------------
   * Encoder
   * -----------------*/

  /*Initialize your encoder if you have*/
  encoder_init();

  /*Register a encoder input device*/
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = encoder_read;
  indev_encoder = lv_indev_drv_register(&indev_drv);

  /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
   *add objects to the group with `lv_group_add_obj(group, obj)`
   *and assign this input device to group to navigate in it:
   *`lv_indev_set_group(indev_encoder, group);`*/
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Encoder
 * -----------------*/

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
extern osMessageQId KEY_QueueHandle;

/*Initialize your keypad*/
static void encoder_init(void)
{
  /*Your code comes here*/
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{

  static uint32_t last_key = 0;
  uint8_t act_enc = 0;

  osEvent Even = osMessageGet(KEY_QueueHandle, 0);

  if (osEventMessage == Even.status)
  {
    act_enc = Even.value.v;
  }
  else
  {
    act_enc = 0;
  }

  if (act_enc != 0)
  {
    switch (act_enc)
    {
    case 1:
      act_enc = LV_KEY_DOWN; //  LV_KEY_RIGHT LV_KEY_DOWN
      data->state = LV_INDEV_STATE_RELEASED;
      data->enc_diff++;
      break;
    case 2:
      act_enc = LV_KEY_UP;  // LV_KEY_LEFT  LV_KEY_UP
      data->state = LV_INDEV_STATE_RELEASED;
      data->enc_diff--;
      break;
    case 3:
      act_enc = LV_KEY_ENTER;
      data->state = LV_INDEV_STATE_PRESSED;
      break;
    }
    last_key = (uint32_t)act_enc;
  }
  data->key = last_key;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
