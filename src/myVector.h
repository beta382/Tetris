/*
 * Author:                 Austin Hash
 * Assignment name:        Program 5: myVector Template
 * Assignment description: Implement the myVector class, a child of the
 *                           containerInterface template
 * Due date:               Mar 7, 2014
 * Date created:           Mar 4, 2014
 * Date last modified:     Mar 4, 2014
 */

#ifndef MYVECTOR_H_
#define MYVECTOR_H_

#include <iostream>
using namespace std;

template <typename T>
class containerInterface
{
   public:
     virtual containerInterface <T>& pushFront(const T) =0;
     virtual containerInterface <T>& pushBack(const T)  =0;
     virtual containerInterface <T>& popFront(T&)       =0;
     virtual containerInterface <T>& popBack(T&)        =0;
     virtual int  getSize() const                       =0;
     virtual bool isEmpty() const                       =0;
     virtual T    front() const                         =0;
     virtual T    back() const                          =0;
     virtual T&   operator [](const int)                =0;
     virtual void erase()                               =0;
     virtual ~containerInterface(){};
};

template <typename T>
class myVector: public containerInterface<T> {
    public:
        myVector();
        ~myVector();
        myVector(const myVector&);
        myVector<T>& operator =(const myVector&);
        myVector<T>& pushFront(const T);
        myVector<T>& pushBack(const T);
        myVector<T>& popFront(T&);
        myVector<T>& popBack(T&);
        T front() const;
        T back() const;
        T& at(int) const;
        T& operator [](const int);
        int getSize() const;
        bool isEmpty() const;
        void erase();
    private:
        T *data;
        int size;
        int capacity;
        void grow();
        void shiftRight();
        void shiftLeft();
};

/*
 * Description:   Creates a myVector object
 * Returns:       None
 * Precondition:  None
 * Postcondition: A myVector object is instantiated
 */
template<typename T>
myVector<T>::myVector() {
    size = 0;
    capacity = 1;
    data = new T[capacity];
}

/*
 * Description:   Destroys a myVector object, properly
 * Returns:       None
 * Precondition:  None
 * Postcondition: The myVector object is properly destructed
 */
template<typename T>
myVector<T>::~myVector() {
    delete [] data;
}

/*
 * Description:   Creates a copy of an existing myVector object
 * Returns:       None
 * Precondition:  A myVector object exists
 * Postcondition: A copy of the passed myVector object is created
 */
template<typename T>
myVector<T>::myVector(const myVector<T>& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

/*
 * Description:   Assigns the data of one myVector object to another 
 * Returns:       myVector<T>&
 * Precondition:  A myVector object exists
 * Postcondition: This myVector is assigned the data of the passed myVector and
 *                  returned by reference
 */
template<typename T>
myVector<T>& myVector<T>::operator =(const myVector<T>& rhs) {
    if (this != &rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        
        delete [] data;
        data = new T[capacity];
        
        for (int i = 0; i < size; i++) {
            data[i] = rhs.data[i];
        }
    }
    
    return *this;
}

/*
 * Description:   Pushes a value to the front of this myVector
 * Returns:       myVector<T>&
 * Precondition:  A T exists
 * Postcondition: The value passed is pushed to the front of this myVector, this
 *                  myVector is returned by reference
 */
template<typename T>
myVector<T>& myVector<T>::pushFront(const T value) {
    size++;
    
    while (size >= capacity) {
        grow();
    }
    
    shiftRight();
    data[0] = value;
    
    return *this;
}

/*
 * Description:   Pushes a value to the back of this myVector
 * Returns:       myVector<T>&
 * Precondition:  A T exists
 * Postcondition: The value passed is pushed to the back of this myVector, this
 *                  myVector is returned by reference
 */
template<typename T>
myVector<T>& myVector<T>::pushBack(const T value) {
    data[size] = value;
    size++;
    
    while (size >= capacity) {
        grow();
    }
    
    return *this;
}

/*
 * Description:   A value is removed from the front of this myVector 
 * Returns:       myVector<T>&
 * Precondition:  A T& exists
 * Postcondition: The value at the front of this myVector is removed, and its
 *                  value is stored in the passed T&
 */
template<typename T>
myVector<T>& myVector<T>::popFront(T& value) {
    if (!isEmpty()) {
        value = front();
        shiftLeft();
        size--;
    }
    
    return *this;
}

/*
 * Description:   A value is removed from the back of this myVector 
 * Returns:       myVector<T>&
 * Precondition:  A T& exists
 * Postcondition: The value at the back of this myVector is removed, and its
 *                  value is stored in the passed T&
 */
template<typename T>
myVector<T>& myVector<T>::popBack(T& value) {
    if (!isEmpty()) {
        value = back();
        size--;
    }
    
    return *this;
}

/*
 * Description:   Returns the value at the front of this myVector
 * Returns:       T
 * Precondition:  None
 * Postcondition: The value at the front of this myVector is returned
 */
template<typename T>
T myVector<T>::front() const {
    return data[0];
}

/*
 * Description:   Returns the back at the front of this myVector
 * Returns:       T
 * Precondition:  None
 * Postcondition: The value at the back of this myVector is returned
 */
template<typename T>
T myVector<T>::back() const {
    return data[size-1];
}

template <typename T>
T& myVector<T>::at (int index) const {
    return data[index];
}

/*
 * Description:   Returns a reference to the data at the specified index of this
 *                  myVector
 * Returns:       T&
 * Precondition:  An int exists
 * Postcondition: A reference to the data at the specified index of this
 *                  myVector is returned
 */
template <typename T>
T& myVector<T>::operator [](int index) {
    return data[index];
}

/*
 * Description:   Returns the size of this myVector
 * Returns:       int
 * Precondition:  None
 * Postcondition: Returns the size of this myVector
 */
template<typename T>
int myVector<T>::getSize() const {
    return size;
}

/*
 * Description:   Determines if this myVector is empty
 * Returns:       bool
 * Precondition:  None
 * Postcondition: If this myVector is empty, returns true, false otherwise
 */
template<typename T>
bool myVector<T>::isEmpty() const {
    return size == 0;
}

/*
 * Description:   Erases the contents of this myVector
 * Returns:       void
 * Precondition:  None
 * Postcondition: The size of this myVector is set to 0
 */
template<typename T>
void myVector<T>::erase() {
    size = 0;
}



/*
 * Description:   Grows this myVector if necessary
 * Returns:       void
 * Precondition:  None
 * Postcondition: If this myVector is too small, doubles the capacity once
 */
template<typename T>
void myVector<T>::grow() {
    if (size >= capacity) {
        T* temp = data;
        
        capacity *= 2;
        data = new T[capacity];
        
        for (int i = 0; i < size; i++) {
            data[i] = temp[i];
        }
        
        delete [] temp;
    }
}

/*
 * Description:   Shifts the data in this myVector one space to the right
 * Returns:       void
 * Precondition:  None
 * Postcondition: The data in this myVector is shifted one space to the right
 */
template<typename T>
void myVector<T>::shiftRight() {
    for (int i = size-1; i > 0; i--) {
        data[i] = data[i-1];
    }
}

/*
 * Description:   Shifts the data in this myVector one space to the left
 * Returns:       void
 * Precondition:  None
 * Postcondition: The data in this myVector is shifted one space to the left
 */
template<typename T>
void myVector<T>::shiftLeft() {
    for (int i = 0; i < size-1; i++) {
        data[i] = data[i+1];
    }
}

#endif /* MYVECTOR_H_ */
