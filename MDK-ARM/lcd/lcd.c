/*
* lcd.c
*
* Created: 2018/1/5 10:35:44
*  Author: HXHZQ
*/

#include "lcd.h"


uchar (lcd_flash)[16][8] = {"2097152",
"2174592","2176640","2178688","2180736",
"2182784","2187008","2191232","2195456",
"2199680","2203904","2208128","2212352",
};


//0ʾɹ1ʾʧ
uchar lcd_cmd(char *cmd, char *reply,uint const waittime )
{
	
	

	

	//LCD_CLEAN_RX();                 //˽ջ

	LCD_TX(cmd);                    //

	//LCD_DEBUG("Send cmd:%s",cmd);

	if(reply == 0)                      //Ҫ
	{
		return LCD_TRUE;
	}
	
	LCD_DELAY(waittime);                 //ʱ
	
	
	return lcd_cmd_check(reply);    //Խݽд
}


//0ʾɹ1ʾʧ
uchar lcd_cmd_check(char *reply)
{

	return 0;
	uchar len;
	uchar n;
	uchar off;
	char *redata;
	


	// redata = LCD_RX(len);   //
	
	// *(redata+len) = '\0';

	
	
	n = 0;
	off = 0;
	while((n + off)<len)
	{
		if(reply[n] == 0)                 //Ϊջ߱Ƚ
		{
			return LCD_TRUE;
		}
		
		if(redata[ n + off]== reply[n])
		{
			n++;                //ƶһ
		}
		else
		{
			off++;              //һƥ
			n=0;                //
		}
		//n++;
	}

	if(reply[n]==0)   //պƥ
	{
		return LCD_TRUE;
	}
	
	return LCD_FALSE;       //ѭʾȽϺûͬݣ
}
uchar lcd_check_busy(void)
{
	return lcd_cmd_check("OK\r\n");
 }

uchar (lcd_reset)(void)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"RESET;\r\n");
	return lcd_cmd(cmd_buf,"OK",230);
}
uchar (lcd_ver)(void)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"VER;\r\n");
	return lcd_cmd(cmd_buf,"OK",105);
}
uchar (lcd_bps)(uint init_bps)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"BPS(%d)\r\n",init_bps);
	return lcd_cmd(cmd_buf,"OK",1);
}

uchar (lcd_clr)(uchar c)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"CLR(%d)\r\n",c);
	return lcd_cmd(cmd_buf,"OK",25);
}
uchar (lcd_lcdon)(lcd_res_e res_e)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"LCDON(%d)\r\n",res_e);
	return lcd_cmd(cmd_buf,"OK",230);
}
uchar (lcd_fsimg)(uchar *addr,uchar x,uchar y, uchar w,uchar h,uchar mode)
{
	uchar cmd_buf[64] = {0};
	sprintf(cmd_buf,"FSIMG(%s,%d,%d,%d,%d,%d);\r\n",addr,x,y,w,h,mode);
	return lcd_cmd(cmd_buf,"OK",200);
}
uchar (lcd_fs_dload)(uchar* size)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"FS_DLOAD(%s)\r\n",size);
	return lcd_cmd(cmd_buf,"OK",3);
}
 uchar (lcd_dir)(lcd_res_e V)
 {
	 uchar cmd_buf[32] = {0};
	 sprintf(cmd_buf,"DIR(%d)\r\n",V);
	 return lcd_cmd(cmd_buf,"OK",500);
 }
uchar (lcd_bl)(uchar p)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"BL(%d)\r\n",p);
	return lcd_cmd(cmd_buf,"OK",1);
}
uchar (lcd_ps)(uchar x,uchar y,uchar c)
{
	
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"PS(%d,%d,%d);\r\n",x,y,c);
	return lcd_cmd(cmd_buf,"OK",1);
	
}
uchar (lcd_pl)(uchar x1,uchar y1,uchar x2,uchar y2,uchar c)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"PL(%d,%d,%d,%d,%d);\r\n",x1,y1,x2,y2,c);
	return lcd_cmd(cmd_buf,"OK",3);
}
uchar (lcd_box)(uchar x1,uchar y1,uchar x2,uchar y2,uchar c,lcd_res_e F)
{

	uchar cmd_buf[32] = {0};
	if(F == LCD_TRUE)
	sprintf(cmd_buf,"BOXF(%d,%d,%d,%d,%d);\r\n",x1,y1,x2,y2,c);
	else
	sprintf(cmd_buf,"BOX(%d,%d,%d,%d,%d);\r\n",x1,y1,x2,y2,c);
	return lcd_cmd(cmd_buf,"OK",3);

}
uchar (lcd_cir)(uchar x,uchar y,uchar r,uchar c,lcd_res_e F)
{
	uchar cmd_buf[32] = {0};
	if(F == LCD_TRUE)
	sprintf(cmd_buf,"CIRF(%d,%d,%d,%d);\r\n",x,y,r,c);
	else
	sprintf(cmd_buf,"CIR(%d,%d,%d,%d);\r\n",x,y,r,c);
	return lcd_cmd(cmd_buf,"OK",3);

}
uchar (lcd_arc)(uchar x,uchar y,uchar r,uchar c,uint d0,uint d1)
{
	
}




