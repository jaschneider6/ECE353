#include "proj.h"

volatile uint16_t ASTEROID_X_COORD = 190;
volatile uint16_t ASTEROID_Y_COORD = 270;
volatile uint16_t PLAYER_X_COORD = 50;
volatile uint16_t PLAYER_Y_COORD = 40;
volatile bool ALERT_ASTEROID = true;
volatile bool ALERT_PLAYER = true;
volatile bool button;
volatile uint16_t pColor;
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
        volatile uint16_t asteroid_x_coord, 
        volatile uint16_t asteroid_y_coord, 
        uint8_t asteroid_height, 
        uint8_t asteroid_width,
        volatile uint16_t player_x_coord, 
        volatile uint16_t player_y_coord, 
        uint8_t player_height, 
        uint8_t player_width
)
{
	//This is handled by checking to see if it is possible that the two objects are not overlapping
	//and then it returns false, if none of these cases are true then we know they must be overlapping
	//so the method returns true
	
	//ships right edge is left of invaders left edge
	if((asteroid_x_coord + (asteroid_width/2) - 1) < (player_x_coord - (player_width/2))){
		return false;
	}
	//ships left edge is right of invaders right edge
	else if((asteroid_x_coord - (asteroid_width/2)) > (player_x_coord + (player_width/2 - 1))){
		return false;
	}//if we've gotten here we know that collision in the x direction is occuring so only y to check
	//ships top edge is below invaders bottom edge
	else if((asteroid_y_coord - (asteroid_height/2)) > (player_y_coord + (player_height/2) - 1)){
		return false;
	}
	//ships bottom edge is above invaders top edge
	else if((asteroid_y_coord + (asteroid_height/2) - 1) < (player_y_coord - (player_height/2))){
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
  
  // Update the Space Shipt 60 times per second.
  gp_timer_config_32(TIMER2_BASE,TIMER_TAMR_TAMR_PERIOD, 1000000, false, true);
  gp_timer_config_32(TIMER3_BASE,TIMER_TAMR_TAMR_PERIOD, 500000, false, true);
  gp_timer_config_32(TIMER4_BASE,TIMER_TAMR_TAMR_PERIOD, 50000, false, true);
}

//volatile uint16_t B1_X = 0;
//volatile uint16_t B1_Y = 0;
//volatile PS2_DIR_t B1_Dir = PS2_DIR_CENTER;
//volatile bool B1_rdy = true;
//volatile uint16_t B2_X = 0;
//volatile uint16_t B2_Y = 0;
//volatile PS2_DIR_t B2_Dir = PS2_DIR_CENTER;
//volatile bool B2_rdy = true;
//volatile uint16_t B3_X = 0;
//volatile uint16_t B3_Y = 0;
//volatile PS2_DIR_t B3_Dir = PS2_DIR_CENTER;
//volatile bool B3_rdy = true;
//volatile uint16_t nextB = 1;
//volatile uint16_t kills = 0;
//
//void ast_shoot(){
//	if ((B1_X >= (ASTEROID_X_COORD - AsteroidWidthPixels/2)) && (B1_X <= (ASTEROID_X_COORD + AsteroidWidthPixels/2))){
//		if((B1_Y >= (ASTEROID_Y_COORD - AsteroidHeightPixels/2)) && (B1_Y <= (ASTEROID_Y_COORD + AsteroidHeightPixels/2))){
//			lcd_draw_image(ASTEROID_X_COORD, AsteroidWidthPixels, ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			kills++;
//			led_kill_count(kills);
//			newAsteroid();//creates new asteroid
//			return;
//		}	
//	}
//	
//	
//	if ((B2_X >= (ASTEROID_X_COORD - AsteroidWidthPixels/2)) && (B2_X <= (ASTEROID_X_COORD + AsteroidWidthPixels/2))){
//		if((B2_Y >= (ASTEROID_Y_COORD - AsteroidHeightPixels/2)) && (B2_Y <= (ASTEROID_Y_COORD + AsteroidHeightPixels/2))){
//			lcd_draw_image(ASTEROID_X_COORD, AsteroidWidthPixels, ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			kills++;
//			led_kill_count(kills);
//			newAsteroid();//creates new asteroid
//			return;
//		}	
//	}
//		
//	
//	if ((B3_X >= (ASTEROID_X_COORD - AsteroidWidthPixels/2)) && (B3_X <= (ASTEROID_X_COORD + AsteroidWidthPixels/2))){
//		if((B3_Y >= (ASTEROID_Y_COORD - AsteroidHeightPixels/2)) && (B3_Y <= (ASTEROID_Y_COORD + AsteroidHeightPixels/2))){
//			lcd_draw_image(ASTEROID_X_COORD, AsteroidWidthPixels, ASTEROID_Y_COORD, AsteroidHeightPixels, AsteroidBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			kills++;
//			led_kill_count(kills);
//			newAsteroid();//creates new asteroid
//			return;
//		}	
//	}
//	return;
//}
//	
//
////***********
////bullet updater
////***********
//
//
//void BulletUpdater(){
//	switch(B1_Dir){
//		case PS2_DIR_DOWN:
//		if(B1_Y < 320){
//			B1_Y++;
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B1_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_UP:
//		if(B1_Y > 0){
//			B1_Y--;
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B1_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_LEFT:
//		if(B1_X > 0){
//			B1_X--;
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B1_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_RIGHT:
//		if(B1_X < 240){
//			B1_X++;
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B1_X, 1, B1_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B1_rdy = true;
//		}
//		break;
//		
//		default:
//			break;
//	}
//	
//	
//		switch(B2_Dir){
//		case PS2_DIR_DOWN:
//		if(B2_Y < 320){
//			B2_Y++;
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B2_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_UP:
//		if(B2_Y > 0){
//			B2_Y--;
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B2_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_LEFT:
//		if(B2_X > 0){
//			B2_X--;
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B2_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_RIGHT:
//		if(B2_X < 240){
//			B2_X++;
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B2_X, 1, B2_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B2_rdy = true;
//		}
//		break;
//		
//		default:
//			break;
//	}
//	
//		switch(B3_Dir){
//		case PS2_DIR_DOWN:
//		if(B3_Y < 320){
//			B3_Y++;
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B3_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_UP:
//		if(B3_Y > 0){
//			B3_Y--;
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B3_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_LEFT:
//		if(B3_X > 0){
//			B3_X--;
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B3_rdy = true;
//		}
//		break;
//		
//		case PS2_DIR_RIGHT:
//		if(B3_X < 240){
//			B3_X++;
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, pColor, LCD_COLOR_BLACK);
//		} else{
//			lcd_draw_image(B3_X, 1, B3_Y, 1, BulletBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
//			B3_rdy = true;
//		}
//		break;
//		
//		default:
//			break;
//	}
//	
//	
//}
//
//
////****
////Shootbullet
////****
//void Shootbullet(PS2_DIR_t dir) {
//	
//	if(B1_rdy){
//		switch (dir){
//			case up:
//				B1_X = PLAYER_X_COORD;
//				B1_Y = PLAYER_Y_COORD - PlayerHeightPixels/2;
//				B1_Dir = PS2_DIR_UP;
//				B1_rdy = false;
//				break;
//			case down:
//				B1_X = PLAYER_X_COORD;
//				B1_Y = PLAYER_Y_COORD + PlayerHeightPixels/2;
//				B1_Dir = PS2_DIR_DOWN;
//				B1_rdy = false;
//				break;
//			case left:
//				B1_X = PLAYER_X_COORD - PlayerWidthPixels/2;
//				B1_Y = PLAYER_Y_COORD;
//				B1_Dir = PS2_DIR_LEFT;
//				B1_rdy = false;
//				break;
//			case right:
//				B1_X = PLAYER_X_COORD + PlayerWidthPixels/2;
//				B1_Y = PLAYER_Y_COORD;
//				B1_Dir = PS2_DIR_RIGHT;
//				B1_rdy = false;
//				break;
//			default:
//				break;
//		}
//	}
//	
//	else if(B2_rdy){
//		switch (dir){
//			case up:
//				B2_X = PLAYER_X_COORD;
//				B2_Y = PLAYER_Y_COORD - PlayerHeightPixels/2;
//				B2_Dir = PS2_DIR_UP;
//				B2_rdy = false;
//				break;
//			case down:
//				B2_X = PLAYER_X_COORD;
//				B2_Y = PLAYER_Y_COORD + PlayerHeightPixels/2;
//				B2_Dir = PS2_DIR_DOWN;
//				B2_rdy = false;
//				break;
//			case left:
//				B2_X = PLAYER_X_COORD - PlayerWidthPixels/2;
//				B2_Y = PLAYER_Y_COORD;
//				B2_Dir = PS2_DIR_LEFT;
//				B2_rdy = false;
//				break;
//			case right:
//				B2_X = PLAYER_X_COORD + PlayerWidthPixels/2;
//				B2_Y = PLAYER_Y_COORD;
//				B2_Dir = PS2_DIR_RIGHT;
//				B2_rdy = false;
//				break;
//			default:
//				break;
//		}
//	}
//	
//	else if(B3_rdy){
//		switch (dir){
//			case up:
//				B3_X = PLAYER_X_COORD;
//				B3_Y = PLAYER_Y_COORD - PlayerHeightPixels/2;
//				B3_Dir = PS2_DIR_UP;
//				B3_rdy = false;
//				break;
//			case down:
//				B3_X = PLAYER_X_COORD;
//				B3_Y = PLAYER_Y_COORD + PlayerHeightPixels/2;
//				B3_Dir = PS2_DIR_DOWN;
//				B3_rdy = false;
//				break;
//			case left:
//				B3_X = PLAYER_X_COORD - PlayerWidthPixels/2;
//				B3_Y = PLAYER_Y_COORD;
//				B3_Dir = PS2_DIR_LEFT;
//				B3_rdy = false;
//				break;
//			case right:
//				B3_X = PLAYER_X_COORD + PlayerWidthPixels/2;
//				B3_Y = PLAYER_Y_COORD;
//				B3_Dir = PS2_DIR_RIGHT;
//				B3_rdy = false;
//				break;
//			default:
//				break;
//		}
//	}
//	
//	
//	
//	
//}
	
	

