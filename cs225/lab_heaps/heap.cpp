/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    if(leftChild(currentIdx) < _elems.size())
    {
        return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    if(rightChild(currentIdx) >= _elems.size())
    {
        return leftChild(currentIdx);
    }
    bool temp = higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]);
    if (temp)
    {
        return leftChild(currentIdx);
    }
    else
    {
        return rightChild(currentIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    if(hasAChild(currentIdx))
    {
        size_t maxPriorityIndex = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[maxPriorityIndex], _elems[currentIdx]))
        {
            std::swap( _elems[ currentIdx ], _elems[ maxPriorityIndex ] );
            heapifyDown(maxPriorityIndex);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (size_t i = 0; i < elems.size(); i++)
    {
        _elems.push_back(elems[i]);
    }
    for (size_t i = _elems.size() - 1; i > 0; i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
    T temp = _elems[root()];
    std::swap( _elems[root()], _elems[_elems.size() - 1]);
    
    _elems.pop_back();
    heapifyDown(1);
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    if(_elems.size() == 0)
        return true;
    return false;
}
