/* Copyright 2011 Stanislaw Adaszewski. All rights reserved.

   Redistribution and use in source and binary forms, with or without modification, are
   permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
   conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
   of conditions and the following disclaimer in the documentation and/or other materials
   provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY STANISLAW ADASZEWSKI ``AS IS'' AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
   FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
   ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   The views and conclusions contained in the software and documentation are those of the
   authors and should not be interpreted as representing official policies, either expressed
   or implied, of Stanislaw Adaszewski. */

#include <iostream>
using namespace std;

#include "qinputeventrecorder.h"

#include <QContextMenuEvent>
#include <QFile>
#include <QDataStream>
#include <QTimer>
#include <QWidget>
#include <QApplication>

#include <iostream>
#include <fstream>
#include <assert.h>

//
// Helper routines
//

static QString objectPath(QObject *obj)
{
  QString res;
  for(; obj; obj = obj->parent())
	{
	  if (!res.isEmpty())
		res.prepend("/");
	  res.prepend(obj->objectName());
	}
  return res;
}

static bool isChild(QObject *obj, QObject *parent){
  while ((obj = obj->parent())){
	if (obj == parent)
	  return true;
  }
  return false;
}

//
// QInputEventRecorder::EventDelivery
//

QInputEventRecorder::EventDelivery::EventDelivery(int timeOffset, QObject *obj, QEvent *ev):
  m_TimeOffset(timeOffset),
  m_ClsName(obj->metaObject()->className()),
  m_ObjName(objectPath(obj)),
  m_Ev(ev)
{
	
}

//
// QInputEventRecorder
//

QEvent* QInputEventRecorder::cloneEvent(QEvent *ev){
  if (dynamic_cast<QContextMenuEvent*>(ev))
	return new QContextMenuEvent(*static_cast<QContextMenuEvent*>(ev));
  else if (dynamic_cast<QKeyEvent*>(ev))
	return new QKeyEvent(*static_cast<QKeyEvent*>(ev));
  else if (dynamic_cast<QMouseEvent*>(ev))
	return new QMouseEvent(*static_cast<QMouseEvent*>(ev));
  else if (dynamic_cast<QTabletEvent*>(ev))
	return new QTabletEvent(*static_cast<QTabletEvent*>(ev));
  else if (dynamic_cast<QTouchEvent*>(ev))
	return new QTouchEvent(*static_cast<QTouchEvent*>(ev));
  else if (dynamic_cast<QWheelEvent*>(ev))
	return new QWheelEvent(*static_cast<QWheelEvent*>(ev));

  return 0;
}

QInputEventRecorder::QInputEventRecorder(QObject *obj,QInputEventRecorderObserver *ob):
  m_Obj(obj),observer(ob),m_Timer(new QTimer),is_saving(false),enable_observer(false){

  m_ReplayPos = 0;
  m_Timer->setSingleShot(true);
  QObject::connect(m_Timer, SIGNAL(timeout()), this, SLOT(replayOp()));
}

QInputEventRecorder::~QInputEventRecorder(){
  delete m_Timer;
}

bool QInputEventRecorder::eventFilter(QObject *obj, QEvent *ev){

  if (!isChild(obj, m_Obj)){
  	return false;
  }

  QEvent *clonedEv = cloneEvent(ev);
  if (clonedEv){
	int timeOffset;
	QDateTime curDt(QDateTime::currentDateTime());
	timeOffset = m_RecordingStartTime.daysTo(curDt) * 24 * 3600 * 1000 + m_RecordingStartTime.time().msecsTo(curDt.time());
	m_Recording.push_back(EventDelivery(timeOffset, obj, clonedEv));
	emit updateTimeOffset();
  }

  return false;
}

void QInputEventRecorder::save(const QString &fileName){

  is_saving = true;
  QFile f(fileName);
  if (!f.open(QFile::WriteOnly))
	return;
	
  QDataStream ds(&f);
  int count = 0;
  foreach(EventDelivery ed, m_Recording){
	ds << (qint32) ed.timeOffset() << ed.clsName() << ed.objName();
	QEvent *ev(ed.event());
	ds << static_cast<QInputEvent*>(ev);
  }
}

