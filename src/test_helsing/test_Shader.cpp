/**
 * @file test_shader.cpp
 * @date 27. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <helsing/Shader.hpp>
#include <helsing/SFMLApplication.hpp>

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

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

void ctordtor(){
	cout << "Testing constructor and destructor...";

	auto theTest = [] (TestApplication& app, uint32_t ticks) {
		if(ticks==3){
			const std::string vertexShader = "#version 120\nvoid main() {gl_Position = gl_Vertex;}";
			const std::string fragmentShader = "#version 120\nvoid main() {}";
			helsing::Shader* shader = new helsing::Shader(vertexShader,fragmentShader);
			delete shader;
		}
		if(ticks>10)app.stop();
	};
	TestApplication app(theTest);
	app.start();


	cout << "OK\n";
}

void flatShader(){
	cout << "Testing flat shader...";

	auto theTest = [] (TestApplication& app, uint32_t ticks) {
		if(ticks==3){
			const std::string vertexShader = "#version 120\nvoid main() {gl_Position = gl_Vertex;}";
			const std::string fragmentShader = "#version 120\nvoid main() {}";
			helsing::Shader(vertexShader,fragmentShader);
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
	flatShader();

	cout << "\nAll tests completed\n\n";
	return EXIT_SUCCESS;
}


