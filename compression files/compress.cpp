// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include <fstream> 
#include <vector>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <stack>
using namespace std;


//---------------------------------------------------------------------------------//
//------------------------------MAKE HEADER FUNCTION-------------------------------//
//---------------------------------------------------------------------------------//
//this is a special function that we use to write the information we need
//to reconstruct the huffman encoding tree when uncompressing
void makeHeader(vector<int> freq, BitOutputStream& out) {
//write array of frequencies into the bitoutputstream	
	for (int i = 0; i < 256; i++ ) {
		//cout << i << freq[i];
		out.writeInt(freq[i]);
	}
}



//=====================================================================//
//-----------------------------MAIN COMPRESS---------------------------//
//=====================================================================//
/** Count and output the number of times char ’a’ occurs in
* a file named by the first command line argument. */
int main(int argc, char** argv) {
//open input file for reading
	ifstream in;
	in.open(argv[1], ios::binary); 
	char buffer;

	vector<int> frequency(256, 0);
//read bytes from the file, counting the number of occurrences of each 
//byte value; then close file
	while(1) {
		buffer = in.get();   
		if (!in.good()) break;
		int index = (unsigned char) buffer;     
	        frequency[index]++;
	}
	in.close();

//open output file for writing
	ofstream out;
	out.open(argv[2], ios::binary);
	BitOutputStream bitout(out);
//construct huffman coding tree using bytes from file
	HCTree hct;
	hct.build(frequency);
	in.open(argv[1], ios::binary);
//write enough information to output file to enable coding tree
//to be reconstructed when file is read
	makeHeader(frequency, bitout);
	
//using huffman coding tree, translate each byte from input to code
//and append code as sequence of bits to output after header
	while (1) {
		buffer = in.get();
		//cout << buffer<<endl;
		if (!in.good()) {
			break;
		}
		int index = (unsigned char) buffer;	
		hct.encode(index,bitout);
		//cout << " called encode \n";
	}
	bitout.flush();

//close input and output files
	in.close();
	out.close();

	return 0;
}
