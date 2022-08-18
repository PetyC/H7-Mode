#include <stdint.h>
#include "st7735s.h"


typedef enum
{
    NOP = 0x00,
    SWRESET = 0x01,   /* Software Reset */
    RDDID = 0x04,     /* Read Display ID */
    RDDST = 0x09,     /* Read Display Status */
    RDDPM = 0x0a,     /* Read Display Power Mode */
    RDDMADCTL = 0x0b, /* Read Display MADCTL */
    RDDCOLMOD = 0x0c, /* Read Display Pixel Format */
    RDDIM = 0x0d,     /* Read Display Image Mode */
    RDDSM = 0x0e,     /* Read Display Signal Mode */
    RDDSDR = 0x0f,    /* Read Display Self-Diagnostic Result */
    SLPIN = 0x10,     /* Sleep In */
    SLPOUT = 0x11,    /* Sleep Out */
    PTLON = 0x12,     /* Partial Display Mode On */
    NORON = 0x13,     /* Normal Display Mode On */
    INVOFF = 0x20,    /* Display Inversion Off */
    INVON = 0x21,     /* Display Inversion On */
    GAMSET = 0x26,    /* Gamma Set */
    DISPOFF = 0x28,   /* Display Off */
    DISPON = 0x29,    /* Display On */
    CASET = 0x2a,     /* Column Address Set */
    RASET = 0x2b,     /* Row Address Set */
    RAMWR = 0x2c,     /* Memory Write */
    RGBSET = 0x2d,    /* Color Setting 4k, 65k, 262k */
    RAMRD = 0x2e,     /* Memory Read */
    PTLAR = 0x30,     /* Partial Area */
    SCRLAR = 0x33,    /* Scroll Area Set */
    TEOFF = 0x34,     /* Tearing Effect Line OFF */
    TEON = 0x35,      /* Tearing Effect Line ON */
    MADCTL = 0x36,    /* Memory Data Access Control */
    VSCSAD = 0x37,    /* Vertical Scroll Start Address of RAM */
    IDMOFF = 0x38,    /* Idle Mode Off */
    IDMON = 0x39,     /* Idle Mode On */
    COLMOD = 0x3a,    /* Interface Pixel Format */
    RDID1 = 0xda,     /* Read ID1 Value */
    RDID2 = 0xdb,     /* Read ID2 Value */
    RDID3 = 0xdc,     /* Read ID3 Value */
    FRMCTR1 = 0xb1,   /* Frame Rate Control in normal mode, full colors */
    FRMCTR2 = 0xb2,   /* Frame Rate Control in idle mode, 8 colors */
    FRMCTR3 = 0xb3,   /* Frame Rate Control in partial mode, full colors */
    INVCTR = 0xb4,    /* Display Inversion Control */
    PWCTR1 = 0xc0,    /* Power Control 1 */
    PWCTR2 = 0xc1,    /* Power Control 2 */
    PWCTR3 = 0xc2,    /* Power Control 3 in normal mode, full colors */
    PWCTR4 = 0xc3,    /* Power Control 4 in idle mode 8colors */
    PWCTR5 = 0xc4,    /* Power Control 5 in partial mode, full colors */
    VMCTR1 = 0xc5,    /* VCOM Control 1 */
    VMOFCTR = 0xc7,   /* VCOM Offset Control */
    WRID2 = 0xd1,     /* Write ID2 Value */
    WRID3 = 0xd2,     /* Write ID3 Value */
    NVFCTR1 = 0xd9,   /* NVM Control Status */
    NVFCTR2 = 0xde,   /* NVM Read Command */
    NVFCTR3 = 0xdf,   /* NVM Write Command */
    GMCTRP1 = 0xe0,   /* Gamma '+'Polarity Correction Characteristics Setting */
    GMCTRN1 = 0xe1,   /* Gamma '-'Polarity Correction Characteristics Setting */
    GCV = 0xfc,       /* Gate Pump Clock Frequency Variable */
} ST7735S_Command;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*相关命令参数*/
uint8_t Set_Frame_Rate_CMD0[] = {0xB1, 0x02, 0x35, 0x36};                   // Frame rate 80Hz   全色正常模式
uint8_t Set_Frame_Rate_CMD1[] = {0xB2, 0x02, 0x35, 0x36};                   // Frame rate 80Hz   空闲模式8色
uint8_t Set_Frame_Rate_CMD2[] = {0xB3, 0x02, 0x35, 0x36, 0x02, 0x35, 0x36}; // Frame rate 80Hz   局部模式全色

