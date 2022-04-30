#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#define LEDSLAYERS 5	//z
#define LEDSWIDTH 5		//y


class Animation
{
public:
	virtual void UpdateLedsState(volatile uint8_t **   ledsState)
	{}
	virtual void Init(volatile uint8_t **   ledsState, uint16_t waitTime = 5, char * some = NULL)
	{}
	
	uint16_t waitTime;	//ticks ?
	uint8_t control;	//LSB -> is Animation Ended
	uint8_t id;
private:

};

class AnimLettersOnMatrix : public Animation
{
public:
	void InitLetters()
	{
		letters['A' - 65][0] = 0b00011111;
		letters['A' - 65][1] = 0b00010001;
		letters['A' - 65][2] = 0b00011111;
		letters['A' - 65][3] = 0b00010001;
		letters['A' - 65][4] = 0b00010001;
		
		letters['B' - 65][0] = 0b00011111;
		letters['B' - 65][1] = 0b00010001;
		letters['B' - 65][2] = 0b00011110;
		letters['B' - 65][3] = 0b00010001;
		letters['B' - 65][4] = 0b00011111;
		
		letters['C' - 65][0] = 0b00011111;
		letters['C' - 65][1] = 0b00010000;
		letters['C' - 65][2] = 0b00010000;
		letters['C' - 65][3] = 0b00010000;
		letters['C' - 65][4] = 0b00011111;
		
		letters['D' - 65][0] = 0b00011110;
		letters['D' - 65][1] = 0b00010001;
		letters['D' - 65][2] = 0b00010001;
		letters['D' - 65][3] = 0b00010001;
		letters['D' - 65][4] = 0b00011110;
		
		letters['E' - 65][0] = 0b00011111;
		letters['E' - 65][1] = 0b00010000;
		letters['E' - 65][2] = 0b00011111;
		letters['E' - 65][3] = 0b00010000;
		letters['E' - 65][4] = 0b00011111;
		
		letters['F' - 65][0] = 0b00011111;
		letters['F' - 65][1] = 0b00010000;
		letters['F' - 65][2] = 0b00011111;
		letters['F' - 65][3] = 0b00010000;
		letters['F' - 65][4] = 0b00010000;
	
		letters['G' - 65][0] = 0b00011111;
		letters['G' - 65][1] = 0b00010000;
		letters['G' - 65][2] = 0b00010111;
		letters['G' - 65][3] = 0b00010001;
		letters['G' - 65][4] = 0b00011111;
		
		letters['H' - 65][0] = 0b00010001;
		letters['H' - 65][1] = 0b00010001;
		letters['H' - 65][2] = 0b00011111;
		letters['H' - 65][3] = 0b00010001;
		letters['H' - 65][4] = 0b00010001;
		
		letters['I' - 65][0] = 0b00000100;
		letters['I' - 65][1] = 0b00000100;
		letters['I' - 65][2] = 0b00000100;
		letters['I' - 65][3] = 0b00000100;
		letters['I' - 65][4] = 0b00000100;
		
		letters['J' - 65][0] = 0b00000001;
		letters['J' - 65][1] = 0b00000001;
		letters['J' - 65][2] = 0b00000001;
		letters['J' - 65][3] = 0b00010001;
		letters['J' - 65][4] = 0b00011111;
		
		letters['K' - 65][0] = 0b00010001;
		letters['K' - 65][1] = 0b00010010;
		letters['K' - 65][2] = 0b00011100;
		letters['K' - 65][3] = 0b00010010;
		letters['K' - 65][4] = 0b00010001;
	
		letters['L' - 65][0] = 0b00010000;
		letters['L' - 65][1] = 0b00010000;
		letters['L' - 65][2] = 0b00010000;
		letters['L' - 65][3] = 0b00010000;
		letters['L' - 65][4] = 0b00011111;
		
		letters['M' - 65][0] = 0b00011111;
		letters['M' - 65][1] = 0b00010101;
		letters['M' - 65][2] = 0b00010101;
		letters['M' - 65][3] = 0b00010101;
		letters['M' - 65][4] = 0b00010101;
	
		letters['N' - 65][0] = 0b00010001;
		letters['N' - 65][1] = 0b00011001;
		letters['N' - 65][2] = 0b00010101;
		letters['N' - 65][3] = 0b00010011;
		letters['N' - 65][4] = 0b00010001;
		
		letters['O' - 65][0] = 0b00011111;
		letters['O' - 65][1] = 0b00010001;
		letters['O' - 65][2] = 0b00010001;
		letters['O' - 65][3] = 0b00010001;
		letters['O' - 65][4] = 0b00011111;
		
		letters['P' - 65][0] = 0b00011111;
		letters['P' - 65][1] = 0b00010001;
		letters['P' - 65][2] = 0b00011111;
		letters['P' - 65][3] = 0b00010000;
		letters['P' - 65][4] = 0b00010000;
		
		letters['Q' - 65][0] = 0b00011110;
		letters['Q' - 65][1] = 0b00010010;
		letters['Q' - 65][2] = 0b00010010;
		letters['Q' - 65][3] = 0b00011110;
		letters['Q' - 65][4] = 0b00000001;
		
		letters['R' - 65][0] = 0b00011111;
		letters['R' - 65][1] = 0b00010001;
		letters['R' - 65][2] = 0b00011111;
		letters['R' - 65][3] = 0b00010010;
		letters['R' - 65][4] = 0b00010001;
		
		letters['S' - 65][0] = 0b00011111;
		letters['S' - 65][1] = 0b00010000;
		letters['S' - 65][2] = 0b00011111;
		letters['S' - 65][3] = 0b00000001;
		letters['S' - 65][4] = 0b00011111;
	
		letters['T' - 65][0] = 0b00011111;
		letters['T' - 65][1] = 0b00000100;
		letters['T' - 65][2] = 0b00000100;
		letters['T' - 65][3] = 0b00000100;
		letters['T' - 65][4] = 0b00000100;
		
		letters['U' - 65][0] = 0b00010001;
		letters['U' - 65][1] = 0b00010001;
		letters['U' - 65][2] = 0b00010001;
		letters['U' - 65][3] = 0b00010001;
		letters['U' - 65][4] = 0b00011111;
		
		letters['V' - 65][0] = 0b00010001;
		letters['V' - 65][1] = 0b00010001;
		letters['V' - 65][2] = 0b00010001;
		letters['V' - 65][3] = 0b00001010;
		letters['V' - 65][4] = 0b00000100;
		
		letters['W' - 65][0] = 0b00010101;
		letters['W' - 65][1] = 0b00010101;
		letters['W' - 65][2] = 0b00010101;
		letters['W' - 65][3] = 0b00010101;
		letters['W' - 65][4] = 0b00011111;
		
		letters['X' - 65][0] = 0b00010001;
		letters['X' - 65][1] = 0b00001010;
		letters['X' - 65][2] = 0b00000100;
		letters['X' - 65][3] = 0b00001010;
		letters['X' - 65][4] = 0b00010001;
		
		letters['Y' - 65][0] = 0b00010001;
		letters['Y' - 65][1] = 0b00010001;
		letters['Y' - 65][2] = 0b00011111;
		letters['Y' - 65][3] = 0b00000100;
		letters['Y' - 65][4] = 0b00000100;
		
		letters['Z' - 65][0] = 0b00011111;
		letters['Z' - 65][1] = 0b00000010;
		letters['Z' - 65][2] = 0b00000100;
		letters['Z' - 65][3] = 0b00001000;
		letters['Z' - 65][4] = 0b00011111;
		
		letters['0' - 22][0] = 0b00011111;
		letters['0' - 22][1] = 0b00010001;
		letters['0' - 22][2] = 0b00010001;
		letters['0' - 22][3] = 0b00010001;
		letters['0' - 22][4] = 0b00011111;
		
		letters['1' - 22][0] = 0b00001100;
		letters['1' - 22][1] = 0b00000100;
		letters['1' - 22][2] = 0b00000100;
		letters['1' - 22][3] = 0b00000100;
		letters['1' - 22][4] = 0b00000100;
		
		letters['2' - 22][0] = 0b00011111;
		letters['2' - 22][1] = 0b00000001;
		letters['2' - 22][2] = 0b00011110;
		letters['2' - 22][3] = 0b00010000;
		letters['2' - 22][4] = 0b00011111;
		
		letters['3' - 22][0] = 0b00011111;
		letters['3' - 22][1] = 0b00000001;
		letters['3' - 22][2] = 0b00011111;
		letters['3' - 22][3] = 0b00000001;
		letters['3' - 22][4] = 0b00011111;
		
		letters['4' - 22][0] = 0b00010001;
		letters['4' - 22][1] = 0b00010001;
		letters['4' - 22][2] = 0b00011111;
		letters['4' - 22][3] = 0b00000001;
		letters['4' - 22][4] = 0b00000001;
		
		letters['5' - 22][0] = 0b00011111;
		letters['5' - 22][1] = 0b00010000;
		letters['5' - 22][2] = 0b00011111;
		letters['5' - 22][3] = 0b00000001;
		letters['5' - 22][4] = 0b00011111;
		
		letters['6' - 22][0] = 0b00011111;
		letters['6' - 22][1] = 0b00010000;
		letters['6' - 22][2] = 0b00011111;
		letters['6' - 22][3] = 0b00010001;
		letters['6' - 22][4] = 0b00011111;
		
		letters['7' - 22][0] = 0b00011111;
		letters['7' - 22][1] = 0b00000010;
		letters['7' - 22][2] = 0b00000100;
		letters['7' - 22][3] = 0b00001000;
		letters['7' - 22][4] = 0b00010000;
		
		letters['8' - 22][0] = 0b00011111;
		letters['8' - 22][1] = 0b00010001;
		letters['8' - 22][2] = 0b00011111;
		letters['8' - 22][3] = 0b00010001;
		letters['8' - 22][4] = 0b00011111;
		
		letters['9' - 22][0] = 0b00011111;
		letters['9' - 22][1] = 0b00010001;
		letters['9' - 22][2] = 0b00011111;
		letters['9' - 22][3] = 0b00000001;
		letters['9' - 22][4] = 0b00011111;
		
		
	}
	  void Init(volatile uint8_t **   ledsState, uint16_t _waitTime = 5, char * some = NULL)
	//void Init(uint8_t ledsState[][LEDSLAYERS], uint16_t _waitTime = 10, char * some = NULL)
	{
		ledsState[0][0] = 0x00;
		ledsState[0][1] = 0x00;
		ledsState[0][2] = 0x00;
		ledsState[0][3] = 0x00;
		ledsState[0][4] = 0x00;
		waitTime = _waitTime;
		control = 0;
		id = '3';
		
		text = some;
		iLetter = 0;
		//Set firs letter
		//UpdateLedsState(ledsState);
	}
	//void UpdateLedsState(uint8_t ledsState[][LEDSLAYERS])
	  void UpdateLedsState(volatile uint8_t **ledsState)
	{
		if(text[iLetter] == 0)
		{
			control |= 0x01;	//set end of animation
			return;
		}
		uint8_t selectedChar = 0;
		
		if(text[iLetter] >= 'A' && text[iLetter] <= 'Z' )
			 selectedChar = text[iLetter] - 65;
		else if(text[iLetter] >= '0' && text[iLetter] <= '9')
			selectedChar = text[iLetter] - 22;
		else
		{
			selectedChar = 'E' - 65;
			//iLetter++;
			//return;
		}
		
		ledsState[0][0] = letters[selectedChar][0];
		ledsState[0][1] = letters[selectedChar][1];
		ledsState[0][2] = letters[selectedChar][2];
		ledsState[0][3] = letters[selectedChar][3];
		ledsState[0][4] = letters[selectedChar][4];
		 
		iLetter++;
	}

private:
	uint8_t letters[36][5];
	uint8_t iLetter;	//somthing like iterator
	char * text;
};