//*****************************************************************************
// Main application for HW3
//*****************************************************************************
void proj_main(void)
{
    bool game_over = false;
    init_hardware();
   

      while(!game_over)
      {
					if(button){
						button = false;
						lcd_draw_rectangle_centered(100, 10, 100, 10, LCD_COLOR_BLUE2);
					}
						
				led_kill_count(0xF);
          if(ALERT_ASTEROID)
          {
            ALERT_ASTEROID = false;
            lcd_draw_rectangle_centered(ASTEROID_X_COORD, AsteroidWidthPixels + 2, ASTEROID_Y_COORD, AsteroidHeightPixels + 2, LCD_COLOR_BLACK);
            lcd_draw_image(
                          ASTEROID_X_COORD,                       // X Center Point
                          AsteroidWidthPixels,   // Image Horizontal Width
                          ASTEROID_Y_COORD,                       // Y Center Point
                          AsteroidHeightPixels,  // Image Vertical Height
                          AsteroidBitmaps,       // Image
                          LCD_COLOR_WHITE,           // Foreground Color
                          LCD_COLOR_BLACK          // Background Color
                        );
              
            game_over = check_game_over(
                                        ASTEROID_X_COORD,
                                        ASTEROID_Y_COORD,
                                        AsteroidHeightPixels,
                                        AsteroidWidthPixels,
                                        PLAYER_X_COORD,
                                        PLAYER_Y_COORD,
                                        PlayerHeightPixels,
                                        PlayerWidthPixels
                                    );
          }
          
          if(ALERT_PLAYER)
          {
            ALERT_PLAYER = false;
            lcd_draw_rectangle_centered(PLAYER_X_COORD, PlayerWidthPixels + 2, PLAYER_Y_COORD, PlayerHeightPixels + 2, LCD_COLOR_BLACK);
            lcd_draw_image(
                          PLAYER_X_COORD,          // X Center Point
                          PlayerWidthPixels,       // Image Horizontal Width
                          PLAYER_Y_COORD,          // Y Center Point
                          PlayerHeightPixels,      // Image Vertical Height
                          PlayerBitmaps,           // Image
                          pColor,            			 // Foreground Color
                          LCD_COLOR_BLACK          // Background Color
                        );
              
             game_over = check_game_over(
                                            ASTEROID_X_COORD,
                                            ASTEROID_Y_COORD,
                                            AsteroidHeightPixels,
                                            AsteroidWidthPixels,
                                            PLAYER_X_COORD,
                                            PLAYER_Y_COORD,
                                            PlayerHeightPixels,
                                            PlayerWidthPixels
                                        );
          }
          
      }   
}
