#include <htc.h>
#include <stdio.h>
#include "uart.h"


__CONFIG(INTIO & WDTDIS & PWRTEN & MCLREN & UNPROTECT & DUNPROTECT & BORDIS & IESODIS & FCMDIS & LVPDIS);

unsigned long von=1,ngan=1,tram=1,chuc=1,dvi=1;
unsigned long temp=0;


void setup_ADC(void)
{ 
	
	ANS0=1;			// NGO VAO ANALOG
	TRISA0=1;		
    ADRESH=0x00; 	// RESET LAI 2 THANH GHI CHUA KET QUA ADC
    ADRESL=0x00;
    ADCON1 = 0;		// TAM TOAN THANG = 5V
	ADFM = 1;		// KET QUA LAP DAY BEN PHAI
	ADCON0 = 0;		
	ADCS0  = 1;		// tan so chuyen doi ADC bang FRC
	ADCS1  = 1;
	
	CHS0 = CHS1 = 0; // chon kenh AN0
	CHS2 = CHS3 = 0;
	
	ADON = 1;		// bat ADC
	__delay_us(5);
	GODONE =1 ;		// run ADC
}

void setup_timer2(void)
{	
	T2CON = 0;		// Prescale và postscale =1
	TMR2ON=1;		// enable timer 2
    PR2=199;		// tan so PWM la 5Khz, T(chu ki)= PWM Period = [(PR2) + 1] • 4 • TOSC •(TMR2 Prescale Value)
}

void setup_pwm(void)
{	
	TRISC1=0;		// config cac chân CCP la output
	TRISC2=0;

	CCPR2L = 6;
	CCPR1L = 6;
	TRISE1 = 0;		// RE0,RE1 la chan dieu huong
	TRISE2 = 0;

}


void setup_interrupt(void)
{	
	GIE=1;			// enable ngat toan cuc
	PEIE=1;			// enable ngat ngoai vi
    ADIE=1;			// enable ngat ADC
	ADIF=0;			// xoa co ngat ADC
}

void interrupt isr()
{

    if( ADIE && ADIF && PEIE)
	 {  
		ADIF=0;
		temp = ((unsigned int )ADRESH<<8)|ADRESL; // doc ket qua ADC
	    temp = temp*200/1024/20;
		//CCPR2L = temp;
		//CCPR1L = temp;
		
		 von=(temp*50);	// lay chinh xac 0.001
		 dvi= von%10;
		 von=(von-dvi)/10;  
		 chuc=von%10;
         von=(von-chuc)/10;
		 tram=von%10;
         von=(von-tram)/10;
    	 ngan=von%10;
     }			
}



void main()
{
	unsigned char a;

	ANSEL=0X00;				// cho tat ca cac chan la digital, sau do chan nao la analog thi config sau
	ANSELH=0X00;

	//TRISB =0x3F;
	//TRISC=0X0F;

	CCP1CON=0x0C;	// enable CCP1
	CCP2CON=0x0C;	// enable CCP2

	ANS5 = 0;
	ANS6 = 0;
	RE0 = 1;
	RE1 = 1;

	ANS8 = 0;
	ANS9 = 0;
	ANS11 = 0;
	ANS13 = 0;
	
	__delay_ms(200);

	uart_init();

	setup_interrupt();
	setup_timer2();	
	setup_ADC();
	setup_pwm();
	
	
	while(1){
		
		while(!RCIF)
		{
		//	GODONE=1;
	  	//	while(GODONE);    //cho xu li xong moi xuat

		}	


		a = RCREG;

		if(a == 'b')
			{
				CCPR1L = 0;
				CCPR2L = 0;
	/*			__delay_ms(200);
				__delay_ms(200);
				__delay_ms(200);	*/
				//CCP1CON=0x0C;	// enable CCP1
				//CCP2CON=0x0C;	// enable CCP2
				CCPR1L = temp;
				CCPR2L = temp;
				RE2 = 1;
				RE1 = 1;
			}

		if(a == 'f')
			{
				CCPR1L = 0;
				CCPR2L = 0;
		/*		__delay_ms(200);
				__delay_ms(200);
				__delay_ms(200); 	*/
				//CCP1CON=0x0C;	// enable CCP1
				//CCP2CON=0x0C;	// enable CCP2
				CCPR1L = temp;
				CCPR2L = temp;
				RE2 = 0;
				RE1 = 0;
			}

		if(a == 'l')
			{
				CCPR1L = 0;
				CCPR2L = 0;
	/*			__delay_ms(200);
				__delay_ms(200);
				__delay_ms(200);		*/
				//CCP1CON=0x0C;	// enable CCP1
				//CCP2CON=0x0C;	// enable CCP2
				CCPR1L = temp/1.3;///2;//6;
				CCPR2L = temp/1.3;
				RE2 = 1;
				RE1 = 0;
			}

		if(a == 'r')
			{
				CCPR1L = 0;
				CCPR2L = 0;
	/*			__delay_ms(200);
				__delay_ms(200);
				__delay_ms(200);		*/
				//CCP1CON=0x0C;	// enable CCP1
				//CCP2CON=0x0C;	// enable CCP2
				CCPR1L = temp/1.3;
				CCPR2L = temp/1.3;///2;// = 6;
				RE2 = 0;
				RE1 = 1;	
			}

		if(a == 's')
			{
				CCPR1L = 0;
				CCPR2L = 0;
				//CCP1CON=0x00;	// disable CCP1
				//CCP2CON=0x00;	// disable CCP2
			}	
		
		}
}
