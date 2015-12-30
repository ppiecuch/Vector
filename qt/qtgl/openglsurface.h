#ifndef OPENGLSURFACE_H
#define OPENGLSURFACE_H

#include <QtCore/QTime>
#include <QtGui/QWindow>


QT_FORWARD_DECLARE_CLASS( QEvent );
QT_FORWARD_DECLARE_CLASS( QExposeEvent );
QT_FORWARD_DECLARE_CLASS( QOpenGLContext );
QT_FORWARD_DECLARE_CLASS( QResizeEvent );
QT_FORWARD_DECLARE_CLASS( QScreen );


namespace core { class OpenGLRenderer; }


class OpenGLSurface : public QWindow
{
    Q_OBJECT
    Q_PROPERTY(bool alwaysRefresh READ alwaysRefresh WRITE setAlwaysRefresh)
    
public:
    explicit OpenGLSurface(QScreen *screen = 0);
    explicit OpenGLSurface(QWindow *parent);
    virtual ~OpenGLSurface();
    
    void printContextInfos();
    
    bool alwaysRefresh() const;
    void setAlwaysRefresh(bool alwaysRefresh);
    
    QOpenGLContext const *context() { return _context; }

protected:
    virtual bool event(QEvent *event);
    virtual void exposeEvent(QExposeEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

public slots:
    void render();
    void requestRefresh();
    
private:
    void initialize();

    QOpenGLContext *_context;
    core::OpenGLRenderer *_renderer;
    
    bool _alwaysRefresh;
    bool _pendingRefresh;
    QTime _time;
};

#endif // OPENGLSURFACE_H
