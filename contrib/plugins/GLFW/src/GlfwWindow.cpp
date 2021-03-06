/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GlfwWindow.h>
#include <iostream>

namespace MinVR {

GlfwWindow::GlfwWindow(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), window(NULL) {
	setAllowThreading(true);
}

GlfwWindow::~GlfwWindow() {
	glfwDestroyWindow(window);
}

void GlfwWindow::useDisplay(const MinVR::VRDisplayAction& action) {
	glfwMakeContextCurrent(window);
	action.exec();
	glfwMakeContextCurrent(NULL);
}

int GlfwWindow::getWidth() {
	glfwGetFramebufferSize(window, &width, &height);
	return width;
}

int GlfwWindow::getHeight() {
	glfwGetFramebufferSize(window, &width, &height);
	return height;
}

void GlfwWindow::initialize() {
	glfwDefaultWindowHints();

	if (isQuadbuffered())
	{
		glfwWindowHint(GLFW_STEREO, true);
	}

	window = glfwCreateWindow(width, height, getName().c_str(), NULL, NULL);
	if (!window)
	{
		std::cout << "Error creating window." << std::endl;
	}

	std::cout << "Created window." << std::endl;
	glfwSetWindowPos(window, x, y);
	glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    inputDevice->registerGlfwWindow(window);

	glfwMakeContextCurrent(NULL);
}

void GlfwWindow::startRendering(const MinVR::VRRenderer& renderer, VRRenderState& state) {
	glfwMakeContextCurrent(window);
	glViewport(0, 0, getWidth(), getHeight());
	startRenderingAllDisplays(renderer, state);
	glFlush();
	glfwMakeContextCurrent(NULL);
}

bool GlfwWindow::isOpen() {
	return !glfwWindowShouldClose(window);
}

void GlfwWindow::finishRendering() {
	glfwMakeContextCurrent(window);
	finishRenderingAllDisplays();

	glfwSwapBuffers(window);
	glfwMakeContextCurrent(NULL);
}

//void GlfwWindow::addSubDisplay(VRDisplayDevice* display) {
//	subDisplays.push_back(display);
//}

} /* namespace MinVR */
