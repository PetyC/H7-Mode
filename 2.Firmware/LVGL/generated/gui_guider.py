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
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)


start_screen = lv.obj()
start_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_start_screen_main_main_default
style_start_screen_main_main_default = lv.style_t()
style_start_screen_main_main_default.init()
style_start_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_start_screen_main_main_default.set_bg_opa(255)

# add style for start_screen
start_screen.add_style(style_start_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

start_screen_schedule_bar = lv.bar(start_screen)
start_screen_schedule_bar.set_pos(int(4),int(100))
start_screen_schedule_bar.set_size(120,10)
start_screen_schedule_bar.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
start_screen_schedule_bar.set_style_anim_time(1000, 0)
start_screen_schedule_bar.set_mode(lv.bar.MODE.NORMAL)
start_screen_schedule_bar.set_value(1, lv.ANIM.ON)
# create style style_start_screen_schedule_bar_main_main_default
style_start_screen_schedule_bar_main_main_default = lv.style_t()
style_start_screen_schedule_bar_main_main_default.init()
style_start_screen_schedule_bar_main_main_default.set_radius(10)
style_start_screen_schedule_bar_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_schedule_bar_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_schedule_bar_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_start_screen_schedule_bar_main_main_default.set_bg_opa(60)

# add style for start_screen_schedule_bar
start_screen_schedule_bar.add_style(style_start_screen_schedule_bar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_start_screen_schedule_bar_main_indicator_default
style_start_screen_schedule_bar_main_indicator_default = lv.style_t()
style_start_screen_schedule_bar_main_indicator_default.init()
style_start_screen_schedule_bar_main_indicator_default.set_radius(10)
style_start_screen_schedule_bar_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_schedule_bar_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_schedule_bar_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_start_screen_schedule_bar_main_indicator_default.set_bg_opa(255)

# add style for start_screen_schedule_bar
start_screen_schedule_bar.add_style(style_start_screen_schedule_bar_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)

start_screen_label_1 = lv.label(start_screen)
start_screen_label_1.set_pos(int(14),int(30))
start_screen_label_1.set_size(100,20)
start_screen_label_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
start_screen_label_1.set_text("H7-Mode")
start_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
# create style style_start_screen_label_1_main_main_default
style_start_screen_label_1_main_main_default = lv.style_t()
style_start_screen_label_1_main_main_default.init()
style_start_screen_label_1_main_main_default.set_radius(0)
style_start_screen_label_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_label_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_label_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_start_screen_label_1_main_main_default.set_bg_opa(0)
style_start_screen_label_1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_start_screen_label_1_main_main_default.set_text_font(lv.font_simsun_20)
except AttributeError:
    try:
        style_start_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_start_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_start_screen_label_1_main_main_default.set_text_letter_space(2)
style_start_screen_label_1_main_main_default.set_text_line_space(0)
style_start_screen_label_1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_start_screen_label_1_main_main_default.set_pad_left(0)
style_start_screen_label_1_main_main_default.set_pad_right(0)
style_start_screen_label_1_main_main_default.set_pad_top(0)
style_start_screen_label_1_main_main_default.set_pad_bottom(0)

# add style for start_screen_label_1
start_screen_label_1.add_style(style_start_screen_label_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

start_screen_label_2 = lv.label(start_screen)
start_screen_label_2.set_pos(int(14),int(88))
start_screen_label_2.set_size(100,10)
start_screen_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
start_screen_label_2.set_text("加载中")
start_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
# create style style_start_screen_label_2_main_main_default
style_start_screen_label_2_main_main_default = lv.style_t()
style_start_screen_label_2_main_main_default.init()
style_start_screen_label_2_main_main_default.set_radius(0)
style_start_screen_label_2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_label_2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_start_screen_label_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_start_screen_label_2_main_main_default.set_bg_opa(0)
style_start_screen_label_2_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_start_screen_label_2_main_main_default.set_text_font(lv.font_simsun_10)
except AttributeError:
    try:
        style_start_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_10)
    except AttributeError:
        style_start_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_start_screen_label_2_main_main_default.set_text_letter_space(2)
style_start_screen_label_2_main_main_default.set_text_line_space(0)
style_start_screen_label_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_start_screen_label_2_main_main_default.set_pad_left(0)
style_start_screen_label_2_main_main_default.set_pad_right(0)
style_start_screen_label_2_main_main_default.set_pad_top(0)
style_start_screen_label_2_main_main_default.set_pad_bottom(0)

# add style for start_screen_label_2
start_screen_label_2.add_style(style_start_screen_label_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen = lv.obj()
main_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_main_screen_main_main_default
style_main_screen_main_main_default = lv.style_t()
style_main_screen_main_main_default.init()
style_main_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_main_main_default.set_bg_opa(255)

# add style for main_screen
main_screen.add_style(style_main_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen_wifi_set_btn = lv.btn(main_screen)
main_screen_wifi_set_btn.set_pos(int(14),int(35))
main_screen_wifi_set_btn.set_size(100,20)
main_screen_wifi_set_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
main_screen_wifi_set_btn_label = lv.label(main_screen_wifi_set_btn)
main_screen_wifi_set_btn_label.set_text("WIFI设置")
main_screen_wifi_set_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
main_screen_wifi_set_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_main_screen_wifi_set_btn_main_main_default
style_main_screen_wifi_set_btn_main_main_default = lv.style_t()
style_main_screen_wifi_set_btn_main_main_default.init()
style_main_screen_wifi_set_btn_main_main_default.set_radius(5)
style_main_screen_wifi_set_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_wifi_set_btn_main_main_default.set_bg_opa(109)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_width(1)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_color(lv.color_make(0x00,0x00,0x00))
style_main_screen_wifi_set_btn_main_main_default.set_shadow_opa(0)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_spread(1)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_ofs_x(0)
style_main_screen_wifi_set_btn_main_main_default.set_shadow_ofs_y(0)
style_main_screen_wifi_set_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_default.set_border_width(0)
style_main_screen_wifi_set_btn_main_main_default.set_border_opa(0)
style_main_screen_wifi_set_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_wifi_set_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_wifi_set_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_wifi_set_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_main_screen_wifi_set_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for main_screen_wifi_set_btn
main_screen_wifi_set_btn.add_style(style_main_screen_wifi_set_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_main_screen_wifi_set_btn_main_main_focused
style_main_screen_wifi_set_btn_main_main_focused = lv.style_t()
style_main_screen_wifi_set_btn_main_main_focused.init()
style_main_screen_wifi_set_btn_main_main_focused.set_radius(5)
style_main_screen_wifi_set_btn_main_main_focused.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_focused.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_focused.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_wifi_set_btn_main_main_focused.set_bg_opa(255)
style_main_screen_wifi_set_btn_main_main_focused.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_focused.set_border_width(0)
style_main_screen_wifi_set_btn_main_main_focused.set_border_opa(255)
style_main_screen_wifi_set_btn_main_main_focused.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_wifi_set_btn_main_main_focused.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_wifi_set_btn_main_main_focused.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_wifi_set_btn_main_main_focused.set_text_font(lv.font_montserrat_16)

# add style for main_screen_wifi_set_btn
main_screen_wifi_set_btn.add_style(style_main_screen_wifi_set_btn_main_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)

# create style style_main_screen_wifi_set_btn_main_main_pressed
style_main_screen_wifi_set_btn_main_main_pressed = lv.style_t()
style_main_screen_wifi_set_btn_main_main_pressed.init()
style_main_screen_wifi_set_btn_main_main_pressed.set_radius(5)
style_main_screen_wifi_set_btn_main_main_pressed.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_pressed.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_pressed.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_wifi_set_btn_main_main_pressed.set_bg_opa(255)
style_main_screen_wifi_set_btn_main_main_pressed.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_wifi_set_btn_main_main_pressed.set_border_width(0)
style_main_screen_wifi_set_btn_main_main_pressed.set_border_opa(255)
style_main_screen_wifi_set_btn_main_main_pressed.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_wifi_set_btn_main_main_pressed.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_wifi_set_btn_main_main_pressed.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_wifi_set_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)

# add style for main_screen_wifi_set_btn
main_screen_wifi_set_btn.add_style(style_main_screen_wifi_set_btn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

main_screen_demo_btn = lv.btn(main_screen)
main_screen_demo_btn.set_pos(int(14),int(70))
main_screen_demo_btn.set_size(100,20)
main_screen_demo_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
main_screen_demo_btn_label = lv.label(main_screen_demo_btn)
main_screen_demo_btn_label.set_text("关于设备")
main_screen_demo_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
main_screen_demo_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_main_screen_demo_btn_main_main_default
style_main_screen_demo_btn_main_main_default = lv.style_t()
style_main_screen_demo_btn_main_main_default.init()
style_main_screen_demo_btn_main_main_default.set_radius(5)
style_main_screen_demo_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_demo_btn_main_main_default.set_bg_opa(109)
style_main_screen_demo_btn_main_main_default.set_shadow_width(1)
style_main_screen_demo_btn_main_main_default.set_shadow_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_demo_btn_main_main_default.set_shadow_opa(0)
style_main_screen_demo_btn_main_main_default.set_shadow_spread(1)
style_main_screen_demo_btn_main_main_default.set_shadow_ofs_x(0)
style_main_screen_demo_btn_main_main_default.set_shadow_ofs_y(0)
style_main_screen_demo_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_default.set_border_width(0)
style_main_screen_demo_btn_main_main_default.set_border_opa(0)
style_main_screen_demo_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_demo_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_demo_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_demo_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_main_screen_demo_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for main_screen_demo_btn
main_screen_demo_btn.add_style(style_main_screen_demo_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_main_screen_demo_btn_main_main_focused
style_main_screen_demo_btn_main_main_focused = lv.style_t()
style_main_screen_demo_btn_main_main_focused.init()
style_main_screen_demo_btn_main_main_focused.set_radius(5)
style_main_screen_demo_btn_main_main_focused.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_focused.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_focused.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_demo_btn_main_main_focused.set_bg_opa(255)
style_main_screen_demo_btn_main_main_focused.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_focused.set_border_width(0)
style_main_screen_demo_btn_main_main_focused.set_border_opa(255)
style_main_screen_demo_btn_main_main_focused.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_demo_btn_main_main_focused.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_demo_btn_main_main_focused.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_demo_btn_main_main_focused.set_text_font(lv.font_montserrat_16)

# add style for main_screen_demo_btn
main_screen_demo_btn.add_style(style_main_screen_demo_btn_main_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)

# create style style_main_screen_demo_btn_main_main_pressed
style_main_screen_demo_btn_main_main_pressed = lv.style_t()
style_main_screen_demo_btn_main_main_pressed.init()
style_main_screen_demo_btn_main_main_pressed.set_radius(5)
style_main_screen_demo_btn_main_main_pressed.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_pressed.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_pressed.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_main_screen_demo_btn_main_main_pressed.set_bg_opa(255)
style_main_screen_demo_btn_main_main_pressed.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_demo_btn_main_main_pressed.set_border_width(0)
style_main_screen_demo_btn_main_main_pressed.set_border_opa(255)
style_main_screen_demo_btn_main_main_pressed.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_demo_btn_main_main_pressed.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_main_screen_demo_btn_main_main_pressed.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_main_screen_demo_btn_main_main_pressed.set_text_font(lv.font_montserrat_16)

# add style for main_screen_demo_btn
main_screen_demo_btn.add_style(style_main_screen_demo_btn_main_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)

main_screen_led_1 = lv.led(main_screen)
main_screen_led_1.set_pos(int(54),int(100))
main_screen_led_1.set_size(20,20)
main_screen_led_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
main_screen_led_1.set_brightness(0)
main_screen_led_1.set_color(lv.color_make(0x00,0xa1,0xb5))
main_screen_wifi_img = lv.img(main_screen)
main_screen_wifi_img.set_pos(int(112),int(2))
main_screen_wifi_img.set_size(15,14)
main_screen_wifi_img.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
main_screen_wifi_img.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\Users\\39810\\Desktop\\H7-Mode\\2.Firmware\\LVGL\\generated\\mPythonImages\\mp237037509.png','rb') as f:
        main_screen_wifi_img_img_data = f.read()
except:
    print('Could not open C:\\Users\\39810\\Desktop\\H7-Mode\\2.Firmware\\LVGL\\generated\\mPythonImages\\mp237037509.png')
    sys.exit()

main_screen_wifi_img_img = lv.img_dsc_t({
  'data_size': len(main_screen_wifi_img_img_data),
  'header': {'always_zero': 0, 'w': 15, 'h': 14, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': main_screen_wifi_img_img_data
})

main_screen_wifi_img.set_src(main_screen_wifi_img_img)
main_screen_wifi_img.set_pivot(0,0)
main_screen_wifi_img.set_angle(0)
# create style style_main_screen_wifi_img_main_main_default
style_main_screen_wifi_img_main_main_default = lv.style_t()
style_main_screen_wifi_img_main_main_default.init()
style_main_screen_wifi_img_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_main_screen_wifi_img_main_main_default.set_img_recolor_opa(0)
style_main_screen_wifi_img_main_main_default.set_img_opa(255)

# add style for main_screen_wifi_img
main_screen_wifi_img.add_style(style_main_screen_wifi_img_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen = lv.obj()
device_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_device_screen_main_main_default
style_device_screen_main_main_default = lv.style_t()
style_device_screen_main_main_default.init()
style_device_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_device_screen_main_main_default.set_bg_opa(255)

# add style for device_screen
device_screen.add_style(style_device_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_about_tileview = lv.tileview(device_screen)
device_screen_about_tileview.set_pos(int(0),int(0))
device_screen_about_tileview.set_size(128,128)
device_screen_about_tileview.set_scrollbar_mode(lv.SCROLLBAR_MODE.ON)
about_tileview_about_name_0 = device_screen_about_tileview.add_tile(0, 0, lv.DIR.BOTTOM)
device_screen_label_3 = lv.label(about_tileview_about_name_0)
device_screen_label_3.set_pos(int(0),int(90))
device_screen_label_3.set_size(128,15)
device_screen_label_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_label_3.set_text("版本号")
device_screen_label_3.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_label_3_main_main_default
style_device_screen_label_3_main_main_default = lv.style_t()
style_device_screen_label_3_main_main_default.init()
style_device_screen_label_3_main_main_default.set_radius(0)
style_device_screen_label_3_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_device_screen_label_3_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_label_3_main_main_default.set_bg_opa(0)
style_device_screen_label_3_main_main_default.set_shadow_width(1)
style_device_screen_label_3_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_3_main_main_default.set_shadow_opa(0)
style_device_screen_label_3_main_main_default.set_shadow_spread(1)
style_device_screen_label_3_main_main_default.set_shadow_ofs_x(0)
style_device_screen_label_3_main_main_default.set_shadow_ofs_y(0)
style_device_screen_label_3_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_label_3_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_label_3_main_main_default.set_text_letter_space(2)
style_device_screen_label_3_main_main_default.set_text_line_space(0)
style_device_screen_label_3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_label_3_main_main_default.set_pad_left(0)
style_device_screen_label_3_main_main_default.set_pad_right(0)
style_device_screen_label_3_main_main_default.set_pad_top(0)
style_device_screen_label_3_main_main_default.set_pad_bottom(0)

# add style for device_screen_label_3
device_screen_label_3.add_style(style_device_screen_label_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_version_label = lv.label(about_tileview_about_name_0)
device_screen_version_label.set_pos(int(7),int(110))
device_screen_version_label.set_size(114,15)
device_screen_version_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_version_label.set_text("0.0.1")
device_screen_version_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_version_label_main_main_default
style_device_screen_version_label_main_main_default = lv.style_t()
style_device_screen_version_label_main_main_default.init()
style_device_screen_version_label_main_main_default.set_radius(0)
style_device_screen_version_label_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_device_screen_version_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_version_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_version_label_main_main_default.set_bg_opa(109)
style_device_screen_version_label_main_main_default.set_shadow_width(1)
style_device_screen_version_label_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_version_label_main_main_default.set_shadow_opa(0)
style_device_screen_version_label_main_main_default.set_shadow_spread(1)
style_device_screen_version_label_main_main_default.set_shadow_ofs_x(0)
style_device_screen_version_label_main_main_default.set_shadow_ofs_y(0)
style_device_screen_version_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_version_label_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_version_label_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_version_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_version_label_main_main_default.set_text_letter_space(2)
style_device_screen_version_label_main_main_default.set_text_line_space(0)
style_device_screen_version_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_version_label_main_main_default.set_pad_left(0)
style_device_screen_version_label_main_main_default.set_pad_right(0)
style_device_screen_version_label_main_main_default.set_pad_top(0)
style_device_screen_version_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_version_label
device_screen_version_label.add_style(style_device_screen_version_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_mcu_label = lv.label(about_tileview_about_name_0)
device_screen_mcu_label.set_pos(int(7),int(70))
device_screen_mcu_label.set_size(110,15)
device_screen_mcu_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_mcu_label.set_text("STM32H743VIT6")
device_screen_mcu_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_mcu_label_main_main_default
style_device_screen_mcu_label_main_main_default = lv.style_t()
style_device_screen_mcu_label_main_main_default.init()
style_device_screen_mcu_label_main_main_default.set_radius(0)
style_device_screen_mcu_label_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_device_screen_mcu_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_mcu_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_mcu_label_main_main_default.set_bg_opa(109)
style_device_screen_mcu_label_main_main_default.set_shadow_width(1)
style_device_screen_mcu_label_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_mcu_label_main_main_default.set_shadow_opa(0)
style_device_screen_mcu_label_main_main_default.set_shadow_spread(1)
style_device_screen_mcu_label_main_main_default.set_shadow_ofs_x(0)
style_device_screen_mcu_label_main_main_default.set_shadow_ofs_y(0)
style_device_screen_mcu_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_mcu_label_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_mcu_label_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_mcu_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_mcu_label_main_main_default.set_text_letter_space(2)
style_device_screen_mcu_label_main_main_default.set_text_line_space(0)
style_device_screen_mcu_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_mcu_label_main_main_default.set_pad_left(0)
style_device_screen_mcu_label_main_main_default.set_pad_right(0)
style_device_screen_mcu_label_main_main_default.set_pad_top(0)
style_device_screen_mcu_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_mcu_label
device_screen_mcu_label.add_style(style_device_screen_mcu_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_label_2 = lv.label(about_tileview_about_name_0)
device_screen_label_2.set_pos(int(0),int(50))
device_screen_label_2.set_size(128,15)
device_screen_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_label_2.set_text("主控芯片")
device_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_label_2_main_main_default
style_device_screen_label_2_main_main_default = lv.style_t()
style_device_screen_label_2_main_main_default.init()
style_device_screen_label_2_main_main_default.set_radius(0)
style_device_screen_label_2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_label_2_main_main_default.set_bg_opa(0)
style_device_screen_label_2_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_label_2_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_label_2_main_main_default.set_text_letter_space(2)
style_device_screen_label_2_main_main_default.set_text_line_space(0)
style_device_screen_label_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_label_2_main_main_default.set_pad_left(0)
style_device_screen_label_2_main_main_default.set_pad_right(0)
style_device_screen_label_2_main_main_default.set_pad_top(0)
style_device_screen_label_2_main_main_default.set_pad_bottom(0)

# add style for device_screen_label_2
device_screen_label_2.add_style(style_device_screen_label_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_type_label = lv.label(about_tileview_about_name_0)
device_screen_type_label.set_pos(int(7),int(30))
device_screen_type_label.set_size(110,15)
device_screen_type_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_type_label.set_text("H7-Mode")
device_screen_type_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_type_label_main_main_default
style_device_screen_type_label_main_main_default = lv.style_t()
style_device_screen_type_label_main_main_default.init()
style_device_screen_type_label_main_main_default.set_radius(0)
style_device_screen_type_label_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_device_screen_type_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_type_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_type_label_main_main_default.set_bg_opa(109)
style_device_screen_type_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_type_label_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_type_label_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_type_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_type_label_main_main_default.set_text_letter_space(2)
style_device_screen_type_label_main_main_default.set_text_line_space(0)
style_device_screen_type_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_type_label_main_main_default.set_pad_left(0)
style_device_screen_type_label_main_main_default.set_pad_right(0)
style_device_screen_type_label_main_main_default.set_pad_top(0)
style_device_screen_type_label_main_main_default.set_pad_bottom(0)

# add style for device_screen_type_label
device_screen_type_label.add_style(style_device_screen_type_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_label_1 = lv.label(about_tileview_about_name_0)
device_screen_label_1.set_pos(int(0),int(10))
device_screen_label_1.set_size(128,15)
device_screen_label_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_label_1.set_text("设备型号")
device_screen_label_1.set_long_mode(lv.label.LONG.WRAP)
# create style style_device_screen_label_1_main_main_default
style_device_screen_label_1_main_main_default = lv.style_t()
style_device_screen_label_1_main_main_default.init()
style_device_screen_label_1_main_main_default.set_radius(0)
style_device_screen_label_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_label_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_label_1_main_main_default.set_bg_opa(0)
style_device_screen_label_1_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_label_1_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_label_1_main_main_default.set_text_letter_space(2)
style_device_screen_label_1_main_main_default.set_text_line_space(0)
style_device_screen_label_1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_device_screen_label_1_main_main_default.set_pad_left(0)
style_device_screen_label_1_main_main_default.set_pad_right(0)
style_device_screen_label_1_main_main_default.set_pad_top(0)
style_device_screen_label_1_main_main_default.set_pad_bottom(0)

# add style for device_screen_label_1
device_screen_label_1.add_style(style_device_screen_label_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

about_tileview_about_name_1 = device_screen_about_tileview.add_tile(0 , 1, lv.DIR.TOP)
device_screen_return_btn = lv.btn(about_tileview_about_name_1)
device_screen_return_btn.set_pos(int(14),int(35))
device_screen_return_btn.set_size(100,20)
device_screen_return_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_return_btn_label = lv.label(device_screen_return_btn)
device_screen_return_btn_label.set_text("返回")
device_screen_return_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
device_screen_return_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_device_screen_return_btn_main_main_default
style_device_screen_return_btn_main_main_default = lv.style_t()
style_device_screen_return_btn_main_main_default.init()
style_device_screen_return_btn_main_main_default.set_radius(5)
style_device_screen_return_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_return_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_return_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_return_btn_main_main_default.set_bg_opa(112)
style_device_screen_return_btn_main_main_default.set_shadow_width(1)
style_device_screen_return_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_return_btn_main_main_default.set_shadow_opa(0)
style_device_screen_return_btn_main_main_default.set_shadow_spread(1)
style_device_screen_return_btn_main_main_default.set_shadow_ofs_x(0)
style_device_screen_return_btn_main_main_default.set_shadow_ofs_y(0)
style_device_screen_return_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_return_btn_main_main_default.set_border_width(0)
style_device_screen_return_btn_main_main_default.set_border_opa(0)
style_device_screen_return_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_return_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_return_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_return_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_return_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_return_btn
device_screen_return_btn.add_style(style_device_screen_return_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

device_screen_check_btn = lv.btn(about_tileview_about_name_1)
device_screen_check_btn.set_pos(int(14),int(10))
device_screen_check_btn.set_size(100,20)
device_screen_check_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
device_screen_check_btn_label = lv.label(device_screen_check_btn)
device_screen_check_btn_label.set_text("检查更新")
device_screen_check_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
device_screen_check_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_device_screen_check_btn_main_main_default
style_device_screen_check_btn_main_main_default = lv.style_t()
style_device_screen_check_btn_main_main_default.init()
style_device_screen_check_btn_main_main_default.set_radius(5)
style_device_screen_check_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_check_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_check_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_check_btn_main_main_default.set_bg_opa(112)
style_device_screen_check_btn_main_main_default.set_shadow_width(1)
style_device_screen_check_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_check_btn_main_main_default.set_shadow_opa(0)
style_device_screen_check_btn_main_main_default.set_shadow_spread(1)
style_device_screen_check_btn_main_main_default.set_shadow_ofs_x(0)
style_device_screen_check_btn_main_main_default.set_shadow_ofs_y(0)
style_device_screen_check_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_device_screen_check_btn_main_main_default.set_border_width(0)
style_device_screen_check_btn_main_main_default.set_border_opa(0)
style_device_screen_check_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_device_screen_check_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_device_screen_check_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_device_screen_check_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_device_screen_check_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for device_screen_check_btn
device_screen_check_btn.add_style(style_device_screen_check_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_about_tileview_main_main_default
style_device_screen_about_tileview_main_main_default = lv.style_t()
style_device_screen_about_tileview_main_main_default.init()
style_device_screen_about_tileview_main_main_default.set_radius(0)
style_device_screen_about_tileview_main_main_default.set_bg_color(lv.color_make(0xf6,0xf6,0xf6))
style_device_screen_about_tileview_main_main_default.set_bg_grad_color(lv.color_make(0xf6,0xf6,0xf6))
style_device_screen_about_tileview_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_device_screen_about_tileview_main_main_default.set_bg_opa(255)

# add style for device_screen_about_tileview
device_screen_about_tileview.add_style(style_device_screen_about_tileview_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_device_screen_about_tileview_main_scrollbar_default
style_device_screen_about_tileview_main_scrollbar_default = lv.style_t()
style_device_screen_about_tileview_main_scrollbar_default.init()
style_device_screen_about_tileview_main_scrollbar_default.set_radius(0)
style_device_screen_about_tileview_main_scrollbar_default.set_bg_color(lv.color_make(0xea,0xef,0xf3))
style_device_screen_about_tileview_main_scrollbar_default.set_bg_opa(255)

# add style for device_screen_about_tileview
device_screen_about_tileview.add_style(style_device_screen_about_tileview_main_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

Wifi_screen = lv.obj()
Wifi_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_wifi_screen_main_main_default
style_wifi_screen_main_main_default = lv.style_t()
style_wifi_screen_main_main_default.init()
style_wifi_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_main_main_default.set_bg_opa(255)

# add style for Wifi_screen
Wifi_screen.add_style(style_wifi_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_APU_btn = lv.btn(Wifi_screen)
Wifi_screen_APU_btn.set_pos(int(14),int(65))
Wifi_screen_APU_btn.set_size(100,20)
Wifi_screen_APU_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_APU_btn_label = lv.label(Wifi_screen_APU_btn)
Wifi_screen_APU_btn_label.set_text("启动APU配网")
Wifi_screen_APU_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
Wifi_screen_APU_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_wifi_screen_apu_btn_main_main_default
style_wifi_screen_apu_btn_main_main_default = lv.style_t()
style_wifi_screen_apu_btn_main_main_default.init()
style_wifi_screen_apu_btn_main_main_default.set_radius(5)
style_wifi_screen_apu_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_apu_btn_main_main_default.set_bg_opa(108)
style_wifi_screen_apu_btn_main_main_default.set_shadow_width(1)
style_wifi_screen_apu_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_shadow_opa(0)
style_wifi_screen_apu_btn_main_main_default.set_shadow_spread(1)
style_wifi_screen_apu_btn_main_main_default.set_shadow_ofs_x(0)
style_wifi_screen_apu_btn_main_main_default.set_shadow_ofs_y(0)
style_wifi_screen_apu_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_apu_btn_main_main_default.set_border_width(0)
style_wifi_screen_apu_btn_main_main_default.set_border_opa(0)
style_wifi_screen_apu_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_apu_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_wifi_screen_apu_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_wifi_screen_apu_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_apu_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for Wifi_screen_APU_btn
Wifi_screen_APU_btn.add_style(style_wifi_screen_apu_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_label_2 = lv.label(Wifi_screen)
Wifi_screen_label_2.set_pos(int(0),int(25))
Wifi_screen_label_2.set_size(128,15)
Wifi_screen_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_label_2.set_text("连接WIFI:")
Wifi_screen_label_2.set_long_mode(lv.label.LONG.WRAP)
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
    style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_wifi_screen_label_2_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_label_2_main_main_default.set_text_letter_space(2)
style_wifi_screen_label_2_main_main_default.set_text_line_space(0)
style_wifi_screen_label_2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_wifi_screen_label_2_main_main_default.set_pad_left(0)
style_wifi_screen_label_2_main_main_default.set_pad_right(0)
style_wifi_screen_label_2_main_main_default.set_pad_top(0)
style_wifi_screen_label_2_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_label_2
Wifi_screen_label_2.add_style(style_wifi_screen_label_2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_wifi_name_now_label = lv.label(Wifi_screen)
Wifi_screen_wifi_name_now_label.set_pos(int(4),int(45))
Wifi_screen_wifi_name_now_label.set_size(120,15)
Wifi_screen_wifi_name_now_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_wifi_name_now_label.set_text("Moujiti")
Wifi_screen_wifi_name_now_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_wifi_screen_wifi_name_now_label_main_main_default
style_wifi_screen_wifi_name_now_label_main_main_default = lv.style_t()
style_wifi_screen_wifi_name_now_label_main_main_default.init()
style_wifi_screen_wifi_name_now_label_main_main_default.set_radius(50)
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_wifi_name_now_label_main_main_default.set_bg_opa(109)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_wifi_screen_wifi_name_now_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_letter_space(1)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_line_space(3)
style_wifi_screen_wifi_name_now_label_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
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
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_line_space(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_text_align(lv.TEXT_ALIGN.CENTER)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_left(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_right(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_top(0)
style_wifi_screen_wifi_name_now_label_main_main_disabled.set_pad_bottom(0)

# add style for Wifi_screen_wifi_name_now_label
Wifi_screen_wifi_name_now_label.add_style(style_wifi_screen_wifi_name_now_label_main_main_disabled, lv.PART.MAIN|lv.STATE.DISABLED)

Wifi_screen_return_btn = lv.btn(Wifi_screen)
Wifi_screen_return_btn.set_pos(int(14),int(90))
Wifi_screen_return_btn.set_size(100,20)
Wifi_screen_return_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_return_btn_label = lv.label(Wifi_screen_return_btn)
Wifi_screen_return_btn_label.set_text("返回")
Wifi_screen_return_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
Wifi_screen_return_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_wifi_screen_return_btn_main_main_default
style_wifi_screen_return_btn_main_main_default = lv.style_t()
style_wifi_screen_return_btn_main_main_default.init()
style_wifi_screen_return_btn_main_main_default.set_radius(5)
style_wifi_screen_return_btn_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_return_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_return_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_wifi_screen_return_btn_main_main_default.set_bg_opa(108)
style_wifi_screen_return_btn_main_main_default.set_shadow_width(1)
style_wifi_screen_return_btn_main_main_default.set_shadow_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_return_btn_main_main_default.set_shadow_opa(0)
style_wifi_screen_return_btn_main_main_default.set_shadow_spread(1)
style_wifi_screen_return_btn_main_main_default.set_shadow_ofs_x(0)
style_wifi_screen_return_btn_main_main_default.set_shadow_ofs_y(0)
style_wifi_screen_return_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_return_btn_main_main_default.set_border_width(0)
style_wifi_screen_return_btn_main_main_default.set_border_opa(0)
style_wifi_screen_return_btn_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_return_btn_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_wifi_screen_return_btn_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_wifi_screen_return_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_return_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for Wifi_screen_return_btn
Wifi_screen_return_btn.add_style(style_wifi_screen_return_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

Wifi_screen_cont = lv.obj(Wifi_screen)
Wifi_screen_cont.set_pos(int(0),int(0))
Wifi_screen_cont.set_size(128,20)
Wifi_screen_cont.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_wifi_en_sw = lv.switch(Wifi_screen_cont)
Wifi_screen_wifi_en_sw.set_pos(int(65),int(5))
Wifi_screen_wifi_en_sw.set_size(40,12)
Wifi_screen_wifi_en_sw.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_wifi_screen_wifi_en_sw_main_main_default
style_wifi_screen_wifi_en_sw_main_main_default = lv.style_t()
style_wifi_screen_wifi_en_sw_main_main_default.init()
style_wifi_screen_wifi_en_sw_main_main_default.set_radius(100)
style_wifi_screen_wifi_en_sw_main_main_default.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_default.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_wifi_en_sw_main_main_default.set_bg_opa(255)
style_wifi_screen_wifi_en_sw_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_main_default.set_border_width(0)
style_wifi_screen_wifi_en_sw_main_main_default.set_border_opa(0)

# add style for Wifi_screen_wifi_en_sw
Wifi_screen_wifi_en_sw.add_style(style_wifi_screen_wifi_en_sw_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_wifi_screen_wifi_en_sw_main_main_focused
style_wifi_screen_wifi_en_sw_main_main_focused = lv.style_t()
style_wifi_screen_wifi_en_sw_main_main_focused.init()
style_wifi_screen_wifi_en_sw_main_main_focused.set_radius(100)
style_wifi_screen_wifi_en_sw_main_main_focused.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_focused.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_focused.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_wifi_en_sw_main_main_focused.set_bg_opa(255)
style_wifi_screen_wifi_en_sw_main_main_focused.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_main_focused.set_border_width(0)
style_wifi_screen_wifi_en_sw_main_main_focused.set_border_opa(255)

# add style for Wifi_screen_wifi_en_sw
Wifi_screen_wifi_en_sw.add_style(style_wifi_screen_wifi_en_sw_main_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)

# create style style_wifi_screen_wifi_en_sw_main_main_disabled
style_wifi_screen_wifi_en_sw_main_main_disabled = lv.style_t()
style_wifi_screen_wifi_en_sw_main_main_disabled.init()
style_wifi_screen_wifi_en_sw_main_main_disabled.set_radius(100)
style_wifi_screen_wifi_en_sw_main_main_disabled.set_bg_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_disabled.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_wifi_screen_wifi_en_sw_main_main_disabled.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_wifi_en_sw_main_main_disabled.set_bg_opa(255)
style_wifi_screen_wifi_en_sw_main_main_disabled.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_main_disabled.set_border_width(0)
style_wifi_screen_wifi_en_sw_main_main_disabled.set_border_opa(255)

# add style for Wifi_screen_wifi_en_sw
Wifi_screen_wifi_en_sw.add_style(style_wifi_screen_wifi_en_sw_main_main_disabled, lv.PART.MAIN|lv.STATE.DISABLED)

# create style style_wifi_screen_wifi_en_sw_main_indicator_checked
style_wifi_screen_wifi_en_sw_main_indicator_checked = lv.style_t()
style_wifi_screen_wifi_en_sw_main_indicator_checked.init()
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_bg_opa(255)
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_border_width(0)
style_wifi_screen_wifi_en_sw_main_indicator_checked.set_border_opa(255)

# add style for Wifi_screen_wifi_en_sw
Wifi_screen_wifi_en_sw.add_style(style_wifi_screen_wifi_en_sw_main_indicator_checked, lv.PART.INDICATOR|lv.STATE.CHECKED)

# create style style_wifi_screen_wifi_en_sw_main_knob_default
style_wifi_screen_wifi_en_sw_main_knob_default = lv.style_t()
style_wifi_screen_wifi_en_sw_main_knob_default.init()
style_wifi_screen_wifi_en_sw_main_knob_default.set_radius(100)
style_wifi_screen_wifi_en_sw_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_wifi_en_sw_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_wifi_screen_wifi_en_sw_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_wifi_en_sw_main_knob_default.set_bg_opa(255)
style_wifi_screen_wifi_en_sw_main_knob_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_wifi_en_sw_main_knob_default.set_border_width(0)
style_wifi_screen_wifi_en_sw_main_knob_default.set_border_opa(255)

# add style for Wifi_screen_wifi_en_sw
Wifi_screen_wifi_en_sw.add_style(style_wifi_screen_wifi_en_sw_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)

Wifi_screen_label_3 = lv.label(Wifi_screen_cont)
Wifi_screen_label_3.set_pos(int(20),int(5))
Wifi_screen_label_3.set_size(50,15)
Wifi_screen_label_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
Wifi_screen_label_3.set_text("WIFI")
Wifi_screen_label_3.set_long_mode(lv.label.LONG.WRAP)
# create style style_wifi_screen_label_3_main_main_default
style_wifi_screen_label_3_main_main_default = lv.style_t()
style_wifi_screen_label_3_main_main_default.init()
style_wifi_screen_label_3_main_main_default.set_radius(0)
style_wifi_screen_label_3_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_3_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_label_3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_label_3_main_main_default.set_bg_opa(0)
style_wifi_screen_label_3_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_wifi_screen_label_3_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_wifi_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_wifi_screen_label_3_main_main_default.set_text_font(lv.font_montserrat_16)
style_wifi_screen_label_3_main_main_default.set_text_letter_space(2)
style_wifi_screen_label_3_main_main_default.set_text_line_space(0)
style_wifi_screen_label_3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_wifi_screen_label_3_main_main_default.set_pad_left(0)
style_wifi_screen_label_3_main_main_default.set_pad_right(0)
style_wifi_screen_label_3_main_main_default.set_pad_top(0)
style_wifi_screen_label_3_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_label_3
Wifi_screen_label_3.add_style(style_wifi_screen_label_3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_wifi_screen_cont_main_main_default
style_wifi_screen_cont_main_main_default = lv.style_t()
style_wifi_screen_cont_main_main_default.init()
style_wifi_screen_cont_main_main_default.set_radius(0)
style_wifi_screen_cont_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_cont_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_cont_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_wifi_screen_cont_main_main_default.set_bg_opa(0)
style_wifi_screen_cont_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_wifi_screen_cont_main_main_default.set_border_width(0)
style_wifi_screen_cont_main_main_default.set_border_opa(0)
style_wifi_screen_cont_main_main_default.set_pad_left(0)
style_wifi_screen_cont_main_main_default.set_pad_right(0)
style_wifi_screen_cont_main_main_default.set_pad_top(0)
style_wifi_screen_cont_main_main_default.set_pad_bottom(0)

# add style for Wifi_screen_cont
Wifi_screen_cont.add_style(style_wifi_screen_cont_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

QR_screen = lv.obj()
QR_screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_qr_screen_main_main_default
style_qr_screen_main_main_default = lv.style_t()
style_qr_screen_main_main_default.init()
style_qr_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_qr_screen_main_main_default.set_bg_opa(255)

# add style for QR_screen
QR_screen.add_style(style_qr_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

QR_screen_img_1 = lv.img(QR_screen)
QR_screen_img_1.set_pos(int(14),int(5))
QR_screen_img_1.set_size(100,100)
QR_screen_img_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
QR_screen_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
try:
    with open('C:\\Users\\39810\\Desktop\\H7-Mode\\2.Firmware\\LVGL\\generated\\mPythonImages\\mp1838870401.png','rb') as f:
        QR_screen_img_1_img_data = f.read()
except:
    print('Could not open C:\\Users\\39810\\Desktop\\H7-Mode\\2.Firmware\\LVGL\\generated\\mPythonImages\\mp1838870401.png')
    sys.exit()

QR_screen_img_1_img = lv.img_dsc_t({
  'data_size': len(QR_screen_img_1_img_data),
  'header': {'always_zero': 0, 'w': 100, 'h': 100, 'cf': lv.img.CF.TRUE_COLOR_ALPHA},
  'data': QR_screen_img_1_img_data
})

QR_screen_img_1.set_src(QR_screen_img_1_img)
QR_screen_img_1.set_pivot(0,0)
QR_screen_img_1.set_angle(0)
# create style style_qr_screen_img_1_main_main_default
style_qr_screen_img_1_main_main_default = lv.style_t()
style_qr_screen_img_1_main_main_default.init()
style_qr_screen_img_1_main_main_default.set_img_recolor(lv.color_make(0xff,0xff,0xff))
style_qr_screen_img_1_main_main_default.set_img_recolor_opa(0)
style_qr_screen_img_1_main_main_default.set_img_opa(255)

# add style for QR_screen_img_1
QR_screen_img_1.add_style(style_qr_screen_img_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

QR_screen_QR_bar = lv.bar(QR_screen)
QR_screen_QR_bar.set_pos(int(0),int(114))
QR_screen_QR_bar.set_size(128,10)
QR_screen_QR_bar.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
QR_screen_QR_bar.set_style_anim_time(1000, 0)
QR_screen_QR_bar.set_mode(lv.bar.MODE.NORMAL)
QR_screen_QR_bar.set_value(0, lv.ANIM.ON)
# create style style_qr_screen_qr_bar_main_main_default
style_qr_screen_qr_bar_main_main_default = lv.style_t()
style_qr_screen_qr_bar_main_main_default.init()
style_qr_screen_qr_bar_main_main_default.set_radius(10)
style_qr_screen_qr_bar_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_qr_screen_qr_bar_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_qr_screen_qr_bar_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_qr_screen_qr_bar_main_main_default.set_bg_opa(60)

# add style for QR_screen_QR_bar
QR_screen_QR_bar.add_style(style_qr_screen_qr_bar_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_qr_screen_qr_bar_main_indicator_default
style_qr_screen_qr_bar_main_indicator_default = lv.style_t()
style_qr_screen_qr_bar_main_indicator_default.init()
style_qr_screen_qr_bar_main_indicator_default.set_radius(10)
style_qr_screen_qr_bar_main_indicator_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_qr_screen_qr_bar_main_indicator_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_qr_screen_qr_bar_main_indicator_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_qr_screen_qr_bar_main_indicator_default.set_bg_opa(255)

# add style for QR_screen_QR_bar
QR_screen_QR_bar.add_style(style_qr_screen_qr_bar_main_indicator_default, lv.PART.INDICATOR|lv.STATE.DEFAULT)




def main_screen_wifi_set_btn_clicked_1_event_cb(e,Wifi_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(Wifi_screen, lv.SCR_LOAD_ANIM.OVER_LEFT, 0, 0, False)
main_screen_wifi_set_btn.add_event_cb(lambda e: main_screen_wifi_set_btn_clicked_1_event_cb(e,Wifi_screen), lv.EVENT.CLICKED, None)


def Wifi_screen_APU_btn_clicked_1_event_cb(e,QR_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(QR_screen, lv.SCR_LOAD_ANIM.OVER_LEFT, 0, 0, False)
Wifi_screen_APU_btn.add_event_cb(lambda e: Wifi_screen_APU_btn_clicked_1_event_cb(e,QR_screen), lv.EVENT.CLICKED, None)


def Wifi_screen_return_btn_clicked_1_event_cb(e,main_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(main_screen, lv.SCR_LOAD_ANIM.OVER_TOP, 0, 0, False)
Wifi_screen_return_btn.add_event_cb(lambda e: Wifi_screen_return_btn_clicked_1_event_cb(e,main_screen), lv.EVENT.CLICKED, None)


def device_screen_return_btn_clicked_1_event_cb(e,main_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(main_screen, lv.SCR_LOAD_ANIM.OVER_TOP, 0, 0, False)
device_screen_return_btn.add_event_cb(lambda e: device_screen_return_btn_clicked_1_event_cb(e,main_screen), lv.EVENT.CLICKED, None)


def main_screen_demo_btn_clicked_1_event_cb(e,device_screen):
    src = e.get_target()
    code = e.get_code()
    lv.scr_load_anim(device_screen, lv.SCR_LOAD_ANIM.OVER_TOP, 0, 0, False)
main_screen_demo_btn.add_event_cb(lambda e: main_screen_demo_btn_clicked_1_event_cb(e,device_screen), lv.EVENT.CLICKED, None)



# content from custom.py

# Load the default screen
lv.scr_load(start_screen)

while SDL.check():
    time.sleep_ms(5)
