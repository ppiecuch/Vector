#ifndef _openglconfig_h_
#define _openglconfig_h_

#include <QSettings>

extern QString glInfo;
extern bool glSupportsThreading;

class OpenGLConfig : public QSettings
{
 public:
  Q_PROPERTY(bool core READ isCore WRITE setCore NOTIFY coreChanged);
  Q_PROPERTY(bool debug READ isDebug WRITE setDebug NOTIFY debugChanged);
  Q_PROPERTY(int depth READ surfDepth WRITE setSurfDepth NOTIFY depthChanged);
  Q_PROPERTY(int sample READ surfSample WRITE setSurfSample NOTIFY sampleChanged);

 public:
  OpenGLConfig() {
    m_saveAsDefaults = false;
    m_isCore = false;
    m_isDebug = false;
    m_surfDepth = 16;
    m_surfSample = 4;
  }
  
 public:
  static OpenGLConfig &Default();

  bool isCore() const { return m_isCore; }
  bool isDebug() const { return m_isDebug; }

 signals:
  void coreChanged();

 private:
  bool m_saveAsDefaults;
  bool m_isCore;
  bool m_isDebug;
  int m_surfDepth;
  int m_surfSample;
};

#endif // _openglconfig_h_
