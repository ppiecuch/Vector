#ifndef __VECTORTESTIMPL_H_
#define __VECTORTESTIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

void VectorTestImpl_Draw(int t);
void VectorTestImpl_Init(int w, int h, float sc);
void VectorTestImpl_Resize(int w, int h, float sc);
void VectorTestImpl_Destroy();

#ifdef __cplusplus
}
#endif

#endif