void QInputEventRecorder::load(const QString &fileName){

  QFile f(fileName);
  if (!f.open(QFile::ReadOnly))
	return;

  m_Recording.clear();
  QDataStream ds(&f);
  while (!ds.atEnd())
	{
	  qint32 timeOffset;
	  QString clsName, objName;
	  ds >> timeOffset >> clsName >> objName;
	  QInputEvent *ev;
	  ds >> ev;
	  m_Recording.push_back(EventDelivery(timeOffset, clsName, objName, ev));
	}
  emit updateTimeOffset();
}

void QInputEventRecorder::nameAllWidgets(QWidget *w){

  static int uniqueId = 0;
  QObjectList children = w->children();
  foreach(QObject *o, children){
	if (dynamic_cast<QWidget*>(o)){
	  if (o->objectName().isEmpty())
		o->setObjectName(QString("unique_%1").arg(uniqueId++));
	  nameAllWidgets(static_cast<QWidget*>(o));
	}
  }
}

void QInputEventRecorder::record(){

  qApp->installEventFilter(this);
  m_RecordingStartTime = QDateTime::currentDateTime();
}

void QInputEventRecorder::stop(){

  qApp->removeEventFilter(this);
  m_Timer->stop();
  emit isPaused(true);
  if(enable_observer && observer!=NULL){
	observer->stopReplayOperations();
  }
}

void QInputEventRecorder::replayScaled(float speedFactor){

  qApp->removeEventFilter(this);
  m_Timer->stop();
  if (m_Recording.size() == 0){
	m_ReplayPos = 0;
	emit replayDone();
	return;
  }

  if(enable_observer && observer!=NULL){
	observer->startReplayOperations();
  }
  m_ReplayPos = 0;
  m_ReplaySpeedFactor = speedFactor;
  m_Timer->setInterval(0);
  m_Timer->start();
}

void QInputEventRecorder::replayOp(){

  if (m_Recording.size() <= m_ReplayPos ){
	stop();
	m_ReplayPos = 0;
	emit replayDone();
	return;
  }

  emit updateTimeOffset();
  EventDelivery& rec(m_Recording[m_ReplayPos++]);
  QStringList path = rec.objName().split("/", QString::KeepEmptyParts);
  if (path.size() > 0){
	QList<QObject*> objects = m_Obj->findChildren<QObject*>(path.last());
	foreach(QObject *obj, objects){
	  if (obj->metaObject()->className()==rec.clsName()&&objectPath(obj)==rec.objName()){
		qApp->postEvent(obj, cloneEvent(rec.event()));
		break;
	  }
	}
  }

  if (m_ReplayPos >= m_Recording.size()){
	stop();
	m_ReplayPos = 0;
	emit replayDone();
	return;
  }

  const int delta=m_Recording[m_ReplayPos].timeOffset()-m_Recording[m_ReplayPos-1].timeOffset();
  m_Timer->setInterval(delta > 0 ? delta * m_ReplaySpeedFactor : 0);
  m_Timer->start();
}

int QInputEventRecorder::removeTheEventsAfter(const int step){

  stop();
  assert(step >= 0);
  const int i0 = step>0?step:0;
  int removed = 0;
  if(i0 < m_Recording.size()){
	removed = m_Recording.size()-i0;
	m_Recording.erase(m_Recording.begin()+step,m_Recording.end());
  }
  emit updateTimeOffset();
  return removed;
}

int QInputEventRecorder::totalTimeOffset()const{

  if (m_Recording.size() > 0)
	return m_Recording[m_Recording.size()-1].timeOffset();
  return 0;
}

int QInputEventRecorder::currentTimeOffset()const{

	if (m_Recording.size() > m_ReplayPos && m_ReplayPos >= 0)
	  return m_Recording[m_ReplayPos].timeOffset();
	return 0;
}



//
// Event serialization
//

QDataStream& operator<<(QDataStream &ds, const QTouchEvent::TouchPoint &pt)
{
	ds << (qint32) pt.id() << (qint32) pt.state() <<
		pt.pos() << pt.startPos() << pt.lastPos() <<
		pt.scenePos() << pt.startScenePos() << pt.lastScenePos() <<
		pt.screenPos() << pt.startScreenPos() << pt.lastScreenPos() <<
		pt.normalizedPos() << pt.startNormalizedPos() << pt.lastNormalizedPos() <<
		pt.rect() << pt.sceneRect() << pt.screenRect() << (qreal) pt.pressure();

	return ds;
}

