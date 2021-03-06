//
// code based on source code by moz from youtube channel LogMaker
//
// expanded and modified by #w0rk
// 


#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};

// The display buffer
// (1 = ON, 0 = OFF)
byte gear[9][8] = {
	{B00000000,B00111100,B00100100,B00101100,B00110000,B00101000,B00100100,B00000000},		// R
	{B00000000,B00110000,B00101000,B00100100,B00100100,B00100100,B00100100,B00000000},		// N
	{B00000000,B00001000,B00011000,B00101000,B00001000,B00001000,B00001000,B00000000},		// 1
	{B00000000,B00111100,B00100100,B00000100,B00111100,B00100000,B00111100,B00000000},		// 2
	{B00000000,B00111100,B00000100,B00000100,B00111100,B00000100,B00111100,B00000000},		// 3
	{B00000000,B00100100,B00100100,B00100100,B00111100,B00000100,B00000100,B00000000},		// 4
	{B00000000,B00111100,B00100000,B00100000,B00111100,B00000100,B00111100,B00000000},		// 5
	{B00000000,B00111100,B00100000,B00100000,B00111100,B00100100,B00111100,B00000000},		// 6
	{B00000000,B00111100,B00000100,B00000100,B00000100,B00000100,B00000100,B00000000}, 		// 7
};

int GearCount = 1;


void setup() {
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 2; i <= 13; i++)

    pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    
}


void loop() {
	int GearUp = digitalRead(A4);
	int GearDown = digitalRead(A5);

        //Serial.print("DEBUG 1.0: GearCount =");
        //Serial.println(GearCount);

	if ((GearUp == 1) && (GearDown == 0) && (GearCount < 8)) {	        // GearUp, if possible
		GearCount ++;
                delay(175);

        //Serial.print("DEBUG 1.1: GearCount =");
        //Serial.println(GearCount);
  
	}	

	if ((GearDown == 1) && (GearDown == 1) && (GearCount > 0 )) {	        // GearDown, if possible
		GearCount --;
                delay(175);

        //Serial.print("DEBUG 1.2: GearCount =");
        //Serial.println(GearCount);

	} 
 
	drawScreen(gear[GearCount]);
    
        //Serial.print("DEBUG 2: GearCount =");
        //Serial.println(GearCount);

}


void drawScreen(byte buffer2[]){
     
    
   // Turn on each row in series
    for (byte i = 0; i < 8; i++) {
        setColumns(buffer2[i]); // Set columns for this specific row
        
        digitalWrite(rows[i], HIGH);
        delay(1); // Set this to 50 or 100 if you want to see the multiplexing effect!
        digitalWrite(rows[i], LOW);
        
    }
}


void setColumns(byte b) {
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
    
    // If the polarity of your matrix is the opposite of mine
    // remove all the '~' above.
}