uchar (lcd_sbc)(uchar c)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"SBC(%d)\r\n",c);
	return lcd_cmd(cmd_buf,"OK",1);
}

uchar (lcd_dc)(uchar x,uchar y,uchar *str,uchar c,lcd_res_e V,uchar s)
{
	uchar cmd_buf[100] = {0};
	switch(s)
	{
		case 0:
		if(V == LCD_TRUE)
		sprintf(cmd_buf,"DCV16(%d,%d,%s,%d);\r\n",x,y,str,c);
		else
		sprintf(cmd_buf,"DC16(%d,%d,%s,%d);\r\n",x,y,str,c);
		break;
		case 1:
		if(V == LCD_TRUE)
		sprintf(cmd_buf,"DCV24(%d,%d,%s,%d);\r\n",x,y,str,c);
		else
		sprintf(cmd_buf,"DC24(%d,%d,%s,%d);\r\n",x,y,str,c);
		break;
		case 2:
		if(V == LCD_TRUE)
		sprintf(cmd_buf,"DCV32(%d,%d,%s,%d);\r\n",x,y,str,c);
		else
		sprintf(cmd_buf,"DC32(%d,%d,%s,%d);\r\n",x,y,str,c);
		break;
		default:
		return LCD_FALSE;
	}

	
	return lcd_cmd(cmd_buf,"OK",1);
}


/************************************************************************/
/* style :	0 BTN򣬼ΪıͬDCDCVָ
1 BTNѹģⰴťµЧ
2 BTŅģⰴţ̌Ч
4 BTNframe_colorָɫ
8 BTNûеɫ
*/
/************************************************************************/


uchar (lcd_btn)(uchar x,uchar y,uchar w,uchar h,uchar *str,uchar style,uchar frame_color,uchar Fcolor,uchar Bcolor)
{
	uchar cmd_buf[256] = {0};
	sprintf(cmd_buf,"BTN(%d,%d,%d,%d,%d,%s,%d,%d,%d,%d)\r\n",x,y,w,h,str,style,frame_color,Fcolor,Bcolor);
	return lcd_cmd(cmd_buf,"OK",250);
}


uchar (lcd_put_var)(uint addr,uchar a,uchar b,uchar c,uchar d)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"PUT_VAR(%d,%d,%d,%d,%d)\r\n",addr,a,b,c,d);
	return lcd_cmd(cmd_buf,"OK",5);
}
uchar (lcd_get_var)(uint addr)
{
	uchar cmd_buf[32] = {0};
	sprintf(cmd_buf,"GET_VAR(%d)\r\n",addr);
	return lcd_cmd(cmd_buf,"OK",5);
}

struct lcd_base_opt base_opt = {
	.reset = lcd_reset,
	.ver = lcd_ver,
	.bps = lcd_bps,
	
	.clr = lcd_clr,
	.lcdon= lcd_lcdon,
	.fsimg= lcd_fsimg,
	.fs_dload= lcd_fs_dload,
	.dir = lcd_dir,
	.bl = lcd_bl,
	.ps = lcd_ps,
	.pl = lcd_pl,
	.box = lcd_box,
	.cir = lcd_cir,
	.sbc = lcd_sbc,
	.dc = lcd_dc,
	.btn = lcd_btn,
	.put_var = lcd_put_var,
	.get_var = lcd_get_var,
	.check_busy = lcd_check_busy,
};

