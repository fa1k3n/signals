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

    Signals::signal<int> intSignal;
    Signals::signal<> voidSignal;
    Signals::signal<bool, std::string> boolStringSignal;
