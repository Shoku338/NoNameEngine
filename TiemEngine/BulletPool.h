#pragma once
#include <queue>
template <class T>

class BulletPool {
private:
    std::queue<T*> objectPool;

public:
    BulletPool(int poolSize);
    ~BulletPool();

    T* GetObject();
    void ReturnObject(T* object);
};