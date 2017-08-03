
/*
Differential Dynamometr with LED Displsy



*/

#include "LedControl.h"  // from  http://playground.arduino.cc/Main/LedControl

#define OUTTYPE 0

#define ZERO_N 50

#define WTACT 20
unsigned  long   CountL;
unsigned char j04, WeightChanel,TactPoint;
int Pokaz[4];
#define PARAMS3 10
float  Weight[4] = {10.1, 10.2, 10.3, 10.4};
unsigned char ChW, ZeroN[4], j2SetZero[4], item, tShow, ilcd;
long  WeightL[4], WeightZero[4], CountW[4];

/*
 pin 11 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin A5 is connected to LOAD 
 We have only two MAX72XX shields.


*/
  LedControl lc=LedControl(11,13,A5,2);
byte LedCh[16],iLed;



void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);


  pinMode(A3, OUTPUT);  
 



  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  Serial.begin(9600);



  lc.shutdown(0,false);
  lc.shutdown(1,false);
  /* Set the brightness to a maximum values */
  lc.setIntensity(0,15);
  lc.setIntensity(1,15);
  
  /* and clear the display */
   lc.clearDisplay(0);
      lc.clearDisplay(1);



}

void loop() {

  


  item = WeightChanel;
   

  switch (WeightChanel)

  {
    case 0:
      

      if (!(PIND & 0x04))  // If PORTD.2 is HIGH  
      {
        CountL = 0;
    cli();  // disable global interrupts
        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x04;
          delayMicroseconds(WTACT);

          PORTC &= ~0x04;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x04)  // If PORTD.2 is HIGH  
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x04;
        delayMicroseconds(WTACT);
        PORTC &= ~0x04;

        delayMicroseconds(WTACT);
            sei();  // enable interrupts

            
        if (CountL > 0x800000L)
          CountW[0] = -((signed long)  (0xFFFFFFL - CountL));
        else
          CountW[0] = (signed long)CountL;

        if (j2SetZero[0]++ > 0xF0)
          j2SetZero[0] = 0xF0;



        if (j2SetZero[0] < PARAMS3 + 3)
        {
          if (j2SetZero[0] > 2)
          {
            WeightZero[0] += CountW[0] / PARAMS3;

          }

          Pokaz[0] = 8888;

        }
        else


        {
          CountW[0] -= WeightZero[0];
          CountW[0] /= 435L;



        }
if(CountW[0]>0)
Pokaz[0]=int(CountW[0]);
else
Pokaz[0]=int(-CountW[0]);

  
     LedCh[0]=Pokaz[0]%10 ;
    
    
    
    LedCh[1]= (Pokaz[0]/10)%10;
    LedCh[2]= (Pokaz[0]/100)%10;
    LedCh[3]= (Pokaz[0]/1000)%10;
    if(LedCh[3] == 0)
    LedCh[3]=' ';





        if (OUTTYPE >0)  
        {

          Serial.print("S0= \t");

          Serial.print( CountW[0]);
          Serial.print("\t  ");

        }
        else
        {

          if (CountW[0] >= 0)
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(    CountW[0] % 256         ));

            Serial.write(0x03);

            Serial.write(char(    CountW[0] / 256         ));



            Serial.write(char( 5 + 3 + CountW[0] / 256   +  CountW[0] % 256   ));



          }
          else
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(   - CountW[0] % 256         ));

            Serial.write(0x03);

            Serial.write(char(   0x80 - CountW[0] / 256         ));






            Serial.write(char( 0x85 + 3 - CountW[0] / 256   -  CountW[0] % 256   ));
          }


        }

        WeightChanel = 1;


      }
      // End of   SENSOR 0 measurement
      break;


    case 2:
      

      if (!(PIND & 0x10))
      {
        CountL = 0;
        cli();                // disable global interrupts



        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x01;
          delayMicroseconds(WTACT);

          PORTC &= ~0x01;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x10)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x01;
        delayMicroseconds(WTACT);
        PORTC &= ~0x01;

        sei();                // enable interrupts


        if (CountL > 0x800000L)
          CountW[2] = -((signed long)  (0xFFFFFFL - CountL));
        else
          CountW[2] = (signed long)CountL;

        if (j2SetZero[2]++ > 0xF0)
          j2SetZero[2] = 0xF0;



        if (j2SetZero[2] < PARAMS3 + 3)
        {
          if (j2SetZero[2] > 2)
          {
            WeightZero[2] += CountW[2] / PARAMS3;

          }

          Pokaz[2] = 8888;

        }
        else


        {
          CountW[2] -= WeightZero[2];
          CountW[2] /= 451L; //26 for 20 kG



          //  if(CountW[0]>0L)
          Pokaz[2] =   CountW[2] / 1000.0;
          // else
          //  Pokaz[0]=0;

        }


