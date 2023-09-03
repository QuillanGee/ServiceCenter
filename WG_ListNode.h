// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - WG_ListNode template class

// WG_ListNode template class

#ifndef WG_LIST_NODE_H
#define WG_LIST_NODE_H

template <typename T>
class WG_ListNode{
  public:
    WG_ListNode(T data);
    ~WG_ListNode();
    T m_data; // actual value being held is
    // each WG_ListNode is pointing to a WG_ListNode front and WG_ListNode back
    WG_ListNode<T>* m_next; // recursive bc it points to instance of itself
    WG_ListNode<T>* m_prev;

};

template <typename T>
WG_ListNode<T>::WG_ListNode(T data){
  m_data = data;
  m_next = NULL;
  m_prev = NULL;
}

template <typename T>
WG_ListNode<T>::~WG_ListNode(){
  m_next = NULL;
  m_prev = NULL;
}

#endif
