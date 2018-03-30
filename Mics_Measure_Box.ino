//https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806
// DHT librry & examples: https://github.com/adafruit/DHT-sensor-library/blob/master/examples/DHTtester/DHTtester.ino

//TODO: alter smiley at wassertemp
//TODO: say hi msges

//TODO HW: add on off switch
//TODO HW: add displ poti
//TODO HW: turn usb akku um 180*
//TODO HW: use 90* abgeknickter usb stecker mit schrumpfschlauch
//TODO HW: add push button



#include "Arduino.h"
#include "LiquidCrystal.h" //Load Liquid Crystal Library

#include "OneWire.h"
#include "DallasTemperature.h"
#include "dht.h"

#define SHORT_DELAY 250
#define MID_DELAY 500
#define LONG_DELAY 3000
#define FALSE 0
#define TRUE 1

#define BUTTON_PIN 7
#define DHT11_PIN 8
#define ONE_WIRE_BUS 9
#define TEMPERATURE_PRECISION 9

#define ALL_SENSORS_ATT 0
#define NO_LIQ_SENSOR_ATT 1
#define NO_DHT_SENSOR_ATT 2
#define NO_SENSOR_ATT 3

#define DHT_FULLY_AVAILABLE 0
#define DHT_PARTIALLY_AVAILABLE 1
#define DHT_NOT_AVAILABLE 2

#define SMILEY 0
#define BIG_SMILEY 1
#define SMILEY_STAUNT 5
#define SMILEY_CROSS 6
#define HEART 2
#define DEGREE 3
#define TVR_E 4

#define SMILEY_TEMP 35
#define SMILEY_STAUNT_TEMP 38
#define SMILEY_CROSS_TEMP 55
#define ABOVE_LIMITS_TEMP 80

#define DHT11_SENSOR 0
#define DS18B20_SENSOR 1

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);  //Create Liquid Crystal Object called LCD

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);
DHT dht(DHT11_PIN, DHT11);

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address
//Variables to 3 sensor addresses
DeviceAddress DS18B20;

//temp var
float DHT11_temp;
float DHT11_humid;
int DHT11_available;
float DS18B20_temp = 0;

int alertMsgGuard = TRUE;
int sayHiGuard   = TRUE;
int ds18b20SmileyGuard = TRUE;

//new display chars
byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00100,
  B00100,
  B10001,
  B01110,
};

byte big_smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B11111,
  B10001,
  B01110,
};

byte smiley_staunt[8] = {
  B11011,
  B11011,
  B00000,
  B00100,
  B01010,
  B01010,
  B00100,
};

byte smiley_cross[8] = {
  B11011,
  B11011,
  B00000,
  B00000,
  B01010,
  B00100,
  B01010,
};

byte heart[8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B01010,
  B00100,
};

byte degree[8] = {
  B00000,
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
};

