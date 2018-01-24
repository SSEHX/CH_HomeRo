#include "stmflash.h"
#include "delay.h"
#include "usart.h"

#define STM32_FLASH_WREN 1

u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN

void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//ַ2.
	}  
} 


#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;
	u16 secoff;
	u16 secremain; //ʣַ(16λּ)	   
 	u16 i;    
	u32 offaddr;   //ȥ0X08000000ĵַ
	
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//Ƿַ
	
	HAL_FLASH_Unlock();					//
	offaddr=WriteAddr-STM32_FLASH_BASE;		//ʵƫƵַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//ڵƫ(2ֽΪ�λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//ʣռС   
	if(NumToWrite<=secremain)secremain=NumToWrite;//ڸΧ
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//
		for(i=0;i<secremain;i++)	//У
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//Ҫ  	  
		}
		if(i<secremain)				//Ҫ
		{
			FLASH_PageErase(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);	//
			FLASH_WaitForLastOperation(FLASH_WAITETIME);            	//ȴϴβ
			CLEAR_BIT(FLASH->CR, FLASH_CR_PER);							//CRĴPERλ˲ӦFLASH_PageErase()ɣ
																		//HAL沢ûӦHALbug
			for(i=0;i<secremain;i++)//
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д  
		}else 
		{
			FLASH_WaitForLastOperation(FLASH_WAITETIME);       	//ȴϴβ
			STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//дѾ˵,ֱдʣ. 
		}
		if(NumToWrite==secremain)break;//д
		else//дδ
		{
			secpos++;				//ַ1
			secoff=0;				//ƫλΪ0 	 
		   	pBuffer+=secremain;  	//ָƫ
			WriteAddr+=secremain*2;	//дַƫ(16λݵַ,Ҫ*2)	   
		   	NumToWrite-=secremain;	//ֽ(16λ)ݼ
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//һд
			else secremain=NumToWrite;//һд
		}	 
	};	
	HAL_FLASH_Lock();		//
}
#endif

//ַָʼָȵ
//ReadAddr:ʼַ
//pBuffer:ָ
//NumToWrite:(16λ)
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//ȡ2ֽ.
		ReadAddr+=2;//ƫ2ֽ.	
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:ʼַ
//WriteData:Ҫд
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);//дһ 
}
















