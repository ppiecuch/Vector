
#include "VectorTest.h"
#include "vector_shapes.h"
#include "../test/VectorTestImpl.h"

#include <vector>
#include <utility>

#include <QTime>


// Demo external interface:
// ------------------------

extern "C" int hour()   { return QTime::currentTime().hour(); }
extern "C" int minute() { return QTime::currentTime().minute(); }
extern "C" int second() { return QTime::currentTime().second(); }
extern "C" int millis() { return QTime::currentTime().second(); }
extern "C" int year()   { return QDate::currentDate().year(); }
extern "C" int month()  { return QDate::currentDate().month(); }
extern "C" int day()    { return QDate::currentDate().day(); }
extern "C" int weekday(){ return QDate::currentDate().dayOfWeek(); }
extern "C" int yearday(){ return QDate::currentDate().dayOfYear(); }

extern "C" const char *dayStr(int weekday) { return QDate::longDayName(weekday).toLatin1().constData(); }


void VectorTest::draw(int t)
{
	VectorTestImpl_Draw(t);
}

void VectorTest::prepare(int w, int h, float sc)
{
    VectorTestImpl_Init(w, h, sc);
}

void VectorTest::reshape(int w, int h, float sc)
{
    VectorTestImpl_Resize(w, h, sc);
}
