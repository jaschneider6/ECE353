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
extern volatile uint16_t pColor;

//*****************************************************************************
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}



//*****************************************************************************
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
  gp_timer_config_32(TIMER0_BASE, TIMER_TAMR_TAMR_1_SHOT, 50000, false, false);
  init_serial_debug(true, true);
  ft6x06_init();
	eeprom_init();
	ps2_initialize();
	io_expander_init();
	lcd_config_screen();
  EnableInterrupts();
}
//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	//Board touch event parameters, used for position and status to check where it is touched
	uint16_t x,y;
  	uint8_t touch_event = 0;
  	i2c_status_t td_status;
  	i2c_status_t x_status;
	//initialize board and clear the screen, then draw a green char on the left and a blue one on the right
	initializeBoard();
	lcd_clear_screen(LCD_COLOR_BLACK);
	lcd_draw_image(50, PlayerWidthPixels, 280, PlayerHeightPixels, PlayerBitmaps, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	lcd_draw_image(190, PlayerWidthPixels, 280, PlayerHeightPixels, PlayerBitmaps, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	//read where player touches board until we get a value
	while(touch_event == 0){
	touch_event = ft6x06_read_td_status();
	};
	//set x value to touch value and if they clicked on the right side then they selected the blue character otherwise they selected
	//the green character
	x = ft6x06_read_x();
	if(x>119){
		pColor = LCD_COLOR_BLUE;
	}
	else{
		pColor = LCD_COLOR_GREEN;
	}
	proj_main();
    while(1){};
}
