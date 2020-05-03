// Copyright (c) 2015-16, Joe Krachey
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

/* 
**  Image data
*/

#include "project_images.h"
/* 
**  Image data for asteroid
*/

const uint8_t AsteroidBitmaps[] =
{
	0x00, 0x01, 0xC0, 0x00, //               ###              
	0x00, 0x02, 0x30, 0x00, //              #   ##            
	0x00, 0x02, 0x18, 0x00, //              #    ##           
	0x00, 0x06, 0x07, 0x80, //             ##      ####       
	0x0E, 0x18, 0x00, 0xC0, //    ###    ##           ##      
	0x11, 0xF0, 0x00, 0x20, //   #   #####              #     
	0x20, 0x00, 0x40, 0x10, //  #              #         #    
	0x40, 0x00, 0x90, 0x18, // #              #  #       ##   
	0x40, 0x00, 0x88, 0x04, // #              #   #        #  
	0x40, 0x00, 0x48, 0x04, // #               #  #        #  
	0x20, 0x00, 0x30, 0x04, //  #               ##         #  
	0x20, 0x00, 0x00, 0x02, //  #                           # 
	0x40, 0x00, 0x00, 0x01, // #                             #
	0x80, 0x00, 0x00, 0x01, //#                              #
	0x70, 0x0F, 0x80, 0x03, // ###        #####             ##
	0x18, 0x30, 0x38, 0x04, //   ##     ##      ###        #  
	0x08, 0x40, 0x06, 0x08, //    #    #           ##     #   
	0x08, 0x80, 0x38, 0x30, //    #   #         ###     ##    
	0x07, 0x7F, 0xC0, 0x60, //     ### #########       ##     
	0x01, 0x80, 0x01, 0xC0, //       ##              ###      
	0x00, 0x70, 0x1E, 0x00, //         ###       ####         
	0x00, 0x0F, 0xE0, 0x00, //            #######             
};


/* Bitmap sizes for space_ship */
const uint8_t AsteroidWidthPixels = 32;
const uint8_t AsteroidHeightPixels = 22;

// 
//  Image data for player
// 

const uint8_t PlayerBitmaps[] =
{
0x00, 0x00, 0xFC, 0x00, 0x00, //                ######                  
0x00, 0x0F, 0x03, 0xC0, 0x00, //            ####      ####              
0x00, 0x70, 0x00, 0x38, 0x00, //         ###              ###           
0x03, 0x80, 0x30, 0x07, 0x00, //      ###         ##         ###        
0x0C, 0x00, 0x00, 0x00, 0xC0, //    ##                          ##      
0x10, 0x20, 0x00, 0x10, 0x20, //   #      #                #      #     
0x20, 0x00, 0x00, 0x00, 0x10, //  #                                #    
0x40, 0x00, 0x00, 0x00, 0x08, // #                                  #   
0x80, 0x00, 0x00, 0x00, 0x04, //#                                    #  
0x84, 0x00, 0x00, 0x00, 0x84, //#    #                          #    #  
0x84, 0x00, 0x00, 0x00, 0x84, //#    #                          #    #  
0x80, 0x00, 0x00, 0x00, 0x04, //#                                    #  
0x40, 0x00, 0x00, 0x00, 0x08, // #                                  #   
0x20, 0x00, 0x00, 0x00, 0x10, //  #                                #    
0x10, 0x20, 0x00, 0x10, 0x20, //   #      #                #      #     
0x0C, 0x00, 0x00, 0x00, 0xC0, //    ##                          ##      
0x03, 0x80, 0x30, 0x07, 0x00, //      ###         ##         ###        
0x00, 0x70, 0x00, 0x38, 0x00, //         ###              ###           
0x00, 0x0F, 0x03, 0xC0, 0x00, //            ####      ####              
0x00, 0x00, 0xFC, 0x00, 0x00, //                ######                  
};


// Bitmap sizes for player
const uint8_t PlayerWidthPixels = 40;
const uint8_t PlayerHeightPixels = 20;


const uint8_t BulletBitmaps[] =
{0};




