#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <signals/signal.hpp>

using namespace testing;

class testEmitter {
public:
	MOCK_METHOD0(noArgsSlot, void());
	Signals::signal<> noArgSignal;
};

TEST(line, basicLambdaConnect) {
	testEmitter tst;
	bool hasBeenCalled = false;
	Signals::connect(&testEmitter::noArgSignal, &tst, [&hasBeenCalled]() {
		hasBeenCalled = true;
	});
	emit tst.noArgSignal();
	EXPECT_TRUE(hasBeenCalled);
}

TEST(line, basicMethodConnect) {
	testEmitter tst;
	EXPECT_CALL(tst, noArgsSlot());
	Signals::connect(&testEmitter::noArgSignal, &tst, &testEmitter::noArgsSlot, &tst);
	emit tst.noArgSignal();
}

bool funCalled = false;
void fun() {
	funCalled = true;
}

TEST(line, basicFunctionConnect) {
	testEmitter tst;
	Signals::connect(&testEmitter::noArgSignal, &tst, &fun);
	emit tst.noArgSignal();
	EXPECT_TRUE(funCalled);
}

