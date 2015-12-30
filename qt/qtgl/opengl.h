
// ------------------------------
// include correct OpenGL header.
// ------------------------------

#ifndef _opengl_h_
#define _opengl_h_

#if defined QT_OPENGL_LIB
# include <QOpenGL>
#elif defined QT_GUI_LIB
# include <QtOpenGL/qgl.h>
#endif

#endif // _opengl_h_

