/*******************************************************************************
 * Size: 8 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_FONT_SIMSUN_8
#define LV_FONT_SIMSUN_8 1
#endif

#if LV_FONT_SIMSUN_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0x54, 0x43, 0x32, 0x21, 0x0, 0x54,

    /* U+0022 "\"" */
    0x9, 0x73, 0x24, 0x60, 0x0, 0x0,

    /* U+0023 "#" */
    0x4, 0x22, 0x7b, 0xb7, 0x4, 0x40, 0x3, 0x40,
    0x7b, 0xb6, 0x21, 0x40,

    /* U+0024 "$" */
    0x1, 0x10, 0x17, 0x81, 0x46, 0x61, 0xb, 0x40,
    0x2, 0xb1, 0x44, 0x54, 0x26, 0x71, 0x2, 0x20,

    /* U+0025 "%" */
    0x54, 0x30, 0x66, 0x40, 0x56, 0x62, 0x36, 0x66,
    0x3, 0x66, 0x11, 0x55,

    /* U+0026 "&" */
    0x25, 0x40, 0x44, 0x40, 0x29, 0x42, 0x59, 0x40,
    0x74, 0x90, 0x65, 0x95,

    /* U+0027 "'" */
    0x46, 0x23, 0x0,

    /* U+0028 "(" */
    0x1, 0x30, 0x60, 0x15, 0x3, 0x30, 0x33, 0x0,
    0x60, 0x5, 0x0, 0x3,

    /* U+0029 ")" */
    0x31, 0x0, 0x60, 0x6, 0x0, 0x43, 0x4, 0x20,
    0x60, 0x5, 0x3, 0x0,

    /* U+002A "*" */
    0x1, 0x10, 0x44, 0x44, 0x28, 0x72, 0x67, 0x66,
    0x4, 0x30,

    /* U+002B "+" */
    0x0, 0x10, 0x1, 0x30, 0x36, 0x73, 0x1, 0x30,
    0x0, 0x10,

    /* U+002D "-" */
    0x35, 0x53,

    /* U+002E "." */
    0x0, 0x55,

    /* U+002F "/" */
    0x0, 0x3, 0x0, 0x12, 0x0, 0x40, 0x0, 0x30,
    0x4, 0x0, 0x4, 0x0, 0x30, 0x0, 0x20, 0x0,

    /* U+0030 "0" */
    0x7, 0x60, 0x62, 0x26, 0x90, 0x8, 0x90, 0x8,
    0x62, 0x26, 0x7, 0x60,

    /* U+0031 "1" */
    0x5, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40,
    0x3, 0x40, 0x7, 0x80,

    /* U+0032 "2" */
    0x24, 0x62, 0x61, 0x26, 0x0, 0x52, 0x1, 0x40,
    0x4, 0x1, 0x78, 0x85,

    /* U+0033 "3" */
    0x34, 0x71, 0x21, 0x52, 0x2, 0x80, 0x0, 0x24,
    0x51, 0x17, 0x35, 0x61,

    /* U+0034 "4" */
    0x0, 0x90, 0x2, 0x90, 0x4, 0x80, 0x31, 0x80,
    0x43, 0x92, 0x1, 0xa2,

    /* U+0035 "5" */
    0x28, 0x82, 0x30, 0x0, 0x45, 0x71, 0x0, 0x17,
    0x51, 0x16, 0x34, 0x61,

    /* U+0036 "6" */
    0x4, 0x72, 0x51, 0x0, 0x85, 0x72, 0x90, 0x8,
    0x71, 0x7, 0x17, 0x52,

    /* U+0037 "7" */
    0x59, 0x85, 0x10, 0x40, 0x0, 0x50, 0x3, 0x30,
    0x7, 0x10, 0x8, 0x10,

    /* U+0038 "8" */
    0x35, 0x52, 0x60, 0x6, 0x1a, 0x61, 0x42, 0x83,
    0x70, 0x7, 0x34, 0x52,

    /* U+0039 "9" */
    0x35, 0x51, 0x80, 0x16, 0x80, 0x28, 0x15, 0x47,
    0x0, 0x43, 0x36, 0x60,

    /* U+003A ":" */
    0x53, 0x0, 0x0, 0x53,

    /* U+003B ";" */
    0x43, 0x0, 0x0, 0x43, 0x31,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x32, 0x3, 0x20, 0x23, 0x0,
    0x14, 0x0, 0x1, 0x40, 0x0, 0x22,

    /* U+003D "=" */
    0x35, 0x53, 0x0, 0x0, 0x34, 0x43,

    /* U+003E ">" */
    0x0, 0x0, 0x23, 0x0, 0x2, 0x30, 0x0, 0x32,
    0x0, 0x41, 0x4, 0x10, 0x22, 0x0,

    /* U+003F "?" */
    0x24, 0x63, 0x71, 0x8, 0x10, 0x54, 0x2, 0x30,
    0x1, 0x0, 0x5, 0x30,

    /* U+0040 "@" */
    0x5, 0x42, 0x51, 0x55, 0x65, 0x64, 0x66, 0x64,
    0x54, 0x53, 0x5, 0x42,

    /* U+0041 "A" */
    0x0, 0x0, 0x5, 0x50, 0x4, 0x70, 0x3, 0x70,
    0x15, 0x80, 0x30, 0x42, 0x80, 0x37,

    /* U+0042 "B" */
    0x75, 0x63, 0x52, 0x16, 0x55, 0x71, 0x52, 0x7,
    0x52, 0x9, 0x75, 0x54,

    /* U+0043 "C" */
    0x6, 0x57, 0x71, 0x2, 0x90, 0x0, 0x90, 0x0,
    0x80, 0x3, 0x17, 0x42,

    /* U+0044 "D" */
    0x75, 0x61, 0x52, 0x17, 0x52, 0x9, 0x52, 0x8,
    0x52, 0x7, 0x75, 0x60,

    /* U+0045 "E" */
    0x65, 0x45, 0x53, 0x1, 0x55, 0x70, 0x53, 0x30,
    0x53, 0x0, 0x65, 0x46,

    /* U+0046 "F" */
    0x65, 0x47, 0x53, 0x1, 0x55, 0x70, 0x53, 0x30,
    0x53, 0x0, 0x64, 0x0,

    /* U+0047 "G" */
    0x15, 0x73, 0x70, 0x2, 0x80, 0x0, 0x80, 0x35,
    0x80, 0x25, 0x16, 0x53,

    /* U+0048 "H" */
    0x82, 0x38, 0x71, 0x16, 0x73, 0x46, 0x71, 0x16,
    0x71, 0x16, 0x82, 0x38,

    /* U+0049 "I" */
    0x6, 0x60, 0x4, 0x40, 0x4, 0x40, 0x4, 0x40,
    0x4, 0x40, 0x6, 0x60,

    /* U+004A "J" */
    0x2, 0xa2, 0x0, 0x80, 0x0, 0x80, 0x0, 0x80,
    0x0, 0x80, 0x0, 0x70, 0x73, 0x40,

    /* U+004B "K" */
    0x74, 0x63, 0x52, 0x30, 0x59, 0x10, 0x54, 0x70,
    0x52, 0x80, 0x74, 0x57,

    /* U+004C "L" */
    0x55, 0x0, 0x44, 0x0, 0x44, 0x0, 0x44, 0x0,
    0x44, 0x1, 0x56, 0x36,

    /* U+004D "M" */
    0xa1, 0x39, 0x54, 0x38, 0x36, 0x38, 0x37, 0x38,
    0x37, 0x28, 0x56, 0x19,

    /* U+004E "N" */
    0x74, 0x16, 0x38, 0x3, 0x35, 0x23, 0x30, 0x83,
    0x30, 0x74, 0x61, 0x5,

    /* U+004F "O" */
    0x16, 0x51, 0x70, 0x7, 0x90, 0x9, 0x90, 0x9,
    0x70, 0x7, 0x15, 0x51,

    /* U+0050 "P" */
    0x66, 0x43, 0x53, 0x8, 0x53, 0x7, 0x55, 0x40,
    0x53, 0x0, 0x64, 0x0,

    /* U+0051 "Q" */
    0x16, 0x51, 0x80, 0x7, 0x90, 0x9, 0x90, 0x9,
    0x75, 0x38, 0x16, 0xb2, 0x0, 0x54,

    /* U+0052 "R" */
    0x66, 0x54, 0x43, 0x7, 0x45, 0x70, 0x43, 0x70,
    0x43, 0x70, 0x65, 0x26,

    /* U+0053 "S" */
    0x34, 0x84, 0x70, 0x1, 0x29, 0x20, 0x0, 0x83,
    0x20, 0x6, 0x76, 0x42,

    /* U+0054 "T" */
    0x67, 0x66, 0x14, 0x31, 0x4, 0x30, 0x4, 0x30,
    0x4, 0x30, 0x6, 0x50,

    /* U+0055 "U" */
    0x82, 0x15, 0x71, 0x3, 0x71, 0x3, 0x71, 0x3,
    0x61, 0x2, 0x26, 0x41,

    /* U+0056 "V" */
    0x83, 0x16, 0x35, 0x21, 0x7, 0x30, 0x8, 0x30,
    0x7, 0x30, 0x5, 0x10,

    /* U+0057 "W" */
    0x94, 0x56, 0x62, 0x63, 0x54, 0x73, 0x36, 0x81,
    0x18, 0x90, 0x5, 0x50,

    /* U+0058 "X" */
    0x46, 0x44, 0x7, 0x40, 0x6, 0x40, 0x4, 0x70,
    0x4, 0x80, 0x53, 0x56,

    /* U+0059 "Y" */
    0x74, 0x26, 0x17, 0x30, 0x7, 0x30, 0x5, 0x30,
    0x4, 0x30, 0x6, 0x50,

    /* U+005A "Z" */
    0x55, 0x56, 0x0, 0x70, 0x1, 0x60, 0x7, 0x0,
    0x17, 0x1, 0x74, 0x45,

    /* U+005B "[" */
    0x34, 0x15, 0x0, 0x50, 0x5, 0x0, 0x50, 0x5,
    0x0, 0x50, 0x3, 0x42,

    /* U+005C "\\" */
    0x32, 0x0, 0x5, 0x0, 0x5, 0x0, 0x1, 0x40,
    0x0, 0x60, 0x0, 0x41, 0x0, 0x5,

    /* U+005D "]" */
    0x24, 0x30, 0x5, 0x0, 0x50, 0x5, 0x0, 0x50,
    0x5, 0x0, 0x52, 0x43,

    /* U+005E "^" */
    0x6, 0x60,

    /* U+005F "_" */
    0x33, 0x33,

    /* U+0060 "`" */
    0x6, 0x0,

    /* U+0061 "a" */
    0x34, 0x61, 0x13, 0x62, 0x61, 0x43, 0x64, 0x66,

    /* U+0062 "b" */
    0x0, 0x0, 0x71, 0x0, 0x51, 0x0, 0x55, 0x62,
    0x52, 0x7, 0x51, 0x7, 0x44, 0x52,

    /* U+0063 "c" */
    0x15, 0x61, 0x70, 0x10, 0x70, 0x0, 0x16, 0x41,

    /* U+0064 "d" */
    0x0, 0x0, 0x0, 0x45, 0x0, 0x25, 0x16, 0x55,
    0x70, 0x25, 0x70, 0x25, 0x26, 0x56,

    /* U+0065 "e" */
    0x14, 0x53, 0x63, 0x34, 0x61, 0x1, 0x17, 0x41,

    /* U+0066 "f" */
    0x3, 0x37, 0x6, 0x0, 0x18, 0x30, 0x7, 0x0,
    0x7, 0x0, 0x19, 0x20,

    /* U+0067 "g" */
    0x15, 0x75, 0x42, 0x51, 0x25, 0x30, 0x35, 0x43,
    0x43, 0x44,

    /* U+0068 "h" */
    0x62, 0x0, 0x52, 0x0, 0x56, 0x72, 0x52, 0x24,
    0x52, 0x25, 0x63, 0x36,

    /* U+0069 "i" */
    0x3, 0x40, 0x0, 0x0, 0x6, 0x30, 0x3, 0x30,
    0x3, 0x30, 0x6, 0x60,

    /* U+006A "j" */
    0x0, 0x51, 0x0, 0x10, 0x0, 0x81, 0x0, 0x51,
    0x0, 0x51, 0x0, 0x51, 0x36, 0x50,

    /* U+006B "k" */
    0x62, 0x0, 0x42, 0x0, 0x42, 0x71, 0x47, 0x40,
    0x44, 0x80, 0x64, 0x65,

    /* U+006C "l" */
    0x6, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30,
    0x3, 0x30, 0x6, 0x60,

    /* U+006D "m" */
    0x96, 0x66, 0x73, 0x47, 0x73, 0x47, 0x84, 0x59,

    /* U+006E "n" */
    0x66, 0x62, 0x52, 0x24, 0x52, 0x25, 0x63, 0x36,

    /* U+006F "o" */
    0x15, 0x51, 0x70, 0x7, 0x70, 0x7, 0x24, 0x42,

    /* U+0070 "p" */
    0x76, 0x53, 0x52, 0x7, 0x52, 0x7, 0x56, 0x52,
    0x64, 0x0,

    /* U+0071 "q" */
    0x25, 0x54, 0x70, 0x24, 0x70, 0x24, 0x25, 0x64,
    0x0, 0x46,

    /* U+0072 "r" */
    0x39, 0x46, 0x8, 0x0, 0x7, 0x0, 0x29, 0x10,

    /* U+0073 "s" */
    0x15, 0x63, 0x18, 0x10, 0x10, 0x63, 0x46, 0x43,

    /* U+0074 "t" */
    0x6, 0x0, 0x18, 0x30, 0x7, 0x0, 0x6, 0x0,
    0x5, 0x51,

    /* U+0075 "u" */
    0x71, 0x44, 0x51, 0x24, 0x51, 0x24, 0x27, 0x55,

    /* U+0076 "v" */
    0x56, 0x34, 0x7, 0x30, 0x7, 0x30, 0x4, 0x20,

    /* U+0077 "w" */
    0x95, 0x56, 0x53, 0x63, 0x26, 0x80, 0x6, 0x60,

    /* U+0078 "x" */
    0x29, 0x62, 0x6, 0x40, 0x4, 0x70, 0x35, 0x73,

    /* U+0079 "y" */
    0x46, 0x44, 0x6, 0x40, 0x6, 0x40, 0x2, 0x20,
    0x35, 0x0,

    /* U+007A "z" */
    0x54, 0x91, 0x1, 0x60, 0x7, 0x1, 0x47, 0x44,

    /* U+007B "{" */
    0x2, 0x10, 0x40, 0x4, 0x0, 0x40, 0x3, 0x0,
    0x40, 0x4, 0x0, 0x21,

    /* U+007C "|" */
    0x10, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
    0x21,

    /* U+007D "}" */
    0x12, 0x0, 0x40, 0x4, 0x0, 0x40, 0x4, 0x0,
    0x40, 0x4, 0x1, 0x20,

    /* U+007E "~" */
    0x25, 0x0, 0x0, 0x52,

    /* U+52A8 "动" */
    0x0, 0x0, 0x2, 0x0, 0x13, 0x34, 0x6, 0x0,
    0x0, 0x0, 0x38, 0x51, 0x14, 0x74, 0x5, 0x60,
    0x6, 0x21, 0x23, 0x60, 0x25, 0x38, 0x50, 0x70,
    0x33, 0x3, 0x31, 0x70, 0x0, 0x2, 0x3, 0x50,

    /* U+542F "启" */
    0x0, 0x2, 0x10, 0x0, 0x33, 0x46, 0x34, 0x7,
    0x0, 0x0, 0x70, 0x73, 0x33, 0x35, 0x7, 0x33,
    0x33, 0x40, 0x76, 0x0, 0x7, 0x14, 0x63, 0x33,
    0x72, 0x3, 0x0, 0x3,

    /* U+56DE "回" */
    0x0, 0x0, 0x0, 0x8, 0x33, 0x33, 0x80, 0x72,
    0x33, 0x36, 0x7, 0x60, 0x7, 0x60, 0x76, 0x33,
    0x76, 0x7, 0x30, 0x3, 0x60, 0x83, 0x33, 0x38,
    0x4, 0x0, 0x0, 0x20,

    /* U+5DF2 "已" */
    0x0, 0x0, 0x0, 0x2, 0x33, 0x33, 0x70, 0x10,
    0x0, 0x7, 0x8, 0x33, 0x33, 0x70, 0x70, 0x0,
    0x0, 0x7, 0x0, 0x0, 0x2, 0x70, 0x0, 0x2,
    0x61, 0x55, 0x55, 0x51,

    /* U+63A5 "接" */
    0x3, 0x0, 0x20, 0x0, 0x6, 0x3, 0x45, 0x40,
    0x28, 0x41, 0x55, 0x10, 0x6, 0x23, 0x74, 0x42,
    0x5a, 0x33, 0x93, 0x33, 0x6, 0x5, 0x17, 0x10,
    0x6, 0x0, 0x78, 0x40, 0x7, 0x24, 0x20, 0x41,

    /* U+7F51 "网" */
    0x0, 0x0, 0x1, 0x8, 0x33, 0x33, 0x80, 0x72,
    0x72, 0x87, 0x7, 0x72, 0x46, 0x70, 0x75, 0x74,
    0x97, 0x8, 0x12, 0x23, 0x70, 0x70, 0x0, 0x18,
    0x3, 0x0, 0x0, 0x50,

    /* U+8FD4 "返" */
    0x0, 0x0, 0x0, 0x20, 0x6, 0x6, 0x34, 0x20,
    0x0, 0x8, 0x33, 0x30, 0x27, 0x17, 0x2, 0x50,
    0x6, 0x6, 0x49, 0x0, 0x6, 0x22, 0x46, 0x60,
    0x7, 0x33, 0x20, 0x30, 0x42, 0x36, 0x77, 0x82,
    0x0, 0x0, 0x0, 0x0,

    /* U+8FDE "连" */
    0x0, 0x0, 0x40, 0x0, 0x7, 0x23, 0x93, 0x60,
    0x0, 0x6, 0x41, 0x0, 0x28, 0x18, 0x83, 0x40,
    0x7, 0x0, 0x60, 0x20, 0x7, 0x23, 0x83, 0x31,
    0x8, 0x30, 0x60, 0x0, 0x41, 0x26, 0x98, 0x82,
    0x0, 0x0, 0x0, 0x0,

    /* U+914D "配" */
    0x0, 0x0, 0x0, 0x0, 0x1, 0x49, 0x33, 0x33,
    0x70, 0x8, 0xa7, 0x0, 0x6, 0x0, 0x97, 0x65,
    0x33, 0x60, 0x8, 0x29, 0x60, 0x0, 0x0, 0x83,
    0x86, 0x0, 0x0, 0x8, 0x38, 0x60, 0x3, 0x0,
    0x60, 0x64, 0x65, 0x90, 0x1, 0x0, 0x0, 0x0,
    0x0,

    /* U+F001 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x26, 0xbe,
    0x0, 0x8d, 0xff, 0xff, 0x0, 0xff, 0xe9, 0x5f,
    0x0, 0xf3, 0x0, 0xf, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0xf0, 0xa, 0xff, 0xaf, 0xf0, 0xa, 0xfa,
    0xaf, 0xa0, 0x0, 0x0,

    /* U+F008 "" */
    0xbd, 0xcc, 0xce, 0xab, 0x8b, 0x0, 0x7, 0x58,
    0xcd, 0x66, 0x6a, 0xac, 0xcd, 0x66, 0x6a, 0xac,
    0x8b, 0x0, 0x7, 0x58, 0xbd, 0xcc, 0xce, 0xab,

    /* U+F00B "" */
    0x34, 0x14, 0x44, 0x43, 0xff, 0x7f, 0xff, 0xff,
    0xab, 0x4b, 0xbb, 0xba, 0xbc, 0x5c, 0xcc, 0xcb,
    0xff, 0x7f, 0xff, 0xff, 0x67, 0x17, 0x88, 0x86,
    0xff, 0x7f, 0xff, 0xff, 0xab, 0x4b, 0xbb, 0xba,

    /* U+F00C "" */
    0x0, 0x0, 0x0, 0x9a, 0x0, 0x0, 0x9, 0xfa,
    0xa9, 0x0, 0x9f, 0xa0, 0xaf, 0x99, 0xfa, 0x0,
    0xa, 0xff, 0xa0, 0x0, 0x0, 0x99, 0x0, 0x0,

    /* U+F00D "" */
    0x63, 0x0, 0x82, 0xcf, 0x4a, 0xf4, 0x1d, 0xff,
    0x60, 0xa, 0xff, 0x30, 0xaf, 0x7d, 0xf3, 0xa6,
    0x1, 0xb3,

    /* U+F011 "" */
    0x0, 0xc, 0x51, 0x0, 0x1d, 0x7d, 0x6e, 0x70,
    0x8d, 0xd, 0x65, 0xf1, 0xc7, 0xd, 0x60, 0xe6,
    0xd7, 0x6, 0x20, 0xe6, 0x9d, 0x0, 0x4, 0xf2,
    0x1e, 0xc7, 0x8f, 0x80, 0x1, 0x9d, 0xc6, 0x0,

    /* U+F013 "" */
    0x0, 0xc, 0xc0, 0x0, 0x18, 0x8f, 0xf8, 0x81,
    0x8f, 0xfe, 0xef, 0xf8, 0x2f, 0xe0, 0xe, 0xf2,
    0x2f, 0xe0, 0xe, 0xf2, 0x8f, 0xfe, 0xef, 0xf8,
    0x18, 0x8f, 0xf8, 0x81, 0x0, 0xc, 0xc0, 0x0,

    /* U+F015 "" */
    0x0, 0x0, 0x30, 0x22, 0x0, 0x0, 0xaf, 0xaa,
    0xa0, 0x1, 0xda, 0x6a, 0xfa, 0x3, 0xe8, 0xbf,
    0xb8, 0xe3, 0xb6, 0xdf, 0xff, 0xd6, 0xb0, 0x8f,
    0xfb, 0xff, 0x80, 0x8, 0xfc, 0xc, 0xf8, 0x0,
    0x5b, 0x80, 0x8b, 0x50,

    /* U+F019 "" */
    0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0xf0, 0x0,
    0x0, 0xf, 0xf0, 0x0, 0x7, 0xff, 0xff, 0x70,
    0x0, 0x9f, 0xf9, 0x0, 0x78, 0x7a, 0xa7, 0x87,
    0xff, 0xfb, 0xbf, 0xff, 0xff, 0xff, 0xfb, 0xbf,

    /* U+F01C "" */
    0x5, 0xff, 0xff, 0xf5, 0x1, 0xe3, 0x0, 0x3,
    0xe1, 0xa8, 0x0, 0x0, 0x8, 0xaf, 0xff, 0x60,
    0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff,
    0xff, 0xff, 0xfd,

    /* U+F021 "" */
    0x0, 0x0, 0x0, 0x3, 0x2, 0xbf, 0xfb, 0x3f,
    0x2e, 0x91, 0x18, 0xff, 0x9a, 0x0, 0x6c, 0xff,
    0x31, 0x0, 0x24, 0x44, 0x44, 0x42, 0x0, 0x13,
    0xff, 0xc6, 0x0, 0xb9, 0xfe, 0xa5, 0x5b, 0xd1,
    0xf2, 0x8c, 0xc8, 0x10, 0x30, 0x0, 0x0, 0x0,

    /* U+F026 "" */
    0x0, 0x9, 0x34, 0xcf, 0xff, 0xff, 0xff, 0xff,
    0xab, 0xff, 0x0, 0x4f, 0x0, 0x1,

    /* U+F027 "" */
    0x0, 0x9, 0x0, 0x34, 0xcf, 0x1, 0xff, 0xff,
    0x1b, 0xff, 0xff, 0x1b, 0xbb, 0xff, 0x1, 0x0,
    0x4f, 0x0, 0x0, 0x1, 0x0,

    /* U+F028 "" */
    0x0, 0x0, 0x0, 0x54, 0x0, 0x0, 0x90, 0x23,
    0xb3, 0x34, 0xcf, 0x2, 0xc3, 0xbf, 0xff, 0xf1,
    0xb5, 0x6c, 0xff, 0xff, 0x1b, 0x56, 0xca, 0xbf,
    0xf0, 0x2c, 0x3a, 0x0, 0x4f, 0x2, 0x3b, 0x30,
    0x0, 0x10, 0x5, 0x40,

    /* U+F03E "" */
    0xdf, 0xff, 0xff, 0xfd, 0xf0, 0x7f, 0xff, 0xff,
    0xf8, 0xcf, 0xb1, 0xbf, 0xfb, 0x5b, 0x0, 0xf,
    0xf0, 0x0, 0x0, 0xf, 0xdf, 0xff, 0xff, 0xfd,

    /* U+F048 "" */
    0x40, 0x0, 0x2f, 0x20, 0x8f, 0xf2, 0x9f, 0xff,
    0xcf, 0xff, 0xff, 0xff, 0xff, 0x5e, 0xff, 0xf2,
    0x2e, 0xfb, 0x10, 0x19,

    /* U+F04B "" */
    0x0, 0x0, 0x0, 0xd, 0xa1, 0x0, 0x0, 0xff,
    0xf7, 0x0, 0xf, 0xff, 0xfd, 0x40, 0xff, 0xff,
    0xff, 0xaf, 0xff, 0xff, 0xfa, 0xff, 0xff, 0xd4,
    0xf, 0xff, 0x70, 0x0, 0xda, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0,

    /* U+F04C "" */
    0x9b, 0x90, 0x9b, 0x9f, 0xff, 0xf, 0xff, 0xff,
    0xf0, 0xff, 0xff, 0xff, 0xf, 0xff, 0xff, 0xf0,
    0xff, 0xff, 0xff, 0xf, 0xff, 0xff, 0xf0, 0xff,
    0xf2, 0x42, 0x2, 0x42,

    /* U+F04D "" */
    0x24, 0x44, 0x44, 0x2f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf8, 0xbb, 0xbb, 0xb8,

    /* U+F051 "" */
    0x20, 0x0, 0x4f, 0x80, 0x2f, 0xff, 0x92, 0xff,
    0xff, 0xcf, 0xff, 0xff, 0xff, 0xfe, 0x5f, 0xfd,
    0x22, 0xf9, 0x10, 0x1b,

    /* U+F052 "" */
    0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x8f, 0x80,
    0x0, 0x0, 0x7f, 0xff, 0x70, 0x0, 0x5f, 0xff,
    0xff, 0x50, 0xe, 0xff, 0xff, 0xfe, 0x0, 0x58,
    0x88, 0x88, 0x50, 0xf, 0xff, 0xff, 0xff, 0x0,
    0xab, 0xbb, 0xbb, 0xa0,

    /* U+F053 "" */
    0x0, 0x6, 0x20, 0x7, 0xf4, 0x7, 0xf5, 0x5,
    0xf6, 0x0, 0x1e, 0xb0, 0x0, 0x2e, 0xb0, 0x0,
    0x2e, 0x60, 0x0, 0x10,

    /* U+F054 "" */
    0x26, 0x0, 0x4, 0xf7, 0x0, 0x5, 0xf7, 0x0,
    0x6, 0xf5, 0x0, 0xbe, 0x10, 0xbe, 0x20, 0x6e,
    0x20, 0x0, 0x10, 0x0,

    /* U+F067 "" */
    0x0, 0x4, 0x0, 0x0, 0x3, 0xf3, 0x0, 0x0,
    0x4f, 0x40, 0x7, 0x8a, 0xfa, 0x87, 0xef, 0xff,
    0xff, 0xe0, 0x4, 0xf4, 0x0, 0x0, 0x4f, 0x40,
    0x0, 0x1, 0xb1, 0x0,

    /* U+F068 "" */
    0x78, 0x88, 0x88, 0x7e, 0xff, 0xff, 0xfe,

    /* U+F06E "" */
    0x0, 0x8c, 0xcc, 0x80, 0x1, 0xdd, 0x16, 0x3d,
    0xd1, 0xcf, 0x55, 0xed, 0x5f, 0xcb, 0xf5, 0xdf,
    0xd5, 0xfc, 0x1d, 0xd3, 0x73, 0xdd, 0x10, 0x8,
    0xdc, 0xc8, 0x10,

    /* U+F070 "" */
    0x1d, 0x30, 0x0, 0x0, 0x0, 0x0, 0x5e, 0x8c,
    0xcc, 0xa2, 0x0, 0x0, 0x2d, 0xb4, 0x49, 0xf4,
    0x0, 0x7a, 0x1a, 0xff, 0x3f, 0xe1, 0x7, 0xfa,
    0x6, 0xf7, 0xff, 0x10, 0xa, 0xf3, 0x3, 0xef,
    0x40, 0x0, 0x6, 0xcc, 0x71, 0xbb, 0x10, 0x0,
    0x0, 0x0, 0x0, 0x89,

    /* U+F071 "" */
    0x0, 0x0, 0x3e, 0x30, 0x0, 0x0, 0x0, 0xc,
    0xfc, 0x0, 0x0, 0x0, 0x6, 0xfc, 0xf6, 0x0,
    0x0, 0x0, 0xed, 0xd, 0xe0, 0x0, 0x0, 0x8f,
    0xe0, 0xef, 0x80, 0x0, 0x2f, 0xff, 0x6f, 0xff,
    0x20, 0xb, 0xff, 0xe2, 0xef, 0xfa, 0x0, 0xdf,
    0xff, 0xff, 0xff, 0xd0,

    /* U+F074 "" */
    0x0, 0x0, 0x0, 0x20, 0x44, 0x0, 0x4, 0xf5,
    0xef, 0xb1, 0xcf, 0xfd, 0x1, 0x8c, 0xd1, 0xc1,
    0x1, 0xdc, 0x81, 0xc1, 0xef, 0xc1, 0xbf, 0xfd,
    0x44, 0x0, 0x4, 0xf5, 0x0, 0x0, 0x0, 0x20,

    /* U+F077 "" */
    0x0, 0x0, 0x0, 0x0, 0x4, 0xe4, 0x0, 0x4,
    0xfc, 0xf4, 0x4, 0xf8, 0x8, 0xf4, 0xb8, 0x0,
    0x8, 0xb0, 0x0, 0x0, 0x0,

    /* U+F078 "" */
    0x0, 0x0, 0x0, 0xb, 0x80, 0x0, 0x8b, 0x4f,
    0x80, 0x8f, 0x40, 0x4f, 0xcf, 0x40, 0x0, 0x4e,
    0x40, 0x0, 0x0, 0x0, 0x0,

    /* U+F079 "" */
    0x0, 0x94, 0x14, 0x44, 0x40, 0x0, 0xbf, 0xf8,
    0xbb, 0xbf, 0x10, 0x8, 0xb7, 0x60, 0x0, 0xe1,
    0x0, 0xb, 0x40, 0x0, 0x1e, 0x20, 0x0, 0xb7,
    0x44, 0x5e, 0xfd, 0x50, 0x7, 0xbb, 0xb8, 0x5f,
    0x80, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0,

    /* U+F07B "" */
    0xdf, 0xfb, 0x0, 0x0, 0xff, 0xff, 0xff, 0xfd,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xfd,

    /* U+F093 "" */
    0x0, 0x9, 0x90, 0x0, 0x0, 0x9f, 0xf9, 0x0,
    0x7, 0xff, 0xff, 0x70, 0x0, 0xf, 0xf0, 0x0,
    0x0, 0xf, 0xf0, 0x0, 0x78, 0x4f, 0xf4, 0x87,
    0xff, 0xe8, 0x8e, 0xff, 0xff, 0xff, 0xfb, 0xbf,

    /* U+F095 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7,
    0xea, 0x0, 0x0, 0x0, 0xef, 0xe0, 0x0, 0x0,
    0xc, 0xfc, 0x0, 0x0, 0x0, 0x4f, 0x70, 0x0,
    0x0, 0x1d, 0xe0, 0x7, 0xdc, 0x4d, 0xf3, 0x0,
    0xef, 0xff, 0xe3, 0x0, 0xa, 0xec, 0x70, 0x0,
    0x0,

    /* U+F0C4 "" */
    0x3, 0x0, 0x0, 0x0, 0xcd, 0xc0, 0x2d, 0xc0,
    0xe7, 0xf2, 0xee, 0x20, 0x4b, 0xff, 0xe2, 0x0,
    0x4, 0xff, 0xa0, 0x0, 0xcd, 0xf9, 0xf9, 0x0,
    0xe7, 0xe0, 0x7f, 0x90, 0x4a, 0x40, 0x4, 0x50,

    /* U+F0C5 "" */
    0x0, 0xff, 0xf7, 0x47, 0x4f, 0xff, 0x47, 0xf8,
    0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xf8, 0xff,
    0xff, 0xff, 0x8f, 0xff, 0xff, 0xfb, 0x78, 0x88,
    0x7f, 0xff, 0xff, 0x0,

    /* U+F0C7 "" */
    0x24, 0x44, 0x41, 0xf, 0xbb, 0xbb, 0xe2, 0xf0,
    0x0, 0xf, 0xdf, 0x44, 0x44, 0xff, 0xff, 0xfc,
    0xff, 0xff, 0xf9, 0x9, 0xff, 0xff, 0xd5, 0xdf,
    0xf8, 0xbb, 0xbb, 0xb8,

    /* U+F0E7 "" */
    0x7, 0xff, 0x60, 0x0, 0xaf, 0xf2, 0x0, 0xc,
    0xff, 0x87, 0x0, 0xef, 0xff, 0xb0, 0x7, 0x8e,
    0xf2, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x3e, 0x0,
    0x0, 0x6, 0x50, 0x0,

    /* U+F0EA "" */
    0x79, 0xb9, 0x70, 0xf, 0xfc, 0xff, 0x0, 0xff,
    0x68, 0x83, 0xf, 0xf8, 0xff, 0x8b, 0xff, 0x8f,
    0xf8, 0x8f, 0xf8, 0xff, 0xff, 0x78, 0x8f, 0xff,
    0xf0, 0x7, 0xff, 0xff,

    /* U+F0F3 "" */
    0x0, 0xd, 0x0, 0x0, 0x4e, 0xfe, 0x30, 0xd,
    0xff, 0xfd, 0x0, 0xff, 0xff, 0xf0, 0x3f, 0xff,
    0xff, 0x3b, 0xff, 0xff, 0xfb, 0x78, 0x88, 0x88,
    0x60, 0x4, 0xf4, 0x0,

    /* U+F11C "" */
    0xdf, 0xff, 0xff, 0xff, 0xdf, 0x18, 0x81, 0x88,
    0x1f, 0xfe, 0xaa, 0xca, 0xae, 0xff, 0xea, 0xac,
    0xaa, 0xef, 0xf1, 0x80, 0x0, 0x81, 0xfd, 0xff,
    0xff, 0xff, 0xfd,

    /* U+F124 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4b, 0xc0, 0x0, 0x0, 0x5c, 0xff, 0xb0, 0x0,
    0x6e, 0xff, 0xff, 0x40, 0xd, 0xff, 0xff, 0xfc,
    0x0, 0x6, 0x88, 0xcf, 0xf5, 0x0, 0x0, 0x0,
    0x8f, 0xe0, 0x0, 0x0, 0x0, 0x8f, 0x60, 0x0,
    0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0,

    /* U+F15B "" */
    0xff, 0xf8, 0xb0, 0xff, 0xf8, 0xfb, 0xff, 0xfc,
    0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+F1EB "" */
    0x0, 0x4, 0x77, 0x40, 0x0, 0x9, 0xff, 0xcc,
    0xff, 0x90, 0xcd, 0x40, 0x0, 0x4, 0xdc, 0x20,
    0x4b, 0xff, 0xb4, 0x2, 0x1, 0xfa, 0x55, 0xaf,
    0x10, 0x0, 0x0, 0x21, 0x0, 0x0, 0x0, 0x0,
    0xee, 0x0, 0x0, 0x0, 0x0, 0x87, 0x0, 0x0,

    /* U+F240 "" */
    0x24, 0x44, 0x44, 0x44, 0x40, 0xfb, 0xbb, 0xbb,
    0xbb, 0xda, 0xf7, 0xee, 0xee, 0xee, 0x5f, 0xf8,
    0xff, 0xff, 0xff, 0x2f, 0xf5, 0x66, 0x66, 0x66,
    0xab, 0x8b, 0xbb, 0xbb, 0xbb, 0xb3,

    /* U+F241 "" */
    0x24, 0x44, 0x44, 0x44, 0x40, 0xfb, 0xbb, 0xbb,
    0xbb, 0xda, 0xf7, 0xee, 0xee, 0x70, 0x5f, 0xf8,
    0xff, 0xff, 0x80, 0x2f, 0xf5, 0x66, 0x66, 0x54,
    0xab, 0x8b, 0xbb, 0xbb, 0xbb, 0xb3,

    /* U+F242 "" */
    0x24, 0x44, 0x44, 0x44, 0x40, 0xfb, 0xbb, 0xbb,
    0xbb, 0xda, 0xf7, 0xee, 0xe0, 0x0, 0x5f, 0xf8,
    0xff, 0xf0, 0x0, 0x2f, 0xf5, 0x66, 0x64, 0x44,
    0xab, 0x8b, 0xbb, 0xbb, 0xbb, 0xb3,

    /* U+F243 "" */
    0x24, 0x44, 0x44, 0x44, 0x40, 0xfb, 0xbb, 0xbb,
    0xbb, 0xda, 0xf7, 0xe7, 0x0, 0x0, 0x5f, 0xf8,
    0xf8, 0x0, 0x0, 0x2f, 0xf5, 0x65, 0x44, 0x44,
    0xab, 0x8b, 0xbb, 0xbb, 0xbb, 0xb3,

    /* U+F244 "" */
    0x24, 0x44, 0x44, 0x44, 0x40, 0xfb, 0xbb, 0xbb,
    0xbb, 0xd8, 0xf0, 0x0, 0x0, 0x0, 0x5f, 0xf0,
    0x0, 0x0, 0x0, 0x2f, 0xf4, 0x44, 0x44, 0x44,
    0xad, 0x8b, 0xbb, 0xbb, 0xbb, 0xb3,

    /* U+F287 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7,
    0xd8, 0x0, 0x0, 0x0, 0x7, 0x36, 0x40, 0x0,
    0x9, 0xb1, 0x91, 0x11, 0x17, 0x20, 0xef, 0x88,
    0xd8, 0x88, 0xd9, 0x2, 0x20, 0x6, 0x48, 0x70,
    0x0, 0x0, 0x0, 0x6, 0xec, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0,

    /* U+F293 "" */
    0x6, 0xdd, 0xc3, 0x4, 0xff, 0x3e, 0xd0, 0x9c,
    0xb5, 0x5f, 0x2b, 0xf7, 0x1a, 0xf4, 0xbf, 0x81,
    0xbf, 0x39, 0xc9, 0x64, 0xf2, 0x4f, 0xf3, 0xde,
    0x0, 0x6d, 0xed, 0x30,

    /* U+F2ED "" */
    0x78, 0xdf, 0xd8, 0x77, 0x88, 0x88, 0x87, 0x8f,
    0xff, 0xff, 0x88, 0xcc, 0x8c, 0xc8, 0x8c, 0xc8,
    0xcc, 0x88, 0xcc, 0x8c, 0xc8, 0x8c, 0xc8, 0xcc,
    0x85, 0xff, 0xff, 0xf5,

    /* U+F304 "" */
    0x0, 0x0, 0x0, 0x7e, 0x30, 0x0, 0x0, 0x4b,
    0xfe, 0x0, 0x0, 0x8f, 0x9b, 0x70, 0x0, 0x8f,
    0xff, 0x40, 0x0, 0x8f, 0xff, 0x80, 0x0, 0x7f,
    0xff, 0x80, 0x0, 0xe, 0xff, 0x80, 0x0, 0x0,
    0xee, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+F55A "" */
    0x0, 0xaf, 0xff, 0xff, 0xfc, 0xb, 0xff, 0x9c,
    0xc9, 0xff, 0xaf, 0xff, 0xc1, 0x1c, 0xff, 0xaf,
    0xff, 0xc1, 0x1c, 0xff, 0xb, 0xff, 0x9c, 0xc9,
    0xff, 0x0, 0xaf, 0xff, 0xff, 0xfc,

    /* U+F7C2 "" */
    0x7, 0xff, 0xfe, 0x17, 0xb6, 0x27, 0xc3, 0xfe,
    0xb9, 0xbe, 0x3f, 0xff, 0xff, 0xf3, 0xff, 0xff,
    0xff, 0x3f, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff,
    0x3c, 0xff, 0xff, 0xe1,

    /* U+F8A2 "" */
    0x0, 0x0, 0x0, 0x3, 0x0, 0x23, 0x0, 0x2,
    0xf0, 0x2e, 0x92, 0x22, 0x5f, 0xd, 0xff, 0xff,
    0xff, 0xf0, 0x2e, 0x92, 0x22, 0x21, 0x0, 0x23,
    0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 64, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 12, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 40, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 64, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 79, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 91, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 111, .adv_w = 64, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 113, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 131, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 64, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 260, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 64, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 280, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 442, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 528, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 648, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 662, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 674, .adv_w = 64, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 676, .adv_w = 64, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 678, .adv_w = 64, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 680, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 754, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 792, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 816, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 850, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 860, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 928, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 948, .adv_w = 64, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 957, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 969, .adv_w = 64, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 973, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1005, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1033, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1061, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1089, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1121, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1149, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1185, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1221, .adv_w = 128, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1262, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1298, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1322, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1354, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1378, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1396, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1428, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1460, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1496, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1528, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1555, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1595, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1609, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1630, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1666, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1690, .adv_w = 112, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1710, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1745, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1773, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1801, .adv_w = 112, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1821, .adv_w = 112, .box_w = 9, .box_h = 8, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1857, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1877, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1897, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1925, .adv_w = 112, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1932, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1959, .adv_w = 160, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2003, .adv_w = 144, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2047, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2079, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2100, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2121, .adv_w = 160, .box_w = 11, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2160, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2184, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2216, .adv_w = 128, .box_w = 9, .box_h = 9, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2257, .adv_w = 112, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2289, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2317, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2345, .adv_w = 80, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2373, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2401, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2429, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2456, .adv_w = 128, .box_w = 10, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2506, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2530, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2570, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2600, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2630, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2660, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2690, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2720, .adv_w = 160, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2764, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2792, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2820, .adv_w = 128, .box_w = 9, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2861, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2891, .adv_w = 96, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2919, .adv_w = 129, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_2[] = {
    0x0, 0x187, 0x436, 0xb4a, 0x10fd, 0x2ca9, 0x3d2c, 0x3d36,
    0x3ea5, 0x9d59, 0x9d60, 0x9d63, 0x9d64, 0x9d65, 0x9d69, 0x9d6b,
    0x9d6d, 0x9d71, 0x9d74, 0x9d79, 0x9d7e, 0x9d7f, 0x9d80, 0x9d96,
    0x9da0, 0x9da3, 0x9da4, 0x9da5, 0x9da9, 0x9daa, 0x9dab, 0x9dac,
    0x9dbf, 0x9dc0, 0x9dc6, 0x9dc8, 0x9dc9, 0x9dcc, 0x9dcf, 0x9dd0,
    0x9dd1, 0x9dd3, 0x9deb, 0x9ded, 0x9e1c, 0x9e1d, 0x9e1f, 0x9e3f,
    0x9e42, 0x9e4b, 0x9e74, 0x9e7c, 0x9eb3, 0x9f43, 0x9f98, 0x9f99,
    0x9f9a, 0x9f9b, 0x9f9c, 0x9fdf, 0x9feb, 0xa045, 0xa05c, 0xa2b2,
    0xa51a, 0xa5fa
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 33, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 45, .range_length = 82, .glyph_id_start = 12,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 21160, .range_length = 42491, .glyph_id_start = 94,
        .unicode_list = unicode_list_2, .glyph_id_ofs_list = NULL, .list_length = 66, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 3,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_font_simsun_8 = {
#else
lv_font_t lv_font_simsun_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_FONT_SIMSUN_8*/

