#include "proj.h"

volatile uint16_t SHIP_X_COORD = 190;
volatile uint16_t SHIP_Y_COORD = 270;
volatile uint16_t INVADER_X_COORD = 50;
volatile uint16_t INVADER_Y_COORD = 40;
volatile bool ALERT_SPACE_SHIP = true;
volatile bool ALERT_INVADER = true;
char STUDENT_NAME[] = "Ryan Andrasco/Jonathan Schneider";

typedef struct
{
    int top;
    int bottom;
    int left;
    int right;
} Rectangle;

//*****************************************************************************
// Determines if any part of the image would be off the screen if the image
// is moved in the specified direction.
//*****************************************************************************
bool contact_edge(
    volatile PS2_DIR_t direction,
    volatile uint16_t x_coord, 
    volatile uint16_t y_coord, 
    uint8_t image_height, 
    uint8_t image_width
)
{
	//Switch statement to handle all cases
		switch(direction){
			//When direction is upward, check if the y coordinate is half of the images height, if so,
			//then we are contacting the top edge, otherwise we aren't
			case PS2_DIR_UP:
				if(y_coord - image_height/2 == 0)
					return true;
				else
					return false;
				break;
			//When direction is downward, check if the y coordinate plus half of the images height is at the max y pixel
			//if so, then we are contacting the bottom edge, otherwise we aren't
			case PS2_DIR_DOWN:
				if(y_coord + image_height/2  == 320)
					return true;
				else
					return false;
				break;
			//When direction is left, check if the x coordinate is half of the images width
			//if so, then we are contacting the left edge, otherwise we aren't
			case PS2_DIR_LEFT:
				if(x_coord - image_width/2 == 0)
					return true;
				else
					return false;
				break;
			//When direction is right, check if the x coordinate plus half of the images width is at the max x pixel
			//if so, then we are contacting the right edge, otherwise we aren't
			case PS2_DIR_RIGHT:
				if(x_coord + image_width/2 + 1 == 240)
					return true;
				else
					return false;
				break;
			//If it is not any of these four directions then we are not moving so the updated coordinates cannot be contacting the edge
			default:
				return false;
				break;
		}
}

//*****************************************************************************
// Moves the image by one pixel in the provided direction.  The second and 
// third parameter should modify the current location of the image (pass by
// reference)
//*****************************************************************************
void move_image(
        volatile PS2_DIR_t direction,
        volatile uint16_t *x_coord, 
        volatile uint16_t *y_coord, 
        uint8_t image_height, 
        uint8_t image_width
)
{
	//switch statement will help handle all 4 movement directions we will increment or decrement the x or
	//value depending upon the direction the object is traveling
   switch(direction){
			//up we decrement the y value found at the pointer location
			case PS2_DIR_UP:
				(*y_coord)--;
				break;
			//down we increment the y value found at the pointer location
			case PS2_DIR_DOWN:
				(*y_coord)++;
				break;
			//left we decrement the x value found at the pointer location
			case PS2_DIR_LEFT:
				(*x_coord)--;
				break;
			//right we increment the x value found at the pointer location
			case PS2_DIR_RIGHT:
				(*x_coord)++;
				break;
			default:
				break;
}
	 }

//*****************************************************************************
// Determines is any portion of the two images are overlapping.  An image is
// considered to be overlapping if the two rectangles determined by the image
// height and widths are overlapping.  An overlap occurs even if the area that
// overlaps are portions of the images where the pixels do not display on the
// screen.
//*****************************************************************************
bool check_game_over(
        volatile uint16_t ship_x_coord, 
        volatile uint16_t ship_y_coord, 
        uint8_t ship_height, 
        uint8_t ship_width,
        volatile uint16_t invader_x_coord, 
        volatile uint16_t invader_y_coord, 
        uint8_t invader_height, 
        uint8_t invader_width
)
{
	//This is handled by checking to see if it is possible that the two objects are not overlapping
	//and then it returns false, if none of these cases are true then we know they must be overlapping
	//so the method returns true
	
	//ships right edge is left of invaders left edge
	if((ship_x_coord + (ship_width/2) - 1) < (invader_x_coord - (invader_width/2))){
		return false;
	}
	//ships left edge is right of invaders right edge
	else if((ship_x_coord - (ship_width/2)) > (invader_x_coord + (invader_width/2 - 1))){
		return false;
	}//if we've gotten here we know that collision in the x direction is occuring so only y to check
	//ships top edge is below invaders bottom edge
	else if((ship_y_coord - (ship_height/2)) > (invader_y_coord + (invader_height/2) - 1)){
		return false;
	}
	//ships bottom edge is above invaders top edge
	else if((ship_y_coord + (ship_height/2) - 1) < (invader_y_coord - (invader_height/2))){
		return false;
	}//if none of these cases are true then collison in both x and y axes is occuring and therefore the
	//rectangles are in contact so game over
	return true;  
}

//*****************************************************************************
// Initializes all of the peripherls used in HW3
//*****************************************************************************
void init_hardware(void)
{
  lcd_config_gpio();
  lcd_config_screen();
  lcd_clear_screen(LCD_COLOR_BLACK);
  ps2_initialize();
  
  // Update the Space Shipt 60 times per second.
  gp_timer_config_32(TIMER2_BASE,TIMER_TAMR_TAMR_PERIOD, 1000000, false, true);
  gp_timer_config_32(TIMER3_BASE,TIMER_TAMR_TAMR_PERIOD, 500000, false, true);
  gp_timer_config_32(TIMER4_BASE,TIMER_TAMR_TAMR_PERIOD, 50000, false, true);
}

//*****************************************************************************
// Main application for HW3
//*****************************************************************************
void hw3_main(void)
{
    bool game_over = false;
    init_hardware();
   

      while(!game_over)
      {
          if(ALERT_SPACE_SHIP)
          {
            ALERT_SPACE_SHIP = false;
            
            lcd_draw_image(
                          SHIP_X_COORD,                       // X Center Point
                          space_shipWidthPixels,   // Image Horizontal Width
                          SHIP_Y_COORD,                       // Y Center Point
                          space_shipHeightPixels,  // Image Vertical Height
                          space_shipBitmaps,       // Image
                          LCD_COLOR_BLUE,           // Foreground Color
                          LCD_COLOR_BLACK          // Background Color
                        );
              
            game_over = check_game_over(
                                        SHIP_X_COORD,
                                        SHIP_Y_COORD,
                                        space_shipHeightPixels,
                                        space_shipWidthPixels,
                                        INVADER_X_COORD,
                                        INVADER_Y_COORD,
                                        invaderHeightPixels,
                                        invaderWidthPixels
                                    );
          }
          
          if(ALERT_INVADER)
          {
            ALERT_INVADER = false;
            
            lcd_draw_image(
                          INVADER_X_COORD,          // X Center Point
                          invaderWidthPixels,       // Image Horizontal Width
                          INVADER_Y_COORD,          // Y Center Point
                          invaderHeightPixels,      // Image Vertical Height
                          invaderBitmaps,           // Image
                          LCD_COLOR_RED,            // Foreground Color
                          LCD_COLOR_BLACK           // Background Color
                        );
              
             game_over = check_game_over(
                                            SHIP_X_COORD,
                                            SHIP_Y_COORD,
                                            space_shipHeightPixels,
                                            space_shipWidthPixels,
                                            INVADER_X_COORD,
                                            INVADER_Y_COORD,
                                            invaderHeightPixels,
                                            invaderWidthPixels
                                        );
          }
          
      }   
}
