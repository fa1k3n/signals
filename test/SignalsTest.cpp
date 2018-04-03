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
	Signals::connect(&tst, &testEmitter::noArgSignal, [&hasBeenCalled]() {
		hasBeenCalled = true;
	});
	emit tst.noArgSignal();
	EXPECT_TRUE(hasBeenCalled);
}

TEST(signal, basicMethodConnect) {
	testEmitter tst;
	EXPECT_CALL(tst, noArgsSlot());
	Signals::connect(&tst, &testEmitter::noArgSignal, &tst, &testEmitter::noArgsSlot);
	emit tst.noArgSignal();
}

bool funCalled = false;
void fun() {
	funCalled = true;
}

TEST(signal, basicFunctionConnect) {
	testEmitter tst;
	Signals::connect(&tst, &testEmitter::noArgSignal, &fun);
	emit tst.noArgSignal();
	EXPECT_TRUE(funCalled);
}

TEST(signal, twoArgumentConnect) {
    testEmitter tst;
    EXPECT_CALL(tst, twoArgsSlot(1, "foo bar"));
    Signals::connect(&tst, &testEmitter::twoArgSignal, &tst, &testEmitter::twoArgsSlot);
    emit tst.twoArgSignal(1, "foo bar");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}