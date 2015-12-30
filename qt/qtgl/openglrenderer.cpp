#include <stdexcept>

#include "opengl.h"
#include "openglrenderer.h"

#include "../VectorTest.h"

using namespace core;


class OpenGLRenderer::Impl
{
public:
    Impl(GLint width, GLint height);
    
    void updateViewport();
    
public:
    bool setup;
    
    GLint width;
    GLint height;
    
    VectorTest test;
};


OpenGLRenderer::Impl::Impl(GLint width, GLint height)
    : setup(false),
      width(width),
      height(height)
{}


//- Public members.

void
OpenGLRenderer::Impl::updateViewport()
{
    glViewport(0, 0, width, height);
	test.reshape(width, height);
}


// OpenGLRenderer class.
OpenGLRenderer::OpenGLRenderer(int width, int height)
    : _d(new Impl(width, height))
{}

OpenGLRenderer::~OpenGLRenderer()
{
    delete _d;
}


//- Public methods.

void
OpenGLRenderer::setup()
{
    // Setup OpenGL here.
}

void
OpenGLRenderer::draw(double time)
{

    if (_d->setup)
		_d->test.draw();
	
}

void
OpenGLRenderer::cleanup()
{
}

void
OpenGLRenderer::setSize(int width, int height)
{
    _d->width = width;
    _d->height = height;
    if (!_d->setup) {
    	_d->test.prepare(width, height);
    }
    
    _d->setup = true;
    
    _d->updateViewport();
}
