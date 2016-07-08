#include <iostream>
using namespace std;

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Milan Dasgupta
 * @date (modified) Summer 2014
 *
 */

template <class T>
List<T>::~List()
{
    clear();
}

template <class T>
void List<T>::clear()
{
    ListNode * curr = head;
    
    while (curr != NULL) {
        curr = head->next;
        delete head;
        head = curr;
    }
    
    length = 0;
}

template <class T>
void List<T>::insertFront(T const & ndata)
{
    ListNode * newNode = new ListNode(ndata);
    
    if (head == NULL) {
        
        head = newNode;
        tail = head;
        
    } else {
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    
    newNode = NULL;
    length++;
    
}

template <class T>
T List<T>::popBack()
{
    
    if (length == 0) {return T();}
    else {
        
        ListNode * temp = tail;
        tail = tail->prev;
        
        T value = temp->data;
        delete temp;
        temp = NULL;
        
        length--;
        
        return value;
    }
    
}

template <class T>
void List<T>::reverse()
{
    reverse(head,tail); //Utilize helper function
}

template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    
    if (startPoint == endPoint || startPoint == NULL || endPoint == NULL || length <= 1) {
        return;
    }
    
    ListNode * newEnd = startPoint;
    ListNode * newStart = endPoint;
    
    ListNode * start_prev = startPoint->prev;
    ListNode * end_next = endPoint->next;
    
    ListNode * temp;
    
    while (startPoint != endPoint) {
        temp = startPoint->prev;
        startPoint->prev = startPoint->next;
        startPoint->next = temp;
        startPoint = startPoint->prev;
    }
    
    temp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = temp;
    
    endPoint = newEnd;
    endPoint->next = end_next;
    
    if (start_prev != NULL) {
        start_prev->next = startPoint;
    } else {
        head = newStart;
    }
    
    if (end_next != NULL) {
        end_next->prev = endPoint;
    } else {
        tail = endPoint;
    }
    
}

template <class T>
List<T> List<T>::split()
{
    int splitPoint = length/2;
    
    if (splitPoint > length)
        return List<T>();
    
    if (splitPoint < 0)
        splitPoint = 0;
    
    ListNode* secondHead = split(head, splitPoint);
    
    int oldLength = length;
    if (secondHead == head) {
        
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }
    
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (length == 0 || splitPoint < 1 || splitPoint >= length) {return NULL;}
    
    // N->1->2->3->4->N
    ListNode * newStart = start;
    ListNode * newEnd;
    
    for (int i=0; i<splitPoint; i++) {
        if (newStart->next == NULL) {return NULL;}
        newStart = newStart->next;
    }
    
    newStart->prev->next = NULL;
    newStart->prev = NULL;
    
    return newStart;
}

template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    if (head == NULL) {
        head = otherList.head;
    } else {
        tail->next = otherList.head;
    }
    tail = otherList.tail;
    length = length + otherList.length;
    
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}