uint8_t Set_Display_Inversion_CMD[] = {0xB4, 0x03}; //开启反转

//------------------------------------ST7735S Power Sequence-----------------------------------------//
uint8_t Set_Power_Sequence_CMD0[] = {0xC0, 0xA2, 0x02, 0x84}; //电源控制1
uint8_t Set_Power_Sequence_CMD1[] = {0xC1, 0xC5};             //电源控制2
uint8_t Set_Power_Sequence_CMD2[] = {0xC2, 0x0D, 0x00};       //电源控制3  正常全色模式
uint8_t Set_Power_Sequence_CMD3[] = {0xC3, 0x8D, 0x2A};       //电源控制3  正常全色模式
uint8_t Set_Power_Sequence_CMD4[] = {0xC4, 0x8D, 0xEE};       //电源控制3  正常全色模式
//---------------------------------End ST7735S Power Sequence---------------------------------------//

// VCOM
uint8_t Set_VCOM_CMD[] = {0xC5, 0x0a};

//内存数据访问控制  通过设置此选项来改变屏幕方向
#if (USE_HORIZONTAL == 0)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0x08}; // 0x08 0xC8 0x78 0xA8
#elif (USE_HORIZONTAL == 1)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0xC8}; // 0x08 0xC8 0x78 0xA8
#elif (USE_HORIZONTAL == 2)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0x78}; // 0x08 0xC8 0x78 0xA8
#else
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0xA8}; // 0x08 0xC8 0x78 0xA8
#endif

//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
uint8_t Set_Gamma_Sequence_CMD0[] = {0XE0, 0x12, 0x1C, 0x10, 0x18, 0x33, 0x2C, 0x25, 0x28, 0x28, 0x27, 0x2F, 0x3C, 0x00, 0x03, 0x03, 0x10}; //伽马 + 矫正
uint8_t Set_Gamma_Sequence_CMD1[] = {0XE1, 0x12, 0x1C, 0x10, 0x18, 0x2D, 0x28, 0x23, 0x28, 0x28, 0x26, 0x2F, 0x3B, 0x00, 0x03, 0x03, 0x10}; //伽马 - 矫正
//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//

// 65k mode
uint8_t Set_Interface_Pixel_CMD[] = {
    0x3A,
    0x05,
}; // 16-Bit
// Display on
uint8_t Set_Display_on_CMD[] = {0x29};
// Sleep out
uint8_t Set_Sleep_Out_CMD[] = {0x11};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(BUFFER)
#define FRAMESIZE (defWIDTH * defHEIGHT)
color565_t frame[FRAMESIZE] = {0};
#elif defined(BUFFER1)
#define FRAMESIZE 1
color565_t frame[FRAMESIZE] = {0};
#elif defined(HVBUFFER)
color565_t hvframe[defWIDTH] = {0};
color565_t hvcolor1;
typedef enum
{
    HF,
    VF,
    ONE,
    NONE
} hvtype_t;
hvtype_t hvtype = NONE;
#else
#error buffer mode not defined
#endif

uint16_t WIDTH = defWIDTH, HEIGHT = defHEIGHT;
uint16_t XSTART = defXSTART, YSTART = defYSTART;

uint16_t xmin, xmax, ymin, ymax;
uint8_t madctl;

