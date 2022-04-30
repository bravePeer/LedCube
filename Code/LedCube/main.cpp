/*
 * LedCube.cpp
 *
 * Created: 20.04.2022 14:56:54
 * Author : Bartolomeo
 */ 

#define F_CPU 14740000L
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

//Diffrent x sizes need change in code
#include "Defines.h"
#include "Animations.h"


class Queue
{
public:
	Queue()
	{
		control = 0x00;
	}
	
	void Enqueue(Animation *anim)
	{
		uint8_t nextPos = (control & 0x07) + 1;
		uint8_t amount = control>>4;
		
		
		if(nextPos > 6)
			nextPos = 0;
		
		//Amount < 7
		if((amount) < 7)
		{
			queue[nextPos] = anim;
			amount++;
			control = (amount<<4) | (nextPos-1);
		}
	}
	
	void Dequeue()
	{
		queue[control&0x07] = NULL;
		uint8_t amount = control>>4;
		amount--;
		control++;
		if((control&0x07) > 6)
			control &= ~0x07;
		control &= 0x0f;
		control |= (amount<<4); 
	}
	Animation* GetActual()
	{
		return queue[control&0x07];
	}
	
	uint8_t GetAmount()
	{
		return (control>>4);
	}
	
private:
	Animation* queue[7];
	uint8_t control;	//amount & pos bin: 0aaa 0ppp
};

volatile uint8_t usartControl = 0;
volatile char recivedDataUSART[MAX_USART_DATA_SIZE] ;//= "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
volatile uint8_t recivedDataPos = 0;

/*		---USART---		*/
inline void InitUSART(unsigned int baudrate)
{
	//Set baud rate
	unsigned int ubrr = F_CPU/16/BAUD - 1;
	
	UBRRH = static_cast<unsigned char>(ubrr >> 8);
	UBRRL = static_cast<unsigned char>(ubrr);
	
	//Set transmitter & reciver
	UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);
	
	//Set frame format: 8 data, 1 stop bit
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
}
void USARTSendChar(char data)
{
	while(!(UCSRA&(1<<UDRE))) ;
	
	UDR = data;
}
void USARTSend(char *s)
{
	uint16_t i = 0;
	
	while(s[i] != 0)
	{
		USARTSendChar((s[i]));
		i++;
	}	
}
inline void USARTRecive(char *outputText, uint8_t& nextAnim)
{
	usartControl &= ~USART_IS_READY_DATA;	//No data to preocess
	
	outputText = 0;
	
	if(recivedDataUSART[0] == 0 )//&& recivedDataUSART[1] != ' '
	{
		nextAnim = 0;
		return;
	}
	
	nextAnim = recivedDataUSART[0];
	//if(recivedDataUSART[1] != ' ')
	//	return;
		
	uint8_t i = 1;
	while(recivedDataUSART[i] != 0)
	{
		if(i >= MAX_USART_DATA_SIZE)
			break;
		outputText[i-2] = recivedDataUSART[i];
		i++;
	}
	
	
	//for (uint8_t i = 2; i < MAX_USART_DATA_SIZE; i++)
	//{
	//	outputText[i-2] = recivedDataUSART[i];
	//	if(recivedDataUSART[i] == 0)
	//		break;
	//}
	
	
}

/*		---Pinouts---		*/
inline void InitLedPin()
{
	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	//PORTD &= ()
	//PORTA |= (1<<0)|(1<<1);
}

/*		---Timer---			*/
inline void InitTimer()
{
	//Timer
	TCCR0 |= (1<<CS02)|(1<<CS00);
	TIMSK |= (1<<TOIE0);
}

/*		---GenerateSeed---		*/
uint16_t GenerateRandomSeed()
{
	ADMUX = (1<<REFS1)|(1<<REFS0);
	ADCSRA = (1<<ADEN);	//enable ADC
	uint16_t seed = 0;
	
	for (uint8_t i = 0; i < 16; i++)
	{
		ADCSRA |= (1<<ADSC);
		seed = (seed<<1) | (ADC & 0xb1);
		while(ADCSRA & (1<<ADSC)); //wait untill conversion ended
	}
	
	ADCSRA = (0<<ADEN);	//disable ADC
	
	return seed;
}

/*		---TurnOn&OffLeds---		*/
inline void LightLeds(volatile uint8_t **ledsState)
{
	for(uint8_t layer = 0; layer < LEDSLAYERS; layer++)
	{
		PORTA = ledsState[0][layer];
		PORTB |= (1<<layer);
		PORTB &= ~(1<<layer);
		//PORTC = ledsState[1][layer]
		//PORTD = ledsState[2][layer]
		//
		//PORTB &= (0<<layer);
	}
	//PB0:PB5 -> layer
	
}


