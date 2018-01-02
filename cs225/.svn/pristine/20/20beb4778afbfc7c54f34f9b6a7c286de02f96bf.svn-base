#include <iostream>
 
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
 */
 
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    this->clear();
}
 
/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    this->length = 0;
    ListNode * curr = this->head;
 
    while (curr != NULL) 
    {
        ListNode * tmp = curr->next;
        delete curr;
        curr = NULL;
        curr = tmp;
    }
 
    this->head = NULL;
    this->tail = NULL;
}
 
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    length++;
 
    if (this->tail != NULL) 
    {
        head->prev = new ListNode(ndata);
 
        ListNode * tmp = head;
        head = head->prev;
        head->prev = NULL;
        head->next = tmp;
    }
    else
    {
        this->head = new ListNode(ndata);
        this->tail = this->head;
 
        head->next = NULL;
        head->prev = NULL;
 
        tail->next = NULL;
        tail->prev = NULL;
    }
 }
 
/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    length++;
 
    if (this->tail != NULL)
    {
        tail->next = new ListNode(ndata);
        ListNode * temp = tail;
 
        tail = tail->next;
        tail->next = NULL;
        tail->prev = temp;
    }
    else 
    {
        this->head = new ListNode(ndata);
        this->tail = this->head;
 
        head->next = NULL;
        head->prev = NULL;
 
        tail->next = NULL;
        tail->prev = NULL;
    }
}
 
 
/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}
 
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    ListNode * temporaryNode;
    ListNode * changingNode = startPoint;

    if(startPoint == NULL || endPoint == NULL)
    {
        return;
    }

    while(changingNode != endPoint)
    {
        temporaryNode = changingNode -> next;
        
        // This is removing the node from the LinkedList.
        if(changingNode->prev != NULL)
        {
            changingNode->prev->next = changingNode->next;
        }
        changingNode->next->prev = changingNode->prev;
        changingNode->next = NULL;
        changingNode-> prev = NULL;
        // This is the end of the removing of the node from the LinkedList.

        // Time to insert it after the endPoint now
        if(endPoint->next != NULL)
        {
            endPoint->next->prev = changingNode;
        }
        changingNode->prev = endPoint;
        changingNode->next = endPoint->next;
        endPoint->next = changingNode;
        // Done inerting the changingNode after endpoint.

        changingNode = temporaryNode;
    }

    ListNode * tmp = startPoint;
    startPoint = endPoint;
    endPoint = tmp;
}
 
 
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    if(head == NULL || tail == NULL)
    {
        //std::cout << "Base Case" << endl;
        return;
    }

    //std::cout << "Before declaration" << endl;
    ListNode * starting_node = head;
    ListNode * end_node = head;

    do
     {
        //std::cout << "First Line in the while loop" << endl;
         for(int i = 0; i < n-1; i++)
         {
            //std::cout << "Inside the for loop" << endl;
            if(end_node->next != NULL)
            {
                end_node = end_node->next;
            }
            //std::cout << "End of the for loop" << endl;
         }
         //std::cout << "Outside the for loop" << endl;
         reverse(starting_node, end_node);
         if(end_node -> next != NULL)
         {
            end_node = end_node->next;
            starting_node = end_node;
         }
     }while(end_node->next!=NULL);
     //std::cout << "Outside the first while loop" << endl;
     while(starting_node->prev != NULL)
     {
        starting_node = starting_node->prev;
     } 
     while(end_node->next != NULL)
     {
        end_node = end_node->next;
     }

     head = starting_node;
     tail = end_node;
}
 
 
/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    if(head == NULL || tail == NULL)
    {
        return;
    }

    ListNode * temporary_node;
    ListNode * changing_node = head;
    int count = 0;

    while(changing_node != NULL && changing_node != tail)
    {
        if(count == 1)
        {
            temporary_node = changing_node->next;
            count = 0;

            // Removing the pointer
            if(changing_node->prev != NULL)
            {
                changing_node->prev->next = changing_node->next;
            }
            changing_node -> next -> prev = changing_node -> prev;
            changing_node -> next = NULL;
            changing_node -> prev = NULL;
            // Done removing the pointer

            //Inserting
            if(tail->next != NULL)
            {
                tail ->next->prev = changing_node;
            }
            changing_node->prev = tail;
            changing_node->next = tail->next;
            tail->next = changing_node;

            tail = tail->next;
            changing_node = temporary_node;
        }
        else
        {
            changing_node = changing_node -> next;
            count++;
        }
    }
    /// @todo Graded in MP3.1
}
 
/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();
 
    if (splitPoint < 0)
        splitPoint = 0;
 
    ListNode * secondHead = split(head, splitPoint);
 
    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }
 
    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}
 
/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    // Null case.
    if(start == NULL)
    {
        return NULL;
    }

    // Initilizers
    ListNode* firstNode = start;
    ListNode* secondNode = start;
    
    int size;
    // This for loop goes through and gets the length of the array by visiting each point in the list.
    for( size = 1; firstNode->next != NULL; size++)
    {
        firstNode=firstNode->next;
    }

    // Edge case in case size is less than the spliting point.
    if(splitPoint > size)
    {
        return NULL;
    }
    
    // Edge case when there is only one element you would return nothing to split.
    if(size ==1)
    {
        return NULL;
    }

    for(int i=0; i<splitPoint; i++)
    {
        secondNode = secondNode->next;
    }
    
    firstNode = secondNode->prev;

    // Updating the pointers.
    secondNode->prev = NULL;
    firstNode->next = NULL;

    // Returning the second half o the list.
    return secondNode;
}
 
/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;
 
    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;
 
    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}
 
/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    // NULL Case #1
    if(second == NULL)
    {
        return first;
    }

    // NULL Case #2
    if(first == NULL)
    {
        return second;
    }

    // Intializers
    ListNode* fNode = first;
    ListNode* sNode;
   
    for( sNode = second; sNode != NULL ; sNode = second)
    {
        if(second != NULL)
        {
            second = second->next;
        }
        while((fNode->data) < (sNode->data))
        {
            if(fNode->next == NULL)
            {
                sNode->prev = fNode;
                fNode->next = sNode;
                while(first->prev != NULL)
                {
                    first = first->prev;
                }

                second = NULL;
                return first;
            }
             fNode = fNode->next;
        }
        sNode->prev = fNode->prev;
        if(fNode->prev != NULL)
        {
            fNode->prev->next = sNode;
        }
        fNode->prev = sNode;
        sNode->next = fNode;
        fNode = sNode;
 
    }
    while(first->prev != NULL)
    {
        first = first->prev;
    }
    second = NULL;
    return first;
}
 
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}
 
/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    ListNode * changingN;
    changingN = start;
    
    // BASE CASE
    if (chainLength <= 1)
    {
        return start;
    }
    // Recursive case.
    else
    {
        ListNode * rNode = split(changingN, chainLength/2);
        // Recursive call for the left side of the list.
        changingN = mergesort(changingN, chainLength/2);
        // Recursive call for the right side of the list.
        rNode = mergesort(rNode, chainLength - (chainLength/2));
        return merge(changingN, rNode);
    }
}