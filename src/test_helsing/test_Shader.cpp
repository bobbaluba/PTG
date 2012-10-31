/*
 * test_shader.cpp
 *
 * @date 27. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <helsing/Shader.hpp>
#include <helsing/Application.hpp>

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class TestApplication : public helsing::Application {
public:
	TestApplication(void(*test)(TestApplication&, uint32_t ticks)):Application(),test(test), ticks(0){}
	virtual void onRender(){
		ticks++;
		test(*this, ticks);
	}
	void (*test)(TestApplication&, uint32_t ticks);
	uint32_t ticks;
};

void ctordtor(){
	cout << "Testing constructor and destructor...";

	auto theTest = [] (TestApplication& app, uint32_t ticks) {
		if(ticks==3){
			helsing::Shader* shader = new helsing::Shader("#version 140\nvoid main() {}");
			delete shader;
		}
		if(ticks>10)app.stop();
	};
	TestApplication app(theTest);
	app.start();


	cout << "OK\n";
}

int main(){
	cout << "\nTesting basic Shader class:\n\n";

	ctordtor();

	cout << "\nAll tests completed\n\n";
	return EXIT_SUCCESS;
}


