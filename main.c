#include <gb/gb.h>
#include "map.c"

UBYTE counter;
UINT16 p1, p2;


void LCD_Interrupt(void){   

	if( LY_REG < 90u){ 
		SCX_REG = p2 >> 2;
		SCY_REG = wave[counter] >> 1;

	}

	if( (LY_REG < 100u) && (LY_REG > 96u) ){ 
		SCX_REG=p2;
		SCY_REG = 0;		
	}

	if(LY_REG >  120u){
		SCX_REG= p1;
		SCY_REG = 0;
	}
}

void VBL_Interrupt(void){
	p1+=1;
	counter+=1;
	if( counter >= 88){
		counter = 0;
	}		
	p2 = p1 >> 1; 	
}


void main(void) {
    
	HIDE_SPRITES;
	HIDE_BKG;
	STAT_REG = 8;

	disable_interrupts();
	add_LCD(LCD_Interrupt);
	add_VBL(VBL_Interrupt); 
	enable_interrupts();    

	counter = 0;

	set_bkg_data(0, 0x51, &background_tile_data);	
	set_bkg_tiles(0, 0, 32, 18, &background_map_data);	

	set_interrupts(LCD_IFLAG | VBL_IFLAG );

	SHOW_BKG;
	SHOW_SPRITES;
    
    	while(1){
		wait_vbl_done();
	}
}
