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