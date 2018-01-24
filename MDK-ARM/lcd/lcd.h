/*
 * lcd.h
 *
 * Created: 2018/1/5 10:35:59
 *  Author: HXHZQ
 */ 


#ifndef LCD_H_
#define LCD_H_



#ifndef __BSP_LCD_GPRS_H
#define __BSP_LCD_GPRS_H

#define __DELAY_BACKWARD_COMPATIBLE__
//#include <integer.h>
#include <util/delay.h>
#include <avr/io.h>

#include "usart.h"
#include <math.h>



typedef enum{
	LCD_TRUE,
	LCD_FALSE,
}lcd_res_e;


 struct lcd_base_opt{
	 uchar (*reset)(void);
	 uchar (*ver)(void);
	 uchar (*bps)(uint );
	 uchar (*clr)(uchar c);
	 uchar (*lcdon)(lcd_res_e res_e);
	 uchar (*fsimg)(uint addr,uchar x,uchar y, uchar w,uchar h,uchar mode);
	 uchar (*fs_dload)(uint size);
	 uchar (*dir)(lcd_res_e V);
	 uchar (*bl)(uchar p);
	 uchar (*ps)(uchar x,uchar y,uchar c);
	 uchar (*pl)(uchar x1,uchar y1,uchar x2,uchar y2,uchar c);
	 uchar (*box)(uchar x1,uchar y1,uchar x2,uchar y2,uchar c,lcd_res_e F);
	 uchar (*cir)(uchar x,uchar y,uchar r,uchar c,lcd_res_e F);
	 uchar (*arc)(uchar x,uchar y,uchar r,uchar c,uint d0,uint d1);
	 uchar (*sbc)(uchar c);
	 uchar (*dc)(uchar x,uchar y,uchar *str,uchar c,lcd_res_e V,uchar s);
	 uchar (*btn)(uchar x,uchar y,uchar w,uchar h,uchar *str,uchar style,uchar frame_color,uchar Fcolor,uchar Bcolor);
	 uchar (*put_var)(uint addr,uchar a,uchar b,uchar c,uchar d);
	 uchar (*get_var)(uint addr);
	 uchar (*check_busy)(void);

 };

 struct lcd_opt{

	uchar (*fsimg_220176)(uchar *addr);
	uchar (*fsimg_3232)(uchar *addr,uchar x,uchar y);
	uchar (*fsimg_4844)(uchar *addr,uchar x,uchar y);
	
	void (*fsimg_fan)(void);

	 uchar (*fsimg_g)(lcd_res_e flag);
	 uchar (*fsimg_l)(lcd_res_e flag);
	 uchar (*fsimg_n)(lcd_res_e flag);
	 uchar (*fsimg_y)(lcd_res_e flag);


	 uchar (*signal)(uchar n);
	
	 //uchar lcd_val(uchar x,uchar y,uint val,uint c);
		uchar (*box_tds_in)(uchar n,uchar c);
		void (*boxn_tds_in)(uchar n);
		uchar (*box_tds_in_bottom)(void);

		uchar (*box_tds_out)(uchar n,uchar c);
		void (*boxn_tds_out)(uchar n);
		uchar (*box_tds_out_bottom)(void);

		uchar (*box_1)(uchar n,uchar c);
		void (*boxn_1)(uchar n);

		uchar (*box_2)(uchar n,uchar c);
		void (*boxn_2)(uchar n);

		uchar (*box_3)(uchar n,uchar c);
		void (*boxn_3)(uchar n);

		uchar (*box_4)(uchar n,uchar c);
		void (*boxn_4)(uchar n);

		uchar (*box_5)(uchar n,uchar c);
		void (*boxn_5)(uchar n);

		uchar (*val_tds_in)(uint val);
		uchar (*val_tds_out)(uint val);

		uchar (*date)(uint val);
		uchar (*flow)(uint water);
		uchar (*title)(char * );

		uchar (*flash_point)(uchar x,uchar y,uchar old_c,uchar new_c);

 };


 struct use_lcd{
	uchar (*addr)[8];
	uchar tds_in_val;
	uchar tds_in_box;
	uchar tds_out_val;
	uchar tds_out_box;
	uchar tds_date;
	uchar tds_water;
	uchar box1;
	uchar box2;
	uchar box3;
	uchar box4;
	uchar box5;
	uchar *title;
	


	struct lcd_base_opt *base_opt;
	struct lcd_opt *opt;
 };



extern  uchar    lcd_cmd         	(char *cmd, char *reply,uint waittime );
extern  uchar    lcd_cmd_check   	(char *reply);


struct use_lcd *get_lcd(void);
void init_lcd_opt(void);





#define     LCD_USART_Config()			Init_LCD()
#define     LCD_CLEAN_RX()              clean_rebuff0()

#define     LCD_TX(cmd)                	hal_uart


#define     LCD_IS_RX()                 ((UCSR0A & (1<<UDRE0)) == RESET)
#define     LCD_RX(len)                 ((char *)get_rebuff0(&(len)))
#define     LCD_DELAY(time)             _delay_ms(time)                 //ʱ





#endif /* LCD_H_ */