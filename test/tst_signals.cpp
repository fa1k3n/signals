#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <signals/signal.hpp>

#include <string>

using namespace testing;

class testEmitter {
public:
	MOCK_METHOD0(noArgsSlot, void());
    MOCK_METHOD2(twoArgsSlot, void(int, std::string));
	Signals::signal<> noArgSignal;
    Signals::signal<int, std::string> twoArgSignal;
};

TEST(signal, basicLambdaConnect) {
	testEmitter tst;
	bool hasBeenCalled = false;
	Signals::connect(&testEmitter::noArgSignal, &tst, [&hasBeenCalled]() {
		hasBeenCalled = true;
	});
	emit tst.noArgSignal();
	EXPECT_TRUE(hasBeenCalled);
}

TEST(signal, basicMethodConnect) {
	testEmitter tst;
	EXPECT_CALL(tst, noArgsSlot());
	Signals::connect(&testEmitter::noArgSignal, &tst, &testEmitter::noArgsSlot, &tst);
	emit tst.noArgSignal();
}

bool funCalled = false;
void fun() {
	funCalled = true;
}

TEST(signal, basicFunctionConnect) {
	testEmitter tst;
	Signals::connect(&testEmitter::noArgSignal, &tst, &fun);
	emit tst.noArgSignal();
	EXPECT_TRUE(funCalled);
}

TEST(signal, twoArgumentConnect) {
    testEmitter tst;
    EXPECT_CALL(tst, twoArgsSlot(1, "foo bar"));
    Signals::connect(&testEmitter::twoArgSignal, &tst, &testEmitter::twoArgsSlot, &tst);
    emit tst.twoArgSignal(1, "foo bar");
}

