#pragma once

#include <chrono>
#include <thread>
#include <vector>

#include "SleepSort.h"

struct Widget
{
   explicit Widget(unsigned int);
   unsigned int i;
};

struct Widget2
{
};

template<std::integral T>
unsigned int intRepr(T a)
{
   return static_cast<unsigned>(a);
}
unsigned int intRepr(const Widget&);
unsigned int intRepr(const std::string&);



template<typename T>
concept IntRepresentable = requires(T a) {
   {intRepr(a)} -> std::unsigned_integral;
};

template<typename T> requires IntRepresentable<T>
   std::vector<T> sleepSort(const std::vector<T>& source)
{
   std::vector<T> outVector;
   outVector.reserve(source.size());

   std::vector<std::thread> threads;
   outVector.reserve(threads.size());

   std::mutex vector_mutex;

   std::mutex mutex;
   std::unique_lock uniqueLock(mutex);

   std::condition_variable conditionVar;
   bool isReady = false;

   auto processItem = [&vector_mutex, &outVector, &mutex, &conditionVar, &isReady](const T& item) {
      std::unique_lock lk(mutex);
      conditionVar.wait(lk, [&isReady] {return isReady; });
      lk.unlock();

      std::this_thread::sleep_for(std::chrono::milliseconds(intRepr(item) * 10));

      {
         std::lock_guard lockGuard(vector_mutex);
         outVector.push_back(item);
      }
   };

   for(const auto& item: source)
      threads.emplace_back([processItem, &item] { return processItem(item); });

   isReady = true;
   uniqueLock.unlock();
   conditionVar.notify_all();

   for (auto& t : threads)
      t.join();

   return outVector;
}
