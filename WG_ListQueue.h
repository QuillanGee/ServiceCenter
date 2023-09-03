// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: The Waiting Game - WG_ListQueue template class

// WG_ListQueue template class

#ifndef WG_ListQueue_H
#define WG_ListQueue_H
#include <iostream>
#include "WG_DblList.h"

template<typename T>
class WG_ListQueue{
    public:
        WG_ListQueue();
        virtual ~WG_ListQueue();
        void add(T data); //add to the back
        T remove(); //remove from the front
        T peek();
        bool isEmpty();
        int size();

    private:
        WG_DblList<T>* m_list;

};

template<typename T>
WG_ListQueue<T>::WG_ListQueue(){
    m_list = new WG_DblList<T>();
}

template<typename T>
WG_ListQueue<T>::~WG_ListQueue(){
    delete m_list;
}

template<typename T>
bool WG_ListQueue<T>::isEmpty(){
    return (m_list->size() == 0);
}

template<typename T>
int WG_ListQueue<T>::size(){
    return m_list->size();;
}

template<typename T>
void WG_ListQueue<T>::add(T data){
    m_list->addBack(data);
}

template<typename T>
T WG_ListQueue<T>::remove(){
    return m_list->removeFront();
}

template<typename T>
T WG_ListQueue<T>::peek(){
    return m_list-> get(0);
}

#endif
