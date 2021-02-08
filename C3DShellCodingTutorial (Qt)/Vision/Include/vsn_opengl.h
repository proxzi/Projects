#ifndef __VSN_OPENGL_H
#define __VSN_OPENGL_H

#include "vsn_global.h"

#ifndef VSN_NO_OPENGL

#if defined(VSN_PLATFORM_WINDOWS)
# include "vsn_windows.h"
#endif

#if defined(VSN_OPENGL_ES_2)
# if defined(VSN_PLATFORM_MAC)
#  if defined(VSN_OPENGL_ES_3)
#   include <OpenGLES/ES3/gl.h>
#   include <OpenGLES/ES3/glext.h>
#  else
#   include <OpenGLES/ES2/gl.h>
#   include <OpenGLES/ES2/glext.h>
#  endif
# else 

#  if defined(VSN_OPENGL_ES_3_1)
#   include <GLES3/gl31.h>
#  elif defined(VSN_OPENGL_ES_3)
#   include <GLES3/gl3.h>
#  else
#   include <GLES2/gl2.h>
#endif

#  include <vsn_opengles2ext.h>
# endif // VSN_PLATFORM_MAC
#else
# if defined(VSN_PLATFORM_MAC)
#  include <OpenGL/gl.h>
#  if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
#   define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#   include <OpenGL/gl3.h>
#  endif
#  include <OpenGL/glext.h>
# else
#  define GL_GLEXT_LEGACY
#  include <GL/gl.h>
#  include "vsn_openglext.h"
# endif
#endif

#if !defined(VSN_OPENGL_ES_2)
# if !defined(VSN_PLATFORM_MAC) || (defined(VSN_PLATFORM_MAC) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7)
#  define VSN_OPENGL_3
#  define VSN_OPENGL_3_2
# endif
# if !defined(VSN_PLATFORM_MAC) || (defined(VSN_PLATFORM_MAC) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_9)
#  define VSN_OPENGL_4
# endif
# if !defined(VSN_PLATFORM_MAC)
#  define VSN_OPENGL_4_3
# endif
#endif

VSN_BEGIN_NAMESPACE
typedef ptrdiff_t vsngl_GLintptr;
typedef ptrdiff_t vsngl_GLsizeiptr;
VSN_END_NAMESPACE
#endif // VSN_NO_OPENGL

#endif // __VSN_OPENGL_H
