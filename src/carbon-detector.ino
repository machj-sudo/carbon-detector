/************************************************
 * Libaries
 ************************************************/
#include <MQ2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/************************************************
 * Macros
 ************************************************/
#define NLEN(x)  (sizeof(x) / sizeof((x)[0]))

/************************************************
 * Memory/Pin Constants
 ************************************************/
#define ANALOG_IN A0
#define REFRESH_RATE 300

/************************************************
 * Types
 ************************************************/
struct Levels {
  const char* status;
  const int max_co_value;
};

/************************************************
 * Declarations
 ************************************************/
LiquidCrystal_I2C lcd( 0x27, 16, 2 );
MQ2 mq2( ANALOG_IN );

const static Levels carbon_levels[] = {
  { "Healthy",            50 },
  { "Fatigue & Conc.",    75 },
  { "Warning",            150 },
  { "Get Fresh Air",      200 },
  { "Physical Sympt.",    400 },
  { "Fatal",              1600 }
};

/************************************************
 * Setup
 ************************************************/
void setup() {
  // Initialize the Serial connection
  Serial.begin( 9600 );

  // Setup the Liquid Crystal display
  lcd.begin();
  lcd.backlight();

  // Setup the MQ-2 gas sensor
  mq2.begin();
}


/************************************************
 * Driver
 ************************************************/
void loop() {
  // Clear the LCD display
  lcd.clear();
  int air_quality = analogRead( ANALOG_IN );

  lcd.setCursor( 0, 0 );

  // Carbon Monoixde
  lcd.print("Carbon: ");
  lcd.print( air_quality );
  lcd.print(" PPM");

  // Second line on the LCD
  lcd.setCursor( 0, 1 );

  // Determine air quality and suggestive actions
  if ( air_quality <= carbon_levels[0].max_co_value ) {
    lcd.print( carbon_levels[0].status );
  }
  else if ( air_quality > carbon_levels[0].max_co_value && air_quality <= carbon_levels[1].max_co_value ) {
    lcd.print( carbon_levels[1].status );
  }
  else if ( air_quality > carbon_levels[1].max_co_value && air_quality <= carbon_levels[2].max_co_value ) {
    lcd.print( carbon_levels[2].status );
  }
  else if ( air_quality > carbon_levels[2].max_co_value && air_quality <= carbon_levels[3].max_co_value ) {
    lcd.print( carbon_levels[3].status );
  }
  else if ( air_quality > carbon_levels[3].max_co_value && air_quality <= carbon_levels[4].max_co_value ) {
    lcd.print( carbon_levels[4].status );
  }
  else {
    lcd.print( carbon_levels[5].status );
  }

  delay( REFRESH_RATE );
}