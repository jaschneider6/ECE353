// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"
#include "project_interrupts.h"


static volatile uint16_t PS2_X_DATA = 0;
static volatile uint16_t PS2_Y_DATA = 0;
static volatile PS2_DIR_t PS2_DIR = PS2_DIR_CENTER;
static volatile uint16_t count = 0;
static volatile PS2_DIR_t direction = PS2_DIR_CENTER;
static volatile DIR_BTN_t DIR_BTN;


//*****************************************************************************
// Returns the most current direction that was pressed.
//*****************************************************************************
PS2_DIR_t ps2_get_direction(void)
{//This function checks to see if the x or y data is above or below the required threshold values
	//if it is it returns the correct direction with priority set by the given table in the hw assingment
	
	//if x is high it means the joystick is left
  if(PS2_X_DATA > PS2_ADC_HIGH_THRESHOLD){
		return PS2_DIR_LEFT;
	}
	//if x is low it means the joystick is right
	if(PS2_X_DATA < PS2_ADC_LOW_THRESHOLD){
		return PS2_DIR_RIGHT;
	}
	//if y is high it means the joystick is up
	if(PS2_Y_DATA > PS2_ADC_HIGH_THRESHOLD){
		return PS2_DIR_UP;
	}
	//if y is low it means the joystick is down
	if(PS2_Y_DATA < PS2_ADC_LOW_THRESHOLD){
		return PS2_DIR_DOWN;
	}
	//default: if joystick is not moving
	return PS2_DIR_CENTER;
}

//*****************************************************************************
// TIMER1 ISR controls the breathing of an LED
//*****************************************************************************
void TIMER1A_Handler(void)
{	
	GPIOF->DATA ^= RED_M;
	
    // Clear the interrupt
	TIMER1->ICR |= TIMER_ICR_TATOCINT;
	
}
//*****************************************************************************
// TIMER2 ISR is used to determine when to move the Invader
//*****************************************************************************
void TIMER2A_Handler(void)
{	
	//if the invader is not going to contact the edge then we set the draw boolean to high, then call move image
	if(!contact_edge(ps2_get_direction(), PLAYER_X_COORD, PLAYER_Y_COORD, PlayerHeightPixels, PlayerWidthPixels)){
		ALERT_PLAYER = true;
		move_image(ps2_get_direction(), &PLAYER_X_COORD, &PLAYER_Y_COORD, PlayerHeightPixels, PlayerHeightPixels);
	}
    // Clear the interrupt
	TIMER2->ICR |= TIMER_ICR_TATOCINT;
	
}

//*****************************************************************************
// TIMER3 ISR is used to determine when to move the spaceship
//*****************************************************************************
void TIMER3A_Handler(void)
{	
	// spaceship is always moving so set boolean high for next write
	ALERT_ASTEROID = true;
	//if we are out of moves in this direction or contacting the edge we need to handle getting a new direction and length to move
	if(contact_edge(direction, ASTEROID_X_COORD, ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidWidthPixels) || count == 0){
		
		direction = get_new_direction(direction); // grabs new direction
		//forces this dirction to be a direction that is not pushing into a wall
		while(contact_edge(direction, ASTEROID_X_COORD, ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidWidthPixels)){
			direction = get_new_direction(direction);
		}
		//gets how far to move
		count = get_new_move_count();		
	}
	//count decrements as we have moved once and we move the image of the spaceship
	count--;
	move_image(direction, &ASTEROID_X_COORD, &ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidWidthPixels);
	// Clear the interrupt
	TIMER3->ICR |= TIMER_ICR_TATOCINT;  
}
//*****************************************************************************
// TIMER4 ISR is used to trigger the ADC
//*****************************************************************************
void TIMER4A_Handler(void)
{	
	//Calls ADC SS2 handler each time timer 4 gets called
	ADC0 -> PSSI |= ADC_PSSI_SS2;
	// Clear the interrupt
	TIMER4->ICR |= TIMER_ICR_TATOCINT; 
}

//*****************************************************************************
// ADC0 SS2 ISR
//*****************************************************************************
void ADC0SS2_Handler(void)
{
	//Uses sample sequencer fifo to get x and y values of the joystick
	PS2_X_DATA = ADC0-> SSFIFO2;
	PS2_Y_DATA = ADC0-> SSFIFO2;
	//updates to the current direction indicated by the joystick
	PS2_DIR = ps2_get_direction();
  // Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN2;
	
	
}

void GPIOF_Handler(void){
	uint8_t buttonVal = 0;
	GPIOA_Type *port;
	port = (GPIOA_Type *)IO_EXPANDER_IRQ_GPIO_BASE;
	buttonVal = io_expander_read_reg(MCP23017_GPIOB_R);
	
	switch(buttonVal){
		case (0xD):
			button = true;
			DIR_BTN = DIR_BTN_DOWN;
		printf("DOWN\n");
			break;
	}
		buttonVal = 0;
		
		port->IM &= ~PF0;
		port->ICR |= GPIO_ICR_GPIO_M;
		port->IM |= PF0;
}
	