if(CountW[2]>0)
Pokaz[2]=int(CountW[2]);
else
Pokaz[2]=int(-CountW[2]);

    LedCh[8]=Pokaz[2]%10;
    LedCh[9]= (Pokaz[2]/10)%10;
    LedCh[10]= (Pokaz[2]/100)%10;
    LedCh[11]= (Pokaz[2]/1000)%10;

if(LedCh[11] == 0)
    LedCh[11]=' ';





        if (OUTTYPE >0)  //( (PINC&0x10) == 0x10)
        {

          Serial.print("S2= \t");
 
          Serial.print( CountW[2]);
          Serial.print("\t  ");
        }
        else
        {

          if (CountW[2] >= 0)
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(    CountW[2] % 256         ));

            Serial.write(0x01);

            Serial.write(char(    CountW[2] / 256         ));






            Serial.write(char( 5 + 1 + CountW[2] / 256   +  CountW[2] % 256   ));



          }
          else
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(   - CountW[2] % 256         ));

            Serial.write(0x01);

            Serial.write(char(   0x80 - CountW[2] / 256         ));






            Serial.write(char( 0x85 + 1 - CountW[2] / 256   -  CountW[2] % 256   ));
          }


        }


        WeightChanel = 3;


      }
      // End of 1 measurement
      break;




    case  1:
       

      if (!(PIND & 0x08))
      {
        CountL = 0;
     cli();  // disable global interrupts
        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x08;
          delayMicroseconds(WTACT);

          PORTC &= ~0x08;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x08)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x08;
        delayMicroseconds(WTACT);
        PORTC &= ~0x08;

        delayMicroseconds(WTACT);


     sei();  // enable interrupts

        if (CountL > 0x800000L)
          CountW[1] = -((signed long)  (0xFFFFFFL - CountL));
        else
          CountW[1] = (signed long)CountL;

        if (j2SetZero[1]++ > 0xF0)
          j2SetZero[1] = 0xF0;



        if (j2SetZero[1] < PARAMS3 + 3)
        {
          if (j2SetZero[1] > 2)
          {
            WeightZero[1] += CountW[1] / PARAMS3;

          }

          Pokaz[1] = 8888;

        }
        else


        {
          CountW[1] -= WeightZero[1];
          CountW[1] /= 426L;

 

        }

