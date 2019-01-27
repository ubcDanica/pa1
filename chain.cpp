#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */

Chain::~Chain(){
	Chain::clear();
 	head_ = NULL;
	height_ = NULL;
	width_ = NULL;
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
	if(head_ == NULL){
		head_ = new Node(ndata);
		head_->prev = head_;
		head_->next = head_;
	}

	else if(head_-> prev == head_ && head_ -> next == head_){

		head_->prev = new Node(ndata);
		head_->prev->next = head_;
		head_->prev->prev = head_;
		
	}

	else {

		head_->prev->next = new Node(ndata);
		head_->prev->next->prev = head_->prev;
		head_->prev = head_->prev->next;
		head_->prev->next = head_;	
	}
}
/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length. 
 */
void Chain::moveBack(int startPos, int len, int dist){
/*	if(startPos + len - 1 + dist > Chain::size()){
		dist = Chain::size() - startPos - len + 1;
	}
		
	Node * startNode = walk(head_, startPos);
	Node * sendNode = walk(startNode,len-1);
	Node * distNode = walk(sendNode, dist);

	startNode -> prev -> next = sendNode -> next;
	sendNode -> next -> prev = startNode -> prev; // let the Node before startPos beginning connect to the Node after ending

	sendNode -> next = distNode -> next;
	distNode -> next = startNode;
*/
		
	 
}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
void Chain::roll(int k){
  /* your code here */
  if(length_>=2){
    for(int i=0; i<k; i++){
      head_->next = head_;
      head_ = head_->prev;
    }
  }
  else if(length_ == 1){
    head_ = head_;
  }
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  /* your code here */
  if(pos1 == pos2){
  }
  else if(pos1 +1 == pos2){
    swap(pos1);
  }
  else{
    reverseSub(pos1+1, pos2);
    reverseSub(pos,pos2-1);

  }
}

void Chain::swap(int pos){
    Node* block = walk(head_,pos1); 
    Node* temp = block->next;
    block->next = block;
    block->next->next = temp->next;
    block->next->prev = temp;
    block->next->prev->prev = temp->prev->prev;
}

/** Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  /* your code here */
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  if(head_ -> prev == head_ || head_ -> next == head_){
      delete head_;
      head_ = NULL;
  }
  else {
      Node * temp = head_;
      head_ = temp -> next;
      head_ -> prev = temp -> prev;
      delete temp;
      temp = NULL;
      clear();
  }
  length_-=1;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  /* your code here */
}