QDataStream& operator>>(QDataStream &ds, QTouchEvent::TouchPoint &pt)
{
	qint32 id, state;
	QPointF pos, startPos, lastPos;
	QPointF scenePos, startScenePos, lastScenePos;
	QPointF screenPos, startScreenPos, lastScreenPos;
	QPointF normalizedPos, startNormalizedPos, lastNormalizedPos;
	QRectF rect, sceneRect, screenRect;
	qreal pressure;

	ds >> id >> state >> pos >> startPos >> lastPos
		>> scenePos >> startScenePos >> lastScenePos
		>> screenPos >> startScreenPos >> lastScreenPos
		>> normalizedPos >> startNormalizedPos >> lastNormalizedPos
		>> rect >> sceneRect >> screenRect >> pressure;

	pt.setId(id);
	pt.setState((Qt::TouchPointStates) state);
	pt.setPos(pos);
	pt.setStartPos(startPos);
	pt.setLastPos(lastPos);
	pt.setScenePos(scenePos);
	pt.setStartScenePos(startScenePos);
	pt.setLastScenePos(lastScenePos);
	pt.setScreenPos(screenPos);
	pt.setStartScreenPos(startScreenPos);
	pt.setLastScreenPos(lastScreenPos);
	pt.setNormalizedPos(normalizedPos);
	pt.setStartNormalizedPos(startNormalizedPos);
	pt.setLastNormalizedPos(lastNormalizedPos);
	pt.setRect(rect);
	pt.setSceneRect(sceneRect);
	pt.setScreenRect(screenRect);
	pt.setPressure(pressure);

	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QContextMenuEvent &ev)
{
	ds
		<< (qint32) EventClass::ContextMenuEvent
		<< (qint32) ev.type()
		<< (qint32) ev.reason()
		<< ev.pos()
		<< ev.globalPos()
		<< (qint32) ev.modifiers();
	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QKeyEvent &ev)
{
	ds
		<< (qint32) EventClass::KeyEvent
		<< (qint32) ev.type()
		<< (qint32) ev.key()
		<< (qint32) ev.modifiers()
		<< ev.text()
		<< ev.isAutoRepeat()
		<< (qint32) ev.count();
	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QMouseEvent &ev)
{
	ds
		<< (qint32) EventClass::MouseEvent
		<< (qint32) ev.type()
		<< ev.pos()
		<< ev.globalPos()
		<< (qint32) ev.button()
		<< (qint32) ev.buttons()
		<< (qint32) ev.modifiers();
	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QTabletEvent &ev)
{
	ds
		<< (qint32) EventClass::TabletEvent
		<< (qint32) ev.type()
		<< ev.pos()
		<< ev.globalPos()
		<< (qint32) ev.device()
		<< (qint32) ev.pointerType()
		<< (qreal) ev.pressure()
		<< (qint32) ev.xTilt()
		<< (qint32) ev.yTilt()
		<< (qreal) ev.tangentialPressure()
		<< (qreal) ev.rotation()
		<< (qint32) ev.z()
		<< (qint32) ev.modifiers()
		<< (qint64) ev.uniqueId();

	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QTouchDevice &ev)
{
	ds
		<< (qint32) EventClass::TouchDevice
		<< ev.name()
		<< (qint32) ev.type()
		<< (qint32) ev.maximumTouchPoints();

	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QTouchEvent &ev)
{
	ds
		<< (qint32) EventClass::TouchEvent
		<< (qint32) ev.type()
		<< ev.device()
		<< (qint32) ev.modifiers()
		<< (qint32) ev.touchPointStates()
		<< ev.touchPoints();

	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QWheelEvent &ev)
{
	ds
		<< (qint32) EventClass::WheelEvent
		<< (qint32) ev.type()
		<< ev.pos()
		<< ev.globalPos()
		<< (qint32) ev.delta()
		<< (qint32) ev.buttons()
		<< (qint32) ev.modifiers()
		<< (qint32) ev.orientation();
	return ds;
}

QDataStream& operator<<(QDataStream &ds, const QInputEvent *ev)
{
	if (dynamic_cast<const QContextMenuEvent*>(ev))
		ds << *static_cast<const QContextMenuEvent*>(ev);
	else if (dynamic_cast<const QKeyEvent*>(ev))
		ds << *static_cast<const QKeyEvent*>(ev);
	else if (dynamic_cast<const QMouseEvent*>(ev))
		ds << *static_cast<const QMouseEvent*>(ev);
	else if (dynamic_cast<const QWheelEvent*>(ev))
		ds << *static_cast<const QWheelEvent*>(ev);

	return ds;
}

