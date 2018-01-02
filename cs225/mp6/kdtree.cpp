/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    if(first[curDim] == second[curDim])
    {
        return first < second;
    }

    return first[curDim] < second[curDim];
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    int current_sum = 0;
    int potential_sum = 0;
    for(int i = 0; i < Dim; i++)
    {
        current_sum += pow((target[i] - currentBest[i]), 2);
        potential_sum += pow((target[i] - potential[i]), 2);
    }

    if(potential_sum == current_sum)
    {
        return potential<currentBest;
    }
    return potential_sum<current_sum;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    if(newPoints.size() != 0)
    {
        points.resize(newPoints.size());
        for(int i = 0; i < points.size(); i++)
            points[i] = newPoints[i];
        int max = points.size() - 1;
        int min = 0;
        make(points, min, max, 0);
    }

}
    

template<int Dim>
void KDTree<Dim>::make(vector< Point<Dim> > & newPoints, int minimum, int maximum, int curDim)
{
    int root = (maximum + minimum)/2;

    if(maximum > minimum)
    {
        select(newPoints, minimum, maximum, root, curDim);
        if( minimum < root)
            make(newPoints, minimum, root - 1, (curDim + 1)%Dim);
        if(maximum > root)
            make(newPoints, root + 1, maximum, (curDim + 1)%Dim);

    }
}

template<int Dim>
void KDTree<Dim>::select(vector< Point<Dim> > & newPoints, int left, int right, int n, int curDim)
{
    if(left >= right)
        return;
    while(left != right)
    {

        int pivot_index = (left + right)/2;
        int new_pivot = partition(newPoints, left, right, pivot_index, curDim);
        if(n == new_pivot)
            return;     
        else if(n < new_pivot)
            right = new_pivot - 1;
        else
        {
            left = new_pivot + 1;
        }
    }
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & newPoints, int left, int right, int pivot, int curDim)
{
    if(!newPoints.empty())
    {   
        Point<Dim> pivVal = newPoints[pivot];
        Point<Dim> temp = newPoints[pivot];
        newPoints[pivot] = newPoints[right];
        newPoints[right] = temp;

        int stored_index = left; //stored_index initialized to left
        
        for(int i = left; i < right; i++) 
        {
            if(smallerDimVal(newPoints[i], pivVal, curDim))
            {
                temp = newPoints[stored_index]; 
                newPoints[stored_index] = newPoints[i];
                newPoints[i] = temp; 
                stored_index++; 
            }
        }

        temp = newPoints[right];
        newPoints[right] = newPoints[stored_index
];
        newPoints[stored_index] = temp; //swap stored_index with right
    
        return stored_index;
    }

    else
        return 0;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    return find(query, 0, (points.size() - 1), 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::find(const Point<Dim> & query, int min, int max, int curDim) const
{
    int midpoint = (min + max)/2;
    bool contains_left = false;
    Point<Dim> currentBest = points[midpoint];

    if(smallerDimVal(query, points[midpoint], curDim))
    {
        contains_left = true;
        if(min == midpoint)
            currentBest = points[midpoint]; 
        else
            currentBest = find(query, min, midpoint - 1, (curDim + 1) % Dim);
    }

    else
    {
        if(max == midpoint)
            currentBest = points[midpoint]; 

        else
            currentBest = find(query, midpoint + 1, max, (curDim + 1) % Dim);
    }

    Point<Dim> potential = points[midpoint];

    if(shouldReplace(query, currentBest, potential))
            currentBest = potential;

    int distance = 0;

    for(int i = 0; i < Dim; i++)
        distance += pow(currentBest[i] - query[i], 2);
                
    int radius = 0;
    radius += pow((query[curDim] - points[midpoint][curDim]), 2);

    if((radius <= distance) && (contains_left) && (max > midpoint))
            potential = find(query, midpoint + 1, max, (curDim + 1) % Dim);

    else if((radius <= distance) && (!contains_left) && (min < midpoint))
            potential = find(query,min, midpoint - 1, (curDim + 1) % Dim);

    if(shouldReplace(query, currentBest, potential))
            currentBest = potential;

    return currentBest;
}
