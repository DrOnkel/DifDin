//The source code for the Arduino environment is covered by the GPL.
#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);


#define ZERO_N 10

#define WTACT 50
unsigned  long   CountL;
unsigned char j04, WeightChanel;
float Pokaz[4];
#define PARAMS3 10
float  Weight[4] = {10.1, 10.2, 10.3, 10.4};
unsigned char ChW, ZeroN[4], j2SetZero[4];
long  WeightL[4], WeightZero[4], CountW[4];






void setup() {
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.begin(9600);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT	- pin #A1
  // HX711.PD_SCK	- pin #A0
  // scale.begin(A1, A0);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  //  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  // Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  //  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  // Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  // scale.set_scale(224.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  //  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  // Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  // Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  // Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Readings:");


  lcd.begin(16, 4);
}

void loop() {

  // WeightChanel=0;
  //Serial.print(F("Ch=\t"));
  //Serial.print (WeightChanel);

  switch (WeightChanel)

  {
    case 0:
      // ADC 0  INPUT 0

      if (!(PIND & 0x08))
      {
        CountL = 0;

        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x04;
          delayMicroseconds(WTACT);

          PORTC &= ~0x04;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x08)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x04;
        delayMicroseconds(WTACT);
        PORTC &= ~0x04;





        delayMicroseconds(WTACT);
        PORTC |= 0x04;
        delayMicroseconds(WTACT);
        PORTC &= ~0x04;

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
          CountW[0] /= 4280L;



          //  if(CountW[0]>0L)
          Pokaz[0] =   CountW[0] / 100.0;
          // else
          //  Pokaz[0]=0;

        }











        Serial.print("Sensor 0 Raw =\t");
        Serial.print(WeightZero[0]);
        Serial.print("\t");
        Serial.print( CountW[0]);
        Serial.print("\t  ");




        WeightChanel = 1;


      }
      // End of ADC 0   SENSOR 0 measurement
      break;


    case 2:
      // ADC 0  INPUT 1

      if (!(PIND & 0x08))
      {
        CountL = 0;

        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x04;
          delayMicroseconds(WTACT);

          PORTC &= ~0x04;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x08)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x04;
        delayMicroseconds(WTACT);
        PORTC &= ~0x04;




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
          CountW[1] /= 1083L; //26 for 20 kG



          //  if(CountW[0]>0L)
          Pokaz[1] =   CountW[1] / 100.0;
          // else
          //  Pokaz[0]=0;

        }











        Serial.print("Sensor 1 Raw =\t");
        Serial.print(WeightZero[1]);
        Serial.print("\t");
        Serial.print( CountW[1]);
        Serial.print("\t  ");




        WeightChanel = 3;


      }
      // End of B 0 measurement
      break;




    case 1:
      // ADC 1  INPUT 0

      if (!(PIND & 0x04))
      {
        CountL = 0;

        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x02;
          delayMicroseconds(WTACT);

          PORTC &= ~0x02;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x04)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x02;
        delayMicroseconds(WTACT);
        PORTC &= ~0x02;





        delayMicroseconds(WTACT);
        PORTC |= 0x02;
        delayMicroseconds(WTACT);
        PORTC &= ~0x02;

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
          CountW[2] /= 2200L;



          //  if(CountW[0]>0L)
          Pokaz[2] =   CountW[2] / 100.0;
          // else
          //  Pokaz[0]=0;

        }





        Serial.print("Sensor 2 Raw =\t");
        Serial.print(WeightZero[2]);
        Serial.print("\t");
        Serial.print( CountW[2]);
        Serial.print("\t  ");




        WeightChanel = 2;


      }
      // End of ADC 0   SENSOR 0 measurement
      break;


    case 3:
      // ADC 1  INPUT 1

      if (!(PIND & 0x04))
      {
        CountL = 0;

        for (j04 = 0; j04 < 24; j04++)
        {
          CountL = CountL << 1;
          PORTC |= 0x02;
          delayMicroseconds(WTACT);

          PORTC &= ~0x02;
          delayMicroseconds(WTACT / 2);
          if (PIND & 0x04)
            CountL++;

          delayMicroseconds(WTACT / 2);

        }
        PORTC |= 0x02;
        delayMicroseconds(WTACT);
        PORTC &= ~0x02;




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
          CountW[3] /= 1083L;



          //  if(CountW[0]>0L)
          Pokaz[3] =   CountW[3] / 100.0;
          // else
          //  Pokaz[0]=0;

        }











        Serial.print("Sensor 3 Raw =\t");
        Serial.print(WeightZero[3]);
        Serial.print("\t");
        Serial.println( CountW[3]);




        WeightChanel = 0;


      }
      // End of B 0 measurement
      break;





  }






  // Serial.print("one reading:\t");
  // Serial.println(1.259, 1);
  //Serial.print("\t| average:\t");
  //Serial.println(scale.get_units(10), 1);

  // scale.power_down();			        // put the ADC in sleep mode
  delay(100);
  //scale.power_up();


  lcd.clear();  // очищаем экран

  lcd.print("1: "); //
  lcd.print(Pokaz[0], 2);  //выводим данные о весе

  lcd.setCursor(9, 0) ;  // вторая строка
  lcd.print("2: "); //
  lcd.print(Pokaz[1], 2);  //выводим данные о весе

  lcd.setCursor(0, 1) ;  // вторая строка
  lcd.print("3: "); //
  lcd.print(Pokaz[2], 2);  //выводим данные о весе


  lcd.setCursor(9, 1) ;  // вторая строка
  lcd.print("4: "); //
  lcd.print(Pokaz[3], 2);  //выводим данные о весе


  //   lcd.print("Avrg: "); //
  //  lcd.print(scale.get_units(10), 1);  //выводим данные о весе
  //  lcd.print(" G");  //








}
