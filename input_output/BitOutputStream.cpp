// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "BitOutputStream.hpp"
#include <bitset>

//=====================================================================//
//-----------------------BIT OUTPUT STREAM CPP-------------------------//
//=====================================================================//


//---------------------------------------------------------------------------------//
//-------------------------------WRITE BIT FUNCTION--------------------------------//
//---------------------------------------------------------------------------------//
// if bit is 1, shift the buffer and put the 1 in the least significant bit
// if bit is 0, just shift the buffer by one
// once the buffer is full, flush to ostream
void BitOutputStream::writeBit(int bit){
	bufi++;
	if (bit == 1) {
		buf = (buf << 1) |  1;
	}
	else {
		buf = (buf << 1);
	}
	if (bufi >= 8) {
		bufi = 0;
		flush();
	}	
}


//---------------------------------------------------------------------------------//
//--------------------------------WRITE BYTE FUNCTION------------------------------//
//---------------------------------------------------------------------------------//
//shift the stream and by 8 bits and place the byte in
void BitOutputStream::writeByte(int b) {
	
}


//---------------------------------------------------------------------------------//
//-------------------------------WRITE INTEGER FUNCTION----------------------------//
//---------------------------------------------------------------------------------//
// shift the stream by 16 bits and place the integer in
void BitOutputStream::writeInt(int i) {
	
}

//---------------------------------------------------------------------------------//
//-----------------------------------FLUSH FUNCTION--------------------------------//
//---------------------------------------------------------------------------------//
// if there is anything in the buffer, place that number of bits into the ostream
void BitOutputStream::flush() {
	bitset<8> b(buf);
	cout<<b<<endl;
	out.put(buf);
	bufi = 0;
}