uchar lcd_fsimg_220176(uchar *addr)
{
	lcd_fsimg(addr,0,0,220,176,0);
}
uchar (lcd_fsimg_7)(uchar *addr,uchar x,uchar y, uchar w,uchar h,uchar mode)
{
	uchar cmd_buf[64] = {0};
	sprintf(cmd_buf,"FSIMG(%s,%d,%d,%d,%d,%d);\r\n",addr,x,y,w,h,mode);
	return lcd_cmd(cmd_buf,"OK",7);
}
uchar lcd_fsimg_3232(uchar *addr,uchar x,uchar y)
{
	lcd_fsimg_7(addr,x,y,32,32,0);
}
uchar (lcd_fsimg_13)(uchar *addr,uchar x,uchar y, uchar w,uchar h,uchar mode)
{
	uchar cmd_buf[64] = {0};
	sprintf(cmd_buf,"FSIMG(%s,%d,%d,%d,%d,%d);\r\n",addr,x,y,w,h,mode);
	return lcd_cmd(cmd_buf,"OK",13);
}
uchar lcd_fsimg_4844(uchar *addr,uchar x,uchar y)
{
	lcd_fsimg_13(addr,x,y,48,44,0);
}
void lcd_fsimg_fan_addr(uchar *addr)
{
	lcd_fsimg_3232(addr,94,42);
}

void lcd_fsimg_fan(void)
{
	
	static uchar fan_f = 0;
	fan_f ++;
	lcd_fsimg_fan_addr(lcd_flash[fan_f]);
	if(fan_f > 3)
		fan_f = 0;
}

uchar lcd_fsimg_g(lcd_res_e flag)
{	
	if(flag == LCD_FALSE)
		lcd_fsimg_4844(lcd_flash[5],172,132);
	else
		lcd_fsimg_4844(lcd_flash[6],172,132);
}
uchar lcd_fsimg_l(lcd_res_e flag)
{
	if(flag == LCD_FALSE)
	lcd_fsimg_4844(lcd_flash[7],0,132);
	else
	lcd_fsimg_4844(lcd_flash[8],0,132);
}
uchar lcd_fsimg_n(lcd_res_e flag)
{
	if(flag == LCD_FALSE)
	lcd_fsimg_4844(lcd_flash[9],0,172);
	else
	lcd_fsimg_4844(lcd_flash[10],0,172);
}
uchar lcd_fsimg_y(lcd_res_e flag)
{
	if(flag == LCD_FALSE)
	lcd_fsimg_4844(lcd_flash[9],172,0);
	else
	lcd_fsimg_4844(lcd_flash[10],172,0);
}


uchar (lcd_box_24_f)(uchar x,uchar y,uchar c)
{
	//
	return lcd_box(x,y,x+1,y+3,c,LCD_TRUE);
}
uchar (lcd_box_28_f)(uchar x,uchar y,uchar c)
{
	//
	return lcd_box(x,y,x+1,y+7,c,LCD_TRUE);
}
uchar (lcd_box_212_f)(uchar x,uchar y,uchar c)
{
	//
	return lcd_box(x,y,x+1,y+11,c,LCD_TRUE);
}
uchar (lcd_box_216_f)(uchar x,uchar y,uchar c)
{
	//
	return lcd_box(x,y,x+1,y+16,c,LCD_TRUE);
}
uchar (lcd_box_13_f)(uchar x,uchar y,uchar c)
{
		return lcd_box(x,y,x+0,y+2,c,LCD_TRUE);
}
uchar (lcd_box_31_f)(uchar x,uchar y,uchar c)
{
	return lcd_box(x,y,x+2,y+0,c,LCD_TRUE);
}

uchar lcd_flash_point(uchar x,uchar y,uchar old_c,uchar new_c)
{
	lcd_ps(x,y,new_c);
	lcd_ps(x,y,old_c);
}

uchar signal_1(uchar c)
{
	(lcd_box_24_f)(22,186, c);
}
uchar signal_2(uchar c)
{
	(lcd_box_28_f)(18,184, c);
}
uchar signal_3(uchar c)
{
	(lcd_box_212_f)(14,182, c);
}
uchar signal_4(uchar c)
{
	(lcd_box_216_f)(10,180, c);
}
uchar (lcd_signal_f)(uchar n)
{
	uchar timewait = 25;
	if(n > 0)
	{
		signal_1(5);
		_delay_ms(timewait);
	}
	else
		signal_1(7);
	
	if(n > 1)
	{
		signal_2(5);
		_delay_ms(timewait);
	}
	else
		signal_2(7);
		
	if(n > 2)
	{
		signal_3(5);
		_delay_ms(timewait);	
	}
	else
		signal_3(7);
	
	if(n > 3)
	{
		signal_4(5);
		_delay_ms(timewait);
	}
	else
		signal_4(7);
}
uchar lcd_signal(uchar n)
{
	//lcd_signal_f(4);
	//_delay_ms(200);
	lcd_signal_f(n);
}



