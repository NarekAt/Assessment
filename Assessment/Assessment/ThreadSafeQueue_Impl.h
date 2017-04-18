#pragma once

#include "ThreadSafeQueue.h"
#include <mutex> // for unique_lock

namespace Parallel
{
typedef std::unique_lock<std::shared_mutex> UniqueLock;
typedef std::shared_lock<std::shared_mutex> SharedLock;


template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(size_type maxSize)
    : dataQueue_()
    , mutex_()
    , cVForProducers_()
    , cVForConsumers_()
    , reachedToMax_(false)
    , maxSize_(maxSize)
{}

template<typename T>
void
ThreadSafeQueue<T>::push(const value_type v)
{
    UniqueLock lck(mutex_);

    cVForProducers_.wait(lck, [this] {
        if (dataQueue_.size() >= maxSize_)
            reachedToMax_ = true;

        return !reachedToMax_;
    });

    dataQueue_.push(v);

    cVForConsumers_.notify_all();
}


template<typename T>
void
ThreadSafeQueue<T>::pop(value_type& v)
{
    UniqueLock lck(mutex_);

    cVForConsumers_.wait(lck, [this] {
        return !dataQueue_.empty();
    });

    v = dataQueue_.front();
    dataQueue_.pop();

    if (!reachedToMax_ && dataQueue_.size() < maxSize_)
        cVForProducers_.notify_all();
}

template<typename T>
bool
ThreadSafeQueue<T>::empty() const
{
    SharedLock lck(mutex_);
    return dataQueue_.empty();
}

template<typename T>
auto
ThreadSafeQueue<T>::size() const
{
    SharedLock lck(mutex_);
    return dataQueue_.size();
}

}