class TestAnimOnMatrix : public Animation
{
public:
	  void Init(volatile uint8_t **   ledsState, uint16_t _waitTime = 5, char * some = NULL)
	//void Init(uint8_t ledsState[][LEDSLAYERS], uint16_t _waitTime = 10)
	{
		ledsState[0][0] = 0b01010101;
		ledsState[0][1] = 0x00;
		ledsState[0][2] = 0x00;
		ledsState[0][3] = 0x00;
		ledsState[0][4] = 0x00;
		buf = 0;
		waitTime = _waitTime;
		control = 0;
		id = '1';
	}
	//void UpdateLedsState(uint8_t ledsState[][LEDSLAYERS])
	  void UpdateLedsState(volatile uint8_t **ledsState)
	  {
		for (uint8_t i =0;i < 5;i++)
		{
			ledsState[0][i] = 0x00;
		}
		
		buf++;
		if(buf == 5)
		{
			buf = 0;
			control = 0x01;
		}
		ledsState[0][buf] = 0b00010101;
		
	}
private:
	uint8_t buf;
};

class AnimRaniDrops2D : public Animation
{
public:
	//AnimRaniDrops2D(uint8_t ledsState[][LEDSLAYERS], uint16_t _waitTime = 10)
	//{
	//	ledsState[0][0] = 0xff;
	//	ledsState[0][1] = 0x00;
	//	ledsState[0][2] = 0x00;
	//	ledsState[0][3] = 0x00;
	//	ledsState[0][4] = 0x00;
	//	waitTime = _waitTime;
	//	control = 0;
	//	lastLayer = 0;
	//}
	//void Init(uint8_t ledsState[][LEDSLAYERS], uint16_t _waitTime = 10)
	void Init(volatile uint8_t ** ledsState, uint16_t _waitTime = 10, char * some = NULL)
	{
		//ledsState[0][0] = 0xff;
		ledsState[0][0] = 0xff;
		ledsState[0][1] = 0x00;
		ledsState[0][2] = 0x00;
		ledsState[0][3] = 0x00;
		ledsState[0][4] = 0x00;
		waitTime = _waitTime;
		control = 0;
		lastLayer = 0;
		id = '2';
		}
	//void UpdateLedsState(uint8_t ledsState[][LEDSLAYERS])
	void UpdateLedsState(volatile uint8_t **  ledsState)
	{
		if(lastLayer == 4)
		{
			lastLayer = 0;
			control &= ~0x80;
		}
		
		if(control & 0x80)
		{
			ledsState[0][lastLayer] &= ~(1<<selectedLed);
			ledsState[0][lastLayer + 1] |= (1<<selectedLed);
			lastLayer++;
			return;
		}
		
		selectedLed = rand() % 5;
		if(ledsState[0][0] & (1<<selectedLed))
		{
			control |= 0x80;
			
		}
		
		control |= 0x01;
		for(uint8_t i = 0; i < 5; i++)
		{
			if(!(ledsState[0][LEDSLAYERS-1] & (1<<i)))
				control &= ~0x01; 
		}
	}
	
private:
	uint8_t selectedLed;
	volatile uint8_t lastLayer;
};



#endif /* ANIMATIONS_H_ */