uchar (lcd_box_147_f)(uchar x,uchar y,uchar c)
 {
 //BOXF(119,10,125,23,3);
	return lcd_box(x,y,x+13,y+6,c,LCD_TRUE);
 }
uchar (lcd_box_282_f)(uchar x,uchar y,uchar c)
 {
 
	return lcd_box(x,y,x+27,y+1,c,LCD_TRUE);
 }
uchar (lcd_box_93_f)(uchar x,uchar y,uchar c)
{
//
return lcd_box(x,y,x+8,y+2,c,LCD_TRUE);
}
uchar (lcd_box_92_f)(uchar x,uchar y,uchar c)
{
return lcd_box(x,y,x+8,y+1,c,LCD_TRUE);
}


typedef uchar (*box_fun)(uchar x,uchar y,uchar c);

uchar lcd_box_f(box_fun f,uchar x,uchar y,uchar c,uchar n)
{
	uchar add_x = 0,add_y = 0,i = 0;
	
	if(f == lcd_box_147_f){add_y = 8, add_x = 14;}
	if(f == lcd_box_282_f){add_y = 3, add_x = 28;}
	if(f == lcd_box_93_f){add_y = 4, add_x = 9;}
	if(f == lcd_box_92_f){add_y = 3, add_x = 9;}
	if(add_y || add_x)
	return f(x , y -add_y * n , c);
}
typedef uchar (*box_g)(uchar n,uchar c);
void lcd_box_nf(box_g f,uchar old_c,uchar new_c,uchar *old_s,uchar new_s)
{
	uchar tmp  = 0;
	for(tmp = *old_s;tmp > new_s;tmp --)
	{
		f(tmp,new_c);
	}
	for(tmp = *old_s;tmp < new_s;tmp ++)
	{
		f(tmp,old_c);
	}
	*old_s = new_s;
}


uchar (lcd_box_tds_in)(uchar n,uchar c)
{
//BOXF(119,196,125,209,1);
	lcd_box_f(lcd_box_147_f,10,119,c,n);
}
void (lcd_boxn_tds_in)(uchar n)
{
	if(n>10)n = 10;
	static uchar tds_in = 0;
	lcd_box_nf(lcd_box_tds_in,1,7,&tds_in,n);
}
uchar (lcd_box_tds_in_bottom)(void)
{	
		//BOXF(127,189,128,217,1);3,127
	return lcd_box_f(lcd_box_282_f,3,127,1,0);
}
uchar (lcd_box_tds_out)(uchar n,uchar c)
{
//BBOXF(119,10,125,23,3);
	return lcd_box_f(lcd_box_147_f,196,119,c,n);
}
void (lcd_boxn_tds_out)(uchar n)
{
	if(n>10)n = 10;
	static uchar tds_out = 0;
	lcd_box_nf(lcd_box_tds_out,3,7,&tds_out,n);
}
uchar (lcd_box_tds_out_bottom)(void)
{
	//BOXF(127,3,128,30,3);
	return lcd_box_f(lcd_box_282_f,189,127,3,0);
}


uchar lcd_box_1(uchar n,uchar c)
{
				//BOXF(107,155,109,163,5);
	return lcd_box_f(lcd_box_93_f,56,107,c,n);
}
void (lcd_boxn_1)(uchar n)
{
	static uchar box_1 = 0;
	lcd_box_nf(lcd_box_1,5,7,&box_1,n);
}


uchar lcd_box_5(uchar n,uchar c)
{
			//BOXF(107,155,109,163,5);
			return lcd_box_f(lcd_box_93_f,155,107,c,n);
}
void (lcd_boxn_5)(uchar n)
{
	if(n>10)n = 10;
	static uchar box_5 = 0;
	lcd_box_nf(lcd_box_5,5,7,&box_5,n);
}

uchar lcd_box_2(uchar n,uchar c)
{
	//BOXF(118,131,119,139,5);
	return lcd_box_f(lcd_box_92_f,80,118,c,n);
	
}
void (lcd_boxn_2)(uchar n)
{
	if(n>10)	n = 10;
	static uchar box_2_tmp = 0;
	lcd_box_nf(lcd_box_2,5,7,&box_2_tmp,n);
}

uchar lcd_box_4(uchar n,uchar c)
{
	//BOXF(118,81,119,89,5);
	return lcd_box_f(lcd_box_92_f,130,118,c,n);


}
void (lcd_boxn_4)(uchar n)
{
	if(n>10)n = 10;
	static uchar box_4 = 0;
	lcd_box_nf(lcd_box_4,5,7,&box_4,n);
}