byte tvr_e[8] = {
  B01010,
  B00000,
  B01110,
  B10001,
  B11111,
  B10000,
  B01110,
};

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  LCD.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD
  //(LCD.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  LCD.createChar(0, smiley);
  LCD.createChar(1, big_smiley);
  LCD.createChar(2, heart);
  LCD.createChar(3, degree);
  LCD.createChar(4, tvr_e);
  LCD.createChar(5, smiley_staunt);
  LCD.createChar(6, smiley_cross);
  ds18b20.begin();
  //ds18b20.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  checkButtonState();

  if ( TRUE == sayHiGuard ) { sayHiGuard = sayHi();  }

  ds18b20.requestTemperatures(); // Send the command to get temperature readings

  DHT11_humid = dht.readHumidity();
  DHT11_temp = dht.readTemperature(false);

  if ( DHT_FULLY_AVAILABLE == dhtAvailable(DHT11_temp, DHT11_humid) )
  {
    if ( ds18b20.getAddress(DS18B20,0) )
    {
      alertMsgGuard  = showMessage (ALL_SENSORS_ATT, alertMsgGuard);

      DS18B20_temp = ds18b20.getTempCByIndex(0);

      LCD.setCursor(0,0);
      LCD.print("Temp Humid Liqui");
      LCD.setCursor(0,1);
      LCD.print (eineNachkommaStelle(DHT11_temp, DHT11_SENSOR));
      LCD.print(" ");
      LCD.print(eineNachkommaStelle(DHT11_humid, DHT11_SENSOR));
      LCD.print("%  ");
      LCD.print(eineNachkommaStelle(DS18B20_temp, DS18B20_SENSOR));
    }
    else
    {
      alertMsgGuard  =  showMessage (NO_LIQ_SENSOR_ATT, alertMsgGuard);

      LCD.setCursor(0,0);
      LCD.print("Temp     Feuchte");
      LCD.setCursor(0,1);
      LCD.print (eineNachkommaStelle(DHT11_temp, DHT11_SENSOR));
      LCD.write(byte(DEGREE));
      LCD.print("C    ");
      LCD.print(eineNachkommaStelle(DHT11_humid, DS18B20_SENSOR));
      LCD.print(" %");
    }
  }
  else if ( DHT_FULLY_AVAILABLE != dhtAvailable(DHT11_temp, DHT11_humid) )
  {
    if ( ds18b20.getAddress(DS18B20,0) )
    {
      alertMsgGuard  = showMessage (NO_DHT_SENSOR_ATT, alertMsgGuard);

      //ds18b20.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
      DS18B20_temp = ds18b20.getTempCByIndex(0);

      //LCD.clear();
      LCD.setCursor(0,0);
      LCD.print("Wassertemperatur");
      LCD.setCursor(0,1);
      LCD.print("         ");
      LCD.print(eineNachkommaStelle(DS18B20_temp, DS18B20_SENSOR));

      if (TRUE == ds18b20SmileyGuard)
      {
        LCD.write(byte(DEGREE));
        LCD.print("C");
      }
      else
      { LCD.print("  ");  }
    }
    else
    {
      alertMsgGuard  = showMessage (NO_SENSOR_ATT, alertMsgGuard);
    }
  }

   delay(MID_DELAY);

   //debugOutput(DHT11_temp, DHT11_humid, DS18B20_temp);
}

void debugOutput (float dht11_temp, float dht11_humid, float ds18b20_temp)
{
  Serial.println("DHT11 Temp: " + String(dht11_temp));
  Serial.println("DHT11 Humid: " + String(dht11_humid));
  Serial.println("DS18B20 Temp: " + String(ds18b20_temp));
}

int sayHi ()
{
  long msgCount = 12;
  long msgToShow;

  msgToShow = random(0, msgCount-1);
  Serial.print(msgToShow);

  LCD.setCursor(0,0);

  switch (msgToShow)
  {
    case 0:
      LCD.print(" The Volcha Ra");
      LCD.write(byte(TVR_E));
      LCD.print(" ");
      LCD.setCursor(0,1);
      LCD.print("   ");
      LCD.write(byte(HEART));
      LCD.print("   you !   ");
      break;
    case 1:
      LCD.print(" Sch");
      LCD.write(0xEF);
      LCD.print("n, dass es ");
      LCD.setCursor(0,1);
      LCD.print("   Euch gibt!   ");
      break;
    case 2:
      LCD.print(" Sch");
      LCD.write(0xEF);
      LCD.print("n, dass es ");
      LCD.setCursor(0,1);
      LCD.print("   uns gibt !   ");
      break;
    case 3:
      LCD.print("Hi.");
      break;
    case 4:
      LCD.print(" Wir haben Euch ");
      LCD.setCursor(0,1);
      LCD.print("    lieb    ");
      break;
    case 5:
      LCD.print("Shooohoooow me a");
      LCD.setCursor(0,1);
      LCD.print("deeeper wehell..");
      break;
    case 6:
      LCD.print(" I don't belong ");
      LCD.setCursor(0,1);
      LCD.print(" to Superheroes ");
      break;
    case 7:
      LCD.print(" Aye Sir! Womit ");
      LCD.setCursor(0,1);
      LCD.print("kann ich dienen?");
      break;
    case 8:
      LCD.print(" Moin, was geht ");
      LCD.setCursor(0,1);
      LCD.print("    Meiner ?    ");
      break;
    case 9:
      LCD.print(" Moin, was geht ");
      LCD.setCursor(0,1);
      LCD.print("    Meine  ?    ");
      break;
    case 10:
      LCD.print(" You are a Star ");
      LCD.setCursor(0,1);
      LCD.print("and I am glad...");
      break;
    case 11:
      LCD.print("Ahoi! Du Fotzen-");
      LCD.setCursor(0,1);
      LCD.print("    knecht !    ");
      break;
  }

  delay (LONG_DELAY);

  return FALSE;
}



