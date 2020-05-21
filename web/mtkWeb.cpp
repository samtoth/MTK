//
// Created by samt on 19/05/2020.
//

#include <emscripten/bind.h>
#include <string>

std::string getVersion(){
	return MTK_VERSION;
}

EMSCRIPTEN_BINDINGS(MTK_module) {
	emscripten::function<std::string>("getVersion", &getVersion);
}
