//
// code based on source code by moz from youtube channel LogMaker
//
// expanded and modified by #w0rk
// 


#define ROW_1 22
#define ROW_2 23
#define ROW_3 24
#define ROW_4 25
#define ROW_5 26
#define ROW_6 27
#define ROW_7 28
#define ROW_8 29

#define COL_1 30
#define COL_2 31
#define COL_3 32
#define COL_4 33
#define COL_5 34
#define COL_6 35
#define COL_7 36
#define COL_8 37

#define LED_01 40
#define LED_02 41
#define LED_03 42
#define LED_04 44
#define LED_05 45
#define LED_06 48

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};

const byte leds[] = {
    LED_01, LED_02, LED_03, LED_04, LED_05, LED_06
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

// setting variables for loop function
    int GearCount = 1;
    int ButtonGearUp = A0;
    int ButtonGearDown = A1;
    int PotPin = A2;
    int valPot = 0;
    int potenzometer = 0;


void setup() {


  // Open serial port
    Serial.begin(9600);
    
    // Set pins to OUTPUT
    for (byte i = 22; i <= 53; i++)
    pinMode(i, OUTPUT);

    for (byte j = 8; j <= 12; j++)
    pinMode(j,OUTPUT);


    // set gearshifter pins to input
    pinMode(ButtonGearUp, INPUT);
    pinMode(ButtonGearDown, INPUT);
    pinMode(PotPin, INPUT);
   
}


void loop() {

    	int GearUp = digitalRead(ButtonGearUp);
	int GearDown = digitalRead(ButtonGearDown);
        valPot = analogRead(PotPin);

        //Serial.print("DEBUG 0.0: valPot = ");
        //Serial.println(valPot);

        //Serial.print("DEBUG 1.0: GearCount = ");
        //Serial.println(GearCount);

	if ((GearUp == 1) && (GearDown == 0) && (GearCount < 8) || (valPot >= 600) && (GearCount < 8)) {	        // GearUp, if possible
		GearCount ++;
                delay(175);


        //Serial.print("DEBUG 1.1: GearCount = ");
        //Serial.println(GearCount);
  
	}	

	if ((GearDown == 1) && (GearDown == 1) && (GearCount > 0 ) || (valPot <= 10) && (GearCount > 0 )) {	        // GearDown, if possible
		GearCount --;
                delay(175);

        //Serial.print("DEBUG 1.2: GearCount = ");
        //Serial.println(GearCount);

	} 
        
	drawScreen(gear[GearCount]);
        flash();

    
        //Serial.print("DEBUG 2: GearCount = ");
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

void flash() {

  potenzometer = analogRead(PotPin);
 
 if (potenzometer <= 100) {
    digitalWrite (LED_01,HIGH);
    digitalWrite (LED_02,LOW);
    digitalWrite (LED_03,LOW);
    digitalWrite (LED_04,LOW);
    digitalWrite (LED_05,LOW);
 }
 else if (potenzometer <= 200) {
    digitalWrite (LED_01,HIGH);
    digitalWrite (LED_02,HIGH);
    digitalWrite (LED_03,LOW);
    digitalWrite (LED_04,LOW);
    digitalWrite (LED_05,LOW);
 } 
 else if (potenzometer <= 300) {
    digitalWrite (LED_01,HIGH);
    digitalWrite (LED_02,HIGH);
    digitalWrite (LED_03,HIGH);
    digitalWrite (LED_04,LOW);
    digitalWrite (LED_05,LOW);
 }
 else if (potenzometer <= 400) {
    digitalWrite (LED_01,HIGH);
    digitalWrite (LED_02,HIGH);
    digitalWrite (LED_03,HIGH);
    digitalWrite (LED_04,HIGH);
    digitalWrite (LED_05,LOW);
 }
 else if (potenzometer <= 450) {
    digitalWrite (LED_01,HIGH);
    digitalWrite (LED_02,HIGH);
    digitalWrite (LED_03,HIGH);
    digitalWrite (LED_04,HIGH);
    digitalWrite (LED_05,HIGH);
 }
 else if (potenzometer <= 590){
    digitalWrite (LED_01,LOW);
    digitalWrite (LED_02,LOW);
    digitalWrite (LED_03,LOW);
    digitalWrite (LED_04,LOW);
    digitalWrite (LED_05,LOW);
    
    digitalWrite (LED_06,HIGH);
    delay(45);
    digitalWrite (LED_06,LOW);
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
