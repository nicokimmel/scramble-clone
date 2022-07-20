#include <iostream>
#include <memory>

#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char** argv) {
	
	auto view = std::make_shared<View>();
	view->init();
	auto controller = std::make_shared<Controller>(view);
	controller->init();
	controller->start();
	
	return 0;
}