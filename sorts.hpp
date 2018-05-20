#ifndef SORTS_HPP_
#define SORTS_HPP_

// Maciej Zwoliński
// 20/04/2018

// Static class including four sorting algorithms:
// Merge sort
// Quick sort
// Heap sort
// Introspective sort

// Algorithms taken from en.wikipedia stating for April 2018


#include <memory>
#include <cmath>

class Sorts {
    // heap sort related functions
    static int parentId( int n );
    static int lChildId( int n );
    template <class var>
    static void heapify( var tab[], int firstIndex, int lastIndex );
    template <class var>
    static void siftDown( var tab[], int rootIndex, int lastIndex );
    // quick sort related functions
    template <class var>
    static int qs_split( var tab[], int first, int last, bool reversed = false );
    template <class var>
    static void qs_swap( var tab[], int id1, int id2 );

    Sorts(){};

    public:
    // merge sort
    template <class var>
    static void mS( var tab[], int first, int last, bool reversed = false );
    // introspective sort
    template <class var>
    static void iS( var tab[], int firstIndex, int lastIndex, int maxDepth );
    // heap sort
    template <class var>
    static void hS( var tab[], int firstIndex, int lastIndex);
    // quick sort 
    template <class var>
    static void qS( var tab[], int first, int last, bool reversed = false );
};

int Sorts::parentId( int n ) { 
    return (n -1) / 2; 
}

int Sorts::lChildId( int n ) { 
    return 2*n + 1; 
}

template <class var>
void Sorts::heapify( var tab[], int firstIndex, int lastIndex ) {
    int start = parentId( lastIndex );
    while ( start >= firstIndex ) {
        siftDown( tab, start, lastIndex );
        start -= 1;
    }
}

template <class var>
void Sorts::siftDown( var tab[], int rootIndex, int lastIndex ) {
    int root = rootIndex;
    while ( lChildId( root ) <= lastIndex ) {
        int child = lChildId( root );
        int swap = root;
        if ( tab[swap] < tab[child] )
            swap = child;
        if ( child+1 <= lastIndex ) 
            if ( tab[swap] < tab[child+1] )
                swap = child + 1;
        if ( swap == root )
            return;
        else {
            qs_swap( tab, root, swap );
            root = swap;
        }
    }
}

template <class var>
int Sorts::qs_split( var tab[], int first, int last, bool reversed ) {
    int refIndex = first + rand()%(last - first);
    var refValue = tab[refIndex];
    qs_swap( tab, refIndex, last );

    int position = first;
    for ( int i = first; i <= last-1; i++ )
        if( (reversed ? (tab[i] > refValue):(tab[i] < refValue)) ) {
            qs_swap( tab, i, position );
            position++;
        }
    qs_swap( tab, position, last );
    return position;
}

template <class var>
void Sorts::qs_swap( var tab[], int id1, int id2 ) {
    var tmp = tab[id1];
    tab[id1] = tab[id2];
    tab[id2] = tmp;
}

template <class var>
void Sorts::mS( var tab[], int first, int last, bool reversed ) {
    int medium = (last + first) / 2;
    if ( first != last ) {
        mS( tab, first, medium, reversed );
        mS( tab, medium+1, last, reversed );

        auto tmpTab = std::make_unique<var[]>(last-first+1);
        int index = 0, left = first, right = medium+1;
        while ( left <= medium && right <= last ) {
            if ( reversed? (tab[left] > tab[right]):(tab[left] < tab[right]) )
                tmpTab[index] = tab[left++];
            else
                tmpTab[index] = tab[right++];
            index++;                      
        }
        while ( left <= medium )
            tmpTab[index++] = tab[left++];

        while ( right <= last )
            tmpTab[index++] = tab[right++];

        for ( int i = first, j = 0; i <= last; i++, j++ )
            tab[i] = tmpTab[j];
    }
    return;
}

template <class var>
void Sorts::iS( var tab[], int firstIndex, int lastIndex, int maxDepth ) {
    if ( firstIndex < lastIndex ) {
        if ( !maxDepth ) {
            hS( tab, firstIndex, lastIndex );
            return;
        }
        int n = qs_split( tab, firstIndex, lastIndex, false );
        iS( tab, firstIndex, n-1, maxDepth-1 );
        iS( tab, n+1, lastIndex, maxDepth-1 );
    }
}

template <class var>
void Sorts::hS( var tab[], int firstIndex, int lastIndex ) {
    int last = lastIndex;
    heapify( tab, firstIndex, lastIndex );
    while ( last > firstIndex + 1 ) {
        qs_swap( tab, firstIndex, last );
        last--;
        heapify( tab, firstIndex, last );
    }
}

template <class var>
void Sorts::qS( var tab[], int first, int last, bool reversed) {
    if ( first < last ) {
        int n = qs_split( tab, first, last, reversed );
        qS( tab, first, n-1, reversed );
        qS( tab, n+1, last, reversed );
    }
}

#endif
