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
    head_->next = head_->prev;  
  }

  else {

    head_->prev->next = new Node(ndata);
    head_->prev->next->prev = head_->prev;
    head_->prev = head_->prev->next;
    head_->prev->next = head_;  
  }
  length_++;
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
  if(startPos + len - 1 + dist > length_){
    dist = length_ - startPos - len + 1;
    cout<< dist<< endl;
  }
  cout<< length_<<endl;   
  Node * startNode = walk(head_, startPos);
  Node * sendNode = walk(startNode,len-1);
  Node * distNode = walk(sendNode, dist);

  startNode -> prev -> next = sendNode -> next;
  sendNode -> next -> prev = startNode -> prev; // let the Node before startPos beginning connect to the Node after ending

  sendNode -> next = distNode -> next;
  distNode -> next -> prev = sendNode;
  distNode -> next = startNode;
  startNode -> prev = distNode;
    
   
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
      //head_->next = head_;
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

  if(pos1 == pos2){

  }
  else if(pos1+1 == pos2){
    swap(pos1);

  }
  else{
    for(int i=pos2; i>pos1; i--){
      for(int j=pos1; j<i; j++)
      swap(j);
    }
  }
}

void Chain::swap(int pos){
    Node* block = walk(head_,pos); 
    Node* next = block->next;
    Node* prev = block->prev;
    Node* nextNext = block->next->next;

    block->prev = next;
    block->next = nextNext;
    next->prev = prev;
    next->next = block;
    prev->next = next;
    nextNext->prev = block;

/*    block->next = block;
    block->next->next = temp->next;
    block->next->prev = temp;
    block->next->prev->prev = temp->prev->prev;*/
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
  int length;
  if(this->size()>other.size())
    length = this->size();
  else
    length = other.size();
  for(int i = 0; i<length;i++){
	  if(i<this->size())
	    this->roll(1);
	  if(i<other.size()) {
        this->insertBack(other.head_->data);
        other.roll(1);
      }
  }
  other.clear();
}


void Chain::weaveHelper(Chain::Node *& l1, Chain::Node *& l2) {
    if(l2 == NULL);
	else if(l1 -> next == head_){
     	  insert(l1,l2);
     	  remove(l2);
     	  weaveHelper(l1->next,l2);
	}
	else if(l1->next->next== head_){
	  insert(head_->prev, l2);
	  remove(l2);
	  weaveHelper(head_->prev,l2);
	}

	else{
	  insert(l1,l2);
	  remove(l2);
	  weaveHelper(l1->next->next, l2);
	}
}

void Chain::insert(Chain::Node *& l1, Chain::Node * l2) {
  l1->next->prev = new Node(l2->data);
  l1->next->prev->next = l1->next;
  l1->next = l1->next->prev;
  l1->next->prev = l1;

}

void Chain::remove(Chain::Node *& l2) {
  l2 -> prev -> next = l2 -> next;
  l2-> next -> prev = l2 -> prev;
  Node * temp = l2;
  l2 = l2 ->next;
  delete temp;
  temp = NULL;

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
/*  length_ = other.size();
  width_ = other.width_;
  height_ = other.height_;
  
  Node* curr = other.head_;
  head_ = new Node(curr->data);
  head_->next = head_;
  head_->prev = head_;

  
  for(int i=0; i<length_; i++){
    head_->prev->next = new Node(curr->data);
    head_->prev->next->prev = head_->prev;
    head_->prev = head_->prev->next;
    head_->prev->next = head_;   

    head_ = head_ ->next;
    curr = curr ->next;
  }*/
  

  length_ = other.size();
  width_ = other.width_;
  height_ = other.height_;
  
  Node* curr = other.head_;
  head_ = new Node(curr->data);
  head_->next = head_;
  head_->prev = head_;

  Node* newCurr = head_;

  
  for(int i=0; i<length_ ; i++){
    newCurr = newCurr ->next;
    curr = curr ->next;

    newCurr->next->prev = new Node(curr->data);
    newCurr->next->prev->next = newCurr->next;
    newCurr->next->prev->prev = newCurr;
    newCurr->next = newCurr->next->prev;

  }

}