String eineNachkommaStelle (float input, int sensortype)
{
  static char outstr[6];

  if (DS18B20_SENSOR == sensortype)
  {
    if ( (SMILEY_TEMP <= DS18B20_temp) && (SMILEY_STAUNT_TEMP >= DS18B20_temp) )
      {
        if (showSmiley(byte(BIG_SMILEY), outstr))
        { return outstr;  }
      }
    else if ( (SMILEY_STAUNT_TEMP < DS18B20_temp) && (SMILEY_CROSS_TEMP >= DS18B20_temp) )
      {
        if (showSmiley(byte(SMILEY_STAUNT), outstr))
        { return outstr;  }
      }
    else if ( (SMILEY_CROSS_TEMP < DS18B20_temp) && (ABOVE_LIMITS_TEMP >= DS18B20_temp) )
      {
        if (showSmiley(byte(SMILEY_CROSS), outstr))
        { return outstr;  }
      }
  }

  dtostrf(input,4, 1, outstr);
  return outstr;
}

int showSmiley (byte _smileyChar, char* _outstr)
{
  if (TRUE == ds18b20SmileyGuard)
  {
    ds18b20SmileyGuard  = FALSE;
    _outstr[0] = ' ';
    _outstr[1] = ' ';
    _outstr[2] = ' ';
    _outstr[3] = _smileyChar;
    _outstr[4] = '\0';
    return TRUE;
  }
  else
  {
    ds18b20SmileyGuard  = TRUE;
    return FALSE;
  }
}

//ret: false = dont show nother message, true = show another message
int showMessage (int indicator, int _alertMsgGuard)
{
  switch (indicator)
  {
    case ALL_SENSORS_ATT:
      return (show ("Setup OK, alle ", "Sensoren i. O. !", _alertMsgGuard) );
    case NO_LIQ_SENSOR_ATT:
      //char str1[16];
      //strcpy(str1, "Kein Sensor f");
      //strcat(str1, '0x5F');
      //strcat(str1, "r");
      //return ( show (String(str1), "Wassertemperatur", _alertMsgGuard) );
      return ( show ("Kein Sensor fuer", "Wassertemperatur", _alertMsgGuard) );
    case NO_DHT_SENSOR_ATT:
      //char str2[16];
      //strcpy(str2, "Kein Sensor f");
      //strcat(str2, '0x5F');
      //strcat(str2, "r");
      //return ( show (String(str2), " Temp & Feuchte ", _alertMsgGuard) );
      return ( show ("Kein Sensor fuer", " Temp & Feuchte ", _alertMsgGuard) );
    case NO_SENSOR_ATT:
      show ("Kein Sensor vor-", "handen. Du Sack!", _alertMsgGuard);
      return TRUE;    //keep showing message as long as there is no sensor attached
    //default:
  }
}

int show (String firstLine, String secLine, int __alertMsgGuard)
{
  if (__alertMsgGuard == TRUE)
  {
    LCD.setCursor(0,0);
    LCD.print(firstLine);
    LCD.setCursor(0,1);
    LCD.print(secLine);
    delay(3000);
    __alertMsgGuard = FALSE;
  }

  return __alertMsgGuard;
}

int dhtAvailable (float temp, float humid)
{
  if (isnan(temp) && isnan(humid))
  { return  DHT_NOT_AVAILABLE;  }
  if (false == temp || false == humid)    //checksum error
  { return  DHT_NOT_AVAILABLE;  }
  else if (isnan(temp) || isnan(humid))
  { return  DHT_PARTIALLY_AVAILABLE;  }
  else
  { return DHT_FULLY_AVAILABLE; }
}

void checkButtonState ()
{
  // read the state of the pushbutton value:
  int buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH)
  {
    Serial.println("Button_psuhed");
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.write(byte(BIG_SMILEY));
    delay(500);
  }
}
