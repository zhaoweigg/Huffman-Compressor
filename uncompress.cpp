// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include <fstream> 
#include <vector>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include <stack>
using namespace std;


//=====================================================================//
//---------------------------MAIN UNCOMPRESS---------------------------//
//=====================================================================//
/** Count and output the number of times char occurs in
* a file named by the first command line argument. */
int main(int argc, char** argv) {

//open input file for reading
	ifstream in;
	in.open(argv[1], ios::binary); 
	unsigned char buffer;
	int recount = 0;
	int totalsymbol = 0;


//---------------------------------------------------------------------------------//
//---------------------------------READ HEADER ------------------------------------//
//---------------------------------------------------------------------------------//
	vector<int> frequency(256, 0);
	for (int i = 0; i < 256 ; i++) {
		recount = 0;
		for (int j = 0; j < 4; j++) {					
			buffer = in.get();   
			recount = recount | (buffer << (24 - 8*j));
			//cout << j << recount << endl;
		}
		frequency[i] = recount;
		totalsymbol = totalsymbol + recount;
		//cout << i << " " << recount<< " " << totalsymbol<< endl;
	}
	HCTree hct;
	hct.build(frequency);

//---------------------------------------------------------------------------------//
//--------------------------------DECODE FILE--------------------------------------//
//---------------------------------------------------------------------------------//
//open output file for writing and decode	
	BitInputStream bitin(in);
	ofstream out;
	out.open(argv[2], ios::binary);
	BitOutputStream bitout(out);
	for (totalsymbol; totalsymbol > 0 ; totalsymbol--) {
		bitout.writeByte(hct.decode(bitin));
	}
//close input and output files
	in.close();
	out.close();
	return 0;
	//	hct.decode(bitin);
	

}
