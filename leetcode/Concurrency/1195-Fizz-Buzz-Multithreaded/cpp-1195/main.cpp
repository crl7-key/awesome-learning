#include <iostream>
#include <functional>
#include<thread>
#include<mutex>
#include <condition_variable>

using namespace std;

class FizzBuzz {
private:
    int n;
    int count;
    mutex m;
    condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
        this->count = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> lock(m);
            while (count <= n && (count % 3 != 0 || count % 5 == 0))
                cv.wait(lock);
            if (count > n) return;
            printFizz();
            ++count;
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
         while (true) {
            unique_lock<mutex> lock(m);
            while (count <= n && (count % 5 != 0 || count % 3 == 0))
                cv.wait(lock);
            if (count > n) return;
            printBuzz();
            ++count;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> lock(m);
            while (count <= n && (count % 5 != 0 || count % 3 != 0))
                cv.wait(lock);
            if (count > n) return;
            printFizzBuzz();
            ++count;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
           while (true) {
            unique_lock<mutex> lock(m);
            while (count <= n && (count % 5 == 0 || count % 3 == 0))
                cv.wait(lock);
            if (count > n) return;
            printNumber(count++);
            cv.notify_all();
        }
    }
};


int main(int argc, char const *argv[])
{
    FizzBuzz fz(15);

    function<void()> fizz = []() {
        cout << "fizz" << endl;
    };

    function<void()> buzz = []() {
        cout << "buzz" << endl;
    };

    function<void()> fizzbuzz = []() {
        cout << "fizzbuzz" << endl;
    };

    function<void(int)> num = [](int n) {
        cout << n << endl;
    };

    thread th1([&]() {
        fz.fizz(fizz);
    });
    thread th2([&]() {
        fz.buzz(buzz);
    });
    thread th3([&]() {
        fz.fizzbuzz(fizzbuzz);
    });
    thread th4([&]() {
        fz.number(num);
    });
    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}
