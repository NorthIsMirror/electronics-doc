#include "stm32f4xx_hal.h"

#define 	UTIME	(SystemCoreClock / 1000000)

void delay_us(uint32_t us)
{
    us *= UTIME;	//pro 168MHz overeno, zmereno hodnota 44
    while(us--)
    {
        __NOP();
    }
}

GPIO_InitTypeDef GPIOStructure;
GPIO_InitTypeDef GPIOControl;

void lcd_strobe(void)
{
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_EN, 1);
    delay_us(2);
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_EN, 0);
}

void lcd_write(unsigned char c)
{
    //upper
    if(c & 0x80) HAL_GPIO_WritePin(LCD_PORT, LCD_D7, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D7, 0);
    if(c & 0x40) HAL_GPIO_WritePin(LCD_PORT, LCD_D6, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D6, 0);
    if(c & 0x20) HAL_GPIO_WritePin(LCD_PORT, LCD_D5, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D5, 0);
    if(c & 0x10) HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 0);
    lcd_strobe();
    //lowwer
    if(c & 0x08) HAL_GPIO_WritePin(LCD_PORT, LCD_D7, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D7, 0);
    if(c & 0x04) HAL_GPIO_WritePin(LCD_PORT, LCD_D6, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D6, 0);
    if(c & 0x02) HAL_GPIO_WritePin(LCD_PORT, LCD_D5, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D5, 0);
    if(c & 0x01) HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 1); else HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 0);
    lcd_strobe();
    delay_us(50);
}

void lcd_clear(void)
{
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RS, 0);    // write control bytes
    lcd_write(1<<LCD_CLR);
    HAL_Delay(10);
}

void lcd_puts(const char * s)
{
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RS, 1);    // write characters
    while(*s)
        lcd_write(*s++);
}

void lcd_putch(unsigned char c)
{
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RS, 1);    // write characters
    lcd_write(c);
}

void lcd_goto(unsigned char pos,unsigned char line)
{
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RS, 0);
    switch (line)
    {
        case 0:
            lcd_write((1<<LCD_DDRAM) + pos + LCD_START_LINE0);
            break;
        case 1:
            lcd_write((1<<LCD_DDRAM) + pos + LCD_START_LINE1);
            break;
        case 2:
            lcd_write((1<<LCD_DDRAM) + pos + LCD_START_LINE2);
            break;
        case 3:
            lcd_write((1<<LCD_DDRAM) + pos + LCD_START_LINE3);
            break;
    }
}

void lcd_init(void)
{
    /* nazpomen uprasnit portik */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    HAL_GPIO_WritePin(LCD_PORT, LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7, 0);
    GPIOStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOStructure.Pull = GPIO_NOPULL;
    GPIOStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIOStructure.Pin = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    HAL_GPIO_Init(LCD_PORT, &GPIOStructure);

    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RW | LCD_RS | LCD_EN , 0);
    GPIOControl.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOControl.Pull = GPIO_NOPULL;
    GPIOControl.Speed = GPIO_SPEED_FREQ_LOW;
    GPIOControl.Pin = LCD_RW | LCD_RS | LCD_EN;
    HAL_GPIO_Init(LCD_DRIVE, &GPIOControl);

    HAL_Delay(10);

    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RW, 0);    //pin, ktery nepouzivam (proto je na nule) chi chi chiii
    HAL_GPIO_WritePin(LCD_DRIVE, LCD_RS, 0);
    HAL_Delay(15);// power on delay
    HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 1);
    HAL_GPIO_WritePin(LCD_PORT, LCD_D5, 1);
    lcd_strobe();
    HAL_Delay(5);
    lcd_strobe();    // init
    delay_us(100);
    lcd_strobe();    // init
    HAL_Delay(5);
    HAL_GPIO_WritePin(LCD_PORT, LCD_D4, 0);
    lcd_strobe();
    delay_us(40);

    lcd_write(LCD_FUNCTION_4BIT_2LINES);// 4 bit mode, 1/16 duty, 5x8 font, 2lines
    lcd_write(LCD_DISP_ON);
    lcd_write(LCD_ENTRY_INC_);// entry mode advance cursor
    lcd_write(LCD_CLR);// clear display and reset cursor
}
