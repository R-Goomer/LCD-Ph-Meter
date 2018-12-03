#include <LiquidCrystal.h>

/*******************LCD SETUP********************************/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/********************PH OFFSET CALIBRATION*********************/
float comp = 8.1;

/********************VARIABLES DEFINITION***********************/
int Po_Pin = A0; //Pin Po on the pH sensor board connects to Arduino pin# A0.
int c=0;
int i = 0;
int final_volatge;
float final_Ph;
float mv=0;

/*********************MAIN SETUP*******************************/
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(5,0);
  lcd.print("Ambtek");
  lcd.setCursor(3,1);
  lcd.print("Innovation");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Digital Ph");
  lcd.setCursor(5,1);
  lcd.print("Meter");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Ph: ");
  lcd.setCursor(4,1);
  lcd.print("mV: ");  
  Serial.begin(9600);
}


/*************************MAIN LOOP******************************/
void loop() {
  int measure = 0;
  float mv=0;

  
  for(i=0;i<20;i++){
    measure = measure + analogRead(Po_Pin);
    delay(10);
  }
  measure = measure/20;

  float voltage = 5.05 / 1024.0 * measure; //Digital to Analog conversion

  float Po = 7 + ((2.5 - voltage) / 0.173);
  final_Ph = Po+comp;

  if(final_Ph<0.05)
  final_Ph=0;

  if(final_Ph>13.95)
  final_Ph=14;
 
  mv = (-59.16 * final_Ph) + 414.12;
    
  Serial.print("\tPH: ");
  Serial.print(final_Ph,1);
  lcd.setCursor(8,0);
  lcd.print(final_Ph,1);
  Serial.println("");
  Serial.print("\tVoltage: ");
  lcd.setCursor(8,1);
  lcd.print("+");

  if(mv<0)
  lcd.setCursor(8,1);
    
  if(-100>=mv)
  lcd.print(mv,1);
    
  else if(-100<mv&&mv<=-10)
  lcd.print(mv,2);

  else if(-10<mv&&mv<0)
  lcd.print(mv,3);

  else if(10>mv&&mv>=0)
  lcd.print(mv,3);
    
  else if(100>mv&&mv>=10)
  lcd.print(mv,2);
    
  else if(mv>=100)
  lcd.print(mv,1);
    
  Serial.print(mv,1);

  delay(1000);
  
}
