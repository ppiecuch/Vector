#include "openglconfig.h"

QString glInfo;
bool    glSupportsThreading;

OpenGLConfig &OpenGLConfig::Default()
{
  static OpenGLConfig _default;

  return _default;
}