if(CountW[1]>0)
Pokaz[1]=int(CountW[1]);
else
Pokaz[1]=int(-CountW[1]);

    LedCh[4]=Pokaz[1]%10;
    LedCh[5]= (Pokaz[1]/10)%10;
    LedCh[6]= (Pokaz[1]/100)%10;
    LedCh[7]= (Pokaz[1]/1000)%10;

        if(LedCh[7] == 0)
    LedCh[7]=' ';


    

       if (OUTTYPE >0)  //( (PINC&0x10) == 0x10)
        {

          Serial.print("S1= \t");
        
          Serial.print( CountW[1]);
          Serial.print("\t  ");
        }

        else
        {

          if (CountW[1] >= 0)
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(    CountW[1] % 256         ));

            Serial.write(0x02);

            Serial.write(char(    CountW[1] / 256         ));






            Serial.write(char( 5 + 2 + CountW[1] / 256   +  CountW[1] % 256   ));



          }
          else
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(   - CountW[1] % 256         ));

            Serial.write(0x02);

            Serial.write(char(   0x80 - CountW[1] / 256         ));






            Serial.write(char( 0x85 + 2 - CountW[1] / 256   -  CountW[1] % 256   ));
          }


        }

        WeightChanel = 2;


      }
      // End   SENSOR 2 measurement
      break;


    case 3:
      //    INPUT 3

      if (!(PIND & 0x20))
      {
        CountL = 0;
              cli();  // disable global interrupts
        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x02;
          delayMicroseconds(WTACT);

          PORTC &= ~0x02;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x20)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x02;
        delayMicroseconds(WTACT);
        PORTC &= ~0x02;


           sei();  // enable interrupts

        if (CountL > 0x800000L)
          CountW[3] = -((signed long)  (0xFFFFFFL - CountL));
        else
          CountW[3] = (signed long)CountL;

        if (j2SetZero[3]++ > 0xF0)
          j2SetZero[3] = 0xF0;



        if (j2SetZero[3] < PARAMS3 + 3)
        {
          if (j2SetZero[3] > 2)
          {
            WeightZero[3] += CountW[3] / PARAMS3;

          }

          Pokaz[3] = 8888;

        }
        else


        {
          CountW[3] -= WeightZero[3];
          CountW[3] /= 417L;
 

        }



    if(CountW[3]>0)
Pokaz[3]=int(CountW[3]);
else
Pokaz[3]=int(-CountW[3]);

    LedCh[12]=Pokaz[3]%10;
    LedCh[13]= (Pokaz[3]/10)%10;
    LedCh[14]= (Pokaz[3]/100)%10;
    LedCh[15]= (Pokaz[3]/1000)%10;

    if(LedCh[15] == 0)
    LedCh[15]=' ';



        if (OUTTYPE >0)  //( (PINC&0x10) == 0x10)
        {

          Serial.print("S3= \t");
 
          Serial.println( CountW[3]);
        }
        else
        {

          if (CountW[3] >= 0)
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(    CountW[3] % 256         ));

            Serial.write(0x00);

            Serial.write(char(    CountW[3] / 256         ));






            Serial.write(char( 5 + 0 + CountW[3] / 256   +  CountW[3] % 256   ));



          }
          else
          {
            Serial.write(0xFF);
            Serial.write(0xFF);
            Serial.write(0x05);
            Serial.write(0x00);

            Serial.write(char(   - CountW[3] % 256         ));

            Serial.write(0x00);

            Serial.write(char(   0x80 - CountW[3] / 256         ));






            Serial.write(char( 0x85 + 0 - CountW[3] / 256   -  CountW[3] % 256   ));
          }


        }

       





        WeightChanel = 0;


      }
      // End   0 measurement
      break;





  }


 
  delay(50);
 
 
 lc.setChar(0,4,LedCh[0],false);
lc.setChar(0,5,LedCh[1],false);
lc.setChar(0,6,LedCh[2],false);
lc.setChar(0,7,LedCh[3],false);

lc.setChar(0,0,LedCh[4],false);
lc.setChar(0,1,LedCh[5],false);
lc.setChar(0,2,LedCh[6],false);
lc.setChar(0,3,LedCh[7],false);

if(TactPoint++>10)
lc.setChar(1,0,LedCh[12],1);
else
lc.setChar(1,0,LedCh[12],false);

if(TactPoint>19)
TactPoint=0;

lc.setChar(1,1,LedCh[13],false);
lc.setChar(1,2,LedCh[14],false);
lc.setChar(1,3,LedCh[15],false);

lc.setChar(1,4,LedCh[8],false);
lc.setChar(1,5,LedCh[9],false);
lc.setChar(1,6,LedCh[10],false);
lc.setChar(1,7,LedCh[11],false);

 


  delay(50);



}