volatile uint64_t nowmillis = 0;


/*		---Main---		*/
int main(void)
{
	srand(GenerateRandomSeed());
	InitLedPin();
	InitUSART(BAUD);
	InitTimer();
	
	sei();	//Interrupts
	
	volatile uint64_t storedMillis = 0;
uint8_t selectedAnim = 0x01;

	
	volatile uint8_t ** volatile ledsState;
	ledsState = (volatile  uint8_t ** )malloc(4*sizeof(uint8_t));
	
	ledsState[0] = (volatile uint8_t * )malloc(5*sizeof(uint8_t));
	ledsState[1] = (volatile uint8_t * )malloc(5*sizeof(uint8_t));
	ledsState[2] = (volatile uint8_t * )malloc(5*sizeof(uint8_t));
	ledsState[3] = (volatile uint8_t * )malloc(5*sizeof(uint8_t));
	ledsState[4] = (volatile uint8_t * )malloc(5*sizeof(uint8_t));
	
	

	TestAnimOnMatrix testAnim;
	AnimRaniDrops2D rainDrop;
	
	AnimLettersOnMatrix letters;
	letters.InitLetters();
	
	Animation *   nowAnim;
	//Animation *  nextAnim;
	nowAnim = (Animation*)&letters;
	
	char textToAnim[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	//char text[] = "01234567890";
	nowAnim->Init(ledsState, 100, (char*)textToAnim);
	selectedAnim = 0;
	
	//char textToAnim[MAX_USART_DATA_SIZE];
	//char eSelAnim[] = "\nNo animation found";
	char iNowAnim[] = "\nnow: ";
	char startText[] = "\nstart\n";
	USARTSend(startText);
			
	
    while (1) 
    {
		//Is available data to process
		if(usartControl & USART_IS_READY_DATA)
			USARTRecive(textToAnim, selectedAnim);

		//Is time to update leds' state
		if(nowmillis - storedMillis >= nowAnim->waitTime)
		{
			nowAnim->UpdateLedsState(ledsState);
			
			if(nowAnim->control & ANIMATION_IS_FINISHED)
			{
				switch (selectedAnim)
				{
					case '1':
						nowAnim = (Animation*)&testAnim;
						//selectedAnim = '2';
						break;
					case '2':
						nowAnim = (Animation*)&rainDrop;
						//selectedAnim = '1';
						break;
					case '3':
						nowAnim = (Animation*)&letters;
						break;
							
				}
				USARTSend(iNowAnim);
				USARTSendChar(nowAnim->id);
				
				
				nowAnim->Init(ledsState, 10, (char*)textToAnim);
				//_delay_ms(25);
				
			}
			storedMillis = nowmillis;
		}
		
		LightLeds(ledsState);
    }
}


/*		---Interrups---		*/
ISR(TIMER0_OVF_vect)
{
	nowmillis++;
}
ISR(USART_RXC_vect) //Receive USART
{
	UCSRB |= (1<<UDRIE);	//Set Interrupt when empty usart buffer
	
	
	//usartControl &= ~0x10;
	char a;
	a = UDR;
	//selectedAnim = a;
	if(recivedDataPos >= MAX_USART_DATA_SIZE)
	{
		USARTSendChar('\n');
		USARTSendChar('E');
		USARTSendChar('R');
		USARTSendChar('R');
		USARTSendChar('O');
		USARTSendChar('R');
		USARTSendChar(':');
		USARTSendChar(' ');
		USARTSendChar('T');
		USARTSendChar('o');
		USARTSendChar('o');
		USARTSendChar(' ');
		USARTSendChar('l');
		USARTSendChar('o');
		USARTSendChar('n');
		USARTSendChar('g');
		
	}	
	recivedDataUSART[recivedDataPos] = a;
	
	recivedDataPos++;
}
ISR(USART_UDRE_vect)
{
	usartControl |= USART_IS_READY_DATA;	//Data is ready to process
	
	recivedDataUSART[recivedDataPos] = 0;
	USARTSendChar('\n');
	USARTSendChar('R');
	USARTSendChar('e');
	USARTSendChar('c');
	USARTSendChar('i');
	USARTSendChar('v');
	USARTSendChar('e');
	USARTSendChar('d');
	USARTSendChar(':');
	USARTSendChar(' ');
	USARTSendChar(recivedDataPos + '0');
	
	recivedDataPos = 0;
	UCSRB &= ~(1<<UDRIE);	//Turn off interrupt of empty usart buffer
}