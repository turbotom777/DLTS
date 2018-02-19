#include "stdafx.h"
#include "dataHandler.h"
#include "wdaq_c.h"
#include "nidaqcns.h"
#include "math.h"


DataHandler::DataHandler(void)
{
	m_isMemLocked = false;
	m_isMemAlloced = false;
}

DataHandler::~DataHandler(void)
{
	
	if (m_isMemLocked){
		NI_DAQ_Mem_Unlock (m_handle);
	}
	if (m_isMemAlloced){
		NI_DAQ_Mem_Free (m_handle);
	}
}


int DataHandler::initMemory(){


	//Heapmax(speichermax);	// Ermittelt den Maximalen Speicherplatz auf dem Heap und vergleicht ihn*)
							//  mit dem zu vereinbarendem Speicherplatz *)


	const int elementSize = 2;		// number of elements in an array
	const int memType = 1;			// 0: host or XMS memory
									// 1: host memory (DOS, DOS16M...)
									// 2: XMS memory
// TODO: check memory type!!!
	const int sourceType = 0;		// 0 or 2: memory of first 16MB
									// 1: XMS memory

	int status = NI_DAQ_Mem_Alloc (&m_handle, elementSize, MAX_MEMORY_ELEMENTS, memType, sourceType);
                            // Vereinbarung eines 2 Byte * Speichermax (=131 080) großen Feldes*)
                            // Bei Status=0 war die Vereinbarung des Feldes erfolgreich *)
                            // In Handle steht der Zeiger auf den Feldzeiger *)

	if (status >= 0){
		m_isMemAlloced = true;
	}

	if (status != 0){		
		console.writeln("NI_DAQ_Mem_Alloc FEHLER NUMMER  %d", status) ;
		return status;
	}

	// was address before!!! 
	// BUT: function expects unsigned long, but address is short!!!!
	status = NI_DAQ_Mem_Lock (m_handle, &m_lockedHandle); // Festlegen des Feldes und Übergabe eines Handles darauf

	if (status >= 0){
		m_isMemLocked = true;
	}


	if (status != 0){
		console.writeln("NI_DAQ_Mem_Alloc FEHLER NUMMER  %d", status);
		/*
		writeln("Das Programm wird bis zur eingabe eines Zeichens angehalten.");
		char halt;
		cin >> halt;  
		*/
		return status;
	}
	return status;
}



void DataHandler::copyData(short *resultArray, int nullification)
{
	short field[MAX_MEMORY_ELEMENTS];

	const short COPY_DIRECTION = 0;
	// 0: from handle to array
	// 1: from array to handle

	int status = NI_DAQ_Mem_Copy (m_handle, field, 0, MAX_MEMORY_ELEMENTS, COPY_DIRECTION);
	 // Kopiert Element Nr.1..32767 in Feld 1*)
	if (status != 0) {
		console.writeln("NIDAQ MEM COPY FELD  FEHLER NUMMER %d",status);
	}


	int resultIndex = 0;
	int memoryIndex = 0;
	int nextMemIndex = 0;
	int distance = 1;

	/*
	for (int i = 0; i < RESULT_FIELD_SIZE; i++){
		resultArray[i] = field[i];
	}
	*/


	int power = 1;
	// do logarithmic data reduction 
 	while (true) {
		for (int n = 0; n < 128; n++){				
			resultArray[resultIndex] = ((short) field[memoryIndex]); // - nullification; 
			resultIndex++;

			if (memoryIndex >=  MAX_MEMORY_ELEMENTS || resultIndex > RESULT_FIELD_SIZE){
				return;
			}
			memoryIndex += distance;
		}
		distance = pow(2, power++);
	}


	//end ;(*Datenreduktion*)

}


unsigned long DataHandler::getMemoryHandle(){
	return m_lockedHandle;
}

/*
void DataHandler::copyData(short *messpunktfeld1, int nullification)
{
	const unsigned long NUM_ELEMENTS = 32767;
	short field1[NUM_ELEMENTS];
	short field2[NUM_ELEMENTS];
 	short field3[NUM_ELEMENTS];
 	short field4[NUM_ELEMENTS];

	const short COPY_DIRECTION = 0;
	// 0: from handle to array
	// 1: from array to handle

	// Umkopieren der Messwerte in Felder mit je 64k Speicherplatz*)
	unsigned long startIndex = 0;
	int status = NI_DAQ_Mem_Copy (m_handle, field1, startIndex, NUM_ELEMENTS, COPY_DIRECTION);
	 // Kopiert Element Nr.1..32767 in Feld 1*)
	if (status != 0) {
		console.writeln("NIDAQ MEM COPY FELD1  FEHLER NUMMER %d",status);
	}

	startIndex+=NUM_ELEMENTS;
	status = NI_DAQ_Mem_Copy (m_handle, field2, startIndex, NUM_ELEMENTS, COPY_DIRECTION);
	// Kopiert Element Nr.32768..65534 in Feld 2*)
	if (status != 0){
		console.writeln("NIDAQ MEM COPY FELD2  FEHLER NUMMER %d",status);
	}

	startIndex+=NUM_ELEMENTS;
	status = NI_DAQ_Mem_Copy (m_handle, field3, startIndex, NUM_ELEMENTS, COPY_DIRECTION);
	// Kopiert Element Nr.65535..98301 in Feld 3*)
	if (status != 0){
		console.writeln("NIDAQ MEM COPY FELD3  FEHLER NUMMER %d",status);
	}

	startIndex+=NUM_ELEMENTS;
	status = NI_DAQ_Mem_Copy (m_handle, field4, startIndex, NUM_ELEMENTS, COPY_DIRECTION);
	// Kopiert Element Nr.98302..131068 in Feld 4*)
	if (status != 0){
		console.writeln("Status NIDAQ MEM COPY FELD4  FEHLER NUMMER %d",status);	
	}
	// Ende Umkopieren *)

	int anzahl = 0;
	int abstand = 1;

	// data reduction! TODO!
	for (int i=0; i< 10; i++){
	// begin (*Datenreduktion*)

		for (int index = 0; index < 128; index++){

		// begin(*Datenreduktion*)

			if ((index*abstand) <= 32767){

			   // begin(*Mittelwertbildung*)
			   messpunktfeld1[anzahl] = (messpunktfeld1[anzahl]+field1[index*abstand])-nullification;
			   //end;(*Mittelwertbildung*)
			}

			if (index*abstand>32767 && index*abstand<=65534){
			   //begin(*Mittelwertbildung*)
			   messpunktfeld1[anzahl] =(messpunktfeld1[anzahl]+field2[((index*abstand)-32767)])-nullification;
			   //end; (*Mittelwertbildung*)
			}

			if (index*abstand>65534 && index*abstand<=98301){
			   //begin(*Mittelwertbildung*)
			   messpunktfeld1[anzahl]=(messpunktfeld1[anzahl]+field3[((index*abstand)-65534)])-nullification;
			   //end; (*Mittelwertbildung*)
			}

			if (index*abstand>98301 && index*abstand<=131068){

			   //begin(*Mittelwertbildung*)
			   messpunktfeld1[anzahl]=(messpunktfeld1[anzahl]+field4[((index*abstand)-98301)])-nullification;
			   //end; (*Mittelwertbildung*)
			}

			anzahl++;
		}

		//end ;(*Datenreduktion*)
		abstand = abstand*2;
	}
	//end ;(*Datenreduktion*)
}
*/

