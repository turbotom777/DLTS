/*
 *
 *
 *                     Win32 include file
 *          for hardware constants
 *
 *
 *         Contains user variables
 *
 *
 *
 */

#ifndef DLTS_CONSTANTS_H       // ensure we are only included once
#define DLTS_CONSTANTS_H




#define TEMPERATURE_MAX 300.0 
#define TEMPERATURE_MIN 50.0

// hardware constants
// change if hardware has changed!

// boonton is connected to gpib0!
#define GPIB0 0
// primary address of boonton is 18
#define PRIMARY_ADDRESS_18 18


#define DEVICE_AT_MIO_16 1
#define DEVICE_PC_TIO_10 2


#define CHANNEL_0 0
#define DEFAULT_IN_CHANNEL 0 

#define COUNTER_1 1
#define COUNTER_2 2


#define NOT_DEFINED 0

#define SHOW_INFO true

// Update mode of AT_MIO out
#define WRITE_ON_UPDATE 0
#define WRITE_ON_CALL_AO_UPDATE 1
#define WRITE_ON_LOW_PULSE_ON_OUT2 2





// -1: apply configuration to all input channels!!!
#define CHANNEL_ALL -1
#define CHANNEL_0 0

// 0: differential configuration (DIFF)
#define INPUT_MODE_DIFF 0
// 1: Referenced Single-Ended (RSE)
#define INPUT_MODE_RSE 1
// 2: Nonreferenced Single-Ended (NRSE)
#define INPUT_MODE_NRSE 2
			
											// 1: Referenced Single-Ended (RSE)
				
// 5: -2.5 to 2.5 or 0 to 5V
// 10: -5 to +5 or 0 to 10V
// 20: -10 to +10V							
#define INPUT_RANGE_0_5 5
#define INPUT_RANGE_0_10 10
#define INPUT_RANGE_MINUS_10_PLUS_10 20
	

// 0: bipolar (default)
// 1: unipolar
#define POLARITY_BIPOLAR 0
#define POLARITY_UNIPOLAR 1

// settings vor DAQ/AI_VScale
// 1: not adjustment
#define GAIN_ADJUSTMENT 1.0
// 0: no offset
#define SCALE_OFFSET 0.0


// 0: no external multiplexer
// 1,2,4: number of AMUX-64T boards connected
#define NO_EXTERNAL_MULTIPLEXER 0


// 0: generate software trigger
// 1: wait for external trigger at STARTTRIG (MIO-16)
#define SOFTWARE_TRIGGER 0
#define EXTERNAL_TRIGGER 1


// 0: use onbaord clocks to controll data acquesition sample interval
// 1: allow external clock to control sample inverval
// 2: allow external clock to control scan-interval timing
#define INTERNAL_CLOCK 0



#define DISABLE_PRETRIGGER 0

#define POINTS_0 0
	
// 0: disable double buffer mode (default)
#define DISABLE_DOUBLE_BUFFER_MODE 0
// 1: enable double buffer
#define ENABLE_DOUBLE_BUFFER_MODE 1

// 0: internal reference; 
// 1: external reference
#define INTERNAL_REFERENCE 0

// analog output channel voltage reference value; range -10 to +10 
#define REFERENCE_VOLTAGE_MINUS_10_PLUS_10 10


// 0: count rising edge
// 1: count falling edge 
#define COUNT_RISING_EDGE 0

#define NO_GATING_USED 0

// 0: TC toggled output
// 1: TC pulse output
#define OUT_TYPE_TOGGLE 0
#define OUT_TYPE_PULSE 1


// 0: positive logic output
// 1: negative logic output (inverted)
#define NEGATIVE_LOGIC_OUTPUT 1

// 0: cancel reservation for counters in list
// 1: reserve counters in list for simulanous start, restart, stop, ....
// 2: perform simultanous start/restart on counters...
// 3: perform simultanous stop
#define CANCEL_RESERVE_FOR_SIMULTANOUS_START_STOP 0
#define RESERVE_FOR_SIMULTANOUS_START_STOP 1
#define PERFORM_SIMULTANOUS_START 2
#define PERFORM_SIMULTANOUS_STOP 3


// 0: high impedance
// 1: low logic out
// 2: high logic out
#define LOGIC_HIGH_OUT 2


// (*Volt=Driftdifferenz/2048*1 * 100 Volt = 48 millivolt *)
#define MAX_DRIFT_DIFFERENCE 100 
// resolution is 12 bit ->  4096 -> 4096/2 = 2048 -> 1V/2048 = 0.000488V
#define MAX_SAMPLE_VALUE 2048

// interval of each new sample: timebase * SAMPLE_INTERVAL z.B. 1탎 * 10 = 10탎
#define SAMPLE_INTERVAL 10 	


#define ABORT_VALUE -9999990

// maximum number of recorded samples -> number * 10탎 = 100ms
#define MAX_MEMORY_ELEMENTS 10000

// default number of recorded samples -> number * 10탎 = 20ms
#define DEFAULT_NUMBER_OF_SAMPLES 2000


// 0: from handle to array
// 1: from array to handle
#define COPY_DIRECTION_TO_ARRAY 0

#define ELEMENT_SIZE_2 2


#define TEMPERATURE_DEVIANCE_MAX 0.1f
#define ERROR_VALUE -9999999
#define ABORT_VALUE -9999990
// 1 seconds
#define CHECK_INTERVAL 1 


// 0: host or XMS memory
// 1: host memory (DOS, DOS16M...)
// 2: XMS memory
#define MEMORY_TYPE_HOST 1

// 0 or 2: memory of first 16MB
// 1: XMS memory
#define MEMORY_SOURCE_FIRST_16MB 0



#define DAQ_NO_TRANSFER_IN_PROGRESS_ERROR -10608
#define DAQ_NO_ERROR 0

// 1: timebase 1 MHz
// 2: timebase 10 MHz
// ... see NIDAQ docu

#define TIMEBASE_INDEX 1		

#define REGISTRY_SECTION "FH Munich"
#define FILE_VERSION 1.3f


















#endif   // DLTS_CONSTANTS_H

