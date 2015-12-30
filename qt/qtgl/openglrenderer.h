#ifndef CORE_OPENGLRENDERER_H
#define CORE_OPENGLRENDERER_H

namespace core
{

class OpenGLRenderer
{
public:
    OpenGLRenderer(int width, int height);
    ~OpenGLRenderer();
    
    void setup();
    void draw(double time);
    void cleanup();
    
    void setSize(int width, int height);
    
private:
    class Impl;
    Impl *_d;
};

} // namespace core

#endif // CORE_OPENGLRENDERER_H
