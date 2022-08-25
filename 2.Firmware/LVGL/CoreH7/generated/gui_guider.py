# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=128,h=128)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(128*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 128
disp_drv.ver_res = 128
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.add_flag(lv.obj.FLAG.HIDDEN)


main_screen = lv.obj()
# create style style_main_screen_main_main_default
style_main_screen_main_main_default = lv.style_t()
style_main_screen_main_main_default.init()
style_main_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_main_main_default.set_bg_opa(255)

# add style for main_screen
main_screen.add_style(style_main_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen_Wifi_Set_btn = lv.btn(main_screen)
main_screen_Wifi_Set_btn.set_pos(15,38)
main_screen_Wifi_Set_btn.set_size(100,50)
main_screen_Wifi_Set_btn_label = lv.label(main_screen_Wifi_Set_btn)
main_screen_Wifi_Set_btn_label.set_text("WIFI设置")
main_screen_Wifi_Set_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
main_screen_Wifi_Set_btn_label.align(lv.ALIGN.CENTER,0,0)
main_screen_Wifi_Set_btn_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    main_screen_Wifi_Set_btn_label.set_style_text_font(lv.font_simsun_20, lv.STATE.DEFAULT)
except AttributeError:
    try:
        main_screen_Wifi_Set_btn_label.set_style_text_font(lv.font_montserrat_20, lv.STATE.DEFAULT)
    except AttributeError:
        main_screen_Wifi_Set_btn_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_main_screen_wifi_set_btn_main_main_default
style_main_screen_wifi_set_btn_main_main_default = lv.style_t()
style_main_screen_wifi_set_btn_main_main_default.init()
style_main_screen_wifi_set_btn_main_main_default.set_radius(5)
style_main_screen_wifi_set_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_main_screen_wifi_set_btn_main_main_default.set_bg_opa(255)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_shadow_opa(255)
style_main_screen_wifi_set_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_border_width(0)
style_main_screen_wifi_set_btn_main_main_default.set_border_opa(255)

# add style for main_screen_Wifi_Set_btn
main_screen_Wifi_Set_btn.add_style(style_main_screen_wifi_set_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen_Wifi_State_label = lv.label(main_screen)
main_screen_Wifi_State_label.set_pos(4,5)
main_screen_Wifi_State_label.set_size(120,10)
main_screen_Wifi_State_label.set_text("WIFI:已连接")
main_screen_Wifi_State_label.set_long_mode(lv.label.LONG.WRAP)
main_screen_Wifi_State_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_main_screen_wifi_state_label_main_main_default
style_main_screen_wifi_state_label_main_main_default = lv.style_t()
style_main_screen_wifi_state_label_main_main_default.init()
style_main_screen_wifi_state_label_main_main_default.set_radius(0)
style_main_screen_wifi_state_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_state_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_state_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_main_screen_wifi_state_label_main_main_default.set_bg_opa(0)
style_main_screen_wifi_state_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_wifi_state_label_main_main_default.set_text_font(lv.font_simsun_10)
except AttributeError:
    try:
        style_main_screen_wifi_state_label_main_main_default.set_text_font(lv.font_montserrat_10)
    except AttributeError:
        style_main_screen_wifi_state_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_main_screen_wifi_state_label_main_main_default.set_text_letter_space(2)
style_main_screen_wifi_state_label_main_main_default.set_pad_left(0)
style_main_screen_wifi_state_label_main_main_default.set_pad_right(0)
style_main_screen_wifi_state_label_main_main_default.set_pad_top(0)
style_main_screen_wifi_state_label_main_main_default.set_pad_bottom(0)

# add style for main_screen_Wifi_State_label
main_screen_Wifi_State_label.add_style(style_main_screen_wifi_state_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen = lv.obj()
# create style style_wifi_screen_main_main_default
style_wifi_screen_main_main_default = lv.style_t()
style_wifi_screen_main_main_default.init()
style_wifi_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_main_main_default.set_bg_opa(255)

# add style for Wifi_screen
Wifi_screen.add_style(style_wifi_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_APU_btn = lv.btn(Wifi_screen)
Wifi_screen_APU_btn.set_pos(4,70)
Wifi_screen_APU_btn.set_size(120,10)
Wifi_screen_APU_btn_label = lv.label(Wifi_screen_APU_btn)
Wifi_screen_APU_btn_label.set_text("启动APU配网")
Wifi_screen_APU_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
Wifi_screen_APU_btn_label.align(lv.ALIGN.CENTER,0,0)
Wifi_screen_APU_btn_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    Wifi_screen_APU_btn_label.set_style_text_font(lv.font_simsun_8, lv.STATE.DEFAULT)
except AttributeError:
    try:
        Wifi_screen_APU_btn_label.set_style_text_font(lv.font_montserrat_8, lv.STATE.DEFAULT)
    except AttributeError:
        Wifi_screen_APU_btn_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_wifi_screen_apu_btn_main_main_default
style_wifi_screen_apu_btn_main_main_default = lv.style_t()
style_wifi_screen_apu_btn_main_main_default.init()
style_wifi_screen_apu_btn_main_main_default.set_radius(5)
style_wifi_screen_apu_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_apu_btn_main_main_default.set_bg_opa(108)
style_wifi_screen_apu_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_shadow_opa(0)
style_wifi_screen_apu_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_border_width(0)
style_wifi_screen_apu_btn_main_main_default.set_border_opa(0)

# add style for Wifi_screen_APU_btn
Wifi_screen_APU_btn.add_style(style_wifi_screen_apu_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_label_1 = lv.label(Wifi_screen)
Wifi_screen_label_1.set_pos(0,3)
Wifi_screen_label_1.set_size(128,10)
Wifi_screen_label_1.set_text("WIFI")
Wifi_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
Wifi_screen_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_wifi_screen_label_1_main_main_default
style_wifi_screen_label_1_main_main_default = lv.style_t()
style_wifi_screen_label_1_main_main_default.init()
style_wifi_screen_label_1_main_main_default.set_radius(0)
style_wifi_screen_label_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_label_1_main_main_default.set_bg_opa(0)
style_wifi_screen_label_1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_label_1_main_main_default.set_text_font(lv.font_simsun_8)
except AttributeError:
    try:
        style_wifi_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_8)
    except AttributeError:
        style_wifi_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_label_1_main_main_default.set_text_letter_space(2)
style_wifi_screen_label_1_main_main_default.set_pad_left(0)
style_wifi_screen_label_1_main_main_default.set_pad_right(0)
style_wifi_screen_label_1_main_main_default.set_pad_top(0)
style_wifi_screen_label_1_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_label_1
Wifi_screen_label_1.add_style(style_wifi_screen_label_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_Wifi_sw = lv.switch(Wifi_screen)
Wifi_screen_Wifi_sw.set_pos(44,20)
Wifi_screen_Wifi_sw.set_size(40,15)
# create style style_wifi_screen_wifi_sw_main_main_default
style_wifi_screen_wifi_sw_main_main_default = lv.style_t()
style_wifi_screen_wifi_sw_main_main_default.init()
style_wifi_screen_wifi_sw_main_main_default.set_radius(100)
style_wifi_screen_wifi_sw_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_sw_main_main_default.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_sw_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_sw_main_main_default.set_bg_opa(255)

# add style for Wifi_screen_Wifi_sw
Wifi_screen_Wifi_sw.add_style(style_wifi_screen_wifi_sw_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_wifi_screen_wifi_sw_main_indicator_checked
style_wifi_screen_wifi_sw_main_indicator_checked = lv.style_t()
style_wifi_screen_wifi_sw_main_indicator_checked.init()
style_wifi_screen_wifi_sw_main_indicator_checked.set_radius(100)
style_wifi_screen_wifi_sw_main_indicator_checked.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_sw_main_indicator_checked.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_sw_main_indicator_checked.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_sw_main_indicator_checked.set_bg_opa(255)

# add style for Wifi_screen_Wifi_sw
Wifi_screen_Wifi_sw.add_style(style_wifi_screen_wifi_sw_main_indicator_checked, lv.PART.INDICATOR|lv.STATE.CHECKED)

# create style style_wifi_screen_wifi_sw_main_knob_default
style_wifi_screen_wifi_sw_main_knob_default = lv.style_t()
style_wifi_screen_wifi_sw_main_knob_default.init()
style_wifi_screen_wifi_sw_main_knob_default.set_radius(100)
style_wifi_screen_wifi_sw_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_wifi_sw_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_wifi_sw_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_sw_main_knob_default.set_bg_opa(255)

# add style for Wifi_screen_Wifi_sw
Wifi_screen_Wifi_sw.add_style(style_wifi_screen_wifi_sw_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

Wifi_screen_label_2 = lv.label(Wifi_screen)
Wifi_screen_label_2.set_pos(0,40)
Wifi_screen_label_2.set_size(128,8)
Wifi_screen_label_2.set_text("已连接WIFI:")
Wifi_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
Wifi_screen_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_wifi_screen_label_2_main_main_default
style_wifi_screen_label_2_main_main_default = lv.style_t()
style_wifi_screen_label_2_main_main_default.init()
style_wifi_screen_label_2_main_main_default.set_radius(50)
style_wifi_screen_label_2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_label_2_main_main_default.set_bg_opa(0)
style_wifi_screen_label_2_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_simsun_8)
except AttributeError:
    try:
        style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_8)
    except AttributeError:
        style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_label_2_main_main_default.set_text_letter_space(2)
style_wifi_screen_label_2_main_main_default.set_pad_left(0)
style_wifi_screen_label_2_main_main_default.set_pad_right(0)
style_wifi_screen_label_2_main_main_default.set_pad_top(0)
style_wifi_screen_label_2_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_label_2
Wifi_screen_label_2.add_style(style_wifi_screen_label_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_wifi_name_now_label = lv.label(Wifi_screen)
Wifi_screen_wifi_name_now_label.set_pos(4,55)
Wifi_screen_wifi_name_now_label.set_size(120,10)
Wifi_screen_wifi_name_now_label.set_text("Moujiti")
Wifi_screen_wifi_name_now_label.set_long_mode(lv.label.LONG.WRAP)
Wifi_screen_wifi_name_now_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_wifi_screen_wifi_name_now_label_main_main_default
style_wifi_screen_wifi_name_now_label_main_main_default = lv.style_t()
style_wifi_screen_wifi_name_now_label_main_main_default.init()
style_wifi_screen_wifi_name_now_label_main_main_default.set_radius(50)
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_opa(108)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_simsun_8)
except AttributeError:
    try:
        style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_montserrat_8)
    except AttributeError:
        style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_letter_space(1)
style_wifi_screen_wifi_name_now_label_main_main_default.set_pad_left(0)
style_wifi_screen_wifi_name_now_label_main_main_default.set_pad_right(0)
style_wifi_screen_wifi_name_now_label_main_main_default.set_pad_top(0)
style_wifi_screen_wifi_name_now_label_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_wifi_name_now_label
Wifi_screen_wifi_name_now_label.add_style(style_wifi_screen_wifi_name_now_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_wifi_screen_wifi_name_now_label_main_main_disabled
style_wifi_screen_wifi_name_now_label_main_main_disabled = lv.style_t()
style_wifi_screen_wifi_name_now_label_main_main_disabled.init()
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_radius(5)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_bg_grad_color(lv.color_make(0xf5,0xf5,0xf5))
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_bg_opa(255)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_font(lv.font_simsun_8)
except AttributeError:
    try:
        style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_font(lv.font_montserrat_8)
    except AttributeError:
        style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_font(lv.font_montserrat_16)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_letter_space(2)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_left(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_right(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_top(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_bottom(0)

# add style for Wifi_screen_wifi_name_now_label
Wifi_screen_wifi_name_now_label.add_style(style_wifi_screen_wifi_name_now_label_main_main_disabled, lv.PART.MAIN|lv.STATE.DISABLED)

Wifi_screen_btn_1 = lv.btn(Wifi_screen)
Wifi_screen_btn_1.set_pos(4,85)
Wifi_screen_btn_1.set_size(120,10)
Wifi_screen_btn_1_label = lv.label(Wifi_screen_btn_1)
Wifi_screen_btn_1_label.set_text("返回")
Wifi_screen_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
Wifi_screen_btn_1_label.align(lv.ALIGN.CENTER,0,0)
Wifi_screen_btn_1_label.set_style_text_color(lv.color_make(0x00,0x00,0x00), lv.STATE.DEFAULT)
try:
    Wifi_screen_btn_1_label.set_style_text_font(lv.font_simsun_8, lv.STATE.DEFAULT)
except AttributeError:
    try:
        Wifi_screen_btn_1_label.set_style_text_font(lv.font_montserrat_8, lv.STATE.DEFAULT)
    except AttributeError:
        Wifi_screen_btn_1_label.set_style_text_font(lv.font_montserrat_16, lv.STATE.DEFAULT)
# create style style_wifi_screen_btn_1_main_main_default
style_wifi_screen_btn_1_main_main_default = lv.style_t()
style_wifi_screen_btn_1_main_main_default.init()
style_wifi_screen_btn_1_main_main_default.set_radius(5)
style_wifi_screen_btn_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_btn_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_btn_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_btn_1_main_main_default.set_bg_opa(108)
style_wifi_screen_btn_1_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_btn_1_main_main_default.set_shadow_opa(0)
style_wifi_screen_btn_1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_btn_1_main_main_default.set_border_width(0)
style_wifi_screen_btn_1_main_main_default.set_border_opa(109)

# add style for Wifi_screen_btn_1
Wifi_screen_btn_1.add_style(style_wifi_screen_btn_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)



def main_screen_Wifi_Set_btn_clicked_1_event_cb(e,Wifi_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(Wifi_screen, lv.SCR_LOAD_ANIM.FADE_ON, 200, 0, False)
main_screen_Wifi_Set_btn.add_event_cb(lambda e: main_screen_Wifi_Set_btn_clicked_1_event_cb(e,Wifi_screen), lv.EVENT.CLICKED, None)


def Wifi_screen_btn_1_clicked_1_event_cb(e,main_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(main_screen, lv.SCR_LOAD_ANIM.NONE, 500, 0, False)
Wifi_screen_btn_1.add_event_cb(lambda e: Wifi_screen_btn_1_clicked_1_event_cb(e,main_screen), lv.EVENT.CLICKED, None)



# content from custom.py

# Load the default screen
lv.scr_load(main_screen)

while SDL.check():
    time.sleep_ms(5)
