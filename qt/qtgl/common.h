#ifndef CORE_COMMON_H
#define CORE_COMMON_H


namespace core
{

enum OpenGLProfile {
    OpenGLDefaultProfile       = 0,
    OpenGLCoreProfile          = 1,
    OpenGLCompatibilityProfile = 2,
    OpenGLDefault // donot set any profile
};

// default surface format:
static const int majorVersion = 3;
static const int minorVersion = 2;
static const OpenGLProfile profile = OpenGLDefault;

} // namespace core.

#endif // CORE_COMMON_H