/* colors */
color565_t color;
color565_t bg_color;

uint8_t backlight_pct;

void ST7735S_sleepIn(void)
{

    uint8_t pct = backlight_pct;
    Pin_BLK_Pct(0);
    backlight_pct = pct;
    uint8_t cmd[] = {DISPOFF, SLPIN};
    SPI_TransmitCmd(cmd, 2);
}

void ST7735S_sleepOut(void)
{
    Pin_BLK_Pct(backlight_pct);
    uint8_t cmd[] = {SLPOUT, DISPON};
    SPI_TransmitCmd(cmd, 2);
}


/**
 * @brief 设置原点显示方向
 * @param {rotation_t} r
 * @return {*}
 */
void setOrientation(rotation_t r)
{

    switch ((uint8_t)r)
    {
    case R0:
    {
        madctl = 0x78;
        WIDTH = defWIDTH;
        HEIGHT = defHEIGHT;
        XSTART = defXSTART;
        YSTART = defYSTART;
        break;
    }
    case R90:
    {
        madctl = 0xC8;      
        WIDTH = defHEIGHT;
        HEIGHT = defWIDTH;
        XSTART = defYSTART;
        YSTART = defXSTART;
        break;
    }
    case R180:
    {
        madctl = 0xA8;   
        WIDTH = defWIDTH;
        HEIGHT = defHEIGHT;
        XSTART = defXSTART;
        YSTART = defYSTART;
        break;
    }
    case R270:
    {
        madctl = 0x08;
        WIDTH = defHEIGHT;
        HEIGHT = defWIDTH;
        XSTART = defYSTART;
        YSTART = defXSTART;
        break;
    }
    }
    
    uint8_t cmd[] = {MADCTL, madctl};
    SPI_Transmit(cmd, 2);
}

void resetWindow(void)
{
    xmin = WIDTH - 1;
    xmax = 0;
    ymin = HEIGHT - 1;
    ymax = 0;
}

void updateWindow(uint16_t x, uint16_t y)
{

    if (x < WIDTH && y < HEIGHT)
    {
        if (x < xmin)
            xmin = x;
        if (x > xmax)
            xmax = x;
        if (y < ymin)
            ymin = y;
        if (y > ymax)
            ymax = y;
    }
}

/**
 * @brief LCD初始化工作
 * @param {*}
 * @return {*}
 */
void ST7735S_Init(void)
{

    Pin_RES_Low(); //复位
    Delay(100);
    Pin_RES_High();
    Delay(100);
    Pin_BLK_High(); //打开背光
    Delay(100);

    SPI_Transmit(Set_Sleep_Out_CMD, sizeof(Set_Sleep_Out_CMD));
    Delay(120); // Delay 120ms

    SPI_Transmit(Set_Frame_Rate_CMD0, sizeof(Set_Frame_Rate_CMD0));
    SPI_Transmit(Set_Frame_Rate_CMD1, sizeof(Set_Frame_Rate_CMD1));
    SPI_Transmit(Set_Frame_Rate_CMD2, sizeof(Set_Frame_Rate_CMD2));

    SPI_Transmit(Set_Display_Inversion_CMD, sizeof(Set_Display_Inversion_CMD));

    SPI_Transmit(Set_Power_Sequence_CMD0, sizeof(Set_Power_Sequence_CMD0));
    SPI_Transmit(Set_Power_Sequence_CMD1, sizeof(Set_Power_Sequence_CMD1));
    SPI_Transmit(Set_Power_Sequence_CMD2, sizeof(Set_Power_Sequence_CMD2));
    SPI_Transmit(Set_Power_Sequence_CMD3, sizeof(Set_Power_Sequence_CMD3));
    SPI_Transmit(Set_Power_Sequence_CMD4, sizeof(Set_Power_Sequence_CMD4));

    SPI_Transmit(Set_VCOM_CMD, sizeof(Set_VCOM_CMD));

    SPI_Transmit(Set_Memory_Data_Access_CMD, sizeof(Set_Memory_Data_Access_CMD));

    SPI_Transmit(Set_Gamma_Sequence_CMD0, sizeof(Set_Gamma_Sequence_CMD0));
    SPI_Transmit(Set_Gamma_Sequence_CMD1, sizeof(Set_Gamma_Sequence_CMD1));

    SPI_Transmit(Set_Interface_Pixel_CMD, sizeof(Set_Interface_Pixel_CMD));

    SPI_Transmit(Set_Display_on_CMD, sizeof(Set_Display_on_CMD));

}

