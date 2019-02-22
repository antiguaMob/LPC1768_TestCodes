#include "lcd.h"


void lcd_send_nibble(uint8_t rs,uint8_t val)

{
	//rs=(0/1) (command/data)
	if(rs==LCD_CMD)
		LCD_CTRL_GPIO->FIOCLR= (1<<LCD_RS);
	else 
		LCD_CTRL_GPIO->FIOSET |= (1<<LCD_RS);

	//rw=0
	LCD_CTRL_GPIO->FIOCLR= (1<<LCD_RW);
	//write nibble on D4 to D7
	LCD_DATA_GPIO->FIOCLR = (1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4);
	LCD_DATA_GPIO->FIOSET |= (uint32_t)val<<LCD_D4;
	//falling edge on EN
	LCD_CTRL_GPIO->FIOSET |= (1<<LCD_EN);
	SW_DELAY_MS(10);
	LCD_CTRL_GPIO->FIOCLR = (1<<LCD_EN);
}

void lcd_busy_wait(void)
{
	//make D7 pin as input --->> FIODIR=0 (as input)
	LCD_DATA_GPIO->FIODIR &= ~(1<<LCD_D7);
	//rs=0
	LCD_CTRL_GPIO->FIOCLR = (1<<LCD_RS);
	//rw=1, en=1
	LCD_CTRL_GPIO->FIOSET |= (1<<LCD_RW)|(1<<LCD_EN);
	//read D7 pin and wait until it becomes 0
	while(LCD_DATA_GPIO->FIOPIN & (1<<LCD_D7));

	//en=0
	LCD_CTRL_GPIO->FIOCLR = (1<<LCD_EN);
	//make D7 pin as O/P
	LCD_DATA_GPIO->FIODIR |= (1<<LCD_D7);
}


void lcd_send_byte(uint8_t rs,uint8_t val)
{
	uint8_t high= (val>>4);
	uint8_t low= (val & 0x0F);
	lcd_send_nibble(rs,high);
	lcd_send_nibble(rs,low);
	lcd_busy_wait();
	SW_DELAY_MS(10);
}

void lcd_puts(uint8_t line,char * s)
{
	int i;
	//set line address: 0x80 or 0xC0
	lcd_send_byte(LCD_CMD,line);
	//send all chars one by one
	for(i=0;*(s+i)!='\0';i++)
		lcd_send_byte(LCD_DATA,*(s+i));
}

void lcd_init(void)
{
	//make data and ctrl ports as Output
	LCD_DATA_GPIO->FIODIR |= (1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4);
	LCD_CTRL_GPIO->FIODIR |= (1<<LCD_RW)|(1<<LCD_RS)|(1<<LCD_EN);
	//reset delay for LCD
	SW_DELAY_MS(300);
	//set LCD mode/function
	lcd_send_byte(LCD_CMD,LCD_4BIT_2LN_5x10);
	lcd_send_byte(LCD_CMD,LCD_DISPON);
	lcd_send_byte(LCD_CMD,LCD_ADDINCR);
	lcd_send_byte(LCD_CMD,LCD_CLEAR);

	SW_DELAY_MS(100);
}
