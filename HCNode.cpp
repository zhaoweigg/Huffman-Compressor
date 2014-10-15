// Evan Su <e2su@ucsd.edu>, Guanhong Zhou <guzhou@ucsd.edu>
#include "HCNode.hpp"
//========================================================//
//-----------------------HCNODE CPP-----------------------//
//========================================================//
//---------------------------------------------------------------------------------//
//--------------------------------------HCNODE DESTRUCTOR--------------------------//
//---------------------------------------------------------------------------------//
HCNode:: ~HCNode() {	// delete points c0 and c1
  if (c0) {
            delete c0;
  }
  if (c1) {
            delete c1;
  }
}
//---------------------------------------------------------------------------------//
//------------------------------OVERLOAD < OPERATOR CODE---------------------------//
//---------------------------------------------------------------------------------//
bool HCNode::operator<(const HCNode& other) {		// overload the < operator so that if other is smaller than this, return true
  if (other.count < this->count) {			
    return true;
  }
  else if ((other.count == this->count) && ( other.symbol > this->symbol)) {		//when two counts are the same, place leaf with smaller symbol in front
    return true;
  }
  else {
    return false;
  }
}

