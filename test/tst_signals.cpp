#include <gtest/gtest.h>

#include <signals/signal.hpp>

using namespace testing;

class testEmitter {
public:
	Signals::signal<> tstNoArgSignal;
};

TEST(line, basicConnect) {
	testEmitter tst;
	Signals::connect(&testEmitter::tstNoArgSignal, &tst, []() {

	});
}
