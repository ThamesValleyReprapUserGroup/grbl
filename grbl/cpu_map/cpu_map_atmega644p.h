/*
  cpu_map_atmega328p.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Grbl officially supports the Arduino Uno, but the other supplied pin mappings are
   supplied by users, so your results may vary. This cpu_map file serves as a central
   pin mapping settings file for AVR 328p used on the Arduino Uno.  */
   
#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif


#define GRBL_PLATFORM "Atmega644p"

// Define serial port pins and interrupt vectors. *********CHECK THIS*********
#define SERIAL_RX     USART_RX_vect
#define SERIAL_UDRE   USART_UDRE_vect

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_DDR        DDRA
#define STEP_PORT       PORTA
#define X_STEP_BIT      3  
#define Y_STEP_BIT      4
#define Z_STEP_BIT      5
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
//*********CHECK Line above*********

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_DDR     DDRC
#define DIRECTION_PORT    PORTC
#define X_DIRECTION_BIT   7
#define Y_DIRECTION_BIT   6
#define Z_DIRECTION_BIT   5
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
//*********CHECK Line above*********

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR    DDRD
#define STEPPERS_DISABLE_PORT   PORTD
#define STEPPERS_DISABLE_BIT    2
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)
//*********CHECK Line above*********

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_DDR        DDRB
#define LIMIT_PIN        PINB
#define LIMIT_PORT       PORTB
#define X_LIMIT_BIT     0
#define Y_LIMIT_BIT      1
#define Z_LIMIT_BIT	2

#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
#define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect   PCINT0_vect 
#define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register
//*********CHECK 4 Lines above*********

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR    DDRB
#define SPINDLE_ENABLE_PORT   PORTB
  #define SPINDLE_ENABLE_BIT   3
#define SPINDLE_DIRECTION_DDR   DDRD
  #define SPINDLE_DIRECTION_PORT  PORTD
  #define SPINDLE_DIRECTION_BIT   6

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_DDR   DDRB
#define COOLANT_FLOOD_PORT  PORTB
#define COOLANT_FLOOD_BIT   4
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
  #define COOLANT_MIST_DDR   DDRD
  #define COOLANT_MIST_PORT  PORTD
  #define COOLANT_MIST_BIT   5
#endif  

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRA
#define CONTROL_PIN       PINA
#define CONTROL_PORT      PORTA
#define RESET_BIT         0
#define FEED_HOLD_BIT     1
#define CYCLE_START_BIT   2
#define SAFETY_DOOR_BIT   6  //  Enabled by config define.
#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK      ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.
//*********CHECK 5 Lines above*********
  
// Define probe switch input pin.
#define PROBE_DDR       DDRC
#define PROBE_PIN       PINC
#define PROBE_PORT      PORTC
#define PROBE_BIT       4
#define PROBE_MASK      (1<<PROBE_BIT)
//*********CHECK Line above*********

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  #define PWM_MAX_VALUE     255.0 // Don't change. 328p fast PWM mode fixes top value as 255.
  #define TCCRA_REGISTER	  TCCR2A
  #define TCCRB_REGISTER	  TCCR2B
  #define OCR_REGISTER      OCR2A
  #define COMB_BIT	        COM2A1
//*********CHECK 4 Lines above*********
  
  // 1/8 Prescaler, 8-bit Fast PWM mode. Translates to about 7.8kHz PWM frequency.
  #define TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))
  #define TCCRB_INIT_MASK   (1<<CS21)
//*********CHECK 2 Lines above*********
      
  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_DDR	  DDRB
  #define SPINDLE_PWM_PORT  PORTB
  #define SPINDLE_PWM_BIT	  3
#endif // End of VARIABLE_SPINDLE