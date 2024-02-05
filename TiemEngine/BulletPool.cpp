#include "BulletPool.h"

template <class T>
BulletPool<T>::BulletPool(int poolSize) {
    for (int i = 0; i < poolSize; ++i) {
        objectPool.push(new T());
    }
}

template <class T>
BulletPool<T>::~BulletPool() {
    while (!objectPool.empty()) {
        delete objectPool.front();
        objectPool.pop();
    }
}

template <class T>
T* BulletPool<T>::GetObject() {
    if (!objectPool.empty()) {
        T* object = objectPool.front();
        objectPool.pop();
        return object;
    }
    else {
        // If the pool is empty, create a new object
        return new T();
    }
}

template <class T>
void BulletPool<T>::ReturnObject(T* object) {
    // Reset the object's state before returning it to the pool
    // You might need to add a Reset method in your bullet classes
    // to properly reset their state.
    object->Reset();
    objectPool.push(object);
}
