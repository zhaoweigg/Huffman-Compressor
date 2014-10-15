// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "BitInputStream.hpp"
#include <bitset>


//===================================================================//
//-----------------------BIT INPUT STREAM CPP------------------------//
//===================================================================//


//---------------------------------------------------------------------------------//
//--------------------------------------READ BIT FUNCTION--------------------------//
//---------------------------------------------------------------------------------//
int BitInputStream::readBit(){
	if (bufi == 8) {		// if buffer is empty, fill the buffer with next 8 bits
		in.get(buf);		
                //bitset<8> b(buf);
                //cout<< b <<endl;
	}
	if (bufi != 0) {		// if buffer isnt full
		--bufi;
                int a = (buf>>bufi) & 1; // a is the buffer shifted by buffer index and "anded" with 1
                if(bufi==0) {		// if buffer is full after decrementing, reset bufi
			bufi = 8;
		}
		//cout<<( (buf>>bufi) & 1) <<" ";
		return a;		// return the first bit-of-interest in buffer
	}

}


//---------------------------------------------------------------------------------//
//------------------------------------READ BYTE FUNCTION---------------------------//
//---------------------------------------------------------------------------------//
//didnt use this function
//int BitInputStream::readByte(){
//}


//---------------------------------------------------------------------------------//
//----------------------------------READ INTEGER FUNCTION--------------------------//
//---------------------------------------------------------------------------------//
//didn't use this function
//int BitInputStream::readInt(){
//	int intbuf = 0;	
//	in.get(buf);



//}
