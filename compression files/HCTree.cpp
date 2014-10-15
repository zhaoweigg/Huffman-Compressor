// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "HCTree.hpp"
#include <stack>
using namespace std;

//=====================================================================//
//-------------------------------HC TREE CPP---------------------------//
//=====================================================================//


//---------------------------------------------------------------------------------//
//-----------------------------------DESTRUCTOR------------------------------------//
//---------------------------------------------------------------------------------//
HCTree::~HCTree() { //delete the root
	delete root;
}

//---------------------------------------------------------------------------------//
//-----------------------------------BUILD FUNCTION--------------------------------//
//---------------------------------------------------------------------------------//
    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
void HCTree::build(const vector<int>& freqs) {

	//creates leaf for each symbol that has a frequnecy greater than 0.
	//also  puts this leaf( pointer to a node) into leaves vector
	//also pushes leaf into priority queue
	priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
	for (int i = 0; i < 256 ; i++) {
		if (freqs[i] != 0) { 
			HCNode* leaf = new HCNode(freqs[i], i);
			leaves[i] = leaf;
			pq.push(leaf);
		}
	}
	if (pq.empty()) {					// for special case when the file is empty. set root to 0 and return
		root = 0;
		return;
	}

	HCNode* node;					
	if (pq.size() == 1) {					// if theres only one symbol in the file, add a dummy node so original algorithm still works
		pq.push(new HCNode(0,0));
	}

	while (pq.size() > 1) {					// as long as there are 2 or more leaves in the priority queue
		HCNode* leaf0 = pq.top();			//create dummy to store first leaf
		pq.pop();				
		HCNode* leaf1 = pq.top();			//create dummy to store 2nd leaf
		pq.pop();
	
		node = new HCNode(0,0);				//create new node which will be the parent of the two leaves
		if (leaf0->symbol < leaf1->symbol) {		// if first dummy leaf has smaller symbol, make it c0
			node->c0 = leaf0;
			node->c0->p = node;			//make sure leaf also knows new node is its parent
			node->c1 = leaf1; 
			node->c1->p = node;			
		}
		else {						// if 2nd dummy leaf has smaller symbol, make it c0
			node->c1 = leaf0;
			node->c1->p = node;			// make sure leaf also knows new node is its parent
			node->c0 = leaf1; 
			node->c0->p = node;
		}	
		node->symbol = node->c0->symbol;		// give the new node the c0's symbol
		node->count = (node->c0->count) + (node->c1->count);		//give new node the sum of the two leaves' counts
		pq.push(node);							// put new node back into the priority queue
	}

	root = pq.top();					// after there is only one node ptr left in the priority queue, make it the root
	pq.pop();
}
//---------------------------------------------------------------------------------//
//--------------------------------ENCODE FUNCTION----------------------------------//
//---------------------------------------------------------------------------------//
    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
void HCTree::encode(byte symbol, BitOutputStream& out) const {		//read the original file and re-write it into output stream using new symbols
	stack<int> stac;						//create a stack 
	HCNode* leaf = leaves[symbol];					//find the pointer to a leaf using the vector we stored all the symbols into
	while(leaf != root) {						// loop as long as we aren't at the root
	//while(1) {
		//if (leaf->p == 0) {		
		//break;
		//}
		if (leaf->p->c0 == leaf) {				// if leaf is a c0 child, push 0 into stack
			stac.push(0);
			//cout<< " i pushed a zero. sorry\n";
		}
		else {							// if leaf is a c1 child, push 1 into the stack
			stac.push(1);
		}
		leaf = leaf->p;						// move up to its parent
	}
	while (!stac.empty()) {						// while the stack isnt empty, write top bit in the stack into outputstream
		out.writeBit(stac.top());
		//cout <<stac.top()<<endl;
		stac.pop();
	}
	//out.flush();
}




//---------------------------------------------------------------------------------//
//--------------------------------DECODE FUNCTION----------------------------------//
//---------------------------------------------------------------------------------//
    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
int HCTree::decode(BitInputStream& in) const {

	HCNode* voyager = root;				//create an iterator to go down the tree till we find the leaf of interest
	//int i = in.readBit();
	while(1) {					//infinite loop
		int i = in.readBit();			//make i into the next bit in the stream
		if (i == 1) {				// if i is 1, make iterator go to c1
			voyager = voyager->c1;
		}
		else {					// else , make iterator go to c0
			voyager = voyager->c0;
		}
		if (voyager->c0 == 0 && voyager->c1 == 0) {			// if the iterator has no c0 and c1, we are at a leaf. return its symbol
			return voyager->symbol;
		} 
	}
}




