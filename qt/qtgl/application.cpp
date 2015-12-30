#include "opengl.h"
#include "application.h"
#include "openglconfig.h"
#include "openglsurface.h"
#include "threadrenderer.h"

#include <QDebug>
#include <QKeyEvent>
#ifdef QT_WIDGETS_LIB
# include <QVBoxLayout>
# include <QMenuBar>
# include <QOpenGLWidget>
#endif
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QApplication>

static QString getGlString(QOpenGLFunctions *functions, GLenum name)
{
    if (const GLubyte *p = functions->glGetString(name))
        return QString::fromLatin1(reinterpret_cast<const char *>(p));
    return QString();
}

class ApplicationPrivate
{
public:
  ApplicationPrivate(Application *parent):
    q_ptr( parent )
  {}

  OpenGLSurface *disp;

  Application * const q_ptr;
  Q_DECLARE_PUBLIC(Application);
};

Application::Application() : d_ptr(new ApplicationPrivate(this)), _layout(new QVBoxLayout)
{
    Q_D(Application);

    d->disp = new OpenGLSurface();

    glInfo = getGlString(d->disp->context()->functions(), GL_VENDOR)
        + QLatin1Char('/') + getGlString(d->disp->context()->functions(), GL_RENDERER);

    glSupportsThreading = !glInfo.contains(QLatin1String("nouveau"), Qt::CaseInsensitive)
        && !glInfo.contains(QLatin1String("ANGLE"), Qt::CaseInsensitive)
        && !glInfo.contains(QLatin1String("llvmpipe"), Qt::CaseInsensitive);

    QWidget *container = QWidget::createWindowContainer(d->disp, const_cast<Application *>(this));
    
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->addWidget(container);
    setLayout(_layout);

    QMetaObject::invokeMethod(this, "setWindowTitle", Q_ARG(QString, glInfo));
    const QString toolTip = glSupportsThreading ? glInfo : glInfo + QStringLiteral("\ndoes not support threaded OpenGL.");
    QMetaObject::invokeMethod(this, "setToolTip", Q_ARG(QString, toolTip));
}

Application::~Application() 
{ 
  delete d_ptr; 
}

QMenuBar *Application::menuBar() const
{
    QMenuBar *menuBar = qobject_cast<QMenuBar *>(_layout->menuBar());
    if (!menuBar) {
        Application *self = const_cast<Application *>(this);
        menuBar = new QMenuBar(self);
        self->setMenuBar(menuBar);
    }
    
    return menuBar;
}

void Application::setMenuBar(QMenuBar *menuBar)
{
    if (_layout->menuBar() && _layout->menuBar() != menuBar) {
        QMenuBar *old = qobject_cast<QMenuBar *>(_layout->menuBar());
        old->hide();
        old->deleteLater();
    }
    
    _layout->setMenuBar(menuBar);
}

void Application::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
  }
}
