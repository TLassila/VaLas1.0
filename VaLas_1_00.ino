//VALAS 1.0
//722.6 GEARBOX CONTROLLER
//SIMPLE MANUAL CONTROLLER WITH MINIMAL FEARURES FOR COMFORTABLE DRIVING
//BY TONI LASSILA & TEEMU VAHTOLA 
//t6lato00@students.oamk.fi

//DOWNLOAD U8G2 TO YOUR ARDUINO LIBRARIRIES, FOR 0,91" OLED GEAR SCREEN!
//OTHERWISE ERASE ALL U8G2 COMMANDS

//LICENCE: CC BY-NC 3.0 https://creativecommons.org/licenses/by-nc/3.0/deed.en
//NOT FOR COMMERCIAL USE!

// GEAR SETTINGS

// PIN  1-2,4-5 SWITCH  ON/OFF
// PIN2 2-3     SWITCH  ON/OFF
// PIN3 3-4     SWITCH  ON/OFF
// PIN4 LINE PRESSURE   PWM 0-255 low=0
// PIN5 SWITCH PRESSURE PWM 0-255 low=0
// PIN6 TURBINE LOCK    PWM 0-255 low=0



#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

const int inpin[2] = {53,50,};
byte gear;

//255/100*40=102
//255/100*33=84


int up_shift=1;
int down_shift=1;
int old_upshift=1;
int old_downshift=1;

int painesole = 5;
int linjasole = 6;

int ledPin = 33; // 1-2, 4-5 vaihto shift      LOW/HIGH
int ledPin2 = 35; // 2-3 vaihto     shift      LOW/HIGH
int ledPin3 = 37; // 3-4 vaihto     shift      LOW/HIGH
int ledPin4 = 39; // Linjapaine     MOD_PC     min-max 255-0
int ledPin5 = 41; // Vaihtopaine    SHIFT_PC   min-max 255-0
int ledPin6 = 43; // Turbiinilukko TCC        min-max 0-255

boolean tila=0;

void setup()
{
 Serial.begin(9600);      // open the serial port at 9600 bps:    
 Serial.write("Ohjelma käynnistyy");
 Serial.write("\n");
 
 delay(1500); 
 
 u8g2.begin(); //näyttökäynnistyy
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"VaLas");
 u8g2.sendBuffer();
 delay(1800);
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"Ver. 1.0");
 u8g2.sendBuffer();
 delay(1500);
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 2");
 u8g2.sendBuffer();

  
 pinMode(inpin[0],INPUT);
 pinMode(inpin[1],INPUT);


         
 pinMode(ledPin, OUTPUT); 
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 pinMode(ledPin4, OUTPUT);
 pinMode(ledPin5, OUTPUT);
 pinMode(ledPin6, OUTPUT);

    gear=2;

}


void loop()
{
 readswitch();

 while(tila==0)
 {
   readswitch();     
  
 }
 // a switch as been pressed
 
 // Check for the up_shift
 if ((up_shift==0) && (tila==1))
{  
  
    gear++;
    delay(100);
 
  
      if ((gear>=1) && (gear<=6))
      {
          
        switch(gear)
        {
          case 1: select_one();break;
          case 2: select_twoup();break;
          case 3: select_threeup();break;
          case 4: select_fourup();break;
          case 5: select_five();break;
          case 6: select_fivetcc();break;
        }
      }
   
      else gear=6; 

}
  
 
 // check for the down_shift  
 if ((down_shift==0) && (tila==1))
 {  
    gear--;
    delay(100);
  
 

    if ((gear>=1) && (gear<=6))
    {
      switch(gear)
      { 
        case 1: select_one();break;
        case 2: select_two();break;
        case 3: select_three();break;
        case 4: select_four();break;
        case 5: select_fivedown();break;
        case 6: select_fivetcc();break;
      }
    }
    else gear=1;
    
  }   
}


void readswitch()
{
 up_shift=digitalRead(inpin[0]);
 // check upshift transition
 if ((up_shift==0) && (old_upshift==1))
 {
   tila=1;
   delay(50);
 }  
 old_upshift=up_shift;
 down_shift=digitalRead(inpin[1]);
 // check downshift transition
 if ((down_shift==0) && (old_downshift==1))
 {
   tila=1;
   delay(50);
 }  
 old_downshift=down_shift;  


//ON
// digitalWrite(ledPin4, 30);   


}

// GEAR SETTINGS

// PIN  1-2,4-5 SWITCH  ON/OFF
// PIN2 2-3     SWITCH  ON/OFF
// PIN3 3-4     SWITCH  ON/OFF
// PIN4 LINE PRESSURE   PWM 0-255
// PIN5 SWITCH PRESSURE PWM 0-255
// PIN6 TURBINE LOCK    PWM 0-255

