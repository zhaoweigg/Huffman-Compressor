// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "BitOutputStream.hpp"
#include <bitset>



//===================================================================//
//-----------------------BIT OUTPUT STREAM CPP-----------------------//
//===================================================================//


//---------------------------------------------------------------------------------//
//---------------------------------WRITE BIT FUNCTION------------------------------//
//---------------------------------------------------------------------------------//
// if bit is 1, shift the buffer and put the 1 in the least significant bit
// if bit is 0, just shift the buffer by one
// once the buffer is full, flush to ostream
void BitOutputStream::writeBit(int bit){
	bufi++;					//increment index
	if (bit == 1) {				//if bit is 1, shift buf and add 1 as least significant
		buf = (buf << 1) |  1;
		//cout << " hi \n";
	}
	else {					//if bit is 0, shift buf and add 0 as least significant bit
		buf = (buf << 1);
		//cout << " hello" << bit<<endl;
	}
	if (bufi >= 8) {			//once buffer is filled, flush to the ostream
		flush();
	}	
}

//---------------------------------------------------------------------------------//
//---------------------------------WRITE BYTE FUNCTION-----------------------------//
//---------------------------------------------------------------------------------//
//shift the stream by 8 bits and place the byte in
void BitOutputStream::writeByte(int b) {
	buf = 0;			//set buf to 0
	bufi = 8;			//set bufi to 8
	buf = b;			//fill buf with the input variable b
	flush();			// flush to ostream
}


//---------------------------------------------------------------------------------//
//-------------------------------WRITE INTEGER FUNCTION----------------------------//
//---------------------------------------------------------------------------------//
// shift the stream by 16 bits and place the integer in
void BitOutputStream::writeInt(int i) {
	buf = 0;				// empty buffer
	for (int j=0; j < 4; j++) {		// fill buffer with byte four times and flush them in order of most to least significant bit 
		bufi = 8;
		buf = (i >> ((24-(8*j)))); 
		//cout<< j;
		flush();
	}

}


//---------------------------------------------------------------------------------//
//-----------------------------------FLUSH FUNCTION--------------------------------//
//---------------------------------------------------------------------------------//
// if there is anything in the buffer, place that number of bits into the ostream
//this function is used at the very end of compress to make sure we flush the last few bits of the file if 
//buffer still has stuff in it
void BitOutputStream::flush() {
	if (bufi < 8) {					// if buffer isnt full 
		buf = buf << (8 - bufi);		// shift buffer by the correct amount so that first interesting bit is in most significant spot
		//cout << (8 - bufi) << endl;
		//cout << " shifted\n";
	}
	//bitset<8> b(buf);
	//cout<<b<<endl;
	out.put(buf);					//put buffer into the ostream
	bufi = 0;					//reset bufi to 0
	buf ^= buf;					//clear buffer
}