QDataStream& operator>>(QDataStream &ds, QContextMenuEvent* &ev)
{
	qint32 type;
	qint32 reason;
	QPoint pos, globalPos;
	qint32 modifiers;
	ds >> type >> reason >> pos >> globalPos >> modifiers;
	ev = new QContextMenuEvent((QContextMenuEvent::Reason) reason, pos, globalPos, (Qt::KeyboardModifiers) modifiers);
	return ds;
}

QDataStream& operator>>(QDataStream &ds, QKeyEvent* &ev)
{
	qint32 type, key, modifiers;
	QString text;
	bool autorep;
	qint32 count;
	ds >> type >> key >> modifiers >> text >> autorep >> count;
	ev = new QKeyEvent((QEvent::Type) type, key, (Qt::KeyboardModifiers) modifiers, text, autorep, count);
	return ds;
}

QDataStream& operator>>(QDataStream &ds, QMouseEvent* &ev)
{
	qint32 type;
	QPoint pos, globalPos;
	qint32 button, buttons, modifiers;
	ds >> type >> pos >> globalPos >> button >> buttons >> modifiers;
	ev = new QMouseEvent((QEvent::Type) type, pos, globalPos, (Qt::MouseButton) button, (Qt::MouseButtons) buttons, (Qt::KeyboardModifiers) modifiers);
	return ds;
}

QDataStream& operator>>(QDataStream &ds, QTabletEvent* &ev)
{
	qint32 type;
	QPoint pos, globalPos;
	qint32 device, pointerType;
	qreal pressure;
	qint32 xTilt, yTilt;
	qreal tangentialPressure, rotation;
	qint32 z, keyState;
	qint64 uniqueID;

	ds >> type >> pos >> globalPos >> device >>
		pointerType >> pressure >> xTilt >> yTilt >>
		tangentialPressure >> rotation >> z >> keyState >> uniqueID;

	ev = new QTabletEvent((QEvent::Type) type, pos, globalPos, device, pointerType, pressure, xTilt, yTilt, tangentialPressure, rotation, z, (Qt::KeyboardModifiers) keyState, uniqueID);

	return ds;
}

QDataStream& operator>>(QDataStream &ds, QTouchDevice* &ev)
{
	qint32 type;
	QString name;
	qint32 	maximumTouchPoints;

	ds >> type >> name >> maximumTouchPoints;
	ev = new QTouchDevice();
	ev->setType((QTouchDevice::DeviceType) type);
	ev->setName(name);
	ev->setMaximumTouchPoints(maximumTouchPoints);

	return ds;
}

QDataStream& operator>>(QDataStream &ds, QTouchEvent* &ev)
{
	qint32 type, modifiers, touchPointStates;
	QTouchDevice *device;
	QList<QTouchEvent::TouchPoint> touchPoints;

	ds >> type >> device >> modifiers >> touchPointStates >> touchPoints;
	ev = new QTouchEvent((QEvent::Type) type, device, (Qt::KeyboardModifiers) modifiers, (Qt::TouchPointStates) touchPointStates, touchPoints);

	return ds;
}

QDataStream& operator>>(QDataStream &ds, QWheelEvent* &ev)
{
	qint32 type;
	QPoint pos, globalPos;
	qint32 delta, buttons, modifiers, orientation;
	ds >> type >> pos >> globalPos >> delta >> buttons >> modifiers >> orientation;
	ev = new QWheelEvent(pos, globalPos, delta, (Qt::MouseButtons) buttons, (Qt::KeyboardModifiers) modifiers, (Qt::Orientation) orientation);
	return ds;
}

QDataStream& operator>>(QDataStream &ds, QInputEvent*& ev)
{
	qint32 cls;
	ds >> cls;

	switch(cls)
	{
	case EventClass::ContextMenuEvent:
		{
			QContextMenuEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
		break;
	case EventClass::KeyEvent:
		{
			QKeyEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
		break;
	case EventClass::MouseEvent:
		{
			QMouseEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
		break;
	case EventClass::TabletEvent:
		{
			QTabletEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
		break;
	case EventClass::TouchEvent:
		{
			QTouchEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
	case EventClass::WheelEvent:
		{
			QWheelEvent *tmp;
			ds >> tmp;
			ev = tmp;
		}
		break;
	}


	return ds;
}
