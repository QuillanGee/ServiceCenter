// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - WG_DblList template class

// WG_DblList template class

#ifndef WG_DBL_LIST_H
#define WG_DBL_LIST_H
#include "WG_ListNode.h"

template <typename T>
class WG_DblList{
  public:
    WG_DblList();
    virtual ~WG_DblList();
    int size();
    void addFront(T data);
    void addBack(T data);
    void add(int pos, T data);

    T removeFront();
    T removeBack();
    T remove(int pos);

    T get(int pos);

    bool isEmpty();

  protected:
    WG_ListNode<T>* m_front;
    WG_ListNode<T>* m_back;
    int m_size;
};

template <typename T>
WG_DblList<T>::WG_DblList(){
  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <typename T>
WG_DblList<T>::~WG_DblList(){
  WG_ListNode<T>* current = m_front;
  while (current != NULL){
    delete current;
    current = current -> m_next;
    --m_size;
  }

  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <typename T>
int WG_DblList<T>::size(){
  return m_size;
}

template <typename T>
bool WG_DblList<T>::isEmpty(){
  return (m_size == 0);
}

template <typename T>
void WG_DblList<T>::addFront(T data){
  WG_ListNode<T>* newNode = new WG_ListNode<T>(data);
  if (!isEmpty()){
    newNode -> m_next = m_front;
    m_front -> m_prev = newNode;
  } else {
    // if theres only 1 thing in list newNode is front and back
    m_back = newNode;
  }
  m_front = newNode;
  ++m_size;
}

template <typename T>
void WG_DblList<T>::addBack(T data){
  WG_ListNode<T>* newNode = new WG_ListNode<T>(data);
  if (!isEmpty()){
    newNode -> m_prev = m_back; // set newNode's prev to old back
    m_back -> m_next = newNode; // set oldBack's next to newNode
  } else {
    // if theres only 1 thing in list newNode is front and back
    m_front = newNode;
  }
  m_back = newNode; // make newNode back regardless
  ++m_size;
}

template <typename T>
void WG_DblList<T>::add(int pos, T data){
  if(isEmpty()){
    addFront(data);
  } else if (pos <= 0){
    addFront(data);
  } else if (pos >= m_size){
    addBack(data);
  } else {
    WG_ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos){
      current = current -> m_next;
      ++cPos;
    }
    WG_ListNode<T>* newNode = new WG_ListNode<T>(data);
    current -> m_prev -> m_next = newNode;
    newNode ->  m_prev = current -> m_prev;
    current -> m_prev = newNode;
    newNode ->  m_next = current;
    ++m_size;
  }
}

template <typename T>
T WG_DblList<T>::removeFront(){
  if (!isEmpty()){
    T data = m_front -> m_data; // so we dont lose access to data later
    if (m_size == 1){
      delete m_front; // dont delete back bc its pointing to the same thing
      m_front = NULL;
      m_back = NULL;
    } else {
      WG_ListNode<T>* currFront = m_front;
      m_front = m_front->m_next;
      m_front -> m_prev = NULL;
      delete currFront;
    }
    --m_size;
    return data;
  }
}

template <typename T>
T WG_DblList<T>::removeBack(){
  if (!isEmpty()){
    T data = m_back -> m_data; // so we dont lose access to data later
    if (m_size == 1){
      delete m_back;
      m_front = NULL;
      m_back = NULL;
    } else {
      WG_ListNode<T>* currBack = m_back;
      m_back = m_back -> m_prev;
      m_back -> m_next = NULL;
      delete currBack;
    }
    --m_size;
    return data;
  }  else {
    // empty
  }
}

template <typename T>
T WG_DblList<T>::remove(int pos){
  if (!isEmpty()){
    T data;
    if(pos <= 0){
      data = removeFront();
    } else if (pos >= m_size){
      data = removeBack();
    } else {
      WG_ListNode<T>* current = m_front;
      int cPos = 0;
      while (cPos != pos){
        current = current -> m_next;
        ++cPos;
      }
      data = current -> m_data;
      current -> m_prev -> m_next = current -> m_next;
      current -> m_next -> m_prev = current -> m_prev;
      delete current;
      --m_size;
    }
    return data;
  }  else {
    // empty
  }
}

template <typename T>
T WG_DblList<T>::get(int pos){
  // check if in range
  if (pos < size()){
    WG_ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos){
      current = current -> m_next;
      ++cPos;
    }
    return current -> m_data;
  } else {
    // not in range
  }
}

#endif
