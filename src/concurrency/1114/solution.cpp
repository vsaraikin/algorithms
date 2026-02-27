#include <iostream>
#include <mutex>

using namespace std;

// solution 1

//class Foo {
//private:
//    mutex mu;
//    condition_variable cv;
//    int count = 0;
//public:
//
//    Foo() {
//    }
//
//    void first(function<void()> printFirst) {
//        unique_lock lock(mu);
//        printFirst();
//        count = 1;
//        cv.notify_all();
//    }
//
//    void second(function<void()> printSecond) {
//        unique_lock lock(mu);
//        cv.wait(lock, [&]{return count == 1;});
//        printSecond();
//        count = 2;
//        cv.notify_all();
//    }
//
//    void third(function<void()> printThird) {
//        unique_lock lock(mu);
//        printThird();
//        cv.wait(lock, [&]{return count == 3;});
//    }
//
//};

// solution 2

// probably the best solution, because it uses atomic operations instead of mutexes and condition variables
// which are more expensive

class Foo {
private:
   atomic<int> state;
public:

   Foo() {
   }

   void first(function<void()> printFirst) {
       printFirst();
       state.store(1, std::memory_order_release);
   }

   void second(function<void()> printSecond) {
       while (state.load(std::memory_order_acquire) < 1);
       printSecond();
       state.store(2, std::memory_order_release);
   }

   void third(function<void()> printThird) {
       while (state.load(std::memory_order_acquire) < 2);
       printThird();
   }

};

// solution 3

//#include <semaphore>
//
//class Foo {
//private:
//    binary_semaphore sem1{0};
//    binary_semaphore sem2{0};
//public:
//
//    Foo() {
//    }
//
//    void first(function<void()> printFirst) {
//        printFirst();
//        sem1.release();
//    }
//
//    void second(function<void()> printSecond) {
//        sem1.acquire();
//        printSecond();
//        sem2.release();
//    }
//
//    void third(function<void()> printThird) {
//        sem2.acquire();
//        printThird();
//    }
//
//};
//
