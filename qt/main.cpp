
#include <QDebug>
#include <QDirIterator>
#include <QTime>
#include <QElapsedTimer>
#include <QWaitCondition>
#include <QMouseEvent>
#include <QPainter>
#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLFunctions>
#include <QApplication>

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "stb_easy_font.h"

#include "VectorTest.h"


/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPLES last frames */

qreal CalcAverageTick(qreal newtick)
{
    const int MAXSAMPLES = 100;
    static qreal ticksum=0;
    static int tickindex=0;
    static int ticklist[MAXSAMPLES] = { 0 };
    ticksum-=ticklist[tickindex];  /* subtract value falling off */
    ticksum+=newtick;              /* add new value */
    ticklist[tickindex]=newtick;   /* save new value so it can be subtracted later */
    if(++tickindex==MAXSAMPLES)    /* inc buffer index */
        tickindex=0;
    /* return average */
    return ticksum/MAXSAMPLES;
}

void print_string(float x, float y, const char *text, float r = 1, float g = 1, float b = 1)
{
  static char buffer[99999]; // ~500 chars
  int num_quads;

  num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

  glColor3f(r,g,b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 16, buffer);
  glDrawArrays(GL_QUADS, 0, num_quads*4);
  glDisableClientState(GL_VERTEX_ARRAY);
}

class SleepSimulator {
	QMutex localMutex;
	QWaitCondition sleepSimulator;
public:
	SleepSimulator() { localMutex.lock(); }
	void sleep(unsigned long sleepMS) { sleepSimulator.wait(&localMutex, sleepMS); }
	void CancelSleep() { sleepSimulator.wakeAll(); }
};

double qtGetTime() {
	static QElapsedTimer timer;
	if (!timer.isValid())
	timer.start();
	return timer.elapsed() / 1000; 
}

void qtDelay(long ms) {
	SleepSimulator s;
	s.sleep(ms);
}


// == Sim interface ==


struct Event
{
	enum EvType {
		EV_QUIT,
		EV_KEYDOWN
	};
	enum EvKey {
		KEY_ESCAPE
	};
	Event() {}
	
	EvType type;
	EvKey keysym;
	
};


// == Qt Window ==

class Window : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT
private:
	bool m_done, m_update_pending, m_resize_pending, m_auto_refresh;
	QOpenGLContext *m_context;
	QOpenGLPaintDevice *m_device;

	Event ev;

    VectorTest test;
    int test_nr;

public:
	QPoint cursorPos;
public:
	Window(QWindow *parent = 0) : QWindow(parent)
	, m_update_pending(false)
	, m_resize_pending(false)
	, m_auto_refresh(false)
	, m_context(0)
	, m_device(0)
	, m_done(false)
	, test_nr(4) {
		setSurfaceType(QWindow::OpenGLSurface);
	}
	~Window() { delete m_device; }
	void setAutoRefresh(bool a) { m_auto_refresh = a; }
	void render(QPainter *painter) {
		Q_UNUSED(painter);

		test.draw(test_nr);

		static QElapsedTimer up = [](){
	    	QElapsedTimer _t; _t.start(); return _t;
	    } ();
	}
	void timerEvent(QTimerEvent *event) {
        update();
	}
	void initialize() {
		qDebug() << "OpenGL infos with gl functions:";
		qDebug() << "-------------------------------";
		qDebug() << " Renderer:" << (const char*)glGetString(GL_RENDERER);
		qDebug() << " Vendor:" << (const char*)glGetString(GL_VENDOR);
		qDebug() << " OpenGL Version:" << (const char*)glGetString(GL_VERSION);
		qDebug() << " GLSL Version:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		setTitle((const char*)glGetString(GL_RENDERER));
		test.prepare(width(), height(), devicePixelRatio());
		startTimer(0);
	}
	void update() { renderLater(); }
	void reshape() {
		const int w = width(), h = height();
		test.reshape(w, h, devicePixelRatio());
	}
	void render() {
		if (!m_device) m_device = new QOpenGLPaintDevice;
		m_device->setSize(size());
		QPainter painter(m_device);
		render(&painter);
	}
	void mousePressEvent(QMouseEvent *event) {
		cursorPos = QPoint(event->x(), event->y());
		Qt::KeyboardModifiers modifiers = event->modifiers();
		if (event->buttons() & Qt::LeftButton) { }
	}
	void mouseReleaseEvent(QMouseEvent *event) {
		cursorPos = QPoint(event->x(), event->y());
		Qt::KeyboardModifiers modifiers = event->modifiers();
		if (event->button() == Qt::LeftButton) { }
	}
	void mouseMoveEvent(QMouseEvent *event) {
		cursorPos = QPoint(event->x(), event->y());
	}
	void keyPressEvent(QKeyEvent* event) {
		switch(event->key()) {
			case Qt::Key_Escape: quit(); break;
			case Qt::Key_Space: ++test_nr; break;
			default: event->ignore();
			break;
		}
	}
	void quit() { m_done = true; }
	bool done() const { return m_done; }
protected:
	void closeEvent(QCloseEvent *event) { quit(); }
	bool event(QEvent *event) {
		switch (event->type()) {
			case QEvent::UpdateRequest:
				m_update_pending = false;
				renderNow();
				return true;
			default:
				return QWindow::event(event);
		}
	}
	void exposeEvent(QExposeEvent *event) {
		Q_UNUSED(event);
		if (isExposed()) renderNow();
	}
	void resizeEvent(QResizeEvent *event)
	{
		if (!m_resize_pending) {
			m_resize_pending = true;
			renderLater();
		}
	}
public slots:
	void renderLater() {
		if (!m_update_pending) {
			m_update_pending = true;
			QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
		}
	}
	void renderNow() {
		if (!isExposed()) return;
		bool needsInitialize = false;
		if (!m_context) {
			m_context = new QOpenGLContext(this);
			m_context->setFormat(requestedFormat());
			m_context->create();
			needsInitialize = true;
		}
		m_context->makeCurrent(this);
		if (needsInitialize) {
			initializeOpenGLFunctions();
			initialize();
		}
		if (m_resize_pending) {
			m_resize_pending = false;
			reshape();
		}
		render();
		m_context->swapBuffers(this);
		if (m_auto_refresh) renderLater();
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	Window win;
	win.resize(800, 600);
	win.show();
	return app.exec();
}

#include "main.moc"
