////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс OpenGLFunctionList представляет кроссплатформенный доступ к функциям OpenGL ES 2.0.
           \en The OpenGLFunctionList class provides cross-platform access to the OpenGL ES 2.0 functions. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GLFUNCTIONLISTINTERFACE_H
#define __VSN_GLFUNCTIONLISTINTERFACE_H

#include "vsn_flags.h"
#include "vsn_opengl.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
/** \brief \ru Класс OpenGLFunctionList представляет кроссплатформенный доступ к функциям OpenGL ES 2.0.
           \en The OpenGLFunctionList class provides cross-platform access to the OpenGL ES 2.0 functions. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS OpenGLFunctionListInterface
{
public:
    enum GLProperty
    {
        Multitexture = 0x0001,
        Shaders = 0x0002,
        Buffers = 0x0004,
        Framebuffers = 0x0008,
        BlendColor = 0x0010,
        BlendEquation = 0x0020,
        BlendEquationSeparate = 0x0040,
        BlendFuncSeparate = 0x0080,
        BlendSubtract = 0x0100,
        CompressedTextures = 0x0200,
        Multisample = 0x0400,
        StencilSeparate = 0x0800,
        NPOTTextures = 0x1000,
        NPOTTextureRepeat = 0x2000,
        FixedFunctionPipeline = 0x4000,
        TextureRGFormats = 0x8000
    };
    VSN_DECLARE_FLAGS(GLProperties, GLProperty)
public:
    virtual void InitGLFunctionList() = 0;
public:
    virtual void glBindTexture(GLenum target, GLuint texture) = 0;
    virtual void glBlendFunc(GLenum sfactor, GLenum dfactor) = 0;
    virtual void glClear(GLbitfield mask) = 0;
    virtual void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = 0;
    virtual void glClearStencil(GLint s) = 0;
    virtual void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = 0;
    virtual void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = 0;
    virtual void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = 0;
    virtual void glCullFace(GLenum mode) = 0;
    virtual void glDeleteTextures(GLsizei n, const GLuint* textures) = 0;
    virtual void glDepthFunc(GLenum func) = 0;
    virtual void glDepthMask(GLboolean flag) = 0;
    virtual void glDisable(GLenum cap) = 0;
    virtual void glDrawArrays(GLenum mode, GLint first, GLsizei count) = 0;
    virtual void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) = 0;
    virtual void glEnable(GLenum cap) = 0;
    virtual void glFinish() = 0;
    virtual void glFlush() = 0;
    virtual void glFrontFace(GLenum mode) = 0;
    virtual void glGenTextures(GLsizei n, GLuint* textures) = 0;
    virtual void glGetBooleanv(GLenum pname, GLboolean* params) = 0;
    virtual GLenum glGetError() = 0;
    virtual void glGetFloatv(GLenum pname, GLfloat* params) = 0;
    virtual void glGetIntegerv(GLenum pname, GLint* params) = 0;
    virtual const GLubyte *glGetString(GLenum name) = 0;
    virtual void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) = 0;
    virtual void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) = 0;
    virtual void glHint(GLenum target, GLenum mode) = 0;
    virtual GLboolean glIsEnabled(GLenum cap) = 0;
    virtual GLboolean glIsTexture(GLuint texture) = 0;
    virtual void glLineWidth(GLfloat width) = 0;
    virtual void glPixelStorei(GLenum pname, GLint param) = 0;
    virtual void glPolygonOffset(GLfloat factor, GLfloat units) = 0;
    virtual void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) = 0;
    virtual void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) = 0;
    virtual void glStencilFunc(GLenum func, GLint ref, GLuint mask) = 0;
    virtual void glStencilMask(GLuint mask) = 0;
    virtual void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) = 0;
    virtual void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) = 0;
    virtual void glTexParameterf(GLenum target, GLenum pname, GLfloat param) = 0;
    virtual void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) = 0;
    virtual void glTexParameteri(GLenum target, GLenum pname, GLint param) = 0;
    virtual void glTexParameteriv(GLenum target, GLenum pname, const GLint* params) = 0;
    virtual void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) = 0;
    virtual void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) = 0;

    // GL(ES)2
    virtual void glActiveTexture(GLenum texture) = 0;
    virtual void glAttachShader(GLuint program, GLuint shader) = 0;
    virtual void glBindAttribLocation(GLuint program, GLuint index, const char* name) = 0;
    virtual void glBindBuffer(GLenum target, GLuint buffer) = 0;
    virtual void glBindFramebuffer(GLenum target, GLuint framebuffer) = 0;
    virtual void glBindRenderbuffer(GLenum target, GLuint renderbuffer) = 0;
    virtual void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = 0;
    virtual void glBlendEquation(GLenum mode) = 0;
    virtual void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) = 0;
    virtual void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = 0;
    virtual void glBufferData(GLenum target, vsngl_GLsizeiptr size, const void* data, GLenum usage) = 0;
    virtual void glBufferSubData(GLenum target, vsngl_GLintptr offset, vsngl_GLsizeiptr size, const void* data) = 0;
    virtual GLenum glCheckFramebufferStatus(GLenum target) = 0;
    virtual void glClearDepthf(GLclampf depth) = 0;
    virtual void glCompileShader(GLuint shader) = 0;
    virtual void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) = 0;
    virtual void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) = 0;
    virtual GLuint glCreateProgram() = 0;
    virtual GLuint glCreateShader(GLenum type) = 0;
    virtual void glDeleteBuffers(GLsizei n, const GLuint* buffers) = 0;
    virtual void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) = 0;
    virtual void glDeleteProgram(GLuint program) = 0;
    virtual void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) = 0;
    virtual void glDeleteShader(GLuint shader) = 0;
    virtual void glDepthRangef(GLclampf zNear, GLclampf zFar) = 0;
    virtual void glDetachShader(GLuint program, GLuint shader) = 0;
    virtual void glDisableVertexAttribArray(GLuint index) = 0;
    virtual void glEnableVertexAttribArray(GLuint index) = 0;
    virtual void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = 0;
    virtual void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = 0;
    virtual void glGenBuffers(GLsizei n, GLuint* buffers) = 0;
    virtual void glGenerateMipmap(GLenum target) = 0;
    virtual void glGenFramebuffers(GLsizei n, GLuint* framebuffers) = 0;
    virtual void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) = 0;
    virtual void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) = 0;
    virtual void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, char* name) = 0;
    virtual void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) = 0;
    virtual GLint glGetAttribLocation(GLuint program, const char* name) = 0;
    virtual void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params) = 0;
    virtual void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) = 0;
    virtual void glGetProgramiv(GLuint program, GLenum pname, GLint* params) = 0;
    virtual void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) = 0;
    virtual void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) = 0;
    virtual void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) = 0;
    virtual void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) = 0;
    virtual void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) = 0;
    virtual void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, char* source) = 0;
    virtual void glGetUniformfv(GLuint program, GLint location, GLfloat* params) = 0;
    virtual void glGetUniformiv(GLuint program, GLint location, GLint* params) = 0;
    virtual GLint glGetUniformLocation(GLuint program, const char* name) = 0;
    virtual void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) = 0;
    virtual void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params) = 0;
    virtual void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) = 0;
    virtual GLboolean glIsBuffer(GLuint buffer) = 0;
    virtual GLboolean glIsFramebuffer(GLuint framebuffer) = 0;
    virtual GLboolean glIsProgram(GLuint program) = 0;
    virtual GLboolean glIsRenderbuffer(GLuint renderbuffer) = 0;
    virtual GLboolean glIsShader(GLuint shader) = 0;
    virtual void glLinkProgram(GLuint program) = 0;
    virtual void glReleaseShaderCompiler() = 0;
    virtual void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = 0;
    virtual void glSampleCoverage(GLclampf value, GLboolean invert) = 0;
    virtual void glShaderBinary(GLint n, const GLuint* shaders, GLenum binaryformat, const void* binary, GLint length) = 0;
    virtual void glShaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) = 0;
    virtual void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) = 0;
    virtual void glStencilMaskSeparate(GLenum face, GLuint mask) = 0;
    virtual void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass) = 0;
    virtual void glUniform1f(GLint location, GLfloat x) = 0;
    virtual void glUniform1fv(GLint location, GLsizei count, const GLfloat* v) = 0;
    virtual void glUniform1i(GLint location, GLint x) = 0;
    virtual void glUniform1iv(GLint location, GLsizei count, const GLint* v) = 0;
    virtual void glUniform2f(GLint location, GLfloat x, GLfloat y) = 0;
    virtual void glUniform2fv(GLint location, GLsizei count, const GLfloat* v) = 0;
    virtual void glUniform2i(GLint location, GLint x, GLint y) = 0;
    virtual void glUniform2iv(GLint location, GLsizei count, const GLint* v) = 0;
    virtual void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) = 0;
    virtual void glUniform3fv(GLint location, GLsizei count, const GLfloat* v) = 0;
    virtual void glUniform3i(GLint location, GLint x, GLint y, GLint z) = 0;
    virtual void glUniform3iv(GLint location, GLsizei count, const GLint* v) = 0;
    virtual void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = 0;
    virtual void glUniform4fv(GLint location, GLsizei count, const GLfloat* v) = 0;
    virtual void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) = 0;
    virtual void glUniform4iv(GLint location, GLsizei count, const GLint* v) = 0;
    virtual void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
    virtual void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
    virtual void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
    virtual void glUseProgram(GLuint program) = 0;
    virtual void glValidateProgram(GLuint program) = 0;
    virtual void glVertexAttrib1f(GLuint indx, GLfloat x) = 0;
    virtual void glVertexAttrib1fv(GLuint indx, const GLfloat* values) = 0;
    virtual void glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y) = 0;
    virtual void glVertexAttrib2fv(GLuint indx, const GLfloat* values) = 0;
    virtual void glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z) = 0;
    virtual void glVertexAttrib3fv(GLuint indx, const GLfloat* values) = 0;
    virtual void glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = 0;
    virtual void glVertexAttrib4fv(GLuint indx, const GLfloat* values) = 0;
    virtual void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr) = 0;
};
VSN_END_NAMESPACE

#endif // __VSN_GLFUNCTIONLISTINTERFACE_H
