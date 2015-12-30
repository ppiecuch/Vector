
#include "VectorTest.h"
#include "../test/VectorTestImpl.h"

void VectorTest::draw()
{
    VectorTestImpl_Draw();
}

void VectorTest::prepare(int w, int h)
{
    VectorTestImpl_Init(w, h);
}

void VectorTest::reshape(int w, int h)
{
    VectorTestImpl_Resize(w, h);
}
