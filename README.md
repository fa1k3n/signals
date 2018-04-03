[![Build status](https://travis-ci.org/fa1k3n/signals.svg?branch=master)](https://travis-ci.org/fa1k3n/signals)

# signals

A small wrapper around boost::signals2 library to simplify the API and align more towards Qt signal-slot mechanism

# Requirements

* boost 1.58.0 or later installed
* googletest for testcases

# Building

    mkdir build & cd build
    cmake ..
    make unittest
    
# Usage

A signal is declared using the signal<T...> type in Signals namespace, e.g.
```c++
Signals::signal<int> intSignal;
Signals::signal<> voidSignal;
Signals::signal<bool, std::string> boolStringSignal;
```

A slot is just a function/method that matches the signal parameters, in Signals ALL signals are returning void. The corresponding slots to above signals are 
```c++
void intSlot(int iVal);
void voidSlot(void);
void boolStringSlot(bool bVal, std::string sVal);
```
observe that the function and parameter can be named as needed, there is no induced logic on these.

A signals can be connected to any number of slots using one of the Signals::connect functions, e.g. 
```c++
Signals::connect(this, &ThisClass::intSignal, this, &ThisClass::intSlot);
Signals::connect(this, &ThisClass::intSignal, &intFuntion);
Signals::connect(this, &ThisClass::intSignal, [](int iVal) {});
```
Connect support connecting to class method, function and lambda. Connections over threads are currently not supported (untested, might work)

A signal "emitted" by calling it as a function
```c++
intSignal(1);       // Send signal with value 1
emit intSignal(1);  // Equivalent to prev call
```
for clarity of reading Signals defines the macro emit which will resolve to nothing, it is just syntax sugaring. 

# Example

```c++
#include <signals/signal.hpp>
#include <iostream>
#include <string>

class SayerClass {
public:
    Signals::signal<std::string> sayWhat;
};

class WriterClass {
public:
    void writeIt(std::string what) {
        std::cout << what << std::endl;
    }
};

int main(void) {
    SayerClass sc;
    WriterClass wc;
    Signals::connect(&sc, &SayerClass::sayWhat, &wc, &WriterClass::writeIt);
    emit sc.sayWhat("Hello Signals");
    return 0;
}
```
