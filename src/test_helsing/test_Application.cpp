/**
 * @file test_Application.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <helsing/SFMLApplication.hpp>

#include <iostream>
#include <cassert>

namespace {

class TestApplication : public helsing::SFMLApplication {
public:
	TestApplication(void(*test)(TestApplication&, uint32_t ticks)):SFMLApplication(),test(test), ticks(0){}
	virtual void onRender(){
		ticks++;
		test(*this, ticks);
	}
	void (*test)(TestApplication&, uint32_t ticks);
	uint32_t ticks;
};

void simpleUse(){
	std::cout << "Testing simple usage...";
	std::cout.flush();
	auto theTest = [] (TestApplication& app, uint32_t ticks) {
		if(ticks>10)app.stop();
	};
	TestApplication app(theTest);
	app.start();
	std::cout << "OK!\n";
}

void secondApplication(){
	std::cout << "Testing two sequential applications...";
	std::cout.flush();
	auto theTest = [] (TestApplication& app, uint32_t ticks) {
		if(ticks>10)app.stop();
	};
	TestApplication app(theTest);
	app.start();
	TestApplication app2(theTest);
	app2.start();
	std::cout << "OK!\n";
}

void test_Application(){
	std::cout << "Testing Application class\n\n";
	simpleUse();
//	secondApplication();
//	resizing();
	std::cout << "\nAll tests completed\n\n";
}

}

int main(){
	test_Application();
	return EXIT_SUCCESS;
}
