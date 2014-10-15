// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;


//============================================================//
//--------------------HCNODE PTR COMP CLASS-------------------//
//============================================================//
/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

//============================================================//
//-----------------------HC TREE CLASS------------------------//
//============================================================//
/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    
public:
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }
//---------------------------------------------------------------------------------//
//-----------------------------------DESTRUCTOR------------------------------------//
//---------------------------------------------------------------------------------//
    ~HCTree();

//---------------------------------------------------------------------------------//
//-----------------------------------BUILD-----------------------------------------//
//---------------------------------------------------------------------------------//
    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);
//---------------------------------------------------------------------------------//
//------------------------------------ENCODE---------------------------------------//
//---------------------------------------------------------------------------------//
    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;
//---------------------------------------------------------------------------------//
//------------------------------------DECODE---------------------------------------//
//---------------------------------------------------------------------------------//
    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;
};

#endif // HCTREE_HPP
