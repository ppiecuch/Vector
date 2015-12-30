#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QOpenGLContext>
#include <QtGui/QResizeEvent>
#include <QtGui/QScreen>
#include <QtGui/QSurfaceFormat>

#include "glassert.h"
#include "common.h"
#include "openglrenderer.h"
#include "openglsurface.h"


static void infoGL()
{
    glCheckError();
    std::cout << "OpenGL infos with gl functions" << std::endl;
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    glCheckError();
}

OpenGLSurface::OpenGLSurface(QScreen *screen)
    : QWindow(screen),
      _context(0),
      _renderer(0),
      _alwaysRefresh(false),
      _pendingRefresh(false)
{
    initialize();
}

OpenGLSurface::OpenGLSurface(QWindow *parent)
    : QWindow(parent),
      _context(0),
      _renderer(0),
      _alwaysRefresh(false),
      _pendingRefresh(false)
{
    initialize();
}

OpenGLSurface::~OpenGLSurface()
{
    _renderer->cleanup();
    delete _renderer;
    delete _context;
}


//- Public properties.

void OpenGLSurface::printContextInfos()
{
    if(!_context->isValid())
        std::cerr << "The OpenGL context is invalid!" << std::endl;

    _context->makeCurrent(this);

    std::cout << "Window format version is: "
              << format().majorVersion() << "."
              << format().minorVersion() << std::endl;

    std::cout << "Context format version is: "
              << _context->format().majorVersion()
              << "." << _context->format().minorVersion() << std::endl;
    infoGL();
}


bool OpenGLSurface::alwaysRefresh() const
{
    return _alwaysRefresh;
}

void OpenGLSurface::setAlwaysRefresh(bool alwaysRefresh)
{
    _alwaysRefresh = alwaysRefresh;
    if (alwaysRefresh) {
        requestRefresh();
    }
}


//- Protected methods.

bool OpenGLSurface::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::UpdateRequest:
            _pendingRefresh = false;
            render();
            return true;
        
        default:
            return QWindow::event(event);
    }
}

void OpenGLSurface::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);
    
    if (isExposed()) {
        render();
    }
}

void OpenGLSurface::resizeEvent(QResizeEvent *event)
{
    _renderer->setSize(event->size().width() * devicePixelRatio(),
                       event->size().height() * devicePixelRatio());
    requestRefresh();
}


//- Private methods.

void OpenGLSurface::initialize()
{
    setSurfaceType(QWindow::OpenGLSurface);
    
    QSurfaceFormat format;

    if (core::profile == core::OpenGLCoreProfile) {
        format.setProfile(QSurfaceFormat::CoreProfile);
    	format.setVersion(core::majorVersion, core::minorVersion);
    	setFormat(format);
    }
    else if (core::profile == core::OpenGLCompatibilityProfile) {
        format.setProfile(QSurfaceFormat::CompatibilityProfile);
    	format.setVersion(core::majorVersion, core::minorVersion);
    	setFormat(format);
    }
    else if (core::profile == core::OpenGLDefaultProfile) {
        format.setProfile(QSurfaceFormat::NoProfile);
    	setFormat(format);
    } else
    	// Use default format only.
    	;
    
    create();
    
    _context = new QOpenGLContext(this);
    _context->setFormat(requestedFormat());
    _context->create();
    
    _renderer = new core::OpenGLRenderer(width() * devicePixelRatio(),
                                         height() * devicePixelRatio());
    
    _context->makeCurrent(this);
    _renderer->setup();

	infoGL();

    _time.start();
}

void OpenGLSurface::render()
{
    if (!isExposed()) {
        return;
    }
    
    _context->makeCurrent(this);
    _renderer->draw(_time.elapsed());
    _context->swapBuffers(this);
    
    if (_alwaysRefresh) {
        requestRefresh();
    }
}

void OpenGLSurface::requestRefresh()
{
    if (!_pendingRefresh) {
        _pendingRefresh = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}
