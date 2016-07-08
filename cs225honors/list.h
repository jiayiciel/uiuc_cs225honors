/**
 * @file list.h
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>
#include <ostream>
#include <algorithm>

using namespace std;

/**
 * List: This is a templated linked list class (meaning it contains data of
 * templated type T, which is a placeholder for a type).
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own helper functions to this class,
 * and are encouraged to add to it.
 */
template <class T>
class List
{
private:
    /**
     * The ListNode class is private to the List class via the principle of
     * encapsulation---the end user does not need to know our node-based
     * implementation details.
     */
    class ListNode
    {
    public:
        /**
         * Default ListNode constructor.
         * Implemented for you.
         * @see list_given.cpp
         */
        ListNode();
        
        /**
         * Constructs a ListNode with the given data.
         * Implemented for you.
         * @see list_given.cpp
         */
        ListNode( const T & ndata );
        
        /**
         * A pointer to the next node in the list. May be NULL
         * if one does not exist.
         */
        ListNode * next;
        
        /**
         * A pointer to the previous node in the list. May be NULL if
         * one does not exist.
         */
        ListNode * prev;
        
        /**
         * The data contained in this node. We do not allow you to
         * modify node data, so it is const.
         */
        const T data;
    };
    
public:
    /**
     * Default List constructor.
     * Creates an empty List. Implemented for you.
     * @see list_given.cpp
     */
    List();
    
    /**
     * Copy constructor for a List.
     * Since Lists allocate dynamic memory (i.e., they use "new", we
     * must define the Big Three).
     * @see list_given.cpp
     *
     * @param other The list we are copying.
     */
    List( const List<T> & other );
    
    /**
     * Overloaded assignment operator for Lists.
     * Part of the Big Three that we must define because the class
     * allocates dynamic memory.
     * @see list_given.cpp
     *
     * @param rhs The right hand side of the assignment statement.
     */
    List<T> & operator=( const List<T> & rhs );
    
    /**
     * Gets the size of the List.
     * Defined as a const function because it promises not to modify
     * the current List in any way.
     * @see list_given.cpp
     *
     * @return The size of the current List.
     */
    int size() const;
    
    /**
     * Used to print the list.
     * Const because it promises not to modify the current List.
     * @see list_given.cpp
     *
     * @param os Output stream to print the list to (e.g. cout)
     */
    void print( ostream & os ) const;
    
    /**
     * Determines if the current List is empty.
     * Const because it promises not to modify the current List.
     * @see list_given.cpp
     *
     * @return Boolean value of whether the current List is empty.
     */
    bool empty() const;
    
    /**
     * Destroys the current List. This function should ensure that
     * memory does not leak on destruction of a list.
     */
    ~List();
    
    
    /**
     * Inserts a new node at the front of the List.
     * This function **SHOULD** create a new ListNode.
     *
     * @param ndata The data to be inserted.
     */
    void insertFront( const T & ndata );
    
    /**
     * Inserts a new node at the front of the List and returns one from the back.
     * This function **SHOULD** create a new ListNode.
     *
     * @param ndata The data to be inserted.
     */
    T popBack();
    
    /**
     * Reverses the current List.
     */
    void reverse();
    
    /**
     * Splits the given list into two parts.
     * Run under the assumption the list's size is greater than 5.
     * @return The second list created from the split.
     */
    List<T> split();
    
    /**
     * Merges the given sorted list into the current sorted list.
     *
     * @param otherList List to be merged into the current list.
     */
    void mergeWith( List<T> & otherList );
    
    // Provided Iterator Functions, don't remove
#include "list_given.h"
    
private:
    /*
     * Private member variables.
     *
     * You must use these as specified in the spec and may not rename them.
     * You may add more if you need them.
     */
    
    /**
     * The head of the List. May be NULL if the List is empty.
     */
    ListNode * head;
    /**
     * The tail of the list. May be NULL if the List is empty.
     */
    ListNode * tail;
    /**
     * The length of the current List. Do not forget to update it!
     */
    int length;
    
    
    /*
     * Private helper functions.
     *
     * You must use these as specified in the spec and may not rename them.
     * You may place more here as you need them.
     */
    
    ListNode* split(ListNode* start, int splitPoint);
    
    /**
     * Copies the given list into the current list.
     * @see list_given.cpp
     * @param other The List to be copied.
     */
    void copy( const List<T> & other ); // implemented in list_given.cpp
    
    void clear();
    /**
     * Helper function to reverse a sequence of linked memory inside a
     * List, starting at startPoint and ending at endPoint. You are
     * responsible for updating startPoint and endPoint to point to the
     * new starting and ending points of the rearranged sequence of
     * linked memory in question.
     *
     * @param startPoint A pointer reference to the first node in the
     *  sequence to be reversed.
     * @param endPoint A pointer reference to the last node in the
     *  sequence to be reversed.
     */
    void reverse( ListNode * & startPoint, ListNode * & endPoint );
    
    
};

// needed for template instantiation
#include "list.cpp"

// this includes all of the functions that are given to you
// (i.e., the ones that you do not need to implement)
#include "list_given.cpp"

#endif