uchar lcd_box_3(uchar n,uchar c)
{

		//BOXF(124,107,125,115,5);
		return lcd_box_f(lcd_box_92_f,104,124,c,n);
}
void (lcd_boxn_3)(uchar n)
{
	if(n>10)n = 10;
	static uchar box_3 = 0;
	lcd_box_nf(lcd_box_3,5,7,&box_3,n);
}

uchar lcd_val_3(uchar x,uchar y,uint val,uchar c)
{
		uchar cmd_buf[64] = {0};
		sprintf(cmd_buf,"BOXF(%u,%u,%u,%u,0);DC16(%u,%u,%u,%u);\r\n",x,y,x+25,y+16,x,y,val,c);
		return lcd_cmd(cmd_buf,"OK",5);
}
uchar lcd_val_4(uchar x,uchar y,uint val,uchar c)
{
	uchar cmd_buf[64] = {0};
	sprintf(cmd_buf,";BOXF(%u,%u,%u,%u,0);DC16(%u,%u,%u,%u);\r\n",x,y,x+30,y+16,x,y,val,c);
	return lcd_cmd(cmd_buf,"OK",5);
}
uchar lcd_val_5(uchar x,uchar y,uint val,uchar c)
{
	uchar cmd_buf[64] = {0};
	sprintf(cmd_buf,"BOXF(%u,%u,%u,%u,0);DC16(%u,%u,%u,%u);\r\n",x,y,x+38,y+16,x,y,val,c);
	return lcd_cmd(cmd_buf,"OK",5);
}

uchar lcd_val_tds_in(uint val)
{
	//DIR(1);DC16(28,44,092,1);
	return lcd_val_4(28,44,val,1);
}
uchar lcd_val_tds_out(uint val)
{
//DIR(1);DC16(169,44,009,3);
	return lcd_val_3(169,44,val,3);
}

uchar lcd_day(uint day)
{
//DC16(58,152,00160,3);
	return lcd_val_5(58,152,day,3);
}
uchar lcd_flow(unsigned int flow)
{
	//DIR(1);DC16(123,152,00260,3);
	return lcd_val_5(123,152,flow,3);

}
uchar lcd_title(char* title)
{			
//DIR(1);DC16(90,2,00260,1);
			uchar cmd_buf[64] = {0};
			sprintf(cmd_buf,"BOXF(90,2,128,18,0);DC16(90,2,%s,1);\r\n",title);
			return lcd_cmd(cmd_buf,"OK",5);
}



struct lcd_opt opt = {
		.fsimg_220176 = lcd_fsimg_220176,
		.fsimg_3232 = lcd_fsimg_3232,
		.fsimg_4844 = lcd_fsimg_4844,
		.fsimg_fan = lcd_fsimg_fan,

		.fsimg_g = lcd_fsimg_g,
		.fsimg_l = lcd_fsimg_l,
		.fsimg_n = lcd_fsimg_n,
		.fsimg_y = lcd_fsimg_y,

		.signal = lcd_signal,


		.box_tds_in = lcd_box_tds_in,
		.boxn_tds_in = lcd_boxn_tds_in,
		.box_tds_in_bottom = lcd_box_tds_in_bottom,

		.box_tds_out = lcd_box_tds_out,
		.boxn_tds_out = lcd_boxn_tds_out,
		.box_tds_out_bottom = lcd_box_tds_out_bottom,

		.box_1 = lcd_box_1,
		.boxn_1 = lcd_boxn_1,

		.box_2 = lcd_box_2,
		.boxn_2 = lcd_boxn_2,

		.box_3 = lcd_box_3,
		.boxn_3 = lcd_boxn_3,

		.box_4 = lcd_box_4,
		.boxn_4 = lcd_boxn_4,

		.box_5 = lcd_box_5,
		.boxn_5 = lcd_boxn_5,
		

		.val_tds_in = lcd_val_tds_in,
		.val_tds_out = lcd_val_tds_out,
		.date = lcd_day,
		.flow = lcd_flow,
		.title = lcd_title,
		.flash_point = lcd_flash_point,
};

struct use_lcd lcd0 = {0};

struct use_lcd *get_lcd(void)
{
	return &lcd0;
}
void init_lcd_opt(void)
{
	lcd0.addr = lcd_flash,
	lcd0.base_opt = &base_opt;
	lcd0.opt = &opt;
}

