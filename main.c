#include <STC8G.H>
#include "intrins.H"

sbit SH = P5^4;
sbit ST = P3^3;
sbit DS = P3^2;
sbit KEY = P5^5;


unsigned char i,x,j;

void Delay300us(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	_nop_();
	i = 4;
	j = 54;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1ms(unsigned char ms)	//@11.0592MHz
{
	while(ms--)
	{
		unsigned char data i, j;

		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}


void send595(unsigned char byteH,byteL)
{ 
		for(i=0;i<8;i++)
		{
				
				DS=byteH&0x80;
				SH = 0;
				SH = 1;
				byteH=byteH<<1;
					
		}
		
		for(i=0;i<8;i++)
		{
				
				DS=byteL&0x80;
				SH = 0;
				SH = 1;
				byteL=byteL<<1;
					
		}
		ST=0;
		ST=1;	
}

unsigned char front[8]=
{
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};

unsigned char behind[16]=
{
	0x55,0x55,0x55,0x55,0x05,0xFC,0xFF,0xFF,
	0xAA,0xAA,0xAA,0xAA,0xFA,0xFF,0xFF,0xFF,
};

void all_in()
{
	send595(0xff,0xff);
}

void wink()
{
	for(j=0;j<100;j++)	
		{	
			for(x=0;x<8;x++)
			{
				send595(front[x],behind[x]);
				Delay300us();
			}
		}
		for(j=0;j<100;j++)	
		{	
			for(x=0;x<8;x++)
			{
				send595(front[x],behind[x+8]);
				Delay300us();
			}
		}
}

void wink2()
{
	for(j=0;j<100;j++)	
		{	
			for(x=0;x<8;x++)
			{
				send595(front[x],behind[x]);
				Delay300us();
			}
		}
		for(j=0;j<100;j++)	
		{	
			for(x=0;x<8;x++)
			{
				send595(front[x],behind[x+16]);
				Delay300us();
			}
		}
}

void main()
{
	P1M0 = 0x00;	P1M1 = 0x00;
	P3M0 = 0x00;	P3M1 = 0x00;
	P5M0 = 0x00;	P5M1 = 0x00;
	KEY=1;
	while(1)
	{
		 while(KEY!=0); 
     Delay1ms(50);
     while(KEY!=0)
    {all_in();}  
     
    while(KEY!=0);  
    Delay1ms(50);
    while(KEY!=0)
    {wink();} 
   
	}
}