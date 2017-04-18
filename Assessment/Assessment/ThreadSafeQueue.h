#pragma once

#include <queue>
#include <condition_variable>
#include <shared_mutex>

namespace Parallel
{

template<typename T>
class ThreadSafeQueue
{
public: // public interface
  typedef typename std::queue<T>::value_type value_type;
  typedef typename std::queue<T>::size_type  size_type;

public:
  ThreadSafeQueue(size_type maxSize = 1000);

  void push(const value_type v);
  void pop(value_type& v);

  bool empty() const;
  auto size() const;

private: // members
  std::queue<value_type>   dataQueue_;
  mutable std::shared_mutex mutex_;

  std::condition_variable_any  cVForProducers_;
  std::condition_variable_any  cVForConsumers_;
  bool                         reachedToMax_;
  size_type                    maxSize_;
};

}