void ST7735S_flush(void)
{
    uint16_t xm = xmin + XSTART, ym = ymin + YSTART;
    uint16_t xx = xmax + XSTART, yx = ymax + YSTART;

    uint8_t cas[] = {CASET, xm >> 8, xm, xx >> 8, xx};
    uint8_t ras[] = {RASET, ym >> 8, ym, yx >> 8, yx};
    uint8_t ram[] = {RAMWR};

    SPI_Transmit(cas, sizeof(cas));
    SPI_Transmit(ras, sizeof(ras));
    SPI_TransmitCmd(ram, 1);

#if defined(BUFFER)
#if 1
    uint16_t len = (xmax - xmin + 1) * 2;
    for (uint16_t y = ymin; y <= ymax; y++)
        SPI_TransmitData((uint8_t *)&frame[WIDTH * y + xmin], len);
#else
    uint16_t len = (xmax - xmin + 1) * 2 * (ymax - ymin + 1);
    SPI_TransmitData((uint8_t *)&frame[WIDTH * ymin + xmin], len);
#endif
#elif defined(HVBUFFER)
    if (hvtype == VF)
    { // horiz line
        uint16_t len = (xmax - xmin + 1) * 2;
        SPI_TransmitData((uint8_t *)&hvframe[xmin], len);
    }
    else if (hvtype == HF)
    { // vert line
        uint16_t len = (ymax - ymin + 1) * 2;
        SPI_TransmitData((uint8_t *)&hvframe[ymin], len);
    }
    else if (hvtype == ONE)
    { // single pixel
        SPI_TransmitData((uint8_t *)&hvcolor1, 2);
    }
    hvtype = NONE;
#elif defined(BUFFER1)
    SPI_TransmitData((uint8_t *)&frame[0], 2);
#else
#error buffer not defined.
#endif
    resetWindow();
}

#if defined(BUFFER)
void ST7735S_Pixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        frame[WIDTH * y + x] = color;
        updateWindow(x, y);
    }
}

void ST7735S_bgPixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        frame[WIDTH * y + x] = bg_color;
        updateWindow(x, y);
    }
}
#elif defined(HVBUFFER)
void set_hvpixel(uint16_t x, uint16_t y)
{
    // first pixel
    if (hvtype == NONE)
    {
    first_pixel:
        hvcolor1 = color;
        hvtype = ONE;
        updateWindow(x, y);
        return;
    }
    // second pixel
    if (hvtype == ONE)
    {
        if (y == ymax && y == ymin && (x == xmin - 1 || x == xmax + 1))
        {
            hvtype = VF;
            hvframe[xmin] = hvcolor1;
            hvframe[x] = color;
            updateWindow(x, y);
            return;
        }
        if (x == xmax && x == xmin && (y == ymin - 1 || y == ymax + 1))
        {
            hvtype = HF;
            hvframe[ymin] = hvcolor1;
            hvframe[y] = color;
            updateWindow(x, y);
            return;
        }
        ST7735S_flush();
        goto first_pixel;
    }
    // third+ pixel
    if (hvtype == VF)
    { // horiz line
        if (y == ymax && y == ymin && (x >= xmin - 1 && x <= xmax + 1))
        {
            hvframe[x] = color;
            updateWindow(x, y);
            return;
        }
        ST7735S_flush();
        goto first_pixel;
    }
    if (hvtype == HF)
    { // vert line
        if (x == xmax && x == xmin && (y >= ymin - 1 && y <= ymax + 1))
        {
            hvframe[y] = color;
            updateWindow(x, y);
            return;
        }
        ST7735S_flush();
        goto first_pixel;
    }
}