void select_one()
// 2 -> 1
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("1");
 
 analogWrite(ledPin4,40); 
 analogWrite(ledPin5, 40);   
 digitalWrite(ledPin, HIGH); 
 digitalWrite(ledPin6, 0); 
  
 delay(700);
 
 analogWrite(ledPin4, 0);                       
 analogWrite(ledPin5, 0); 
 digitalWrite(ledPin, LOW);
 
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 1");
 u8g2.sendBuffer();

  tila=0;  
}


void select_two()
// 3 -> 2
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("2");

 analogWrite(ledPin4, 180); 
 analogWrite(ledPin5, 180);
 digitalWrite(ledPin6, 0); 
 
 delay (20); 
 
 digitalWrite(ledPin2, HIGH);
   
 delay(600);

 analogWrite(ledPin4, 70);
 analogWrite(ledPin5, 70);                       
 digitalWrite(ledPin2, LOW);   

 delay(50);

 analogWrite(ledPin4, 20);
 analogWrite(ledPin5, 0); 

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 2");
 u8g2.sendBuffer();

  tila=0;   
}


void select_three()
// 4 -> 3
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("3");
 
 analogWrite(ledPin4, 140); 
 analogWrite(ledPin5, 140); 
 digitalWrite(ledPin3, HIGH); 
 digitalWrite(ledPin6, 0);   

 delay(600);
                     
 analogWrite(ledPin5, 0); 
 analogWrite(ledPin4, 0); 
 digitalWrite(ledPin3, LOW);   
 digitalWrite(ledPin6, 0);
 
 delay(50);
 
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 3");
 u8g2.sendBuffer();

  tila=0;  
}
 
void select_four()
// 5 -> 4
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("4");

 analogWrite(ledPin4, 140); 
 analogWrite(ledPin5, 140); 
 digitalWrite(ledPin, HIGH); 
 digitalWrite(ledPin6, 0);   

 delay(600);

 analogWrite(ledPin4, 0); 
 analogWrite(ledPin5, 0);                      
 digitalWrite(ledPin, LOW); 
 digitalWrite(ledPin6, 0);  

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 4");
 u8g2.sendBuffer();

  tila=0;   
       
}


void select_five()
// 4 -> 5
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("5");
 
 analogWrite(ledPin4, 100); 
 analogWrite(ledPin5, 120);
 digitalWrite(ledPin, HIGH); 
 digitalWrite(ledPin6, 0);   

 delay(600);

 analogWrite(ledPin4, 15);   
 analogWrite(ledPin5, 0);                    
 digitalWrite(ledPin, LOW);   
 digitalWrite(ledPin6, LOW);

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 5");
 u8g2.sendBuffer();

  tila=0;  
}


void select_fivetcc()
// 5 -> 5 OD
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("5tcc");

 delay(400);
 
 analogWrite(ledPin4, 25);  
 analogWrite(ledPin5, 0);                     
 digitalWrite(ledPin, LOW);   
 digitalWrite(ledPin6, HIGH);

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 5+");
 u8g2.sendBuffer();


  tila=0;  
}

void select_fivedown()
// 5 OD -> 5
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("5");

 delay(400);
 
 analogWrite(ledPin4, 15); 
 analogWrite(ledPin5, 0);                      
 digitalWrite(ledPin, LOW);
 digitalWrite(ledPin6, 0);

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 5");
 u8g2.sendBuffer();

  tila=0;  
}


void select_twoup()
// 1 -> 2
{
  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("2");

 analogWrite(ledPin4, 80); 
 analogWrite(ledPin5, 90); 
 digitalWrite(ledPin, HIGH); 
 digitalWrite(ledPin6, 0);   

 delay(600);

 analogWrite(ledPin4, 0); 
 analogWrite(ledPin5, 0);                      
 digitalWrite(ledPin, LOW);   
 digitalWrite(ledPin6, 0);
 
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 2");
 u8g2.sendBuffer();

  tila=0;  
}

void select_threeup()
// 2 ->3
{ 

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("3");

 analogWrite(ledPin4, 80);  
 analogWrite(ledPin5, 80); 
 digitalWrite(ledPin2, HIGH);
 digitalWrite(ledPin6, 0);   

 delay(600);

 analogWrite(ledPin4, 0);   
 analogWrite(ledPin5, 0);                     
 digitalWrite(ledPin2, LOW);   
 digitalWrite(ledPin6, 0);

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 3");
 u8g2.sendBuffer();

  tila=0;  
}


void select_fourup()
// 3 -> 4
{  
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"SHIFT");
 u8g2.sendBuffer();
 Serial.println("4");
 
 analogWrite(ledPin4, 90); 
 analogWrite(ledPin5, 100); 
 digitalWrite(ledPin3, HIGH); 
 digitalWrite(ledPin6, 0);
 
 delay(1200);

 analogWrite(ledPin4, 0);  
 analogWrite(ledPin5, 0);                     
 digitalWrite(ledPin3, LOW);   
 digitalWrite(ledPin6, 0);

 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_logisoso28_tr);
 u8g2.drawStr(1,29,"GEAR 4");
 u8g2.sendBuffer();

  tila=0;  
}

