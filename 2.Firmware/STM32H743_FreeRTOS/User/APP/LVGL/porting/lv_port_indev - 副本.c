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
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y);

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);


/*
static void button_init(void);
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);
*/
/**********************
 *  STATIC VARIABLES
 **********************/

lv_indev_t * indev_keypad;
//lv_indev_t * indev_button;



/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;

    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

    /*------------------
     * Button
     * -----------------*/

    /*Initialize your button if you have*/
   // button_init();

    /*Register a button input device*/
   // lv_indev_drv_init(&indev_drv);
   // indev_drv.type = LV_INDEV_TYPE_BUTTON;
   // indev_drv.read_cb = button_read;
   // indev_button = lv_indev_drv_register(&indev_drv);

    /*Assign buttons to points on the screen*/
   // static const lv_point_t btn_points[2] = {
   //         {10, 10},   /*Button 0 -> x:10; y:10*/
   //         {40, 100},  /*Button 1 -> x:40; y:100*/
   // };
  //  lv_indev_set_button_points(indev_button, btn_points);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
/*Get the x and y coordinates if the mouse is pressed*/
static void mouse_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
        case 1:
            act_key = LV_KEY_LEFT; //LV_KEY_NEXT;
            break;
        case 2:
            act_key = LV_KEY_RIGHT; //LV_KEY_PREV;
            break;
        case 3:
            act_key = LV_KEY_ENTER;
            break;
        }

        last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
extern osMessageQId KEY_QueueHandle;

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
  osEvent Even = osMessageGet(KEY_QueueHandle , 0);
  
  if(osEventMessage == Even.status)
  {
    return Even.value.v;
  }
  else
  {
    return 0;
  }
}


/*------------------
 * Button
 * -----------------*/

/*Initialize your buttons*/
//static void button_init(void)
//{
//    /*Your code comes here*/
//}

///*Will be called by the library to read the button*/
//static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
//{

//    static uint8_t last_btn = 0;

//    /*Get the pressed button's ID*/
//    int8_t btn_act = button_get_pressed_id();

//    if(btn_act >= 0) {
//        data->state = LV_INDEV_STATE_PR;
//        last_btn = btn_act;
//    } else {
//        data->state = LV_INDEV_STATE_REL;
//    }

//    /*Save the last pressed button's ID*/
//    data->btn_id = last_btn;
//}

///*Get ID  (0, 1, 2 ..) of the pressed button*/
//static int8_t button_get_pressed_id(void)
//{
//    uint8_t i;

//    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
//    for(i = 0; i < 2; i++) {
//        /*Return the pressed button's ID*/
//        if(button_is_pressed(i)) {
//            return i;
//        }
//    }

//    /*No button pressed*/
//    return -1;
//}

///*Test if `id` button is pressed or not*/
//static bool button_is_pressed(uint8_t id)
//{

//    /*Your code comes here*/

//    return false;
//}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