void ST7735S_Pixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        set_hvpixel(x, y);
    }
}

void ST7735S_bgPixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        color565_t c = color;
        color = bg_color;
        set_hvpixel(x, y);
        color = c;
    }
}

#elif defined(BUFFER1)
void ST7735S_Pixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        frame[0] = color;
        updateWindow(x, y);
        ST7735S_flush();
    }
}

void ST7735S_bgPixel(uint16_t x, uint16_t y)
{
    if (x < WIDTH && y < HEIGHT)
    {
        frame[0] = bg_color;
        updateWindow(x, y);
        ST7735S_flush();
    }
}
#endif

bool ST7735S_defineScrollArea(uint16_t x, uint16_t x2)
{

    /* tfa: top fixed area: nr of line from top of the frame mem and display) */
    uint16_t tfa = WIDTH - x2 + XSTART;
    /* vsa: height of the vertical scrolling area in nr of line of the frame mem
       (not the display) from the vertical scrolling address. the first line appears
       immediately after the bottom most line of the top fixed area. */
    uint16_t vsa = x2 - x + XSTART;
    /* bfa: bottom fixed are in nr of lines from bottom of the frame memory and display */
    uint16_t bfa = x + XSTART;

    if (tfa + vsa + bfa < 162)
        return false;

    /* reset mv */
    uint8_t CMD1[] = {MADCTL, madctl & ~(1 << 5)};
    SPI_Transmit(CMD1, sizeof(CMD1));

    uint8_t CMD[] = {SCRLAR, tfa >> 8, tfa,
                     vsa >> 8, vsa,
                     bfa >> 8, bfa};

    SPI_Transmit(CMD, sizeof(CMD));

    return true;
}

void ST7735S_tearingOn(bool blanking_only)
{

    uint8_t CMD[] = {TEON, (blanking_only) ? 0 : 1};
    SPI_Transmit(CMD, 2);
}

void ST7735S_tearingOff(void)
{

    uint8_t CMD[] = {TEOFF};
    SPI_Transmit(CMD, 1);
}

void ST7735S_scroll(uint8_t line)
{

    uint8_t CMD[] = {VSCSAD, 0, line};
    SPI_Transmit(CMD, 3);
}

void ST7735S_normalMode(void)
{
    uint8_t CMD[] = {NORON};
    SPI_Transmit(CMD, 1);
    /* reset mv */
    uint8_t CMD1[] = {MADCTL, madctl};
    SPI_Transmit(CMD1, sizeof(CMD1));
}

void ST7735S_partialArea(uint16_t from, uint16_t to)
{
    /* set ml */
    uint8_t bit = (from > to) ? 0 : 1;
    uint8_t CMD1[] = {MADCTL, madctl & ~(bit << 4)};
    SPI_Transmit(CMD1, sizeof(CMD1));

    uint8_t CMD[] = {PTLAR, (WIDTH - to + XSTART) >> 8, WIDTH - to + XSTART,
                     (WIDTH - from + XSTART) >> 8, WIDTH - from + XSTART};
    SPI_Transmit(CMD, sizeof(CMD));

    /* partial mode on */
    uint8_t CMD2[] = {PTLON};
    SPI_Transmit(CMD2, sizeof(CMD2));
}

void Delay(uint32_t d)
{
    _Delay(d);
}

/**
 * @brief LCD背光调整
 * @param {uint8_t} p
 * @return {*}
 */
void Backlight_Pct(uint8_t p)
{
    Pin_BLK_Pct(p % 101);
}
