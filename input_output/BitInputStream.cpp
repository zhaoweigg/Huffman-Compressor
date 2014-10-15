// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "BitInputStream.hpp"
#include <bitset>
//---------------------------------------------------------------------------------//
//-------------------------------------READ BIT------------------------------------//
//---------------------------------------------------------------------------------//
int BitInputStream::readBit(){
	if (bufi == 8) {	
		in.get(buf);
                //bitset<8> b(buf);
                //cout<< b <<endl;
	}
	if (bufi != 0) {
		--bufi;
                int a = (buf>>bufi) & 1;
                if(bufi==0)
			bufi = 8;
		//cout<<( (buf>>bufi) & 1) <<" ";
		return a;
	}

}
//int BitInputStream::readByte(){
//}

//int BitInputStream::readInt(){
//}
