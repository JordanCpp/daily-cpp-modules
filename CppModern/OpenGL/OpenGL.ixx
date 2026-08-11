
// Copyright 2026-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

module;

#include <cstdint>
#include <expected>
#include <Windows.h>

export module OpenGL;

export using GLenum = std::uint32_t;
export using GLuint = std::uint32_t;
export using GLint = std::int32_t;
export using GLsizei = std::int32_t;
export using GLfloat = float;
export using GLdouble = double;
export using GLbyte = std::int8_t;
export using GLshort = std::int16_t;
export using GLboolean = std::uint8_t;
export using GLbitfield = std::uint32_t;
export using GLvoid = void;
export using GLchar = char;
export using GLubyte = std::uint8_t;
export using GLushort = std::uint16_t;
export using GLuint64 = std::uint64_t;
export using GLint64 = std::int64_t;
export using GLsizeiptr = std::intptr_t;
export using GLintptr = std::intptr_t;
export using GLsync = void*;


export using GLhalf = std::uint16_t;
export using GLclampf = float;
export using GLclampd = double;

export constexpr GLenum GL_FALSE = 0;


#ifdef _WIN32
#define GL_CALL __stdcall
#else
#define GL_CALL
#endif

export using GLDEBUGPROC = void (GL_CALL*)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

// ==================== OpenGL 1.0 Functions ====================

export using PFNGLCULLFACEPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLCULLFACEPROC glCullFace;
PFNGLCULLFACEPROC glCullFace = nullptr;

export using PFNGLFRONTFACEPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLFRONTFACEPROC glFrontFace;
PFNGLFRONTFACEPROC glFrontFace = nullptr;

export using PFNGLHINTPROC = void (GL_CALL*)(GLenum target, GLenum mode);
export extern PFNGLHINTPROC glHint;
PFNGLHINTPROC glHint = nullptr;

export using PFNGLLINEWIDTHPROC = void (GL_CALL*)(GLfloat width);
export extern PFNGLLINEWIDTHPROC glLineWidth;
PFNGLLINEWIDTHPROC glLineWidth = nullptr;

export using PFNGLPOINTSIZEPROC = void (GL_CALL*)(GLfloat size);
export extern PFNGLPOINTSIZEPROC glPointSize;
PFNGLPOINTSIZEPROC glPointSize = nullptr;

export using PFNGLPOLYGONMODEPROC = void (GL_CALL*)(GLenum face, GLenum mode);
export extern PFNGLPOLYGONMODEPROC glPolygonMode;
PFNGLPOLYGONMODEPROC glPolygonMode = nullptr;

export using PFNGLSCISSORPROC = void (GL_CALL*)(GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLSCISSORPROC glScissor;
PFNGLSCISSORPROC glScissor = nullptr;

export using PFNGLTEXPARAMETERFPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLfloat param);
export extern PFNGLTEXPARAMETERFPROC glTexParameterf;
PFNGLTEXPARAMETERFPROC glTexParameterf = nullptr;

export using PFNGLTEXPARAMETERFVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLfloat* params);
export extern PFNGLTEXPARAMETERFVPROC glTexParameterfv;
PFNGLTEXPARAMETERFVPROC glTexParameterfv = nullptr;

export using PFNGLTEXPARAMETERIPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint param);
export extern PFNGLTEXPARAMETERIPROC glTexParameteri;
PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;

export using PFNGLTEXPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLint* params);
export extern PFNGLTEXPARAMETERIVPROC glTexParameteriv;
PFNGLTEXPARAMETERIVPROC glTexParameteriv = nullptr;

export using PFNGLTEXIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXIMAGE1DPROC glTexImage1D;
PFNGLTEXIMAGE1DPROC glTexImage1D = nullptr;

export using PFNGLTEXIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXIMAGE2DPROC glTexImage2D;
PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;

export using PFNGLDRAWBUFFERPROC = void (GL_CALL*)(GLenum buf);
export extern PFNGLDRAWBUFFERPROC glDrawBuffer;
PFNGLDRAWBUFFERPROC glDrawBuffer = nullptr;

export using PFNGLCLEARPROC = void (GL_CALL*)(GLbitfield mask);
export extern PFNGLCLEARPROC glClear;
PFNGLCLEARPROC glClear = nullptr;

export using PFNGLCLEARCOLORPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
export extern PFNGLCLEARCOLORPROC glClearColor;
PFNGLCLEARCOLORPROC glClearColor = nullptr;

export using PFNGLCLEARSTENCILPROC = void (GL_CALL*)(GLint s);
export extern PFNGLCLEARSTENCILPROC glClearStencil;
PFNGLCLEARSTENCILPROC glClearStencil = nullptr;

export using PFNGLCLEARDEPTHPROC = void (GL_CALL*)(GLdouble depth);
export extern PFNGLCLEARDEPTHPROC glClearDepth;
PFNGLCLEARDEPTHPROC glClearDepth = nullptr;

export using PFNGLSTENCILMASKPROC = void (GL_CALL*)(GLuint mask);
export extern PFNGLSTENCILMASKPROC glStencilMask;
PFNGLSTENCILMASKPROC glStencilMask = nullptr;

export using PFNGLCOLORMASKPROC = void (GL_CALL*)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
export extern PFNGLCOLORMASKPROC glColorMask;
PFNGLCOLORMASKPROC glColorMask = nullptr;

export using PFNGLDEPTHMASKPROC = void (GL_CALL*)(GLboolean flag);
export extern PFNGLDEPTHMASKPROC glDepthMask;
PFNGLDEPTHMASKPROC glDepthMask = nullptr;

export using PFNGLDISABLEPROC = void (GL_CALL*)(GLenum cap);
export extern PFNGLDISABLEPROC glDisable;
PFNGLDISABLEPROC glDisable = nullptr;

export using PFNGLENABLEPROC = void (GL_CALL*)(GLenum cap);
export extern PFNGLENABLEPROC glEnable;
PFNGLENABLEPROC glEnable = nullptr;

export using PFNGLFINISHPROC = void (GL_CALL*)();
export extern PFNGLFINISHPROC glFinish;
PFNGLFINISHPROC glFinish = nullptr;

export using PFNGLFLUSHPROC = void (GL_CALL*)();
export extern PFNGLFLUSHPROC glFlush;
PFNGLFLUSHPROC glFlush = nullptr;

export using PFNGLBLENDFUNCPROC = void (GL_CALL*)(GLenum sfactor, GLenum dfactor);
export extern PFNGLBLENDFUNCPROC glBlendFunc;
PFNGLBLENDFUNCPROC glBlendFunc = nullptr;

export using PFNGLLOGICOPPROC = void (GL_CALL*)(GLenum opcode);
export extern PFNGLLOGICOPPROC glLogicOp;
PFNGLLOGICOPPROC glLogicOp = nullptr;

export using PFNGLSTENCILFUNCPROC = void (GL_CALL*)(GLenum func, GLint ref, GLuint mask);
export extern PFNGLSTENCILFUNCPROC glStencilFunc;
PFNGLSTENCILFUNCPROC glStencilFunc = nullptr;

export using PFNGLSTENCILOPPROC = void (GL_CALL*)(GLenum fail, GLenum zfail, GLenum zpass);
export extern PFNGLSTENCILOPPROC glStencilOp;
PFNGLSTENCILOPPROC glStencilOp = nullptr;

export using PFNGLDEPTHFUNCPROC = void (GL_CALL*)(GLenum func);
export extern PFNGLDEPTHFUNCPROC glDepthFunc;
PFNGLDEPTHFUNCPROC glDepthFunc = nullptr;

export using PFNGLPIXELSTOREFPROC = void (GL_CALL*)(GLenum pname, GLfloat param);
export extern PFNGLPIXELSTOREFPROC glPixelStoref;
PFNGLPIXELSTOREFPROC glPixelStoref = nullptr;

export using PFNGLPIXELSTOREIPROC = void (GL_CALL*)(GLenum pname, GLint param);
export extern PFNGLPIXELSTOREIPROC glPixelStorei;
PFNGLPIXELSTOREIPROC glPixelStorei = nullptr;

export using PFNGLREADBUFFERPROC = void (GL_CALL*)(GLenum src);
export extern PFNGLREADBUFFERPROC glReadBuffer;
PFNGLREADBUFFERPROC glReadBuffer = nullptr;

export using PFNGLREADPIXELSPROC = void (GL_CALL*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
export extern PFNGLREADPIXELSPROC glReadPixels;
PFNGLREADPIXELSPROC glReadPixels = nullptr;

export using PFNGLGETBOOLEANVPROC = void (GL_CALL*)(GLenum pname, GLboolean* data);
export extern PFNGLGETBOOLEANVPROC glGetBooleanv;
PFNGLGETBOOLEANVPROC glGetBooleanv = nullptr;

export using PFNGLGETDOUBLEVPROC = void (GL_CALL*)(GLenum pname, GLdouble* data);
export extern PFNGLGETDOUBLEVPROC glGetDoublev;
PFNGLGETDOUBLEVPROC glGetDoublev = nullptr;

export using PFNGLGETERRORPROC = GLenum(GL_CALL*)();
export extern PFNGLGETERRORPROC glGetError;
PFNGLGETERRORPROC glGetError = nullptr;

export using PFNGLGETFLOATVPROC = void (GL_CALL*)(GLenum pname, GLfloat* data);
export extern PFNGLGETFLOATVPROC glGetFloatv;
PFNGLGETFLOATVPROC glGetFloatv = nullptr;

export using PFNGLGETINTEGERVPROC = void (GL_CALL*)(GLenum pname, GLint* data);
export extern PFNGLGETINTEGERVPROC glGetIntegerv;
PFNGLGETINTEGERVPROC glGetIntegerv = nullptr;

export using PFNGLGETSTRINGPROC = const GLubyte* (GL_CALL*)(GLenum name);
export extern PFNGLGETSTRINGPROC glGetString;
PFNGLGETSTRINGPROC glGetString = nullptr;

export using PFNGLGETTEXIMAGEPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
export extern PFNGLGETTEXIMAGEPROC glGetTexImage;
PFNGLGETTEXIMAGEPROC glGetTexImage = nullptr;

export using PFNGLGETTEXPARAMETERFVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv;
PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = nullptr;

export using PFNGLGETTEXPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv;
PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = nullptr;

export using PFNGLGETTEXLEVELPARAMETERFVPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv = nullptr;

export using PFNGLGETTEXLEVELPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum pname, GLint* params);
export extern PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv;
PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv = nullptr;

export using PFNGLISENABLEDPROC = GLboolean(GL_CALL*)(GLenum cap);
export extern PFNGLISENABLEDPROC glIsEnabled;
PFNGLISENABLEDPROC glIsEnabled = nullptr;

export using PFNGLDEPTHRANGEPROC = void (GL_CALL*)(GLdouble n, GLdouble f);
export extern PFNGLDEPTHRANGEPROC glDepthRange;
PFNGLDEPTHRANGEPROC glDepthRange = nullptr;

export using PFNGLVIEWPORTPROC = void (GL_CALL*)(GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLVIEWPORTPROC glViewport;
PFNGLVIEWPORTPROC glViewport = nullptr;

export using PFNGLNEWLISTPROC = void (GL_CALL*)(GLuint list, GLenum mode);
export extern PFNGLNEWLISTPROC glNewList;
PFNGLNEWLISTPROC glNewList = nullptr;

export using PFNGLENDLISTPROC = void (GL_CALL*)();
export extern PFNGLENDLISTPROC glEndList;
PFNGLENDLISTPROC glEndList = nullptr;

export using PFNGLCALLLISTPROC = void (GL_CALL*)(GLuint list);
export extern PFNGLCALLLISTPROC glCallList;
PFNGLCALLLISTPROC glCallList = nullptr;

export using PFNGLCALLLISTSPROC = void (GL_CALL*)(GLsizei n, GLenum type, const void* lists);
export extern PFNGLCALLLISTSPROC glCallLists;
PFNGLCALLLISTSPROC glCallLists = nullptr;

export using PFNGLDELETELISTSPROC = void (GL_CALL*)(GLuint list, GLsizei range);
export extern PFNGLDELETELISTSPROC glDeleteLists;
PFNGLDELETELISTSPROC glDeleteLists = nullptr;

export using PFNGLGENLISTSPROC = GLuint(GL_CALL*)(GLsizei range);
export extern PFNGLGENLISTSPROC glGenLists;
PFNGLGENLISTSPROC glGenLists = nullptr;

export using PFNGLLISTBASEPROC = void (GL_CALL*)(GLuint base);
export extern PFNGLLISTBASEPROC glListBase;
PFNGLLISTBASEPROC glListBase = nullptr;

export using PFNGLBEGINPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLBEGINPROC glBegin;
PFNGLBEGINPROC glBegin = nullptr;

export using PFNGLBITMAPPROC = void (GL_CALL*)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap);
export extern PFNGLBITMAPPROC glBitmap;
PFNGLBITMAPPROC glBitmap = nullptr;

export using PFNGLCOLOR3BPROC = void (GL_CALL*)(GLbyte red, GLbyte green, GLbyte blue);
export extern PFNGLCOLOR3BPROC glColor3b;
PFNGLCOLOR3BPROC glColor3b = nullptr;

export using PFNGLCOLOR3BVPROC = void (GL_CALL*)(const GLbyte* v);
export extern PFNGLCOLOR3BVPROC glColor3bv;
PFNGLCOLOR3BVPROC glColor3bv = nullptr;

export using PFNGLCOLOR3DPROC = void (GL_CALL*)(GLdouble red, GLdouble green, GLdouble blue);
export extern PFNGLCOLOR3DPROC glColor3d;
PFNGLCOLOR3DPROC glColor3d = nullptr;

export using PFNGLCOLOR3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLCOLOR3DVPROC glColor3dv;
PFNGLCOLOR3DVPROC glColor3dv = nullptr;

export using PFNGLCOLOR3FPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue);
export extern PFNGLCOLOR3FPROC glColor3f;
PFNGLCOLOR3FPROC glColor3f = nullptr;

export using PFNGLCOLOR3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLCOLOR3FVPROC glColor3fv;
PFNGLCOLOR3FVPROC glColor3fv = nullptr;

export using PFNGLCOLOR3IPROC = void (GL_CALL*)(GLint red, GLint green, GLint blue);
export extern PFNGLCOLOR3IPROC glColor3i;
PFNGLCOLOR3IPROC glColor3i = nullptr;

export using PFNGLCOLOR3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLCOLOR3IVPROC glColor3iv;
PFNGLCOLOR3IVPROC glColor3iv = nullptr;

export using PFNGLCOLOR3SPROC = void (GL_CALL*)(GLshort red, GLshort green, GLshort blue);
export extern PFNGLCOLOR3SPROC glColor3s;
PFNGLCOLOR3SPROC glColor3s = nullptr;

export using PFNGLCOLOR3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLCOLOR3SVPROC glColor3sv;
PFNGLCOLOR3SVPROC glColor3sv = nullptr;

export using PFNGLCOLOR3UBPROC = void (GL_CALL*)(GLubyte red, GLubyte green, GLubyte blue);
export extern PFNGLCOLOR3UBPROC glColor3ub;
PFNGLCOLOR3UBPROC glColor3ub = nullptr;

export using PFNGLCOLOR3UBVPROC = void (GL_CALL*)(const GLubyte* v);
export extern PFNGLCOLOR3UBVPROC glColor3ubv;
PFNGLCOLOR3UBVPROC glColor3ubv = nullptr;

export using PFNGLCOLOR3UIPROC = void (GL_CALL*)(GLuint red, GLuint green, GLuint blue);
export extern PFNGLCOLOR3UIPROC glColor3ui;
PFNGLCOLOR3UIPROC glColor3ui = nullptr;

export using PFNGLCOLOR3UIVPROC = void (GL_CALL*)(const GLuint* v);
export extern PFNGLCOLOR3UIVPROC glColor3uiv;
PFNGLCOLOR3UIVPROC glColor3uiv = nullptr;

export using PFNGLCOLOR3USPROC = void (GL_CALL*)(GLushort red, GLushort green, GLushort blue);
export extern PFNGLCOLOR3USPROC glColor3us;
PFNGLCOLOR3USPROC glColor3us = nullptr;

export using PFNGLCOLOR3USVPROC = void (GL_CALL*)(const GLushort* v);
export extern PFNGLCOLOR3USVPROC glColor3usv;
PFNGLCOLOR3USVPROC glColor3usv = nullptr;

export using PFNGLCOLOR4BPROC = void (GL_CALL*)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
export extern PFNGLCOLOR4BPROC glColor4b;
PFNGLCOLOR4BPROC glColor4b = nullptr;

export using PFNGLCOLOR4BVPROC = void (GL_CALL*)(const GLbyte* v);
export extern PFNGLCOLOR4BVPROC glColor4bv;
PFNGLCOLOR4BVPROC glColor4bv = nullptr;

export using PFNGLCOLOR4DPROC = void (GL_CALL*)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
export extern PFNGLCOLOR4DPROC glColor4d;
PFNGLCOLOR4DPROC glColor4d = nullptr;

export using PFNGLCOLOR4DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLCOLOR4DVPROC glColor4dv;
PFNGLCOLOR4DVPROC glColor4dv = nullptr;

export using PFNGLCOLOR4FPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
export extern PFNGLCOLOR4FPROC glColor4f;
PFNGLCOLOR4FPROC glColor4f = nullptr;

export using PFNGLCOLOR4FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLCOLOR4FVPROC glColor4fv;
PFNGLCOLOR4FVPROC glColor4fv = nullptr;

export using PFNGLCOLOR4IPROC = void (GL_CALL*)(GLint red, GLint green, GLint blue, GLint alpha);
export extern PFNGLCOLOR4IPROC glColor4i;
PFNGLCOLOR4IPROC glColor4i = nullptr;

export using PFNGLCOLOR4IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLCOLOR4IVPROC glColor4iv;
PFNGLCOLOR4IVPROC glColor4iv = nullptr;

export using PFNGLCOLOR4SPROC = void (GL_CALL*)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
export extern PFNGLCOLOR4SPROC glColor4s;
PFNGLCOLOR4SPROC glColor4s = nullptr;

export using PFNGLCOLOR4SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLCOLOR4SVPROC glColor4sv;
PFNGLCOLOR4SVPROC glColor4sv = nullptr;

export using PFNGLCOLOR4UBPROC = void (GL_CALL*)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
export extern PFNGLCOLOR4UBPROC glColor4ub;
PFNGLCOLOR4UBPROC glColor4ub = nullptr;

export using PFNGLCOLOR4UBVPROC = void (GL_CALL*)(const GLubyte* v);
export extern PFNGLCOLOR4UBVPROC glColor4ubv;
PFNGLCOLOR4UBVPROC glColor4ubv = nullptr;

export using PFNGLCOLOR4UIPROC = void (GL_CALL*)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
export extern PFNGLCOLOR4UIPROC glColor4ui;
PFNGLCOLOR4UIPROC glColor4ui = nullptr;

export using PFNGLCOLOR4UIVPROC = void (GL_CALL*)(const GLuint* v);
export extern PFNGLCOLOR4UIVPROC glColor4uiv;
PFNGLCOLOR4UIVPROC glColor4uiv = nullptr;

export using PFNGLCOLOR4USPROC = void (GL_CALL*)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
export extern PFNGLCOLOR4USPROC glColor4us;
PFNGLCOLOR4USPROC glColor4us = nullptr;

export using PFNGLCOLOR4USVPROC = void (GL_CALL*)(const GLushort* v);
export extern PFNGLCOLOR4USVPROC glColor4usv;
PFNGLCOLOR4USVPROC glColor4usv = nullptr;

export using PFNGLEDGEFLAGPROC = void (GL_CALL*)(GLboolean flag);
export extern PFNGLEDGEFLAGPROC glEdgeFlag;
PFNGLEDGEFLAGPROC glEdgeFlag = nullptr;

export using PFNGLEDGEFLAGVPROC = void (GL_CALL*)(const GLboolean* flag);
export extern PFNGLEDGEFLAGVPROC glEdgeFlagv;
PFNGLEDGEFLAGVPROC glEdgeFlagv = nullptr;

export using PFNGLENDPROC = void (GL_CALL*)();
export extern PFNGLENDPROC glEnd;
PFNGLENDPROC glEnd = nullptr;

export using PFNGLINDEXDPROC = void (GL_CALL*)(GLdouble c);
export extern PFNGLINDEXDPROC glIndexd;
PFNGLINDEXDPROC glIndexd = nullptr;

export using PFNGLINDEXDVPROC = void (GL_CALL*)(const GLdouble* c);
export extern PFNGLINDEXDVPROC glIndexdv;
PFNGLINDEXDVPROC glIndexdv = nullptr;

export using PFNGLINDEXFPROC = void (GL_CALL*)(GLfloat c);
export extern PFNGLINDEXFPROC glIndexf;
PFNGLINDEXFPROC glIndexf = nullptr;

export using PFNGLINDEXFVPROC = void (GL_CALL*)(const GLfloat* c);
export extern PFNGLINDEXFVPROC glIndexfv;
PFNGLINDEXFVPROC glIndexfv = nullptr;

export using PFNGLINDEXIPROC = void (GL_CALL*)(GLint c);
export extern PFNGLINDEXIPROC glIndexi;
PFNGLINDEXIPROC glIndexi = nullptr;

export using PFNGLINDEXIVPROC = void (GL_CALL*)(const GLint* c);
export extern PFNGLINDEXIVPROC glIndexiv;
PFNGLINDEXIVPROC glIndexiv = nullptr;

export using PFNGLINDEXSPROC = void (GL_CALL*)(GLshort c);
export extern PFNGLINDEXSPROC glIndexs;
PFNGLINDEXSPROC glIndexs = nullptr;

export using PFNGLINDEXSVPROC = void (GL_CALL*)(const GLshort* c);
export extern PFNGLINDEXSVPROC glIndexsv;
PFNGLINDEXSVPROC glIndexsv = nullptr;

export using PFNGLNORMAL3BPROC = void (GL_CALL*)(GLbyte nx, GLbyte ny, GLbyte nz);
export extern PFNGLNORMAL3BPROC glNormal3b;
PFNGLNORMAL3BPROC glNormal3b = nullptr;

export using PFNGLNORMAL3BVPROC = void (GL_CALL*)(const GLbyte* v);
export extern PFNGLNORMAL3BVPROC glNormal3bv;
PFNGLNORMAL3BVPROC glNormal3bv = nullptr;

export using PFNGLNORMAL3DPROC = void (GL_CALL*)(GLdouble nx, GLdouble ny, GLdouble nz);
export extern PFNGLNORMAL3DPROC glNormal3d;
PFNGLNORMAL3DPROC glNormal3d = nullptr;

export using PFNGLNORMAL3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLNORMAL3DVPROC glNormal3dv;
PFNGLNORMAL3DVPROC glNormal3dv = nullptr;

export using PFNGLNORMAL3FPROC = void (GL_CALL*)(GLfloat nx, GLfloat ny, GLfloat nz);
export extern PFNGLNORMAL3FPROC glNormal3f;
PFNGLNORMAL3FPROC glNormal3f = nullptr;

export using PFNGLNORMAL3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLNORMAL3FVPROC glNormal3fv;
PFNGLNORMAL3FVPROC glNormal3fv = nullptr;

export using PFNGLNORMAL3IPROC = void (GL_CALL*)(GLint nx, GLint ny, GLint nz);
export extern PFNGLNORMAL3IPROC glNormal3i;
PFNGLNORMAL3IPROC glNormal3i = nullptr;

export using PFNGLNORMAL3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLNORMAL3IVPROC glNormal3iv;
PFNGLNORMAL3IVPROC glNormal3iv = nullptr;

export using PFNGLNORMAL3SPROC = void (GL_CALL*)(GLshort nx, GLshort ny, GLshort nz);
export extern PFNGLNORMAL3SPROC glNormal3s;
PFNGLNORMAL3SPROC glNormal3s = nullptr;

export using PFNGLNORMAL3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLNORMAL3SVPROC glNormal3sv;
PFNGLNORMAL3SVPROC glNormal3sv = nullptr;

export using PFNGLRASTERPOS2DPROC = void (GL_CALL*)(GLdouble x, GLdouble y);
export extern PFNGLRASTERPOS2DPROC glRasterPos2d;
PFNGLRASTERPOS2DPROC glRasterPos2d = nullptr;

export using PFNGLRASTERPOS2DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLRASTERPOS2DVPROC glRasterPos2dv;
PFNGLRASTERPOS2DVPROC glRasterPos2dv = nullptr;

export using PFNGLRASTERPOS2FPROC = void (GL_CALL*)(GLfloat x, GLfloat y);
export extern PFNGLRASTERPOS2FPROC glRasterPos2f;
PFNGLRASTERPOS2FPROC glRasterPos2f = nullptr;

export using PFNGLRASTERPOS2FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLRASTERPOS2FVPROC glRasterPos2fv;
PFNGLRASTERPOS2FVPROC glRasterPos2fv = nullptr;

export using PFNGLRASTERPOS2IPROC = void (GL_CALL*)(GLint x, GLint y);
export extern PFNGLRASTERPOS2IPROC glRasterPos2i;
PFNGLRASTERPOS2IPROC glRasterPos2i = nullptr;

export using PFNGLRASTERPOS2IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLRASTERPOS2IVPROC glRasterPos2iv;
PFNGLRASTERPOS2IVPROC glRasterPos2iv = nullptr;

export using PFNGLRASTERPOS2SPROC = void (GL_CALL*)(GLshort x, GLshort y);
export extern PFNGLRASTERPOS2SPROC glRasterPos2s;
PFNGLRASTERPOS2SPROC glRasterPos2s = nullptr;

export using PFNGLRASTERPOS2SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLRASTERPOS2SVPROC glRasterPos2sv;
PFNGLRASTERPOS2SVPROC glRasterPos2sv = nullptr;

export using PFNGLRASTERPOS3DPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLRASTERPOS3DPROC glRasterPos3d;
PFNGLRASTERPOS3DPROC glRasterPos3d = nullptr;

export using PFNGLRASTERPOS3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLRASTERPOS3DVPROC glRasterPos3dv;
PFNGLRASTERPOS3DVPROC glRasterPos3dv = nullptr;

export using PFNGLRASTERPOS3FPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLRASTERPOS3FPROC glRasterPos3f;
PFNGLRASTERPOS3FPROC glRasterPos3f = nullptr;

export using PFNGLRASTERPOS3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLRASTERPOS3FVPROC glRasterPos3fv;
PFNGLRASTERPOS3FVPROC glRasterPos3fv = nullptr;

export using PFNGLRASTERPOS3IPROC = void (GL_CALL*)(GLint x, GLint y, GLint z);
export extern PFNGLRASTERPOS3IPROC glRasterPos3i;
PFNGLRASTERPOS3IPROC glRasterPos3i = nullptr;

export using PFNGLRASTERPOS3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLRASTERPOS3IVPROC glRasterPos3iv;
PFNGLRASTERPOS3IVPROC glRasterPos3iv = nullptr;

export using PFNGLRASTERPOS3SPROC = void (GL_CALL*)(GLshort x, GLshort y, GLshort z);
export extern PFNGLRASTERPOS3SPROC glRasterPos3s;
PFNGLRASTERPOS3SPROC glRasterPos3s = nullptr;

export using PFNGLRASTERPOS3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLRASTERPOS3SVPROC glRasterPos3sv;
PFNGLRASTERPOS3SVPROC glRasterPos3sv = nullptr;

export using PFNGLRASTERPOS4DPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
export extern PFNGLRASTERPOS4DPROC glRasterPos4d;
PFNGLRASTERPOS4DPROC glRasterPos4d = nullptr;

export using PFNGLRASTERPOS4DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLRASTERPOS4DVPROC glRasterPos4dv;
PFNGLRASTERPOS4DVPROC glRasterPos4dv = nullptr;

export using PFNGLRASTERPOS4FPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
export extern PFNGLRASTERPOS4FPROC glRasterPos4f;
PFNGLRASTERPOS4FPROC glRasterPos4f = nullptr;

export using PFNGLRASTERPOS4FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLRASTERPOS4FVPROC glRasterPos4fv;
PFNGLRASTERPOS4FVPROC glRasterPos4fv = nullptr;

export using PFNGLRASTERPOS4IPROC = void (GL_CALL*)(GLint x, GLint y, GLint z, GLint w);
export extern PFNGLRASTERPOS4IPROC glRasterPos4i;
PFNGLRASTERPOS4IPROC glRasterPos4i = nullptr;

export using PFNGLRASTERPOS4IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLRASTERPOS4IVPROC glRasterPos4iv;
PFNGLRASTERPOS4IVPROC glRasterPos4iv = nullptr;

export using PFNGLRASTERPOS4SPROC = void (GL_CALL*)(GLshort x, GLshort y, GLshort z, GLshort w);
export extern PFNGLRASTERPOS4SPROC glRasterPos4s;
PFNGLRASTERPOS4SPROC glRasterPos4s = nullptr;

export using PFNGLRASTERPOS4SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLRASTERPOS4SVPROC glRasterPos4sv;
PFNGLRASTERPOS4SVPROC glRasterPos4sv = nullptr;

export using PFNGLRECTDPROC = void (GL_CALL*)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
export extern PFNGLRECTDPROC glRectd;
PFNGLRECTDPROC glRectd = nullptr;

export using PFNGLRECTDVPROC = void (GL_CALL*)(const GLdouble* v1, const GLdouble* v2);
export extern PFNGLRECTDVPROC glRectdv;
PFNGLRECTDVPROC glRectdv = nullptr;

export using PFNGLRECTFPROC = void (GL_CALL*)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
export extern PFNGLRECTFPROC glRectf;
PFNGLRECTFPROC glRectf = nullptr;

export using PFNGLRECTFVPROC = void (GL_CALL*)(const GLfloat* v1, const GLfloat* v2);
export extern PFNGLRECTFVPROC glRectfv;
PFNGLRECTFVPROC glRectfv = nullptr;

export using PFNGLRECTIPROC = void (GL_CALL*)(GLint x1, GLint y1, GLint x2, GLint y2);
export extern PFNGLRECTIPROC glRecti;
PFNGLRECTIPROC glRecti = nullptr;

export using PFNGLRECTIVPROC = void (GL_CALL*)(const GLint* v1, const GLint* v2);
export extern PFNGLRECTIVPROC glRectiv;
PFNGLRECTIVPROC glRectiv = nullptr;

export using PFNGLRECTSPROC = void (GL_CALL*)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
export extern PFNGLRECTSPROC glRects;
PFNGLRECTSPROC glRects = nullptr;

export using PFNGLRECTSVPROC = void (GL_CALL*)(const GLshort* v1, const GLshort* v2);
export extern PFNGLRECTSVPROC glRectsv;
PFNGLRECTSVPROC glRectsv = nullptr;

export using PFNGLTEXCOORD1DPROC = void (GL_CALL*)(GLdouble s);
export extern PFNGLTEXCOORD1DPROC glTexCoord1d;
PFNGLTEXCOORD1DPROC glTexCoord1d = nullptr;

export using PFNGLTEXCOORD1DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLTEXCOORD1DVPROC glTexCoord1dv;
PFNGLTEXCOORD1DVPROC glTexCoord1dv = nullptr;

export using PFNGLTEXCOORD1FPROC = void (GL_CALL*)(GLfloat s);
export extern PFNGLTEXCOORD1FPROC glTexCoord1f;
PFNGLTEXCOORD1FPROC glTexCoord1f = nullptr;

export using PFNGLTEXCOORD1FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLTEXCOORD1FVPROC glTexCoord1fv;
PFNGLTEXCOORD1FVPROC glTexCoord1fv = nullptr;

export using PFNGLTEXCOORD1IPROC = void (GL_CALL*)(GLint s);
export extern PFNGLTEXCOORD1IPROC glTexCoord1i;
PFNGLTEXCOORD1IPROC glTexCoord1i = nullptr;

export using PFNGLTEXCOORD1IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLTEXCOORD1IVPROC glTexCoord1iv;
PFNGLTEXCOORD1IVPROC glTexCoord1iv = nullptr;

export using PFNGLTEXCOORD1SPROC = void (GL_CALL*)(GLshort s);
export extern PFNGLTEXCOORD1SPROC glTexCoord1s;
PFNGLTEXCOORD1SPROC glTexCoord1s = nullptr;

export using PFNGLTEXCOORD1SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLTEXCOORD1SVPROC glTexCoord1sv;
PFNGLTEXCOORD1SVPROC glTexCoord1sv = nullptr;

export using PFNGLTEXCOORD2DPROC = void (GL_CALL*)(GLdouble s, GLdouble t);
export extern PFNGLTEXCOORD2DPROC glTexCoord2d;
PFNGLTEXCOORD2DPROC glTexCoord2d = nullptr;

export using PFNGLTEXCOORD2DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLTEXCOORD2DVPROC glTexCoord2dv;
PFNGLTEXCOORD2DVPROC glTexCoord2dv = nullptr;

export using PFNGLTEXCOORD2FPROC = void (GL_CALL*)(GLfloat s, GLfloat t);
export extern PFNGLTEXCOORD2FPROC glTexCoord2f;
PFNGLTEXCOORD2FPROC glTexCoord2f = nullptr;

export using PFNGLTEXCOORD2FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLTEXCOORD2FVPROC glTexCoord2fv;
PFNGLTEXCOORD2FVPROC glTexCoord2fv = nullptr;

export using PFNGLTEXCOORD2IPROC = void (GL_CALL*)(GLint s, GLint t);
export extern PFNGLTEXCOORD2IPROC glTexCoord2i;
PFNGLTEXCOORD2IPROC glTexCoord2i = nullptr;

export using PFNGLTEXCOORD2IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLTEXCOORD2IVPROC glTexCoord2iv;
PFNGLTEXCOORD2IVPROC glTexCoord2iv = nullptr;

export using PFNGLTEXCOORD2SPROC = void (GL_CALL*)(GLshort s, GLshort t);
export extern PFNGLTEXCOORD2SPROC glTexCoord2s;
PFNGLTEXCOORD2SPROC glTexCoord2s = nullptr;

export using PFNGLTEXCOORD2SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLTEXCOORD2SVPROC glTexCoord2sv;
PFNGLTEXCOORD2SVPROC glTexCoord2sv = nullptr;

export using PFNGLTEXCOORD3DPROC = void (GL_CALL*)(GLdouble s, GLdouble t, GLdouble r);
export extern PFNGLTEXCOORD3DPROC glTexCoord3d;
PFNGLTEXCOORD3DPROC glTexCoord3d = nullptr;

export using PFNGLTEXCOORD3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLTEXCOORD3DVPROC glTexCoord3dv;
PFNGLTEXCOORD3DVPROC glTexCoord3dv = nullptr;

export using PFNGLTEXCOORD3FPROC = void (GL_CALL*)(GLfloat s, GLfloat t, GLfloat r);
export extern PFNGLTEXCOORD3FPROC glTexCoord3f;
PFNGLTEXCOORD3FPROC glTexCoord3f = nullptr;

export using PFNGLTEXCOORD3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLTEXCOORD3FVPROC glTexCoord3fv;
PFNGLTEXCOORD3FVPROC glTexCoord3fv = nullptr;

export using PFNGLTEXCOORD3IPROC = void (GL_CALL*)(GLint s, GLint t, GLint r);
export extern PFNGLTEXCOORD3IPROC glTexCoord3i;
PFNGLTEXCOORD3IPROC glTexCoord3i = nullptr;

export using PFNGLTEXCOORD3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLTEXCOORD3IVPROC glTexCoord3iv;
PFNGLTEXCOORD3IVPROC glTexCoord3iv = nullptr;

export using PFNGLTEXCOORD3SPROC = void (GL_CALL*)(GLshort s, GLshort t, GLshort r);
export extern PFNGLTEXCOORD3SPROC glTexCoord3s;
PFNGLTEXCOORD3SPROC glTexCoord3s = nullptr;

export using PFNGLTEXCOORD3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLTEXCOORD3SVPROC glTexCoord3sv;
PFNGLTEXCOORD3SVPROC glTexCoord3sv = nullptr;

export using PFNGLTEXCOORD4DPROC = void (GL_CALL*)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
export extern PFNGLTEXCOORD4DPROC glTexCoord4d;
PFNGLTEXCOORD4DPROC glTexCoord4d = nullptr;

export using PFNGLTEXCOORD4DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLTEXCOORD4DVPROC glTexCoord4dv;
PFNGLTEXCOORD4DVPROC glTexCoord4dv = nullptr;

export using PFNGLTEXCOORD4FPROC = void (GL_CALL*)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
export extern PFNGLTEXCOORD4FPROC glTexCoord4f;
PFNGLTEXCOORD4FPROC glTexCoord4f = nullptr;

export using PFNGLTEXCOORD4FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLTEXCOORD4FVPROC glTexCoord4fv;
PFNGLTEXCOORD4FVPROC glTexCoord4fv = nullptr;

export using PFNGLTEXCOORD4IPROC = void (GL_CALL*)(GLint s, GLint t, GLint r, GLint q);
export extern PFNGLTEXCOORD4IPROC glTexCoord4i;
PFNGLTEXCOORD4IPROC glTexCoord4i = nullptr;

export using PFNGLTEXCOORD4IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLTEXCOORD4IVPROC glTexCoord4iv;
PFNGLTEXCOORD4IVPROC glTexCoord4iv = nullptr;

export using PFNGLTEXCOORD4SPROC = void (GL_CALL*)(GLshort s, GLshort t, GLshort r, GLshort q);
export extern PFNGLTEXCOORD4SPROC glTexCoord4s;
PFNGLTEXCOORD4SPROC glTexCoord4s = nullptr;

export using PFNGLTEXCOORD4SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLTEXCOORD4SVPROC glTexCoord4sv;
PFNGLTEXCOORD4SVPROC glTexCoord4sv = nullptr;

export using PFNGLVERTEX2DPROC = void (GL_CALL*)(GLdouble x, GLdouble y);
export extern PFNGLVERTEX2DPROC glVertex2d;
PFNGLVERTEX2DPROC glVertex2d = nullptr;

export using PFNGLVERTEX2DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLVERTEX2DVPROC glVertex2dv;
PFNGLVERTEX2DVPROC glVertex2dv = nullptr;

export using PFNGLVERTEX2FPROC = void (GL_CALL*)(GLfloat x, GLfloat y);
export extern PFNGLVERTEX2FPROC glVertex2f;
PFNGLVERTEX2FPROC glVertex2f = nullptr;

export using PFNGLVERTEX2FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLVERTEX2FVPROC glVertex2fv;
PFNGLVERTEX2FVPROC glVertex2fv = nullptr;

export using PFNGLVERTEX2IPROC = void (GL_CALL*)(GLint x, GLint y);
export extern PFNGLVERTEX2IPROC glVertex2i;
PFNGLVERTEX2IPROC glVertex2i = nullptr;

export using PFNGLVERTEX2IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLVERTEX2IVPROC glVertex2iv;
PFNGLVERTEX2IVPROC glVertex2iv = nullptr;

export using PFNGLVERTEX2SPROC = void (GL_CALL*)(GLshort x, GLshort y);
export extern PFNGLVERTEX2SPROC glVertex2s;
PFNGLVERTEX2SPROC glVertex2s = nullptr;

export using PFNGLVERTEX2SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLVERTEX2SVPROC glVertex2sv;
PFNGLVERTEX2SVPROC glVertex2sv = nullptr;

export using PFNGLVERTEX3DPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLVERTEX3DPROC glVertex3d;
PFNGLVERTEX3DPROC glVertex3d = nullptr;

export using PFNGLVERTEX3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLVERTEX3DVPROC glVertex3dv;
PFNGLVERTEX3DVPROC glVertex3dv = nullptr;

export using PFNGLVERTEX3FPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLVERTEX3FPROC glVertex3f;
PFNGLVERTEX3FPROC glVertex3f = nullptr;

export using PFNGLVERTEX3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLVERTEX3FVPROC glVertex3fv;
PFNGLVERTEX3FVPROC glVertex3fv = nullptr;

export using PFNGLVERTEX3IPROC = void (GL_CALL*)(GLint x, GLint y, GLint z);
export extern PFNGLVERTEX3IPROC glVertex3i;
PFNGLVERTEX3IPROC glVertex3i = nullptr;

export using PFNGLVERTEX3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLVERTEX3IVPROC glVertex3iv;
PFNGLVERTEX3IVPROC glVertex3iv = nullptr;

export using PFNGLVERTEX3SPROC = void (GL_CALL*)(GLshort x, GLshort y, GLshort z);
export extern PFNGLVERTEX3SPROC glVertex3s;
PFNGLVERTEX3SPROC glVertex3s = nullptr;

export using PFNGLVERTEX3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLVERTEX3SVPROC glVertex3sv;
PFNGLVERTEX3SVPROC glVertex3sv = nullptr;

export using PFNGLVERTEX4DPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
export extern PFNGLVERTEX4DPROC glVertex4d;
PFNGLVERTEX4DPROC glVertex4d = nullptr;

export using PFNGLVERTEX4DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLVERTEX4DVPROC glVertex4dv;
PFNGLVERTEX4DVPROC glVertex4dv = nullptr;

export using PFNGLVERTEX4FPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
export extern PFNGLVERTEX4FPROC glVertex4f;
PFNGLVERTEX4FPROC glVertex4f = nullptr;

export using PFNGLVERTEX4FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLVERTEX4FVPROC glVertex4fv;
PFNGLVERTEX4FVPROC glVertex4fv = nullptr;

export using PFNGLVERTEX4IPROC = void (GL_CALL*)(GLint x, GLint y, GLint z, GLint w);
export extern PFNGLVERTEX4IPROC glVertex4i;
PFNGLVERTEX4IPROC glVertex4i = nullptr;

export using PFNGLVERTEX4IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLVERTEX4IVPROC glVertex4iv;
PFNGLVERTEX4IVPROC glVertex4iv = nullptr;

export using PFNGLVERTEX4SPROC = void (GL_CALL*)(GLshort x, GLshort y, GLshort z, GLshort w);
export extern PFNGLVERTEX4SPROC glVertex4s;
PFNGLVERTEX4SPROC glVertex4s = nullptr;

export using PFNGLVERTEX4SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLVERTEX4SVPROC glVertex4sv;
PFNGLVERTEX4SVPROC glVertex4sv = nullptr;

export using PFNGLCLIPPLANEPROC = void (GL_CALL*)(GLenum plane, const GLdouble* equation);
export extern PFNGLCLIPPLANEPROC glClipPlane;
PFNGLCLIPPLANEPROC glClipPlane = nullptr;

export using PFNGLCOLORMATERIALPROC = void (GL_CALL*)(GLenum face, GLenum mode);
export extern PFNGLCOLORMATERIALPROC glColorMaterial;
PFNGLCOLORMATERIALPROC glColorMaterial = nullptr;

export using PFNGLFOGFPROC = void (GL_CALL*)(GLenum pname, GLfloat param);
export extern PFNGLFOGFPROC glFogf;
PFNGLFOGFPROC glFogf = nullptr;

export using PFNGLFOGFVPROC = void (GL_CALL*)(GLenum pname, const GLfloat* params);
export extern PFNGLFOGFVPROC glFogfv;
PFNGLFOGFVPROC glFogfv = nullptr;

export using PFNGLFOGIPROC = void (GL_CALL*)(GLenum pname, GLint param);
export extern PFNGLFOGIPROC glFogi;
PFNGLFOGIPROC glFogi = nullptr;

export using PFNGLFOGIVPROC = void (GL_CALL*)(GLenum pname, const GLint* params);
export extern PFNGLFOGIVPROC glFogiv;
PFNGLFOGIVPROC glFogiv = nullptr;

export using PFNGLLIGHTFPROC = void (GL_CALL*)(GLenum light, GLenum pname, GLfloat param);
export extern PFNGLLIGHTFPROC glLightf;
PFNGLLIGHTFPROC glLightf = nullptr;

export using PFNGLLIGHTFVPROC = void (GL_CALL*)(GLenum light, GLenum pname, const GLfloat* params);
export extern PFNGLLIGHTFVPROC glLightfv;
PFNGLLIGHTFVPROC glLightfv = nullptr;

export using PFNGLLIGHTIPROC = void (GL_CALL*)(GLenum light, GLenum pname, GLint param);
export extern PFNGLLIGHTIPROC glLighti;
PFNGLLIGHTIPROC glLighti = nullptr;

export using PFNGLLIGHTIVPROC = void (GL_CALL*)(GLenum light, GLenum pname, const GLint* params);
export extern PFNGLLIGHTIVPROC glLightiv;
PFNGLLIGHTIVPROC glLightiv = nullptr;

export using PFNGLLIGHTMODELFPROC = void (GL_CALL*)(GLenum pname, GLfloat param);
export extern PFNGLLIGHTMODELFPROC glLightModelf;
PFNGLLIGHTMODELFPROC glLightModelf = nullptr;

export using PFNGLLIGHTMODELFVPROC = void (GL_CALL*)(GLenum pname, const GLfloat* params);
export extern PFNGLLIGHTMODELFVPROC glLightModelfv;
PFNGLLIGHTMODELFVPROC glLightModelfv = nullptr;

export using PFNGLLIGHTMODELIPROC = void (GL_CALL*)(GLenum pname, GLint param);
export extern PFNGLLIGHTMODELIPROC glLightModeli;
PFNGLLIGHTMODELIPROC glLightModeli = nullptr;

export using PFNGLLIGHTMODELIVPROC = void (GL_CALL*)(GLenum pname, const GLint* params);
export extern PFNGLLIGHTMODELIVPROC glLightModeliv;
PFNGLLIGHTMODELIVPROC glLightModeliv = nullptr;

export using PFNGLLINESTIPPLEPROC = void (GL_CALL*)(GLint factor, GLushort pattern);
export extern PFNGLLINESTIPPLEPROC glLineStipple;
PFNGLLINESTIPPLEPROC glLineStipple = nullptr;

export using PFNGLMATERIALFPROC = void (GL_CALL*)(GLenum face, GLenum pname, GLfloat param);
export extern PFNGLMATERIALFPROC glMaterialf;
PFNGLMATERIALFPROC glMaterialf = nullptr;

export using PFNGLMATERIALFVPROC = void (GL_CALL*)(GLenum face, GLenum pname, const GLfloat* params);
export extern PFNGLMATERIALFVPROC glMaterialfv;
PFNGLMATERIALFVPROC glMaterialfv = nullptr;

export using PFNGLMATERIALIPROC = void (GL_CALL*)(GLenum face, GLenum pname, GLint param);
export extern PFNGLMATERIALIPROC glMateriali;
PFNGLMATERIALIPROC glMateriali = nullptr;

export using PFNGLMATERIALIVPROC = void (GL_CALL*)(GLenum face, GLenum pname, const GLint* params);
export extern PFNGLMATERIALIVPROC glMaterialiv;
PFNGLMATERIALIVPROC glMaterialiv = nullptr;

export using PFNGLPOLYGONSTIPPLEPROC = void (GL_CALL*)(const GLubyte* mask);
export extern PFNGLPOLYGONSTIPPLEPROC glPolygonStipple;
PFNGLPOLYGONSTIPPLEPROC glPolygonStipple = nullptr;

export using PFNGLSHADEMODELPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLSHADEMODELPROC glShadeModel;
PFNGLSHADEMODELPROC glShadeModel = nullptr;

export using PFNGLTEXENVFPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLfloat param);
export extern PFNGLTEXENVFPROC glTexEnvf;
PFNGLTEXENVFPROC glTexEnvf = nullptr;

export using PFNGLTEXENVFVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLfloat* params);
export extern PFNGLTEXENVFVPROC glTexEnvfv;
PFNGLTEXENVFVPROC glTexEnvfv = nullptr;

export using PFNGLTEXENVIPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint param);
export extern PFNGLTEXENVIPROC glTexEnvi;
PFNGLTEXENVIPROC glTexEnvi = nullptr;

export using PFNGLTEXENVIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLint* params);
export extern PFNGLTEXENVIVPROC glTexEnviv;
PFNGLTEXENVIVPROC glTexEnviv = nullptr;

export using PFNGLTEXGENDPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLdouble param);
export extern PFNGLTEXGENDPROC glTexGend;
PFNGLTEXGENDPROC glTexGend = nullptr;

export using PFNGLTEXGENDVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, const GLdouble* params);
export extern PFNGLTEXGENDVPROC glTexGendv;
PFNGLTEXGENDVPROC glTexGendv = nullptr;

export using PFNGLTEXGENFPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLfloat param);
export extern PFNGLTEXGENFPROC glTexGenf;
PFNGLTEXGENFPROC glTexGenf = nullptr;

export using PFNGLTEXGENFVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, const GLfloat* params);
export extern PFNGLTEXGENFVPROC glTexGenfv;
PFNGLTEXGENFVPROC glTexGenfv = nullptr;

export using PFNGLTEXGENIPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLint param);
export extern PFNGLTEXGENIPROC glTexGeni;
PFNGLTEXGENIPROC glTexGeni = nullptr;

export using PFNGLTEXGENIVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, const GLint* params);
export extern PFNGLTEXGENIVPROC glTexGeniv;
PFNGLTEXGENIVPROC glTexGeniv = nullptr;

export using PFNGLFEEDBACKBUFFERPROC = void (GL_CALL*)(GLsizei size, GLenum type, GLfloat* buffer);
export extern PFNGLFEEDBACKBUFFERPROC glFeedbackBuffer;
PFNGLFEEDBACKBUFFERPROC glFeedbackBuffer = nullptr;

export using PFNGLSELECTBUFFERPROC = void (GL_CALL*)(GLsizei size, GLuint* buffer);
export extern PFNGLSELECTBUFFERPROC glSelectBuffer;
PFNGLSELECTBUFFERPROC glSelectBuffer = nullptr;

export using PFNGLRENDERMODEPROC = GLint(GL_CALL*)(GLenum mode);
export extern PFNGLRENDERMODEPROC glRenderMode;
PFNGLRENDERMODEPROC glRenderMode = nullptr;

export using PFNGLINITNAMESPROC = void (GL_CALL*)();
export extern PFNGLINITNAMESPROC glInitNames;
PFNGLINITNAMESPROC glInitNames = nullptr;

export using PFNGLLOADNAMEPROC = void (GL_CALL*)(GLuint name);
export extern PFNGLLOADNAMEPROC glLoadName;
PFNGLLOADNAMEPROC glLoadName = nullptr;

export using PFNGLPASSTHROUGHPROC = void (GL_CALL*)(GLfloat token);
export extern PFNGLPASSTHROUGHPROC glPassThrough;
PFNGLPASSTHROUGHPROC glPassThrough = nullptr;

export using PFNGLPOPNAMEPROC = void (GL_CALL*)();
export extern PFNGLPOPNAMEPROC glPopName;
PFNGLPOPNAMEPROC glPopName = nullptr;

export using PFNGLPUSHNAMEPROC = void (GL_CALL*)(GLuint name);
export extern PFNGLPUSHNAMEPROC glPushName;
PFNGLPUSHNAMEPROC glPushName = nullptr;

export using PFNGLCLEARACCUMPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
export extern PFNGLCLEARACCUMPROC glClearAccum;
PFNGLCLEARACCUMPROC glClearAccum = nullptr;

export using PFNGLCLEARINDEXPROC = void (GL_CALL*)(GLfloat c);
export extern PFNGLCLEARINDEXPROC glClearIndex;
PFNGLCLEARINDEXPROC glClearIndex = nullptr;

export using PFNGLINDEXMASKPROC = void (GL_CALL*)(GLuint mask);
export extern PFNGLINDEXMASKPROC glIndexMask;
PFNGLINDEXMASKPROC glIndexMask = nullptr;

export using PFNGLACCUMPROC = void (GL_CALL*)(GLenum op, GLfloat value);
export extern PFNGLACCUMPROC glAccum;
PFNGLACCUMPROC glAccum = nullptr;

export using PFNGLPOPATTRIBPROC = void (GL_CALL*)();
export extern PFNGLPOPATTRIBPROC glPopAttrib;
PFNGLPOPATTRIBPROC glPopAttrib = nullptr;

export using PFNGLPUSHATTRIBPROC = void (GL_CALL*)(GLbitfield mask);
export extern PFNGLPUSHATTRIBPROC glPushAttrib;
PFNGLPUSHATTRIBPROC glPushAttrib = nullptr;

export using PFNGLMAP1DPROC = void (GL_CALL*)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points);
export extern PFNGLMAP1DPROC glMap1d;
PFNGLMAP1DPROC glMap1d = nullptr;

export using PFNGLMAP1FPROC = void (GL_CALL*)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points);
export extern PFNGLMAP1FPROC glMap1f;
PFNGLMAP1FPROC glMap1f = nullptr;

export using PFNGLMAP2DPROC = void (GL_CALL*)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points);
export extern PFNGLMAP2DPROC glMap2d;
PFNGLMAP2DPROC glMap2d = nullptr;

export using PFNGLMAP2FPROC = void (GL_CALL*)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points);
export extern PFNGLMAP2FPROC glMap2f;
PFNGLMAP2FPROC glMap2f = nullptr;

export using PFNGLMAPGRID1DPROC = void (GL_CALL*)(GLint un, GLdouble u1, GLdouble u2);
export extern PFNGLMAPGRID1DPROC glMapGrid1d;
PFNGLMAPGRID1DPROC glMapGrid1d = nullptr;

export using PFNGLMAPGRID1FPROC = void (GL_CALL*)(GLint un, GLfloat u1, GLfloat u2);
export extern PFNGLMAPGRID1FPROC glMapGrid1f;
PFNGLMAPGRID1FPROC glMapGrid1f = nullptr;

export using PFNGLMAPGRID2DPROC = void (GL_CALL*)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
export extern PFNGLMAPGRID2DPROC glMapGrid2d;
PFNGLMAPGRID2DPROC glMapGrid2d = nullptr;

export using PFNGLMAPGRID2FPROC = void (GL_CALL*)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
export extern PFNGLMAPGRID2FPROC glMapGrid2f;
PFNGLMAPGRID2FPROC glMapGrid2f = nullptr;

export using PFNGLEVALCOORD1DPROC = void (GL_CALL*)(GLdouble u);
export extern PFNGLEVALCOORD1DPROC glEvalCoord1d;
PFNGLEVALCOORD1DPROC glEvalCoord1d = nullptr;

export using PFNGLEVALCOORD1DVPROC = void (GL_CALL*)(const GLdouble* u);
export extern PFNGLEVALCOORD1DVPROC glEvalCoord1dv;
PFNGLEVALCOORD1DVPROC glEvalCoord1dv = nullptr;

export using PFNGLEVALCOORD1FPROC = void (GL_CALL*)(GLfloat u);
export extern PFNGLEVALCOORD1FPROC glEvalCoord1f;
PFNGLEVALCOORD1FPROC glEvalCoord1f = nullptr;

export using PFNGLEVALCOORD1FVPROC = void (GL_CALL*)(const GLfloat* u);
export extern PFNGLEVALCOORD1FVPROC glEvalCoord1fv;
PFNGLEVALCOORD1FVPROC glEvalCoord1fv = nullptr;

export using PFNGLEVALCOORD2DPROC = void (GL_CALL*)(GLdouble u, GLdouble v);
export extern PFNGLEVALCOORD2DPROC glEvalCoord2d;
PFNGLEVALCOORD2DPROC glEvalCoord2d = nullptr;

export using PFNGLEVALCOORD2DVPROC = void (GL_CALL*)(const GLdouble* u);
export extern PFNGLEVALCOORD2DVPROC glEvalCoord2dv;
PFNGLEVALCOORD2DVPROC glEvalCoord2dv = nullptr;

export using PFNGLEVALCOORD2FPROC = void (GL_CALL*)(GLfloat u, GLfloat v);
export extern PFNGLEVALCOORD2FPROC glEvalCoord2f;
PFNGLEVALCOORD2FPROC glEvalCoord2f = nullptr;

export using PFNGLEVALCOORD2FVPROC = void (GL_CALL*)(const GLfloat* u);
export extern PFNGLEVALCOORD2FVPROC glEvalCoord2fv;
PFNGLEVALCOORD2FVPROC glEvalCoord2fv = nullptr;

export using PFNGLEVALMESH1PROC = void (GL_CALL*)(GLenum mode, GLint i1, GLint i2);
export extern PFNGLEVALMESH1PROC glEvalMesh1;
PFNGLEVALMESH1PROC glEvalMesh1 = nullptr;

export using PFNGLEVALPOINT1PROC = void (GL_CALL*)(GLint i);
export extern PFNGLEVALPOINT1PROC glEvalPoint1;
PFNGLEVALPOINT1PROC glEvalPoint1 = nullptr;

export using PFNGLEVALMESH2PROC = void (GL_CALL*)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
export extern PFNGLEVALMESH2PROC glEvalMesh2;
PFNGLEVALMESH2PROC glEvalMesh2 = nullptr;

export using PFNGLEVALPOINT2PROC = void (GL_CALL*)(GLint i, GLint j);
export extern PFNGLEVALPOINT2PROC glEvalPoint2;
PFNGLEVALPOINT2PROC glEvalPoint2 = nullptr;

export using PFNGLALPHAFUNCPROC = void (GL_CALL*)(GLenum func, GLfloat ref);
export extern PFNGLALPHAFUNCPROC glAlphaFunc;
PFNGLALPHAFUNCPROC glAlphaFunc = nullptr;

export using PFNGLPIXELZOOMPROC = void (GL_CALL*)(GLfloat xfactor, GLfloat yfactor);
export extern PFNGLPIXELZOOMPROC glPixelZoom;
PFNGLPIXELZOOMPROC glPixelZoom = nullptr;

export using PFNGLPIXELTRANSFERFPROC = void (GL_CALL*)(GLenum pname, GLfloat param);
export extern PFNGLPIXELTRANSFERFPROC glPixelTransferf;
PFNGLPIXELTRANSFERFPROC glPixelTransferf = nullptr;

export using PFNGLPIXELTRANSFERIPROC = void (GL_CALL*)(GLenum pname, GLint param);
export extern PFNGLPIXELTRANSFERIPROC glPixelTransferi;
PFNGLPIXELTRANSFERIPROC glPixelTransferi = nullptr;

export using PFNGLPIXELMAPFVPROC = void (GL_CALL*)(GLenum map, GLsizei mapsize, const GLfloat* values);
export extern PFNGLPIXELMAPFVPROC glPixelMapfv;
PFNGLPIXELMAPFVPROC glPixelMapfv = nullptr;

export using PFNGLPIXELMAPUIVPROC = void (GL_CALL*)(GLenum map, GLsizei mapsize, const GLuint* values);
export extern PFNGLPIXELMAPUIVPROC glPixelMapuiv;
PFNGLPIXELMAPUIVPROC glPixelMapuiv = nullptr;

export using PFNGLPIXELMAPUSVPROC = void (GL_CALL*)(GLenum map, GLsizei mapsize, const GLushort* values);
export extern PFNGLPIXELMAPUSVPROC glPixelMapusv;
PFNGLPIXELMAPUSVPROC glPixelMapusv = nullptr;

export using PFNGLCOPYPIXELSPROC = void (GL_CALL*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
export extern PFNGLCOPYPIXELSPROC glCopyPixels;
PFNGLCOPYPIXELSPROC glCopyPixels = nullptr;

export using PFNGLDRAWPIXELSPROC = void (GL_CALL*)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
export extern PFNGLDRAWPIXELSPROC glDrawPixels;
PFNGLDRAWPIXELSPROC glDrawPixels = nullptr;

export using PFNGLGETCLIPPLANEPROC = void (GL_CALL*)(GLenum plane, GLdouble* equation);
export extern PFNGLGETCLIPPLANEPROC glGetClipPlane;
PFNGLGETCLIPPLANEPROC glGetClipPlane = nullptr;

export using PFNGLGETLIGHTFVPROC = void (GL_CALL*)(GLenum light, GLenum pname, GLfloat* params);
export extern PFNGLGETLIGHTFVPROC glGetLightfv;
PFNGLGETLIGHTFVPROC glGetLightfv = nullptr;

export using PFNGLGETLIGHTIVPROC = void (GL_CALL*)(GLenum light, GLenum pname, GLint* params);
export extern PFNGLGETLIGHTIVPROC glGetLightiv;
PFNGLGETLIGHTIVPROC glGetLightiv = nullptr;

export using PFNGLGETMAPDVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLdouble* v);
export extern PFNGLGETMAPDVPROC glGetMapdv;
PFNGLGETMAPDVPROC glGetMapdv = nullptr;

export using PFNGLGETMAPFVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLfloat* v);
export extern PFNGLGETMAPFVPROC glGetMapfv;
PFNGLGETMAPFVPROC glGetMapfv = nullptr;

export using PFNGLGETMAPIVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLint* v);
export extern PFNGLGETMAPIVPROC glGetMapiv;
PFNGLGETMAPIVPROC glGetMapiv = nullptr;

export using PFNGLGETMATERIALFVPROC = void (GL_CALL*)(GLenum face, GLenum pname, GLfloat* params);
export extern PFNGLGETMATERIALFVPROC glGetMaterialfv;
PFNGLGETMATERIALFVPROC glGetMaterialfv = nullptr;

export using PFNGLGETMATERIALIVPROC = void (GL_CALL*)(GLenum face, GLenum pname, GLint* params);
export extern PFNGLGETMATERIALIVPROC glGetMaterialiv;
PFNGLGETMATERIALIVPROC glGetMaterialiv = nullptr;

export using PFNGLGETPIXELMAPFVPROC = void (GL_CALL*)(GLenum map, GLfloat* values);
export extern PFNGLGETPIXELMAPFVPROC glGetPixelMapfv;
PFNGLGETPIXELMAPFVPROC glGetPixelMapfv = nullptr;

export using PFNGLGETPIXELMAPUIVPROC = void (GL_CALL*)(GLenum map, GLuint* values);
export extern PFNGLGETPIXELMAPUIVPROC glGetPixelMapuiv;
PFNGLGETPIXELMAPUIVPROC glGetPixelMapuiv = nullptr;

export using PFNGLGETPIXELMAPUSVPROC = void (GL_CALL*)(GLenum map, GLushort* values);
export extern PFNGLGETPIXELMAPUSVPROC glGetPixelMapusv;
PFNGLGETPIXELMAPUSVPROC glGetPixelMapusv = nullptr;

export using PFNGLGETPOLYGONSTIPPLEPROC = void (GL_CALL*)(GLubyte* mask);
export extern PFNGLGETPOLYGONSTIPPLEPROC glGetPolygonStipple;
PFNGLGETPOLYGONSTIPPLEPROC glGetPolygonStipple = nullptr;

export using PFNGLGETTEXENVFVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXENVFVPROC glGetTexEnvfv;
PFNGLGETTEXENVFVPROC glGetTexEnvfv = nullptr;

export using PFNGLGETTEXENVIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETTEXENVIVPROC glGetTexEnviv;
PFNGLGETTEXENVIVPROC glGetTexEnviv = nullptr;

export using PFNGLGETTEXGENDVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLdouble* params);
export extern PFNGLGETTEXGENDVPROC glGetTexGendv;
PFNGLGETTEXGENDVPROC glGetTexGendv = nullptr;

export using PFNGLGETTEXGENFVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXGENFVPROC glGetTexGenfv;
PFNGLGETTEXGENFVPROC glGetTexGenfv = nullptr;

export using PFNGLGETTEXGENIVPROC = void (GL_CALL*)(GLenum coord, GLenum pname, GLint* params);
export extern PFNGLGETTEXGENIVPROC glGetTexGeniv;
PFNGLGETTEXGENIVPROC glGetTexGeniv = nullptr;

export using PFNGLISLISTPROC = GLboolean(GL_CALL*)(GLuint list);
export extern PFNGLISLISTPROC glIsList;
PFNGLISLISTPROC glIsList = nullptr;

export using PFNGLFRUSTUMPROC = void (GL_CALL*)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
export extern PFNGLFRUSTUMPROC glFrustum;
PFNGLFRUSTUMPROC glFrustum = nullptr;

export using PFNGLLOADIDENTITYPROC = void (GL_CALL*)();
export extern PFNGLLOADIDENTITYPROC glLoadIdentity;
PFNGLLOADIDENTITYPROC glLoadIdentity = nullptr;

export using PFNGLLOADMATRIXFPROC = void (GL_CALL*)(const GLfloat* m);
export extern PFNGLLOADMATRIXFPROC glLoadMatrixf;
PFNGLLOADMATRIXFPROC glLoadMatrixf = nullptr;

export using PFNGLLOADMATRIXDPROC = void (GL_CALL*)(const GLdouble* m);
export extern PFNGLLOADMATRIXDPROC glLoadMatrixd;
PFNGLLOADMATRIXDPROC glLoadMatrixd = nullptr;

export using PFNGLMATRIXMODEPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLMATRIXMODEPROC glMatrixMode;
PFNGLMATRIXMODEPROC glMatrixMode = nullptr;

export using PFNGLMULTMATRIXFPROC = void (GL_CALL*)(const GLfloat* m);
export extern PFNGLMULTMATRIXFPROC glMultMatrixf;
PFNGLMULTMATRIXFPROC glMultMatrixf = nullptr;

export using PFNGLMULTMATRIXDPROC = void (GL_CALL*)(const GLdouble* m);
export extern PFNGLMULTMATRIXDPROC glMultMatrixd;
PFNGLMULTMATRIXDPROC glMultMatrixd = nullptr;

export using PFNGLORTHOPROC = void (GL_CALL*)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
export extern PFNGLORTHOPROC glOrtho;
PFNGLORTHOPROC glOrtho = nullptr;

export using PFNGLPOPMATRIXPROC = void (GL_CALL*)();
export extern PFNGLPOPMATRIXPROC glPopMatrix;
PFNGLPOPMATRIXPROC glPopMatrix = nullptr;

export using PFNGLPUSHMATRIXPROC = void (GL_CALL*)();
export extern PFNGLPUSHMATRIXPROC glPushMatrix;
PFNGLPUSHMATRIXPROC glPushMatrix = nullptr;

export using PFNGLROTATEDPROC = void (GL_CALL*)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLROTATEDPROC glRotated;
PFNGLROTATEDPROC glRotated = nullptr;

export using PFNGLROTATEFPROC = void (GL_CALL*)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLROTATEFPROC glRotatef;
PFNGLROTATEFPROC glRotatef = nullptr;

export using PFNGLSCALEDPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLSCALEDPROC glScaled;
PFNGLSCALEDPROC glScaled = nullptr;

export using PFNGLSCALEFPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLSCALEFPROC glScalef;
PFNGLSCALEFPROC glScalef = nullptr;

export using PFNGLTRANSLATEDPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLTRANSLATEDPROC glTranslated;
PFNGLTRANSLATEDPROC glTranslated = nullptr;

export using PFNGLTRANSLATEFPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLTRANSLATEFPROC glTranslatef;
PFNGLTRANSLATEFPROC glTranslatef = nullptr;

// ==================== OpenGL 1.1 Array Functions ====================

export using PFNGLDRAWARRAYSPROC = void (GL_CALL*)(GLenum mode, GLint first, GLsizei count);
export extern PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLDRAWARRAYSPROC glDrawArrays = nullptr;

export using PFNGLDRAWELEMENTSPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices);
export extern PFNGLDRAWELEMENTSPROC glDrawElements;
PFNGLDRAWELEMENTSPROC glDrawElements = nullptr;

export using PFNGLGETPOINTERVPROC = void (GL_CALL*)(GLenum pname, void** params);
export extern PFNGLGETPOINTERVPROC glGetPointerv;
PFNGLGETPOINTERVPROC glGetPointerv = nullptr;

export using PFNGLPOLYGONOFFSETPROC = void (GL_CALL*)(GLfloat factor, GLfloat units);
export extern PFNGLPOLYGONOFFSETPROC glPolygonOffset;
PFNGLPOLYGONOFFSETPROC glPolygonOffset = nullptr;

export using PFNGLCOPYTEXIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
export extern PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D;
PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D = nullptr;

export using PFNGLCOPYTEXIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
export extern PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D;
PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = nullptr;

export using PFNGLCOPYTEXSUBIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
export extern PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D = nullptr;

export using PFNGLCOPYTEXSUBIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D;
PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = nullptr;

export using PFNGLTEXSUBIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D;
PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D = nullptr;

export using PFNGLTEXSUBIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = nullptr;

export using PFNGLBINDTEXTUREPROC = void (GL_CALL*)(GLenum target, GLuint texture);
export extern PFNGLBINDTEXTUREPROC glBindTexture;
PFNGLBINDTEXTUREPROC glBindTexture = nullptr;

export using PFNGLDELETETEXTURESPROC = void (GL_CALL*)(GLsizei n, const GLuint* textures);
export extern PFNGLDELETETEXTURESPROC glDeleteTextures;
PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;

export using PFNGLGENTEXTURESPROC = void (GL_CALL*)(GLsizei n, GLuint* textures);
export extern PFNGLGENTEXTURESPROC glGenTextures;
PFNGLGENTEXTURESPROC glGenTextures = nullptr;

export using PFNGLISTEXTUREPROC = GLboolean(GL_CALL*)(GLuint texture);
export extern PFNGLISTEXTUREPROC glIsTexture;
PFNGLISTEXTUREPROC glIsTexture = nullptr;

export using PFNGLARRAYELEMENTPROC = void (GL_CALL*)(GLint i);
export extern PFNGLARRAYELEMENTPROC glArrayElement;
PFNGLARRAYELEMENTPROC glArrayElement = nullptr;

export using PFNGLCOLORPOINTERPROC = void (GL_CALL*)(GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLCOLORPOINTERPROC glColorPointer;
PFNGLCOLORPOINTERPROC glColorPointer = nullptr;

export using PFNGLDISABLECLIENTSTATEPROC = void (GL_CALL*)(GLenum array);
export extern PFNGLDISABLECLIENTSTATEPROC glDisableClientState;
PFNGLDISABLECLIENTSTATEPROC glDisableClientState = nullptr;

export using PFNGLEDGEFLAGPOINTERPROC = void (GL_CALL*)(GLsizei stride, const void* pointer);
export extern PFNGLEDGEFLAGPOINTERPROC glEdgeFlagPointer;
PFNGLEDGEFLAGPOINTERPROC glEdgeFlagPointer = nullptr;

export using PFNGLENABLECLIENTSTATEPROC = void (GL_CALL*)(GLenum array);
export extern PFNGLENABLECLIENTSTATEPROC glEnableClientState;
PFNGLENABLECLIENTSTATEPROC glEnableClientState = nullptr;

export using PFNGLINDEXPOINTERPROC = void (GL_CALL*)(GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLINDEXPOINTERPROC glIndexPointer;
PFNGLINDEXPOINTERPROC glIndexPointer = nullptr;

export using PFNGLINTERLEAVEDARRAYSPROC = void (GL_CALL*)(GLenum format, GLsizei stride, const void* pointer);
export extern PFNGLINTERLEAVEDARRAYSPROC glInterleavedArrays;
PFNGLINTERLEAVEDARRAYSPROC glInterleavedArrays = nullptr;

export using PFNGLNORMALPOINTERPROC = void (GL_CALL*)(GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLNORMALPOINTERPROC glNormalPointer;
PFNGLNORMALPOINTERPROC glNormalPointer = nullptr;

export using PFNGLTEXCOORDPOINTERPROC = void (GL_CALL*)(GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLTEXCOORDPOINTERPROC glTexCoordPointer;
PFNGLTEXCOORDPOINTERPROC glTexCoordPointer = nullptr;

export using PFNGLVERTEXPOINTERPROC = void (GL_CALL*)(GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLVERTEXPOINTERPROC glVertexPointer;
PFNGLVERTEXPOINTERPROC glVertexPointer = nullptr;

export using PFNGLARETEXTURESRESIDENTPROC = GLboolean(GL_CALL*)(GLsizei n, const GLuint* textures, GLboolean* residences);
export extern PFNGLARETEXTURESRESIDENTPROC glAreTexturesResident;
PFNGLARETEXTURESRESIDENTPROC glAreTexturesResident = nullptr;

export using PFNGLPRIORITIZETEXTURESPROC = void (GL_CALL*)(GLsizei n, const GLuint* textures, const GLfloat* priorities);
export extern PFNGLPRIORITIZETEXTURESPROC glPrioritizeTextures;
PFNGLPRIORITIZETEXTURESPROC glPrioritizeTextures = nullptr;

export using PFNGLINDEXUBPROC = void (GL_CALL*)(GLubyte c);
export extern PFNGLINDEXUBPROC glIndexub;
PFNGLINDEXUBPROC glIndexub = nullptr;

export using PFNGLINDEXUBVPROC = void (GL_CALL*)(const GLubyte* c);
export extern PFNGLINDEXUBVPROC glIndexubv;
PFNGLINDEXUBVPROC glIndexubv = nullptr;

export using PFNGLPOPCLIENTATTRIBPROC = void (GL_CALL*)();
export extern PFNGLPOPCLIENTATTRIBPROC glPopClientAttrib;
PFNGLPOPCLIENTATTRIBPROC glPopClientAttrib = nullptr;

export using PFNGLPUSHCLIENTATTRIBPROC = void (GL_CALL*)(GLbitfield mask);
export extern PFNGLPUSHCLIENTATTRIBPROC glPushClientAttrib;
PFNGLPUSHCLIENTATTRIBPROC glPushClientAttrib = nullptr;

// ==================== OpenGL 1.2 Functions ====================

export using PFNGLDRAWRANGEELEMENTSPROC = void (GL_CALL*)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
export extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = nullptr;

export using PFNGLTEXIMAGE3DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXIMAGE3DPROC glTexImage3D;
PFNGLTEXIMAGE3DPROC glTexImage3D = nullptr;

export using PFNGLTEXSUBIMAGE3DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = nullptr;

export using PFNGLCOPYTEXSUBIMAGE3DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = nullptr;

// ==================== OpenGL 1.3 Functions ====================

export using PFNGLACTIVETEXTUREPROC = void (GL_CALL*)(GLenum texture);
export extern PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;

export using PFNGLSAMPLECOVERAGEPROC = void (GL_CALL*)(GLfloat value, GLboolean invert);
export extern PFNGLSAMPLECOVERAGEPROC glSampleCoverage;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = nullptr;

export using PFNGLCOMPRESSEDTEXIMAGE3DPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = nullptr;

export using PFNGLCOMPRESSEDTEXIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = nullptr;

export using PFNGLCOMPRESSEDTEXIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = nullptr;

export using PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = nullptr;

export using PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = nullptr;

export using PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC = void (GL_CALL*)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = nullptr;

export using PFNGLGETCOMPRESSEDTEXIMAGEPROC = void (GL_CALL*)(GLenum target, GLint level, void* img);
export extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = nullptr;

export using PFNGLCLIENTACTIVETEXTUREPROC = void (GL_CALL*)(GLenum texture);
export extern PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = nullptr;

export using PFNGLMULTITEXCOORD1DPROC = void (GL_CALL*)(GLenum target, GLdouble s);
export extern PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = nullptr;

export using PFNGLMULTITEXCOORD1DVPROC = void (GL_CALL*)(GLenum target, const GLdouble* v);
export extern PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = nullptr;

export using PFNGLMULTITEXCOORD1FPROC = void (GL_CALL*)(GLenum target, GLfloat s);
export extern PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = nullptr;

export using PFNGLMULTITEXCOORD1FVPROC = void (GL_CALL*)(GLenum target, const GLfloat* v);
export extern PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = nullptr;

export using PFNGLMULTITEXCOORD1IPROC = void (GL_CALL*)(GLenum target, GLint s);
export extern PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = nullptr;

export using PFNGLMULTITEXCOORD1IVPROC = void (GL_CALL*)(GLenum target, const GLint* v);
export extern PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = nullptr;

export using PFNGLMULTITEXCOORD1SPROC = void (GL_CALL*)(GLenum target, GLshort s);
export extern PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = nullptr;

export using PFNGLMULTITEXCOORD1SVPROC = void (GL_CALL*)(GLenum target, const GLshort* v);
export extern PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = nullptr;

export using PFNGLMULTITEXCOORD2DPROC = void (GL_CALL*)(GLenum target, GLdouble s, GLdouble t);
export extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = nullptr;

export using PFNGLMULTITEXCOORD2DVPROC = void (GL_CALL*)(GLenum target, const GLdouble* v);
export extern PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = nullptr;

export using PFNGLMULTITEXCOORD2FPROC = void (GL_CALL*)(GLenum target, GLfloat s, GLfloat t);
export extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = nullptr;

export using PFNGLMULTITEXCOORD2FVPROC = void (GL_CALL*)(GLenum target, const GLfloat* v);
export extern PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = nullptr;

export using PFNGLMULTITEXCOORD2IPROC = void (GL_CALL*)(GLenum target, GLint s, GLint t);
export extern PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = nullptr;

export using PFNGLMULTITEXCOORD2IVPROC = void (GL_CALL*)(GLenum target, const GLint* v);
export extern PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = nullptr;

export using PFNGLMULTITEXCOORD2SPROC = void (GL_CALL*)(GLenum target, GLshort s, GLshort t);
export extern PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = nullptr;

export using PFNGLMULTITEXCOORD2SVPROC = void (GL_CALL*)(GLenum target, const GLshort* v);
export extern PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = nullptr;

export using PFNGLMULTITEXCOORD3DPROC = void (GL_CALL*)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
export extern PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = nullptr;

export using PFNGLMULTITEXCOORD3DVPROC = void (GL_CALL*)(GLenum target, const GLdouble* v);
export extern PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = nullptr;

export using PFNGLMULTITEXCOORD3FPROC = void (GL_CALL*)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
export extern PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = nullptr;

export using PFNGLMULTITEXCOORD3FVPROC = void (GL_CALL*)(GLenum target, const GLfloat* v);
export extern PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = nullptr;

export using PFNGLMULTITEXCOORD3IPROC = void (GL_CALL*)(GLenum target, GLint s, GLint t, GLint r);
export extern PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = nullptr;

export using PFNGLMULTITEXCOORD3IVPROC = void (GL_CALL*)(GLenum target, const GLint* v);
export extern PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = nullptr;

export using PFNGLMULTITEXCOORD3SPROC = void (GL_CALL*)(GLenum target, GLshort s, GLshort t, GLshort r);
export extern PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = nullptr;

export using PFNGLMULTITEXCOORD3SVPROC = void (GL_CALL*)(GLenum target, const GLshort* v);
export extern PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = nullptr;

export using PFNGLMULTITEXCOORD4DPROC = void (GL_CALL*)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
export extern PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = nullptr;

export using PFNGLMULTITEXCOORD4DVPROC = void (GL_CALL*)(GLenum target, const GLdouble* v);
export extern PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = nullptr;

export using PFNGLMULTITEXCOORD4FPROC = void (GL_CALL*)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
export extern PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = nullptr;

export using PFNGLMULTITEXCOORD4FVPROC = void (GL_CALL*)(GLenum target, const GLfloat* v);
export extern PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = nullptr;

export using PFNGLMULTITEXCOORD4IPROC = void (GL_CALL*)(GLenum target, GLint s, GLint t, GLint r, GLint q);
export extern PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = nullptr;

export using PFNGLMULTITEXCOORD4IVPROC = void (GL_CALL*)(GLenum target, const GLint* v);
export extern PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = nullptr;

export using PFNGLMULTITEXCOORD4SPROC = void (GL_CALL*)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
export extern PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = nullptr;

export using PFNGLMULTITEXCOORD4SVPROC = void (GL_CALL*)(GLenum target, const GLshort* v);
export extern PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = nullptr;

export using PFNGLLOADTRANSPOSEMATRIXFPROC = void (GL_CALL*)(const GLfloat* m);
export extern PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = nullptr;

export using PFNGLLOADTRANSPOSEMATRIXDPROC = void (GL_CALL*)(const GLdouble* m);
export extern PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = nullptr;

export using PFNGLMULTTRANSPOSEMATRIXFPROC = void (GL_CALL*)(const GLfloat* m);
export extern PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = nullptr;

export using PFNGLMULTTRANSPOSEMATRIXDPROC = void (GL_CALL*)(const GLdouble* m);
export extern PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = nullptr;

// ==================== OpenGL 1.4 Functions ====================

export using PFNGLBLENDFUNCSEPARATEPROC = void (GL_CALL*)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
export extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = nullptr;

export using PFNGLMULTIDRAWARRAYSPROC = void (GL_CALL*)(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount);
export extern PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = nullptr;

export using PFNGLMULTIDRAWELEMENTSPROC = void (GL_CALL*)(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount);
export extern PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = nullptr;

export using PFNGLPOINTPARAMETERFPROC = void (GL_CALL*)(GLenum pname, GLfloat param);
export extern PFNGLPOINTPARAMETERFPROC glPointParameterf;
PFNGLPOINTPARAMETERFPROC glPointParameterf = nullptr;

export using PFNGLPOINTPARAMETERFVPROC = void (GL_CALL*)(GLenum pname, const GLfloat* params);
export extern PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = nullptr;

export using PFNGLPOINTPARAMETERIPROC = void (GL_CALL*)(GLenum pname, GLint param);
export extern PFNGLPOINTPARAMETERIPROC glPointParameteri;
PFNGLPOINTPARAMETERIPROC glPointParameteri = nullptr;

export using PFNGLPOINTPARAMETERIVPROC = void (GL_CALL*)(GLenum pname, const GLint* params);
export extern PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = nullptr;

export using PFNGLFOGCOORDFPROC = void (GL_CALL*)(GLfloat coord);
export extern PFNGLFOGCOORDFPROC glFogCoordf;
PFNGLFOGCOORDFPROC glFogCoordf = nullptr;

export using PFNGLFOGCOORDFVPROC = void (GL_CALL*)(const GLfloat* coord);
export extern PFNGLFOGCOORDFVPROC glFogCoordfv;
PFNGLFOGCOORDFVPROC glFogCoordfv = nullptr;

export using PFNGLFOGCOORDDPROC = void (GL_CALL*)(GLdouble coord);
export extern PFNGLFOGCOORDDPROC glFogCoordd;
PFNGLFOGCOORDDPROC glFogCoordd = nullptr;

export using PFNGLFOGCOORDDVPROC = void (GL_CALL*)(const GLdouble* coord);
export extern PFNGLFOGCOORDDVPROC glFogCoorddv;
PFNGLFOGCOORDDVPROC glFogCoorddv = nullptr;

export using PFNGLFOGCOORDPOINTERPROC = void (GL_CALL*)(GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLFOGCOORDPOINTERPROC glFogCoordPointer;
PFNGLFOGCOORDPOINTERPROC glFogCoordPointer = nullptr;

export using PFNGLSECONDARYCOLOR3BPROC = void (GL_CALL*)(GLbyte red, GLbyte green, GLbyte blue);
export extern PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b;
PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b = nullptr;

export using PFNGLSECONDARYCOLOR3BVPROC = void (GL_CALL*)(const GLbyte* v);
export extern PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv;
PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv = nullptr;

export using PFNGLSECONDARYCOLOR3DPROC = void (GL_CALL*)(GLdouble red, GLdouble green, GLdouble blue);
export extern PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d;
PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d = nullptr;

export using PFNGLSECONDARYCOLOR3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv;
PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv = nullptr;

export using PFNGLSECONDARYCOLOR3FPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue);
export extern PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f;
PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f = nullptr;

export using PFNGLSECONDARYCOLOR3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv;
PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv = nullptr;

export using PFNGLSECONDARYCOLOR3IPROC = void (GL_CALL*)(GLint red, GLint green, GLint blue);
export extern PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i;
PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i = nullptr;

export using PFNGLSECONDARYCOLOR3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv;
PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv = nullptr;

export using PFNGLSECONDARYCOLOR3SPROC = void (GL_CALL*)(GLshort red, GLshort green, GLshort blue);
export extern PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s;
PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s = nullptr;

export using PFNGLSECONDARYCOLOR3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv;
PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv = nullptr;

export using PFNGLSECONDARYCOLOR3UBPROC = void (GL_CALL*)(GLubyte red, GLubyte green, GLubyte blue);
export extern PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub;
PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub = nullptr;

export using PFNGLSECONDARYCOLOR3UBVPROC = void (GL_CALL*)(const GLubyte* v);
export extern PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv;
PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv = nullptr;

export using PFNGLSECONDARYCOLOR3UIPROC = void (GL_CALL*)(GLuint red, GLuint green, GLuint blue);
export extern PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui;
PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui = nullptr;

export using PFNGLSECONDARYCOLOR3UIVPROC = void (GL_CALL*)(const GLuint* v);
export extern PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv;
PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv = nullptr;

export using PFNGLSECONDARYCOLOR3USPROC = void (GL_CALL*)(GLushort red, GLushort green, GLushort blue);
export extern PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us;
PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us = nullptr;

export using PFNGLSECONDARYCOLOR3USVPROC = void (GL_CALL*)(const GLushort* v);
export extern PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv;
PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv = nullptr;

export using PFNGLSECONDARYCOLORPOINTERPROC = void (GL_CALL*)(GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer;
PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer = nullptr;

export using PFNGLWINDOWPOS2DPROC = void (GL_CALL*)(GLdouble x, GLdouble y);
export extern PFNGLWINDOWPOS2DPROC glWindowPos2d;
PFNGLWINDOWPOS2DPROC glWindowPos2d = nullptr;

export using PFNGLWINDOWPOS2DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLWINDOWPOS2DVPROC glWindowPos2dv;
PFNGLWINDOWPOS2DVPROC glWindowPos2dv = nullptr;

export using PFNGLWINDOWPOS2FPROC = void (GL_CALL*)(GLfloat x, GLfloat y);
export extern PFNGLWINDOWPOS2FPROC glWindowPos2f;
PFNGLWINDOWPOS2FPROC glWindowPos2f = nullptr;

export using PFNGLWINDOWPOS2FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLWINDOWPOS2FVPROC glWindowPos2fv;
PFNGLWINDOWPOS2FVPROC glWindowPos2fv = nullptr;

export using PFNGLWINDOWPOS2IPROC = void (GL_CALL*)(GLint x, GLint y);
export extern PFNGLWINDOWPOS2IPROC glWindowPos2i;
PFNGLWINDOWPOS2IPROC glWindowPos2i = nullptr;

export using PFNGLWINDOWPOS2IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLWINDOWPOS2IVPROC glWindowPos2iv;
PFNGLWINDOWPOS2IVPROC glWindowPos2iv = nullptr;

export using PFNGLWINDOWPOS2SPROC = void (GL_CALL*)(GLshort x, GLshort y);
export extern PFNGLWINDOWPOS2SPROC glWindowPos2s;
PFNGLWINDOWPOS2SPROC glWindowPos2s = nullptr;

export using PFNGLWINDOWPOS2SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLWINDOWPOS2SVPROC glWindowPos2sv;
PFNGLWINDOWPOS2SVPROC glWindowPos2sv = nullptr;

export using PFNGLWINDOWPOS3DPROC = void (GL_CALL*)(GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLWINDOWPOS3DPROC glWindowPos3d;
PFNGLWINDOWPOS3DPROC glWindowPos3d = nullptr;

export using PFNGLWINDOWPOS3DVPROC = void (GL_CALL*)(const GLdouble* v);
export extern PFNGLWINDOWPOS3DVPROC glWindowPos3dv;
PFNGLWINDOWPOS3DVPROC glWindowPos3dv = nullptr;

export using PFNGLWINDOWPOS3FPROC = void (GL_CALL*)(GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLWINDOWPOS3FPROC glWindowPos3f;
PFNGLWINDOWPOS3FPROC glWindowPos3f = nullptr;

export using PFNGLWINDOWPOS3FVPROC = void (GL_CALL*)(const GLfloat* v);
export extern PFNGLWINDOWPOS3FVPROC glWindowPos3fv;
PFNGLWINDOWPOS3FVPROC glWindowPos3fv = nullptr;

export using PFNGLWINDOWPOS3IPROC = void (GL_CALL*)(GLint x, GLint y, GLint z);
export extern PFNGLWINDOWPOS3IPROC glWindowPos3i;
PFNGLWINDOWPOS3IPROC glWindowPos3i = nullptr;

export using PFNGLWINDOWPOS3IVPROC = void (GL_CALL*)(const GLint* v);
export extern PFNGLWINDOWPOS3IVPROC glWindowPos3iv;
PFNGLWINDOWPOS3IVPROC glWindowPos3iv = nullptr;

export using PFNGLWINDOWPOS3SPROC = void (GL_CALL*)(GLshort x, GLshort y, GLshort z);
export extern PFNGLWINDOWPOS3SPROC glWindowPos3s;
PFNGLWINDOWPOS3SPROC glWindowPos3s = nullptr;

export using PFNGLWINDOWPOS3SVPROC = void (GL_CALL*)(const GLshort* v);
export extern PFNGLWINDOWPOS3SVPROC glWindowPos3sv;
PFNGLWINDOWPOS3SVPROC glWindowPos3sv = nullptr;

export using PFNGLBLENDCOLORPROC = void (GL_CALL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
export extern PFNGLBLENDCOLORPROC glBlendColor;
PFNGLBLENDCOLORPROC glBlendColor = nullptr;

export using PFNGLBLENDEQUATIONPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLBLENDEQUATIONPROC glBlendEquation;
PFNGLBLENDEQUATIONPROC glBlendEquation = nullptr;

// ==================== OpenGL 1.5 Functions ====================

export using PFNGLGENQUERIESPROC = void (GL_CALL*)(GLsizei n, GLuint* ids);
export extern PFNGLGENQUERIESPROC glGenQueries;
PFNGLGENQUERIESPROC glGenQueries = nullptr;

export using PFNGLDELETEQUERIESPROC = void (GL_CALL*)(GLsizei n, const GLuint* ids);
export extern PFNGLDELETEQUERIESPROC glDeleteQueries;
PFNGLDELETEQUERIESPROC glDeleteQueries = nullptr;

export using PFNGLISQUERYPROC = GLboolean(GL_CALL*)(GLuint id);
export extern PFNGLISQUERYPROC glIsQuery;
PFNGLISQUERYPROC glIsQuery = nullptr;

export using PFNGLBEGINQUERYPROC = void (GL_CALL*)(GLenum target, GLuint id);
export extern PFNGLBEGINQUERYPROC glBeginQuery;
PFNGLBEGINQUERYPROC glBeginQuery = nullptr;

export using PFNGLENDQUERYPROC = void (GL_CALL*)(GLenum target);
export extern PFNGLENDQUERYPROC glEndQuery;
PFNGLENDQUERYPROC glEndQuery = nullptr;

export using PFNGLGETQUERYIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETQUERYIVPROC glGetQueryiv;
PFNGLGETQUERYIVPROC glGetQueryiv = nullptr;

export using PFNGLGETQUERYOBJECTIVPROC = void (GL_CALL*)(GLuint id, GLenum pname, GLint* params);
export extern PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = nullptr;

export using PFNGLGETQUERYOBJECTUIVPROC = void (GL_CALL*)(GLuint id, GLenum pname, GLuint* params);
export extern PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = nullptr;

export using PFNGLBINDBUFFERPROC = void (GL_CALL*)(GLenum target, GLuint buffer);
export extern PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;

export using PFNGLDELETEBUFFERSPROC = void (GL_CALL*)(GLsizei n, const GLuint* buffers);
export extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;

export using PFNGLGENBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* buffers);
export extern PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;

export using PFNGLISBUFFERPROC = GLboolean(GL_CALL*)(GLuint buffer);
export extern PFNGLISBUFFERPROC glIsBuffer;
PFNGLISBUFFERPROC glIsBuffer = nullptr;

export using PFNGLBUFFERDATAPROC = void (GL_CALL*)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
export extern PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERDATAPROC glBufferData = nullptr;

export using PFNGLBUFFERSUBDATAPROC = void (GL_CALL*)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
export extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;

export using PFNGLGETBUFFERSUBDATAPROC = void (GL_CALL*)(GLenum target, GLintptr offset, GLsizeiptr size, void* data);
export extern PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = nullptr;

export using PFNGLMAPBUFFERPROC = void* (GL_CALL*)(GLenum target, GLenum access);
export extern PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLMAPBUFFERPROC glMapBuffer = nullptr;

export using PFNGLUNMAPBUFFERPROC = GLboolean(GL_CALL*)(GLenum target);
export extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = nullptr;

export using PFNGLGETBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = nullptr;

export using PFNGLGETBUFFERPOINTERVPROC = void (GL_CALL*)(GLenum target, GLenum pname, void** params);
export extern PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = nullptr;

// ==================== OpenGL 2.0 Functions ====================

export using PFNGLBLENDEQUATIONSEPARATEPROC = void (GL_CALL*)(GLenum modeRGB, GLenum modeAlpha);
export extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = nullptr;

export using PFNGLDRAWBUFFERSPROC = void (GL_CALL*)(GLsizei n, const GLenum* bufs);
export extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
PFNGLDRAWBUFFERSPROC glDrawBuffers = nullptr;

export using PFNGLSTENCILOPSEPARATEPROC = void (GL_CALL*)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
export extern PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = nullptr;

export using PFNGLSTENCILFUNCSEPARATEPROC = void (GL_CALL*)(GLenum face, GLenum func, GLint ref, GLuint mask);
export extern PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = nullptr;

export using PFNGLSTENCILMASKSEPARATEPROC = void (GL_CALL*)(GLenum face, GLuint mask);
export extern PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = nullptr;

export using PFNGLATTACHSHADERPROC = void (GL_CALL*)(GLuint program, GLuint shader);
export extern PFNGLATTACHSHADERPROC glAttachShader;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;

export using PFNGLBINDATTRIBLOCATIONPROC = void (GL_CALL*)(GLuint program, GLuint index, const GLchar* name);
export extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;

export using PFNGLCOMPILESHADERPROC = void (GL_CALL*)(GLuint shader);
export extern PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;

export using PFNGLCREATEPROGRAMPROC = GLuint(GL_CALL*)();
export extern PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;

export using PFNGLCREATESHADERPROC = GLuint(GL_CALL*)(GLenum type);
export extern PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATESHADERPROC glCreateShader = nullptr;

export using PFNGLDELETEPROGRAMPROC = void (GL_CALL*)(GLuint program);
export extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;

export using PFNGLDELETESHADERPROC = void (GL_CALL*)(GLuint shader);
export extern PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

export using PFNGLDETACHSHADERPROC = void (GL_CALL*)(GLuint program, GLuint shader);
export extern PFNGLDETACHSHADERPROC glDetachShader;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;

export using PFNGLDISABLEVERTEXATTRIBARRAYPROC = void (GL_CALL*)(GLuint index);
export extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

export using PFNGLENABLEVERTEXATTRIBARRAYPROC = void (GL_CALL*)(GLuint index);
export extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;

export using PFNGLGETACTIVEATTRIBPROC = void (GL_CALL*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
export extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = nullptr;

export using PFNGLGETACTIVEUNIFORMPROC = void (GL_CALL*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
export extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;

export using PFNGLGETATTACHEDSHADERSPROC = void (GL_CALL*)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
export extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = nullptr;

export using PFNGLGETATTRIBLOCATIONPROC = GLint(GL_CALL*)(GLuint program, const GLchar* name);
export extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;

export using PFNGLGETPROGRAMIVPROC = void (GL_CALL*)(GLuint program, GLenum pname, GLint* params);
export extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;

export using PFNGLGETPROGRAMINFOLOGPROC = void (GL_CALL*)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
export extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;

export using PFNGLGETSHADERIVPROC = void (GL_CALL*)(GLuint shader, GLenum pname, GLint* params);
export extern PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;

export using PFNGLGETSHADERINFOLOGPROC = void (GL_CALL*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
export extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

export using PFNGLGETSHADERSOURCEPROC = void (GL_CALL*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
export extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = nullptr;

export using PFNGLGETUNIFORMLOCATIONPROC = GLint(GL_CALL*)(GLuint program, const GLchar* name);
export extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;

export using PFNGLGETUNIFORMFVPROC = void (GL_CALL*)(GLuint program, GLint location, GLfloat* params);
export extern PFNGLGETUNIFORMFVPROC glGetUniformfv;
PFNGLGETUNIFORMFVPROC glGetUniformfv = nullptr;

export using PFNGLGETUNIFORMIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLint* params);
export extern PFNGLGETUNIFORMIVPROC glGetUniformiv;
PFNGLGETUNIFORMIVPROC glGetUniformiv = nullptr;

export using PFNGLGETVERTEXATTRIBDVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLdouble* params);
export extern PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = nullptr;

export using PFNGLGETVERTEXATTRIBFVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLfloat* params);
export extern PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = nullptr;

export using PFNGLGETVERTEXATTRIBIVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLint* params);
export extern PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = nullptr;

export using PFNGLGETVERTEXATTRIBPOINTERVPROC = void (GL_CALL*)(GLuint index, GLenum pname, void** pointer);
export extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = nullptr;

export using PFNGLISPROGRAMPROC = GLboolean(GL_CALL*)(GLuint program);
export extern PFNGLISPROGRAMPROC glIsProgram;
PFNGLISPROGRAMPROC glIsProgram = nullptr;

export using PFNGLISSHADERPROC = GLboolean(GL_CALL*)(GLuint shader);
export extern PFNGLISSHADERPROC glIsShader;
PFNGLISSHADERPROC glIsShader = nullptr;

export using PFNGLLINKPROGRAMPROC = void (GL_CALL*)(GLuint program);
export extern PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;

export using PFNGLSHADERSOURCEPROC = void (GL_CALL*)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
export extern PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;

export using PFNGLUSEPROGRAMPROC = void (GL_CALL*)(GLuint program);
export extern PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;

export using PFNGLUNIFORM1FPROC = void (GL_CALL*)(GLint location, GLfloat v0);
export extern PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;

export using PFNGLUNIFORM2FPROC = void (GL_CALL*)(GLint location, GLfloat v0, GLfloat v1);
export extern PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM2FPROC glUniform2f = nullptr;

export using PFNGLUNIFORM3FPROC = void (GL_CALL*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
export extern PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;

export using PFNGLUNIFORM4FPROC = void (GL_CALL*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
export extern PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORM4FPROC glUniform4f = nullptr;

export using PFNGLUNIFORM1IPROC = void (GL_CALL*)(GLint location, GLint v0);
export extern PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;

export using PFNGLUNIFORM2IPROC = void (GL_CALL*)(GLint location, GLint v0, GLint v1);
export extern PFNGLUNIFORM2IPROC glUniform2i;
PFNGLUNIFORM2IPROC glUniform2i = nullptr;

export using PFNGLUNIFORM3IPROC = void (GL_CALL*)(GLint location, GLint v0, GLint v1, GLint v2);
export extern PFNGLUNIFORM3IPROC glUniform3i;
PFNGLUNIFORM3IPROC glUniform3i = nullptr;

export using PFNGLUNIFORM4IPROC = void (GL_CALL*)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
export extern PFNGLUNIFORM4IPROC glUniform4i;
PFNGLUNIFORM4IPROC glUniform4i = nullptr;

export using PFNGLUNIFORM1FVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;

export using PFNGLUNIFORM2FVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;

export using PFNGLUNIFORM3FVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;

export using PFNGLUNIFORM4FVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;

export using PFNGLUNIFORM1IVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLint* value);
export extern PFNGLUNIFORM1IVPROC glUniform1iv;
PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;

export using PFNGLUNIFORM2IVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLint* value);
export extern PFNGLUNIFORM2IVPROC glUniform2iv;
PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;

export using PFNGLUNIFORM3IVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLint* value);
export extern PFNGLUNIFORM3IVPROC glUniform3iv;
PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;

export using PFNGLUNIFORM4IVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLint* value);
export extern PFNGLUNIFORM4IVPROC glUniform4iv;
PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;

export using PFNGLUNIFORMMATRIX2FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;

export using PFNGLUNIFORMMATRIX3FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;

export using PFNGLUNIFORMMATRIX4FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;

export using PFNGLVALIDATEPROGRAMPROC = void (GL_CALL*)(GLuint program);
export extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;

export using PFNGLVERTEXATTRIB1DPROC = void (GL_CALL*)(GLuint index, GLdouble x);
export extern PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = nullptr;

export using PFNGLVERTEXATTRIB1DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = nullptr;

export using PFNGLVERTEXATTRIB1FPROC = void (GL_CALL*)(GLuint index, GLfloat x);
export extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = nullptr;

export using PFNGLVERTEXATTRIB1FVPROC = void (GL_CALL*)(GLuint index, const GLfloat* v);
export extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = nullptr;

export using PFNGLVERTEXATTRIB1SPROC = void (GL_CALL*)(GLuint index, GLshort x);
export extern PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = nullptr;

export using PFNGLVERTEXATTRIB1SVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = nullptr;

export using PFNGLVERTEXATTRIB2DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y);
export extern PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = nullptr;

export using PFNGLVERTEXATTRIB2DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = nullptr;

export using PFNGLVERTEXATTRIB2FPROC = void (GL_CALL*)(GLuint index, GLfloat x, GLfloat y);
export extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = nullptr;

export using PFNGLVERTEXATTRIB2FVPROC = void (GL_CALL*)(GLuint index, const GLfloat* v);
export extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = nullptr;

export using PFNGLVERTEXATTRIB2SPROC = void (GL_CALL*)(GLuint index, GLshort x, GLshort y);
export extern PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = nullptr;

export using PFNGLVERTEXATTRIB2SVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = nullptr;

export using PFNGLVERTEXATTRIB3DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = nullptr;

export using PFNGLVERTEXATTRIB3DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = nullptr;

export using PFNGLVERTEXATTRIB3FPROC = void (GL_CALL*)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
export extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = nullptr;

export using PFNGLVERTEXATTRIB3FVPROC = void (GL_CALL*)(GLuint index, const GLfloat* v);
export extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = nullptr;

export using PFNGLVERTEXATTRIB3SPROC = void (GL_CALL*)(GLuint index, GLshort x, GLshort y, GLshort z);
export extern PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = nullptr;

export using PFNGLVERTEXATTRIB3SVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = nullptr;

export using PFNGLVERTEXATTRIB4NBVPROC = void (GL_CALL*)(GLuint index, const GLbyte* v);
export extern PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = nullptr;

export using PFNGLVERTEXATTRIB4NIVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = nullptr;

export using PFNGLVERTEXATTRIB4NSVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = nullptr;

export using PFNGLVERTEXATTRIB4NUBPROC = void (GL_CALL*)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
export extern PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = nullptr;

export using PFNGLVERTEXATTRIB4NUBVPROC = void (GL_CALL*)(GLuint index, const GLubyte* v);
export extern PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = nullptr;

export using PFNGLVERTEXATTRIB4NUIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = nullptr;

export using PFNGLVERTEXATTRIB4NUSVPROC = void (GL_CALL*)(GLuint index, const GLushort* v);
export extern PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = nullptr;

export using PFNGLVERTEXATTRIB4BVPROC = void (GL_CALL*)(GLuint index, const GLbyte* v);
export extern PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = nullptr;

export using PFNGLVERTEXATTRIB4DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
export extern PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = nullptr;

export using PFNGLVERTEXATTRIB4DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = nullptr;

export using PFNGLVERTEXATTRIB4FPROC = void (GL_CALL*)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
export extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = nullptr;

export using PFNGLVERTEXATTRIB4FVPROC = void (GL_CALL*)(GLuint index, const GLfloat* v);
export extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = nullptr;

export using PFNGLVERTEXATTRIB4IVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = nullptr;

export using PFNGLVERTEXATTRIB4SPROC = void (GL_CALL*)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
export extern PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = nullptr;

export using PFNGLVERTEXATTRIB4SVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = nullptr;

export using PFNGLVERTEXATTRIB4UBVPROC = void (GL_CALL*)(GLuint index, const GLubyte* v);
export extern PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = nullptr;

export using PFNGLVERTEXATTRIB4UIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = nullptr;

export using PFNGLVERTEXATTRIB4USVPROC = void (GL_CALL*)(GLuint index, const GLushort* v);
export extern PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = nullptr;

export using PFNGLVERTEXATTRIBPOINTERPROC = void (GL_CALL*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
export extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

// ==================== OpenGL 2.1 Functions ====================

export using PFNGLUNIFORMMATRIX2X3FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = nullptr;

export using PFNGLUNIFORMMATRIX3X2FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = nullptr;

export using PFNGLUNIFORMMATRIX2X4FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = nullptr;

export using PFNGLUNIFORMMATRIX4X2FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = nullptr;

export using PFNGLUNIFORMMATRIX3X4FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = nullptr;

export using PFNGLUNIFORMMATRIX4X3FVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = nullptr;

// ==================== OpenGL 3.0 Functions ====================

export using PFNGLCOLORMASKIPROC = void (GL_CALL*)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
export extern PFNGLCOLORMASKIPROC glColorMaski;
PFNGLCOLORMASKIPROC glColorMaski = nullptr;

export using PFNGLGETBOOLEANI_VPROC = void (GL_CALL*)(GLenum target, GLuint index, GLboolean* data);
export extern PFNGLGETBOOLEANI_VPROC glGetBooleani_v;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = nullptr;

export using PFNGLGETINTEGERI_VPROC = void (GL_CALL*)(GLenum target, GLuint index, GLint* data);
export extern PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = nullptr;

export using PFNGLENABLEIPROC = void (GL_CALL*)(GLenum target, GLuint index);
export extern PFNGLENABLEIPROC glEnablei;
PFNGLENABLEIPROC glEnablei = nullptr;

export using PFNGLDISABLEIPROC = void (GL_CALL*)(GLenum target, GLuint index);
export extern PFNGLDISABLEIPROC glDisablei;
PFNGLDISABLEIPROC glDisablei = nullptr;

export using PFNGLISENABLEDIPROC = GLboolean(GL_CALL*)(GLenum target, GLuint index);
export extern PFNGLISENABLEDIPROC glIsEnabledi;
PFNGLISENABLEDIPROC glIsEnabledi = nullptr;

export using PFNGLBEGINTRANSFORMFEEDBACKPROC = void (GL_CALL*)(GLenum primitiveMode);
export extern PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = nullptr;

export using PFNGLENDTRANSFORMFEEDBACKPROC = void (GL_CALL*)();
export extern PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = nullptr;

export using PFNGLBINDBUFFERRANGEPROC = void (GL_CALL*)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
export extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = nullptr;

export using PFNGLBINDBUFFERBASEPROC = void (GL_CALL*)(GLenum target, GLuint index, GLuint buffer);
export extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;

export using PFNGLTRANSFORMFEEDBACKVARYINGSPROC = void (GL_CALL*)(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
export extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = nullptr;

export using PFNGLGETTRANSFORMFEEDBACKVARYINGPROC = void (GL_CALL*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
export extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = nullptr;

export using PFNGLCLAMPCOLORPROC = void (GL_CALL*)(GLenum target, GLenum clamp);
export extern PFNGLCLAMPCOLORPROC glClampColor;
PFNGLCLAMPCOLORPROC glClampColor = nullptr;

export using PFNGLBEGINCONDITIONALRENDERPROC = void (GL_CALL*)(GLuint id, GLenum mode);
export extern PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = nullptr;

export using PFNGLENDCONDITIONALRENDERPROC = void (GL_CALL*)();
export extern PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = nullptr;

export using PFNGLVERTEXATTRIBIPOINTERPROC = void (GL_CALL*)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = nullptr;

export using PFNGLGETVERTEXATTRIBIIVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLint* params);
export extern PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = nullptr;

export using PFNGLGETVERTEXATTRIBIUIVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLuint* params);
export extern PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = nullptr;

export using PFNGLVERTEXATTRIBI1IPROC = void (GL_CALL*)(GLuint index, GLint x);
export extern PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = nullptr;

export using PFNGLVERTEXATTRIBI2IPROC = void (GL_CALL*)(GLuint index, GLint x, GLint y);
export extern PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = nullptr;

export using PFNGLVERTEXATTRIBI3IPROC = void (GL_CALL*)(GLuint index, GLint x, GLint y, GLint z);
export extern PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = nullptr;

export using PFNGLVERTEXATTRIBI4IPROC = void (GL_CALL*)(GLuint index, GLint x, GLint y, GLint z, GLint w);
export extern PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = nullptr;

export using PFNGLVERTEXATTRIBI1UIPROC = void (GL_CALL*)(GLuint index, GLuint x);
export extern PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = nullptr;

export using PFNGLVERTEXATTRIBI2UIPROC = void (GL_CALL*)(GLuint index, GLuint x, GLuint y);
export extern PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = nullptr;

export using PFNGLVERTEXATTRIBI3UIPROC = void (GL_CALL*)(GLuint index, GLuint x, GLuint y, GLuint z);
export extern PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = nullptr;

export using PFNGLVERTEXATTRIBI4UIPROC = void (GL_CALL*)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
export extern PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = nullptr;

export using PFNGLVERTEXATTRIBI1IVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = nullptr;

export using PFNGLVERTEXATTRIBI2IVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = nullptr;

export using PFNGLVERTEXATTRIBI3IVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = nullptr;

export using PFNGLVERTEXATTRIBI4IVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = nullptr;

export using PFNGLVERTEXATTRIBI1UIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = nullptr;

export using PFNGLVERTEXATTRIBI2UIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = nullptr;

export using PFNGLVERTEXATTRIBI3UIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = nullptr;

export using PFNGLVERTEXATTRIBI4UIVPROC = void (GL_CALL*)(GLuint index, const GLuint* v);
export extern PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = nullptr;

export using PFNGLVERTEXATTRIBI4BVPROC = void (GL_CALL*)(GLuint index, const GLbyte* v);
export extern PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = nullptr;

export using PFNGLVERTEXATTRIBI4SVPROC = void (GL_CALL*)(GLuint index, const GLshort* v);
export extern PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = nullptr;

export using PFNGLVERTEXATTRIBI4UBVPROC = void (GL_CALL*)(GLuint index, const GLubyte* v);
export extern PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = nullptr;

export using PFNGLVERTEXATTRIBI4USVPROC = void (GL_CALL*)(GLuint index, const GLushort* v);
export extern PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = nullptr;

export using PFNGLGETUNIFORMUIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLuint* params);
export extern PFNGLGETUNIFORMUIVPROC glGetUniformuiv;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = nullptr;

export using PFNGLBINDFRAGDATALOCATIONPROC = void (GL_CALL*)(GLuint program, GLuint color, const GLchar* name);
export extern PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = nullptr;

export using PFNGLGETFRAGDATALOCATIONPROC = GLint(GL_CALL*)(GLuint program, const GLchar* name);
export extern PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = nullptr;

export using PFNGLUNIFORM1UIPROC = void (GL_CALL*)(GLint location, GLuint v0);
export extern PFNGLUNIFORM1UIPROC glUniform1ui;
PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;

export using PFNGLUNIFORM2UIPROC = void (GL_CALL*)(GLint location, GLuint v0, GLuint v1);
export extern PFNGLUNIFORM2UIPROC glUniform2ui;
PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;

export using PFNGLUNIFORM3UIPROC = void (GL_CALL*)(GLint location, GLuint v0, GLuint v1, GLuint v2);
export extern PFNGLUNIFORM3UIPROC glUniform3ui;
PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;

export using PFNGLUNIFORM4UIPROC = void (GL_CALL*)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
export extern PFNGLUNIFORM4UIPROC glUniform4ui;
PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;

export using PFNGLUNIFORM1UIVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLuint* value);
export extern PFNGLUNIFORM1UIVPROC glUniform1uiv;
PFNGLUNIFORM1UIVPROC glUniform1uiv = nullptr;

export using PFNGLUNIFORM2UIVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLuint* value);
export extern PFNGLUNIFORM2UIVPROC glUniform2uiv;
PFNGLUNIFORM2UIVPROC glUniform2uiv = nullptr;

export using PFNGLUNIFORM3UIVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLuint* value);
export extern PFNGLUNIFORM3UIVPROC glUniform3uiv;
PFNGLUNIFORM3UIVPROC glUniform3uiv = nullptr;

export using PFNGLUNIFORM4UIVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLuint* value);
export extern PFNGLUNIFORM4UIVPROC glUniform4uiv;
PFNGLUNIFORM4UIVPROC glUniform4uiv = nullptr;

export using PFNGLTEXPARAMETERIIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLint* params);
export extern PFNGLTEXPARAMETERIIVPROC glTexParameterIiv;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = nullptr;

export using PFNGLTEXPARAMETERIUIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, const GLuint* params);
export extern PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = nullptr;

export using PFNGLGETTEXPARAMETERIIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = nullptr;

export using PFNGLGETTEXPARAMETERIUIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLuint* params);
export extern PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = nullptr;

export using PFNGLCLEARBUFFERIVPROC = void (GL_CALL*)(GLenum buffer, GLint drawbuffer, const GLint* value);
export extern PFNGLCLEARBUFFERIVPROC glClearBufferiv;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = nullptr;

export using PFNGLCLEARBUFFERUIVPROC = void (GL_CALL*)(GLenum buffer, GLint drawbuffer, const GLuint* value);
export extern PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = nullptr;

export using PFNGLCLEARBUFFERFVPROC = void (GL_CALL*)(GLenum buffer, GLint drawbuffer, const GLfloat* value);
export extern PFNGLCLEARBUFFERFVPROC glClearBufferfv;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = nullptr;

export using PFNGLCLEARBUFFERFIPROC = void (GL_CALL*)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
export extern PFNGLCLEARBUFFERFIPROC glClearBufferfi;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = nullptr;

export using PFNGLGETSTRINGIPROC = const GLubyte* (GL_CALL*)(GLenum name, GLuint index);
export extern PFNGLGETSTRINGIPROC glGetStringi;
PFNGLGETSTRINGIPROC glGetStringi = nullptr;

export using PFNGLISRENDERBUFFERPROC = GLboolean(GL_CALL*)(GLuint renderbuffer);
export extern PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = nullptr;

export using PFNGLBINDRENDERBUFFERPROC = void (GL_CALL*)(GLenum target, GLuint renderbuffer);
export extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = nullptr;

export using PFNGLDELETERENDERBUFFERSPROC = void (GL_CALL*)(GLsizei n, const GLuint* renderbuffers);
export extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = nullptr;

export using PFNGLGENRENDERBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* renderbuffers);
export extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = nullptr;

export using PFNGLRENDERBUFFERSTORAGEPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = nullptr;

export using PFNGLGETRENDERBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = nullptr;

export using PFNGLISFRAMEBUFFERPROC = GLboolean(GL_CALL*)(GLuint framebuffer);
export extern PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = nullptr;

export using PFNGLBINDFRAMEBUFFERPROC = void (GL_CALL*)(GLenum target, GLuint framebuffer);
export extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;

export using PFNGLDELETEFRAMEBUFFERSPROC = void (GL_CALL*)(GLsizei n, const GLuint* framebuffers);
export extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = nullptr;

export using PFNGLGENFRAMEBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* framebuffers);
export extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;

export using PFNGLCHECKFRAMEBUFFERSTATUSPROC = GLenum(GL_CALL*)(GLenum target);
export extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;

export using PFNGLFRAMEBUFFERTEXTURE1DPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
export extern PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = nullptr;

export using PFNGLFRAMEBUFFERTEXTURE2DPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
export extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;

export using PFNGLFRAMEBUFFERTEXTURE3DPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
export extern PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = nullptr;

export using PFNGLFRAMEBUFFERRENDERBUFFERPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
export extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = nullptr;

export using PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
export extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = nullptr;

export using PFNGLGENERATEMIPMAPPROC = void (GL_CALL*)(GLenum target);
export extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;

export using PFNGLBLITFRAMEBUFFERPROC = void (GL_CALL*)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
export extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = nullptr;

export using PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC = void (GL_CALL*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = nullptr;

export using PFNGLFRAMEBUFFERTEXTURELAYERPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
export extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = nullptr;

export using PFNGLMAPBUFFERRANGEPROC = void* (GL_CALL*)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
export extern PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = nullptr;

export using PFNGLFLUSHMAPPEDBUFFERRANGEPROC = void (GL_CALL*)(GLenum target, GLintptr offset, GLsizeiptr length);
export extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = nullptr;

export using PFNGLBINDVERTEXARRAYPROC = void (GL_CALL*)(GLuint array);
export extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;

export using PFNGLDELETEVERTEXARRAYSPROC = void (GL_CALL*)(GLsizei n, const GLuint* arrays);
export extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;

export using PFNGLGENVERTEXARRAYSPROC = void (GL_CALL*)(GLsizei n, GLuint* arrays);
export extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;

export using PFNGLISVERTEXARRAYPROC = GLboolean(GL_CALL*)(GLuint array);
export extern PFNGLISVERTEXARRAYPROC glIsVertexArray;
PFNGLISVERTEXARRAYPROC glIsVertexArray = nullptr;

// ==================== OpenGL 3.1 Functions ====================

export using PFNGLDRAWARRAYSINSTANCEDPROC = void (GL_CALL*)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
export extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;

export using PFNGLDRAWELEMENTSINSTANCEDPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);
export extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = nullptr;

export using PFNGLTEXBUFFERPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLuint buffer);
export extern PFNGLTEXBUFFERPROC glTexBuffer;
PFNGLTEXBUFFERPROC glTexBuffer = nullptr;

export using PFNGLPRIMITIVERESTARTINDEXPROC = void (GL_CALL*)(GLuint index);
export extern PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = nullptr;

export using PFNGLCOPYBUFFERSUBDATAPROC = void (GL_CALL*)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
export extern PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;
PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = nullptr;

export using PFNGLGETUNIFORMINDICESPROC = void (GL_CALL*)(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices);
export extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = nullptr;

export using PFNGLGETACTIVEUNIFORMSIVPROC = void (GL_CALL*)(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
export extern PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = nullptr;

export using PFNGLGETACTIVEUNIFORMNAMEPROC = void (GL_CALL*)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName);
export extern PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = nullptr;

export using PFNGLGETUNIFORMBLOCKINDEXPROC = GLuint(GL_CALL*)(GLuint program, const GLchar* uniformBlockName);
export extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = nullptr;

export using PFNGLGETACTIVEUNIFORMBLOCKIVPROC = void (GL_CALL*)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
export extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = nullptr;

export using PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC = void (GL_CALL*)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
export extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = nullptr;

export using PFNGLUNIFORMBLOCKBINDINGPROC = void (GL_CALL*)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
export extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = nullptr;

// ==================== OpenGL 3.2 Functions ====================

export using PFNGLDRAWELEMENTSBASEVERTEXPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex);
export extern PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = nullptr;

export using PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC = void (GL_CALL*)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex);
export extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex = nullptr;

export using PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex);
export extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex = nullptr;

export using PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC = void (GL_CALL*)(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex);
export extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex = nullptr;

export using PFNGLPROVOKINGVERTEXPROC = void (GL_CALL*)(GLenum mode);
export extern PFNGLPROVOKINGVERTEXPROC glProvokingVertex;
PFNGLPROVOKINGVERTEXPROC glProvokingVertex = nullptr;

export using PFNGLFENCESYNCPROC = GLsync(GL_CALL*)(GLenum condition, GLbitfield flags);
export extern PFNGLFENCESYNCPROC glFenceSync;
PFNGLFENCESYNCPROC glFenceSync = nullptr;

export using PFNGLISSYNCPROC = GLboolean(GL_CALL*)(GLsync sync);
export extern PFNGLISSYNCPROC glIsSync;
PFNGLISSYNCPROC glIsSync = nullptr;

export using PFNGLDELETESYNCPROC = void (GL_CALL*)(GLsync sync);
export extern PFNGLDELETESYNCPROC glDeleteSync;
PFNGLDELETESYNCPROC glDeleteSync = nullptr;

export using PFNGLCLIENTWAITSYNCPROC = GLenum(GL_CALL*)(GLsync sync, GLbitfield flags, GLuint64 timeout);
export extern PFNGLCLIENTWAITSYNCPROC glClientWaitSync;
PFNGLCLIENTWAITSYNCPROC glClientWaitSync = nullptr;

export using PFNGLWAITSYNCPROC = void (GL_CALL*)(GLsync sync, GLbitfield flags, GLuint64 timeout);
export extern PFNGLWAITSYNCPROC glWaitSync;
PFNGLWAITSYNCPROC glWaitSync = nullptr;

export using PFNGLGETINTEGER64VPROC = void (GL_CALL*)(GLenum pname, GLint64* data);
export extern PFNGLGETINTEGER64VPROC glGetInteger64v;
PFNGLGETINTEGER64VPROC glGetInteger64v = nullptr;

export using PFNGLGETSYNCIVPROC = void (GL_CALL*)(GLsync sync, GLenum pname, GLsizei count, GLsizei* length, GLint* values);
export extern PFNGLGETSYNCIVPROC glGetSynciv;
PFNGLGETSYNCIVPROC glGetSynciv = nullptr;

export using PFNGLGETINTEGER64I_VPROC = void (GL_CALL*)(GLenum target, GLuint index, GLint64* data);
export extern PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = nullptr;

export using PFNGLGETBUFFERPARAMETERI64VPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint64* params);
export extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = nullptr;

export using PFNGLFRAMEBUFFERTEXTUREPROC = void (GL_CALL*)(GLenum target, GLenum attachment, GLuint texture, GLint level);
export extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = nullptr;

export using PFNGLTEXIMAGE2DMULTISAMPLEPROC = void (GL_CALL*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
export extern PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample = nullptr;

export using PFNGLTEXIMAGE3DMULTISAMPLEPROC = void (GL_CALL*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
export extern PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample;
PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample = nullptr;

export using PFNGLGETMULTISAMPLEFVPROC = void (GL_CALL*)(GLenum pname, GLuint index, GLfloat* val);
export extern PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv;
PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv = nullptr;

export using PFNGLSAMPLEMASKIPROC = void (GL_CALL*)(GLuint maskNumber, GLbitfield mask);
export extern PFNGLSAMPLEMASKIPROC glSampleMaski;
PFNGLSAMPLEMASKIPROC glSampleMaski = nullptr;

// ==================== OpenGL 3.3 Functions ====================

export using PFNGLBINDFRAGDATALOCATIONINDEXEDPROC = void (GL_CALL*)(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name);
export extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed = nullptr;

export using PFNGLGETFRAGDATAINDEXPROC = GLint(GL_CALL*)(GLuint program, const GLchar* name);
export extern PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex;
PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex = nullptr;

export using PFNGLGENSAMPLERSPROC = void (GL_CALL*)(GLsizei count, GLuint* samplers);
export extern PFNGLGENSAMPLERSPROC glGenSamplers;
PFNGLGENSAMPLERSPROC glGenSamplers = nullptr;

export using PFNGLDELETESAMPLERSPROC = void (GL_CALL*)(GLsizei count, const GLuint* samplers);
export extern PFNGLDELETESAMPLERSPROC glDeleteSamplers;
PFNGLDELETESAMPLERSPROC glDeleteSamplers = nullptr;

export using PFNGLISSAMPLERPROC = GLboolean(GL_CALL*)(GLuint sampler);
export extern PFNGLISSAMPLERPROC glIsSampler;
PFNGLISSAMPLERPROC glIsSampler = nullptr;

export using PFNGLBINDSAMPLERPROC = void (GL_CALL*)(GLuint unit, GLuint sampler);
export extern PFNGLBINDSAMPLERPROC glBindSampler;
PFNGLBINDSAMPLERPROC glBindSampler = nullptr;

export using PFNGLSAMPLERPARAMETERIPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLint param);
export extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = nullptr;

export using PFNGLSAMPLERPARAMETERIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, const GLint* param);
export extern PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;
PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = nullptr;

export using PFNGLSAMPLERPARAMETERFPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLfloat param);
export extern PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;
PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = nullptr;

export using PFNGLSAMPLERPARAMETERFVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, const GLfloat* param);
export extern PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;
PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = nullptr;

export using PFNGLSAMPLERPARAMETERIIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, const GLint* param);
export extern PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = nullptr;

export using PFNGLSAMPLERPARAMETERIUIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, const GLuint* param);
export extern PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv;
PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = nullptr;

export using PFNGLGETSAMPLERPARAMETERIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLint* params);
export extern PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;
PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = nullptr;

export using PFNGLGETSAMPLERPARAMETERIIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLint* params);
export extern PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = nullptr;

export using PFNGLGETSAMPLERPARAMETERFVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLfloat* params);
export extern PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = nullptr;

export using PFNGLGETSAMPLERPARAMETERIUIVPROC = void (GL_CALL*)(GLuint sampler, GLenum pname, GLuint* params);
export extern PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv = nullptr;

export using PFNGLQUERYCOUNTERPROC = void (GL_CALL*)(GLuint id, GLenum target);
export extern PFNGLQUERYCOUNTERPROC glQueryCounter;
PFNGLQUERYCOUNTERPROC glQueryCounter = nullptr;

export using PFNGLGETQUERYOBJECTI64VPROC = void (GL_CALL*)(GLuint id, GLenum pname, GLint64* params);
export extern PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v;
PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = nullptr;

export using PFNGLGETQUERYOBJECTUI64VPROC = void (GL_CALL*)(GLuint id, GLenum pname, GLuint64* params);
export extern PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v;
PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = nullptr;

export using PFNGLVERTEXATTRIBDIVISORPROC = void (GL_CALL*)(GLuint index, GLuint divisor);
export extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = nullptr;

export using PFNGLVERTEXATTRIBP1UIPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
export extern PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui;
PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui = nullptr;

export using PFNGLVERTEXATTRIBP1UIVPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
export extern PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv;
PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv = nullptr;

export using PFNGLVERTEXATTRIBP2UIPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
export extern PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui;
PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui = nullptr;

export using PFNGLVERTEXATTRIBP2UIVPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
export extern PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv;
PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv = nullptr;

export using PFNGLVERTEXATTRIBP3UIPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
export extern PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui;
PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui = nullptr;

export using PFNGLVERTEXATTRIBP3UIVPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
export extern PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv;
PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv = nullptr;

export using PFNGLVERTEXATTRIBP4UIPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
export extern PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui;
PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui = nullptr;

export using PFNGLVERTEXATTRIBP4UIVPROC = void (GL_CALL*)(GLuint index, GLenum type, GLboolean normalized, const GLuint* value);
export extern PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv;
PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv = nullptr;

export using PFNGLVERTEXP2UIPROC = void (GL_CALL*)(GLenum type, GLuint value);
export extern PFNGLVERTEXP2UIPROC glVertexP2ui;
PFNGLVERTEXP2UIPROC glVertexP2ui = nullptr;

export using PFNGLVERTEXP2UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* value);
export extern PFNGLVERTEXP2UIVPROC glVertexP2uiv;
PFNGLVERTEXP2UIVPROC glVertexP2uiv = nullptr;

export using PFNGLVERTEXP3UIPROC = void (GL_CALL*)(GLenum type, GLuint value);
export extern PFNGLVERTEXP3UIPROC glVertexP3ui;
PFNGLVERTEXP3UIPROC glVertexP3ui = nullptr;

export using PFNGLVERTEXP3UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* value);
export extern PFNGLVERTEXP3UIVPROC glVertexP3uiv;
PFNGLVERTEXP3UIVPROC glVertexP3uiv = nullptr;

export using PFNGLVERTEXP4UIPROC = void (GL_CALL*)(GLenum type, GLuint value);
export extern PFNGLVERTEXP4UIPROC glVertexP4ui;
PFNGLVERTEXP4UIPROC glVertexP4ui = nullptr;

export using PFNGLVERTEXP4UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* value);
export extern PFNGLVERTEXP4UIVPROC glVertexP4uiv;
PFNGLVERTEXP4UIVPROC glVertexP4uiv = nullptr;

export using PFNGLTEXCOORDP1UIPROC = void (GL_CALL*)(GLenum type, GLuint coords);
export extern PFNGLTEXCOORDP1UIPROC glTexCoordP1ui;
PFNGLTEXCOORDP1UIPROC glTexCoordP1ui = nullptr;

export using PFNGLTEXCOORDP1UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* coords);
export extern PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv;
PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv = nullptr;

export using PFNGLTEXCOORDP2UIPROC = void (GL_CALL*)(GLenum type, GLuint coords);
export extern PFNGLTEXCOORDP2UIPROC glTexCoordP2ui;
PFNGLTEXCOORDP2UIPROC glTexCoordP2ui = nullptr;

export using PFNGLTEXCOORDP2UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* coords);
export extern PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv;
PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv = nullptr;

export using PFNGLTEXCOORDP3UIPROC = void (GL_CALL*)(GLenum type, GLuint coords);
export extern PFNGLTEXCOORDP3UIPROC glTexCoordP3ui;
PFNGLTEXCOORDP3UIPROC glTexCoordP3ui = nullptr;

export using PFNGLTEXCOORDP3UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* coords);
export extern PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv;
PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv = nullptr;

export using PFNGLTEXCOORDP4UIPROC = void (GL_CALL*)(GLenum type, GLuint coords);
export extern PFNGLTEXCOORDP4UIPROC glTexCoordP4ui;
PFNGLTEXCOORDP4UIPROC glTexCoordP4ui = nullptr;

export using PFNGLTEXCOORDP4UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* coords);
export extern PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv;
PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv = nullptr;

export using PFNGLMULTITEXCOORDP1UIPROC = void (GL_CALL*)(GLenum texture, GLenum type, GLuint coords);
export extern PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui;
PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui = nullptr;

export using PFNGLMULTITEXCOORDP1UIVPROC = void (GL_CALL*)(GLenum texture, GLenum type, const GLuint* coords);
export extern PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv;
PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv = nullptr;

export using PFNGLMULTITEXCOORDP2UIPROC = void (GL_CALL*)(GLenum texture, GLenum type, GLuint coords);
export extern PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui;
PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui = nullptr;

export using PFNGLMULTITEXCOORDP2UIVPROC = void (GL_CALL*)(GLenum texture, GLenum type, const GLuint* coords);
export extern PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv;
PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv = nullptr;

export using PFNGLMULTITEXCOORDP3UIPROC = void (GL_CALL*)(GLenum texture, GLenum type, GLuint coords);
export extern PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui;
PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui = nullptr;

export using PFNGLMULTITEXCOORDP3UIVPROC = void (GL_CALL*)(GLenum texture, GLenum type, const GLuint* coords);
export extern PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv;
PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv = nullptr;

export using PFNGLMULTITEXCOORDP4UIPROC = void (GL_CALL*)(GLenum texture, GLenum type, GLuint coords);
export extern PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui;
PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui = nullptr;

export using PFNGLMULTITEXCOORDP4UIVPROC = void (GL_CALL*)(GLenum texture, GLenum type, const GLuint* coords);
export extern PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv;
PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv = nullptr;

export using PFNGLNORMALP3UIPROC = void (GL_CALL*)(GLenum type, GLuint coords);
export extern PFNGLNORMALP3UIPROC glNormalP3ui;
PFNGLNORMALP3UIPROC glNormalP3ui = nullptr;

export using PFNGLNORMALP3UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* coords);
export extern PFNGLNORMALP3UIVPROC glNormalP3uiv;
PFNGLNORMALP3UIVPROC glNormalP3uiv = nullptr;

export using PFNGLCOLORP3UIPROC = void (GL_CALL*)(GLenum type, GLuint color);
export extern PFNGLCOLORP3UIPROC glColorP3ui;
PFNGLCOLORP3UIPROC glColorP3ui = nullptr;

export using PFNGLCOLORP3UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* color);
export extern PFNGLCOLORP3UIVPROC glColorP3uiv;
PFNGLCOLORP3UIVPROC glColorP3uiv = nullptr;

export using PFNGLCOLORP4UIPROC = void (GL_CALL*)(GLenum type, GLuint color);
export extern PFNGLCOLORP4UIPROC glColorP4ui;
PFNGLCOLORP4UIPROC glColorP4ui = nullptr;

export using PFNGLCOLORP4UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* color);
export extern PFNGLCOLORP4UIVPROC glColorP4uiv;
PFNGLCOLORP4UIVPROC glColorP4uiv = nullptr;

export using PFNGLSECONDARYCOLORP3UIPROC = void (GL_CALL*)(GLenum type, GLuint color);
export extern PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui;
PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui = nullptr;

export using PFNGLSECONDARYCOLORP3UIVPROC = void (GL_CALL*)(GLenum type, const GLuint* color);
export extern PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv;
PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv = nullptr;

// ==================== OpenGL 4.0 Functions ====================

export using PFNGLMINSAMPLESHADINGPROC = void (GL_CALL*)(GLfloat value);
export extern PFNGLMINSAMPLESHADINGPROC glMinSampleShading;
PFNGLMINSAMPLESHADINGPROC glMinSampleShading = nullptr;

export using PFNGLBLENDEQUATIONIPROC = void (GL_CALL*)(GLuint buf, GLenum mode);
export extern PFNGLBLENDEQUATIONIPROC glBlendEquationi;
PFNGLBLENDEQUATIONIPROC glBlendEquationi = nullptr;

export using PFNGLBLENDEQUATIONSEPARATEIPROC = void (GL_CALL*)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
export extern PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei = nullptr;

export using PFNGLBLENDFUNCIPROC = void (GL_CALL*)(GLuint buf, GLenum src, GLenum dst);
export extern PFNGLBLENDFUNCIPROC glBlendFunci;
PFNGLBLENDFUNCIPROC glBlendFunci = nullptr;

export using PFNGLBLENDFUNCSEPARATEIPROC = void (GL_CALL*)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
export extern PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei;
PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei = nullptr;

export using PFNGLDRAWARRAYSINDIRECTPROC = void (GL_CALL*)(GLenum mode, const void* indirect);
export extern PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;
PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect = nullptr;

export using PFNGLDRAWELEMENTSINDIRECTPROC = void (GL_CALL*)(GLenum mode, GLenum type, const void* indirect);
export extern PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;
PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect = nullptr;

export using PFNGLUNIFORM1DPROC = void (GL_CALL*)(GLint location, GLdouble x);
export extern PFNGLUNIFORM1DPROC glUniform1d;
PFNGLUNIFORM1DPROC glUniform1d = nullptr;

export using PFNGLUNIFORM2DPROC = void (GL_CALL*)(GLint location, GLdouble x, GLdouble y);
export extern PFNGLUNIFORM2DPROC glUniform2d;
PFNGLUNIFORM2DPROC glUniform2d = nullptr;

export using PFNGLUNIFORM3DPROC = void (GL_CALL*)(GLint location, GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLUNIFORM3DPROC glUniform3d;
PFNGLUNIFORM3DPROC glUniform3d = nullptr;

export using PFNGLUNIFORM4DPROC = void (GL_CALL*)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
export extern PFNGLUNIFORM4DPROC glUniform4d;
PFNGLUNIFORM4DPROC glUniform4d = nullptr;

export using PFNGLUNIFORM1DVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLUNIFORM1DVPROC glUniform1dv;
PFNGLUNIFORM1DVPROC glUniform1dv = nullptr;

export using PFNGLUNIFORM2DVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLUNIFORM2DVPROC glUniform2dv;
PFNGLUNIFORM2DVPROC glUniform2dv = nullptr;

export using PFNGLUNIFORM3DVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLUNIFORM3DVPROC glUniform3dv;
PFNGLUNIFORM3DVPROC glUniform3dv = nullptr;

export using PFNGLUNIFORM4DVPROC = void (GL_CALL*)(GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLUNIFORM4DVPROC glUniform4dv;
PFNGLUNIFORM4DVPROC glUniform4dv = nullptr;

export using PFNGLUNIFORMMATRIX2DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv;
PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv = nullptr;

export using PFNGLUNIFORMMATRIX3DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv;
PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv = nullptr;

export using PFNGLUNIFORMMATRIX4DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv;
PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv = nullptr;

export using PFNGLUNIFORMMATRIX2X3DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv;
PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv = nullptr;

export using PFNGLUNIFORMMATRIX2X4DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv;
PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv = nullptr;

export using PFNGLUNIFORMMATRIX3X2DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv;
PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv = nullptr;

export using PFNGLUNIFORMMATRIX3X4DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv;
PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv = nullptr;

export using PFNGLUNIFORMMATRIX4X2DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv;
PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv = nullptr;

export using PFNGLUNIFORMMATRIX4X3DVPROC = void (GL_CALL*)(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv;
PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv = nullptr;

export using PFNGLGETUNIFORMDVPROC = void (GL_CALL*)(GLuint program, GLint location, GLdouble* params);
export extern PFNGLGETUNIFORMDVPROC glGetUniformdv;
PFNGLGETUNIFORMDVPROC glGetUniformdv = nullptr;

export using PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC = GLint(GL_CALL*)(GLuint program, GLenum shadertype, const GLchar* name);
export extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation = nullptr;

export using PFNGLGETSUBROUTINEINDEXPROC = GLuint(GL_CALL*)(GLuint program, GLenum shadertype, const GLchar* name);
export extern PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex;
PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex = nullptr;

export using PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC = void (GL_CALL*)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values);
export extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv = nullptr;

export using PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC = void (GL_CALL*)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
export extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName = nullptr;

export using PFNGLGETACTIVESUBROUTINENAMEPROC = void (GL_CALL*)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
export extern PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName;
PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName = nullptr;

export using PFNGLUNIFORMSUBROUTINESUIVPROC = void (GL_CALL*)(GLenum shadertype, GLsizei count, const GLuint* indices);
export extern PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv;
PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv = nullptr;

export using PFNGLGETUNIFORMSUBROUTINEUIVPROC = void (GL_CALL*)(GLenum shadertype, GLint location, GLuint* params);
export extern PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv;
PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv = nullptr;

export using PFNGLGETPROGRAMSTAGEIVPROC = void (GL_CALL*)(GLuint program, GLenum shadertype, GLenum pname, GLint* values);
export extern PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv;
PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = nullptr;

export using PFNGLPATCHPARAMETERIPROC = void (GL_CALL*)(GLenum pname, GLint value);
export extern PFNGLPATCHPARAMETERIPROC glPatchParameteri;
PFNGLPATCHPARAMETERIPROC glPatchParameteri = nullptr;

export using PFNGLPATCHPARAMETERFVPROC = void (GL_CALL*)(GLenum pname, const GLfloat* values);
export extern PFNGLPATCHPARAMETERFVPROC glPatchParameterfv;
PFNGLPATCHPARAMETERFVPROC glPatchParameterfv = nullptr;

export using PFNGLBINDTRANSFORMFEEDBACKPROC = void (GL_CALL*)(GLenum target, GLuint id);
export extern PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;
PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = nullptr;

export using PFNGLDELETETRANSFORMFEEDBACKSPROC = void (GL_CALL*)(GLsizei n, const GLuint* ids);
export extern PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;
PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = nullptr;

export using PFNGLGENTRANSFORMFEEDBACKSPROC = void (GL_CALL*)(GLsizei n, GLuint* ids);
export extern PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;
PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = nullptr;

export using PFNGLISTRANSFORMFEEDBACKPROC = GLboolean(GL_CALL*)(GLuint id);
export extern PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;
PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = nullptr;

export using PFNGLPAUSETRANSFORMFEEDBACKPROC = void (GL_CALL*)();
export extern PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;
PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = nullptr;

export using PFNGLRESUMETRANSFORMFEEDBACKPROC = void (GL_CALL*)();
export extern PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;
PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = nullptr;

export using PFNGLDRAWTRANSFORMFEEDBACKPROC = void (GL_CALL*)(GLenum mode, GLuint id);
export extern PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback = nullptr;

export using PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC = void (GL_CALL*)(GLenum mode, GLuint id, GLuint stream);
export extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream = nullptr;

export using PFNGLBEGINQUERYINDEXEDPROC = void (GL_CALL*)(GLenum target, GLuint index, GLuint id);
export extern PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed;
PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed = nullptr;

export using PFNGLENDQUERYINDEXEDPROC = void (GL_CALL*)(GLenum target, GLuint index);
export extern PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed;
PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed = nullptr;

export using PFNGLGETQUERYINDEXEDIVPROC = void (GL_CALL*)(GLenum target, GLuint index, GLenum pname, GLint* params);
export extern PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv;
PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv = nullptr;

// ==================== OpenGL 4.1 Functions ====================

export using PFNGLRELEASESHADERCOMPILERPROC = void (GL_CALL*)();
export extern PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;
PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = nullptr;

export using PFNGLSHADERBINARYPROC = void (GL_CALL*)(GLsizei count, const GLuint* shaders, GLenum binaryFormat, const void* binary, GLsizei length);
export extern PFNGLSHADERBINARYPROC glShaderBinary;
PFNGLSHADERBINARYPROC glShaderBinary = nullptr;

export using PFNGLGETSHADERPRECISIONFORMATPROC = void (GL_CALL*)(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
export extern PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;
PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = nullptr;

export using PFNGLDEPTHRANGEFPROC = void (GL_CALL*)(GLfloat n, GLfloat f);
export extern PFNGLDEPTHRANGEFPROC glDepthRangef;
PFNGLDEPTHRANGEFPROC glDepthRangef = nullptr;

export using PFNGLCLEARDEPTHFPROC = void (GL_CALL*)(GLfloat d);
export extern PFNGLCLEARDEPTHFPROC glClearDepthf;
PFNGLCLEARDEPTHFPROC glClearDepthf = nullptr;

export using PFNGLGETPROGRAMBINARYPROC = void (GL_CALL*)(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
export extern PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = nullptr;

export using PFNGLPROGRAMBINARYPROC = void (GL_CALL*)(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length);
export extern PFNGLPROGRAMBINARYPROC glProgramBinary;
PFNGLPROGRAMBINARYPROC glProgramBinary = nullptr;

export using PFNGLPROGRAMPARAMETERIPROC = void (GL_CALL*)(GLuint program, GLenum pname, GLint value);
export extern PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = nullptr;

export using PFNGLUSEPROGRAMSTAGESPROC = void (GL_CALL*)(GLuint pipeline, GLbitfield stages, GLuint program);
export extern PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages;
PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = nullptr;

export using PFNGLACTIVESHADERPROGRAMPROC = void (GL_CALL*)(GLuint pipeline, GLuint program);
export extern PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram;
PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram = nullptr;

export using PFNGLCREATESHADERPROGRAMVPROC = GLuint(GL_CALL*)(GLenum type, GLsizei count, const GLchar* const* strings);
export extern PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = nullptr;

export using PFNGLBINDPROGRAMPIPELINEPROC = void (GL_CALL*)(GLuint pipeline);
export extern PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline;
PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline = nullptr;

export using PFNGLDELETEPROGRAMPIPELINESPROC = void (GL_CALL*)(GLsizei n, const GLuint* pipelines);
export extern PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines;
PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines = nullptr;

export using PFNGLGENPROGRAMPIPELINESPROC = void (GL_CALL*)(GLsizei n, GLuint* pipelines);
export extern PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines;
PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines = nullptr;

export using PFNGLISPROGRAMPIPELINEPROC = GLboolean(GL_CALL*)(GLuint pipeline);
export extern PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline;
PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline = nullptr;

export using PFNGLGETPROGRAMPIPELINEIVPROC = void (GL_CALL*)(GLuint pipeline, GLenum pname, GLint* params);
export extern PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv;
PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv = nullptr;

export using PFNGLPROGRAMUNIFORM1IPROC = void (GL_CALL*)(GLuint program, GLint location, GLint v0);
export extern PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = nullptr;

export using PFNGLPROGRAMUNIFORM1IVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
export extern PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv;
PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = nullptr;

export using PFNGLPROGRAMUNIFORM1FPROC = void (GL_CALL*)(GLuint program, GLint location, GLfloat v0);
export extern PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f;
PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = nullptr;

export using PFNGLPROGRAMUNIFORM1FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv;
PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = nullptr;

export using PFNGLPROGRAMUNIFORM1DPROC = void (GL_CALL*)(GLuint program, GLint location, GLdouble v0);
export extern PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d;
PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = nullptr;

export using PFNGLPROGRAMUNIFORM1DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv;
PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = nullptr;

export using PFNGLPROGRAMUNIFORM1UIPROC = void (GL_CALL*)(GLuint program, GLint location, GLuint v0);
export extern PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = nullptr;

export using PFNGLPROGRAMUNIFORM1UIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLuint* value);
export extern PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv;
PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = nullptr;

export using PFNGLPROGRAMUNIFORM2IPROC = void (GL_CALL*)(GLuint program, GLint location, GLint v0, GLint v1);
export extern PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i;
PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = nullptr;

export using PFNGLPROGRAMUNIFORM2IVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
export extern PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv;
PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = nullptr;

export using PFNGLPROGRAMUNIFORM2FPROC = void (GL_CALL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
export extern PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = nullptr;

export using PFNGLPROGRAMUNIFORM2FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv;
PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = nullptr;

export using PFNGLPROGRAMUNIFORM2DPROC = void (GL_CALL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
export extern PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d;
PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = nullptr;

export using PFNGLPROGRAMUNIFORM2DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv;
PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = nullptr;

export using PFNGLPROGRAMUNIFORM2UIPROC = void (GL_CALL*)(GLuint program, GLint location, GLuint v0, GLuint v1);
export extern PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = nullptr;

export using PFNGLPROGRAMUNIFORM2UIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLuint* value);
export extern PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv;
PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = nullptr;

export using PFNGLPROGRAMUNIFORM3IPROC = void (GL_CALL*)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
export extern PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i;
PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = nullptr;

export using PFNGLPROGRAMUNIFORM3IVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
export extern PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv;
PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = nullptr;

export using PFNGLPROGRAMUNIFORM3FPROC = void (GL_CALL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
export extern PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = nullptr;

export using PFNGLPROGRAMUNIFORM3FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = nullptr;

export using PFNGLPROGRAMUNIFORM3DPROC = void (GL_CALL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
export extern PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d;
PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = nullptr;

export using PFNGLPROGRAMUNIFORM3DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv;
PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = nullptr;

export using PFNGLPROGRAMUNIFORM3UIPROC = void (GL_CALL*)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
export extern PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = nullptr;

export using PFNGLPROGRAMUNIFORM3UIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLuint* value);
export extern PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv;
PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = nullptr;

export using PFNGLPROGRAMUNIFORM4IPROC = void (GL_CALL*)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
export extern PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;
PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = nullptr;

export using PFNGLPROGRAMUNIFORM4IVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
export extern PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv;
PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = nullptr;

export using PFNGLPROGRAMUNIFORM4FPROC = void (GL_CALL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
export extern PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;
PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = nullptr;

export using PFNGLPROGRAMUNIFORM4FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = nullptr;

export using PFNGLPROGRAMUNIFORM4DPROC = void (GL_CALL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
export extern PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d;
PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = nullptr;

export using PFNGLPROGRAMUNIFORM4DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv;
PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = nullptr;

export using PFNGLPROGRAMUNIFORM4UIPROC = void (GL_CALL*)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
export extern PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = nullptr;

export using PFNGLPROGRAMUNIFORM4UIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, const GLuint* value);
export extern PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv;
PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = nullptr;

export using PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
export extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = nullptr;

export using PFNGLVALIDATEPROGRAMPIPELINEPROC = void (GL_CALL*)(GLuint pipeline);
export extern PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline;
PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline = nullptr;

export using PFNGLGETPROGRAMPIPELINEINFOLOGPROC = void (GL_CALL*)(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
export extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog = nullptr;

export using PFNGLVERTEXATTRIBL1DPROC = void (GL_CALL*)(GLuint index, GLdouble x);
export extern PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d;
PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d = nullptr;

export using PFNGLVERTEXATTRIBL2DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y);
export extern PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d;
PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d = nullptr;

export using PFNGLVERTEXATTRIBL3DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
export extern PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d;
PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d = nullptr;

export using PFNGLVERTEXATTRIBL4DPROC = void (GL_CALL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
export extern PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d;
PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d = nullptr;

export using PFNGLVERTEXATTRIBL1DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv;
PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv = nullptr;

export using PFNGLVERTEXATTRIBL2DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv;
PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv = nullptr;

export using PFNGLVERTEXATTRIBL3DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv;
PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv = nullptr;

export using PFNGLVERTEXATTRIBL4DVPROC = void (GL_CALL*)(GLuint index, const GLdouble* v);
export extern PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv;
PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv = nullptr;

export using PFNGLVERTEXATTRIBLPOINTERPROC = void (GL_CALL*)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
export extern PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer;
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = nullptr;

export using PFNGLGETVERTEXATTRIBLDVPROC = void (GL_CALL*)(GLuint index, GLenum pname, GLdouble* params);
export extern PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv;
PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv = nullptr;

export using PFNGLVIEWPORTARRAYVPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLfloat* v);
export extern PFNGLVIEWPORTARRAYVPROC glViewportArrayv;
PFNGLVIEWPORTARRAYVPROC glViewportArrayv = nullptr;

export using PFNGLVIEWPORTINDEXEDFPROC = void (GL_CALL*)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
export extern PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf;
PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf = nullptr;

export using PFNGLVIEWPORTINDEXEDFVPROC = void (GL_CALL*)(GLuint index, const GLfloat* v);
export extern PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv;
PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv = nullptr;

export using PFNGLSCISSORARRAYVPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLint* v);
export extern PFNGLSCISSORARRAYVPROC glScissorArrayv;
PFNGLSCISSORARRAYVPROC glScissorArrayv = nullptr;

export using PFNGLSCISSORINDEXEDPROC = void (GL_CALL*)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
export extern PFNGLSCISSORINDEXEDPROC glScissorIndexed;
PFNGLSCISSORINDEXEDPROC glScissorIndexed = nullptr;

export using PFNGLSCISSORINDEXEDVPROC = void (GL_CALL*)(GLuint index, const GLint* v);
export extern PFNGLSCISSORINDEXEDVPROC glScissorIndexedv;
PFNGLSCISSORINDEXEDVPROC glScissorIndexedv = nullptr;

export using PFNGLDEPTHRANGEARRAYVPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLdouble* v);
export extern PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv;
PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv = nullptr;

export using PFNGLDEPTHRANGEINDEXEDPROC = void (GL_CALL*)(GLuint index, GLdouble n, GLdouble f);
export extern PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed;
PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed = nullptr;

export using PFNGLGETFLOATI_VPROC = void (GL_CALL*)(GLenum target, GLuint index, GLfloat* data);
export extern PFNGLGETFLOATI_VPROC glGetFloati_v;
PFNGLGETFLOATI_VPROC glGetFloati_v = nullptr;

export using PFNGLGETDOUBLEI_VPROC = void (GL_CALL*)(GLenum target, GLuint index, GLdouble* data);
export extern PFNGLGETDOUBLEI_VPROC glGetDoublei_v;
PFNGLGETDOUBLEI_VPROC glGetDoublei_v = nullptr;

// ==================== OpenGL 4.2 Functions ====================

export using PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC = void (GL_CALL*)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
export extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance = nullptr;

export using PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance);
export extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance = nullptr;

export using PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC = void (GL_CALL*)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
export extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance = nullptr;

export using PFNGLGETINTERNALFORMATIVPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint* params);
export extern PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ;
PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = nullptr;

export using PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC = void (GL_CALL*)(GLuint program, GLuint bufferIndex, GLenum pname, GLint* params);
export extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv = nullptr;

export using PFNGLBINDIMAGETEXTUREPROC = void (GL_CALL*)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
export extern PFNGLBINDIMAGETEXTUREPROC glBindImageTexture;
PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = nullptr;

export using PFNGLMEMORYBARRIERPROC = void (GL_CALL*)(GLbitfield barriers);
export extern PFNGLMEMORYBARRIERPROC glMemoryBarrier;
PFNGLMEMORYBARRIERPROC glMemoryBarrier = nullptr;

export using PFNGLTEXSTORAGE1DPROC = void (GL_CALL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
export extern PFNGLTEXSTORAGE1DPROC glTexStorage1D;
PFNGLTEXSTORAGE1DPROC glTexStorage1D = nullptr;

export using PFNGLTEXSTORAGE2DPROC = void (GL_CALL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLTEXSTORAGE2DPROC glTexStorage2D;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = nullptr;

export using PFNGLTEXSTORAGE3DPROC = void (GL_CALL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
export extern PFNGLTEXSTORAGE3DPROC glTexStorage3D;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = nullptr;

export using PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC = void (GL_CALL*)(GLenum mode, GLuint id, GLsizei instancecount);
export extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced = nullptr;

export using PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC = void (GL_CALL*)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
export extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced = nullptr;

// ==================== OpenGL 4.3 Functions ====================

export using PFNGLCLEARBUFFERDATAPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARBUFFERDATAPROC glClearBufferData;
PFNGLCLEARBUFFERDATAPROC glClearBufferData = nullptr;

export using PFNGLCLEARBUFFERSUBDATAPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData;
PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData = nullptr;

export using PFNGLDISPATCHCOMPUTEPROC = void (GL_CALL*)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
export extern PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = nullptr;

export using PFNGLDISPATCHCOMPUTEINDIRECTPROC = void (GL_CALL*)(GLintptr indirect);
export extern PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect;
PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect = nullptr;

export using PFNGLCOPYIMAGESUBDATAPROC = void (GL_CALL*)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
export extern PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData;
PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData = nullptr;

export using PFNGLFRAMEBUFFERPARAMETERIPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint param);
export extern PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri;
PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri = nullptr;

export using PFNGLGETFRAMEBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLenum target, GLenum pname, GLint* params);
export extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv = nullptr;

export using PFNGLGETINTERNALFORMATI64VPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64* params);
export extern PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v;
PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v = nullptr;

export using PFNGLINVALIDATETEXSUBIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
export extern PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage;
PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage = nullptr;

export using PFNGLINVALIDATETEXIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level);
export extern PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage;
PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage = nullptr;

export using PFNGLINVALIDATEBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint buffer, GLintptr offset, GLsizeiptr length);
export extern PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData;
PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData = nullptr;

export using PFNGLINVALIDATEBUFFERDATAPROC = void (GL_CALL*)(GLuint buffer);
export extern PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData;
PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData = nullptr;

export using PFNGLINVALIDATEFRAMEBUFFERPROC = void (GL_CALL*)(GLenum target, GLsizei numAttachments, const GLenum* attachments);
export extern PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;
PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = nullptr;

export using PFNGLINVALIDATESUBFRAMEBUFFERPROC = void (GL_CALL*)(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = nullptr;

export using PFNGLMULTIDRAWARRAYSINDIRECTPROC = void (GL_CALL*)(GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride);
export extern PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect;
PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect = nullptr;

export using PFNGLMULTIDRAWELEMENTSINDIRECTPROC = void (GL_CALL*)(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride);
export extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect = nullptr;

export using PFNGLGETPROGRAMINTERFACEIVPROC = void (GL_CALL*)(GLuint program, GLenum programInterface, GLenum pname, GLint* params);
export extern PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv;
PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = nullptr;

export using PFNGLGETPROGRAMRESOURCEINDEXPROC = GLuint(GL_CALL*)(GLuint program, GLenum programInterface, const GLchar* name);
export extern PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex;
PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex = nullptr;

export using PFNGLGETPROGRAMRESOURCENAMEPROC = void (GL_CALL*)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
export extern PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = nullptr;

export using PFNGLGETPROGRAMRESOURCEIVPROC = void (GL_CALL*)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei count, GLsizei* length, GLint* params);
export extern PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = nullptr;

export using PFNGLGETPROGRAMRESOURCELOCATIONPROC = GLint(GL_CALL*)(GLuint program, GLenum programInterface, const GLchar* name);
export extern PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation;
PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation = nullptr;

export using PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC = GLint(GL_CALL*)(GLuint program, GLenum programInterface, const GLchar* name);
export extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex = nullptr;

export using PFNGLSHADERSTORAGEBLOCKBINDINGPROC = void (GL_CALL*)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
export extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding = nullptr;

export using PFNGLTEXBUFFERRANGEPROC = void (GL_CALL*)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
export extern PFNGLTEXBUFFERRANGEPROC glTexBufferRange;
PFNGLTEXBUFFERRANGEPROC glTexBufferRange = nullptr;

export using PFNGLTEXSTORAGE2DMULTISAMPLEPROC = void (GL_CALL*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
export extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample = nullptr;

export using PFNGLTEXSTORAGE3DMULTISAMPLEPROC = void (GL_CALL*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
export extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample = nullptr;

export using PFNGLTEXTUREVIEWPROC = void (GL_CALL*)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
export extern PFNGLTEXTUREVIEWPROC glTextureView;
PFNGLTEXTUREVIEWPROC glTextureView = nullptr;

export using PFNGLBINDVERTEXBUFFERPROC = void (GL_CALL*)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
export extern PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = nullptr;

export using PFNGLVERTEXATTRIBFORMATPROC = void (GL_CALL*)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
export extern PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat = nullptr;

export using PFNGLVERTEXATTRIBIFORMATPROC = void (GL_CALL*)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
export extern PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat;
PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat = nullptr;

export using PFNGLVERTEXATTRIBLFORMATPROC = void (GL_CALL*)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
export extern PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat;
PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat = nullptr;

export using PFNGLVERTEXATTRIBBINDINGPROC = void (GL_CALL*)(GLuint attribindex, GLuint bindingindex);
export extern PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding = nullptr;

export using PFNGLVERTEXBINDINGDIVISORPROC = void (GL_CALL*)(GLuint bindingindex, GLuint divisor);
export extern PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor;
PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor = nullptr;

export using PFNGLDEBUGMESSAGECONTROLPROC = void (GL_CALL*)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
export extern PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = nullptr;

export using PFNGLDEBUGMESSAGEINSERTPROC = void (GL_CALL*)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf);
export extern PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;
PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert = nullptr;

export using PFNGLDEBUGMESSAGECALLBACKPROC = void (GL_CALL*)(GLDEBUGPROC callback, const void* userParam);
export extern PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;

export using PFNGLGETDEBUGMESSAGELOGPROC = GLuint(GL_CALL*)(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);
export extern PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;
PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog = nullptr;

export using PFNGLPUSHDEBUGGROUPPROC = void (GL_CALL*)(GLenum source, GLuint id, GLsizei length, const GLchar* message);
export extern PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup;
PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup = nullptr;

export using PFNGLPOPDEBUGGROUPPROC = void (GL_CALL*)();
export extern PFNGLPOPDEBUGGROUPPROC glPopDebugGroup;
PFNGLPOPDEBUGGROUPPROC glPopDebugGroup = nullptr;

export using PFNGLOBJECTLABELPROC = void (GL_CALL*)(GLenum identifier, GLuint name, GLsizei length, const GLchar* label);
export extern PFNGLOBJECTLABELPROC glObjectLabel;
PFNGLOBJECTLABELPROC glObjectLabel = nullptr;

export using PFNGLGETOBJECTLABELPROC = void (GL_CALL*)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label);
export extern PFNGLGETOBJECTLABELPROC glGetObjectLabel;
PFNGLGETOBJECTLABELPROC glGetObjectLabel = nullptr;

export using PFNGLOBJECTPTRLABELPROC = void (GL_CALL*)(const void* ptr, GLsizei length, const GLchar* label);
export extern PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;
PFNGLOBJECTPTRLABELPROC glObjectPtrLabel = nullptr;

export using PFNGLGETOBJECTPTRLABELPROC = void (GL_CALL*)(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label);
export extern PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;
PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel = nullptr;

// ==================== OpenGL 4.4 Functions ====================

export using PFNGLBUFFERSTORAGEPROC = void (GL_CALL*)(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags);
export extern PFNGLBUFFERSTORAGEPROC glBufferStorage;
PFNGLBUFFERSTORAGEPROC glBufferStorage = nullptr;

export using PFNGLCLEARTEXIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARTEXIMAGEPROC glClearTexImage;
PFNGLCLEARTEXIMAGEPROC glClearTexImage = nullptr;

export using PFNGLCLEARTEXSUBIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage;
PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage = nullptr;

export using PFNGLBINDBUFFERSBASEPROC = void (GL_CALL*)(GLenum target, GLuint first, GLsizei count, const GLuint* buffers);
export extern PFNGLBINDBUFFERSBASEPROC glBindBuffersBase;
PFNGLBINDBUFFERSBASEPROC glBindBuffersBase = nullptr;

export using PFNGLBINDBUFFERSRANGEPROC = void (GL_CALL*)(GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes);
export extern PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange;
PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange = nullptr;

export using PFNGLBINDTEXTURESPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLuint* textures);
export extern PFNGLBINDTEXTURESPROC glBindTextures;
PFNGLBINDTEXTURESPROC glBindTextures = nullptr;

export using PFNGLBINDSAMPLERSPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLuint* samplers);
export extern PFNGLBINDSAMPLERSPROC glBindSamplers;
PFNGLBINDSAMPLERSPROC glBindSamplers = nullptr;

export using PFNGLBINDIMAGETEXTURESPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLuint* textures);
export extern PFNGLBINDIMAGETEXTURESPROC glBindImageTextures;
PFNGLBINDIMAGETEXTURESPROC glBindImageTextures = nullptr;

export using PFNGLBINDVERTEXBUFFERSPROC = void (GL_CALL*)(GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides);
export extern PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers;
PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers = nullptr;

// ==================== OpenGL 4.5 Functions ====================

export using PFNGLCLIPCONTROLPROC = void (GL_CALL*)(GLenum origin, GLenum depth);
export extern PFNGLCLIPCONTROLPROC glClipControl;
PFNGLCLIPCONTROLPROC glClipControl = nullptr;

export using PFNGLCREATETRANSFORMFEEDBACKSPROC = void (GL_CALL*)(GLsizei n, GLuint* ids);
export extern PFNGLCREATETRANSFORMFEEDBACKSPROC glCreateTransformFeedbacks;
PFNGLCREATETRANSFORMFEEDBACKSPROC glCreateTransformFeedbacks = nullptr;

export using PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC = void (GL_CALL*)(GLuint xfb, GLuint index, GLuint buffer);
export extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glTransformFeedbackBufferBase;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glTransformFeedbackBufferBase = nullptr;

export using PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC = void (GL_CALL*)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
export extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glTransformFeedbackBufferRange;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glTransformFeedbackBufferRange = nullptr;

export using PFNGLGETTRANSFORMFEEDBACKIVPROC = void (GL_CALL*)(GLuint xfb, GLenum pname, GLint* param);
export extern PFNGLGETTRANSFORMFEEDBACKIVPROC glGetTransformFeedbackiv;
PFNGLGETTRANSFORMFEEDBACKIVPROC glGetTransformFeedbackiv = nullptr;

export using PFNGLGETTRANSFORMFEEDBACKI_VPROC = void (GL_CALL*)(GLuint xfb, GLenum pname, GLuint index, GLint* param);
export extern PFNGLGETTRANSFORMFEEDBACKI_VPROC glGetTransformFeedbacki_v;
PFNGLGETTRANSFORMFEEDBACKI_VPROC glGetTransformFeedbacki_v = nullptr;

export using PFNGLGETTRANSFORMFEEDBACKI64_VPROC = void (GL_CALL*)(GLuint xfb, GLenum pname, GLuint index, GLint64* param);
export extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC glGetTransformFeedbacki64_v;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC glGetTransformFeedbacki64_v = nullptr;

export using PFNGLCREATEBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* buffers);
export extern PFNGLCREATEBUFFERSPROC glCreateBuffers;
PFNGLCREATEBUFFERSPROC glCreateBuffers = nullptr;

export using PFNGLNAMEDBUFFERSTORAGEPROC = void (GL_CALL*)(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags);
export extern PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorage;
PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorage = nullptr;

export using PFNGLNAMEDBUFFERDATAPROC = void (GL_CALL*)(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
export extern PFNGLNAMEDBUFFERDATAPROC glNamedBufferData;
PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = nullptr;

export using PFNGLNAMEDBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
export extern PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData;
PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = nullptr;

export using PFNGLCOPYNAMEDBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
export extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC glCopyNamedBufferSubData;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC glCopyNamedBufferSubData = nullptr;

export using PFNGLCLEARNAMEDBUFFERDATAPROC = void (GL_CALL*)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARNAMEDBUFFERDATAPROC glClearNamedBufferData;
PFNGLCLEARNAMEDBUFFERDATAPROC glClearNamedBufferData = nullptr;

export using PFNGLCLEARNAMEDBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data);
export extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC glClearNamedBufferSubData;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC glClearNamedBufferSubData = nullptr;

export using PFNGLMAPNAMEDBUFFERPROC = void* (GL_CALL*)(GLuint buffer, GLenum access);
export extern PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer;
PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer = nullptr;

export using PFNGLMAPNAMEDBUFFERRANGEPROC = void* (GL_CALL*)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
export extern PFNGLMAPNAMEDBUFFERRANGEPROC glMapNamedBufferRange;
PFNGLMAPNAMEDBUFFERRANGEPROC glMapNamedBufferRange = nullptr;

export using PFNGLUNMAPNAMEDBUFFERPROC = GLboolean(GL_CALL*)(GLuint buffer);
export extern PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer;
PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer = nullptr;

export using PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC = void (GL_CALL*)(GLuint buffer, GLintptr offset, GLsizeiptr length);
export extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glFlushMappedNamedBufferRange;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glFlushMappedNamedBufferRange = nullptr;

export using PFNGLGETNAMEDBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLuint buffer, GLenum pname, GLint* params);
export extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC glGetNamedBufferParameteriv;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC glGetNamedBufferParameteriv = nullptr;

export using PFNGLGETNAMEDBUFFERPARAMETERI64VPROC = void (GL_CALL*)(GLuint buffer, GLenum pname, GLint64* params);
export extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glGetNamedBufferParameteri64v;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glGetNamedBufferParameteri64v = nullptr;

export using PFNGLGETNAMEDBUFFERPOINTERVPROC = void (GL_CALL*)(GLuint buffer, GLenum pname, void** params);
export extern PFNGLGETNAMEDBUFFERPOINTERVPROC glGetNamedBufferPointerv;
PFNGLGETNAMEDBUFFERPOINTERVPROC glGetNamedBufferPointerv = nullptr;

export using PFNGLGETNAMEDBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data);
export extern PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData;
PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData = nullptr;

export using PFNGLCREATEFRAMEBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* framebuffers);
export extern PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers;
PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers = nullptr;

export using PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC = void (GL_CALL*)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
export extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glNamedFramebufferRenderbuffer;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glNamedFramebufferRenderbuffer = nullptr;

export using PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC = void (GL_CALL*)(GLuint framebuffer, GLenum pname, GLint param);
export extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glNamedFramebufferParameteri;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glNamedFramebufferParameteri = nullptr;

export using PFNGLNAMEDFRAMEBUFFERTEXTUREPROC = void (GL_CALL*)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
export extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture = nullptr;

export using PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC = void (GL_CALL*)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
export extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glNamedFramebufferTextureLayer;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glNamedFramebufferTextureLayer = nullptr;

export using PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC = void (GL_CALL*)(GLuint framebuffer, GLenum buf);
export extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glNamedFramebufferDrawBuffer;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glNamedFramebufferDrawBuffer = nullptr;

export using PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC = void (GL_CALL*)(GLuint framebuffer, GLsizei n, const GLenum* bufs);
export extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glNamedFramebufferDrawBuffers;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glNamedFramebufferDrawBuffers = nullptr;

export using PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC = void (GL_CALL*)(GLuint framebuffer, GLenum src);
export extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer = nullptr;

export using PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC = void (GL_CALL*)(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments);
export extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glInvalidateNamedFramebufferData;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glInvalidateNamedFramebufferData = nullptr;

export using PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC = void (GL_CALL*)(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glInvalidateNamedFramebufferSubData;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glInvalidateNamedFramebufferSubData = nullptr;

export using PFNGLCLEARNAMEDFRAMEBUFFERIVPROC = void (GL_CALL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value);
export extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glClearNamedFramebufferiv;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glClearNamedFramebufferiv = nullptr;

export using PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC = void (GL_CALL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value);
export extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glClearNamedFramebufferuiv;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glClearNamedFramebufferuiv = nullptr;

export using PFNGLCLEARNAMEDFRAMEBUFFERFVPROC = void (GL_CALL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value);
export extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv = nullptr;

export using PFNGLCLEARNAMEDFRAMEBUFFERFIPROC = void (GL_CALL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
export extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glClearNamedFramebufferfi;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glClearNamedFramebufferfi = nullptr;

export using PFNGLBLITNAMEDFRAMEBUFFERPROC = void (GL_CALL*)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
export extern PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer;
PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer = nullptr;

export using PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC = GLenum(GL_CALL*)(GLuint framebuffer, GLenum target);
export extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glCheckNamedFramebufferStatus;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glCheckNamedFramebufferStatus = nullptr;

export using PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLuint framebuffer, GLenum pname, GLint* param);
export extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glGetNamedFramebufferParameteriv;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glGetNamedFramebufferParameteriv = nullptr;

export using PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC = void (GL_CALL*)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params);
export extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetNamedFramebufferAttachmentParameteriv;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetNamedFramebufferAttachmentParameteriv = nullptr;

export using PFNGLCREATERENDERBUFFERSPROC = void (GL_CALL*)(GLsizei n, GLuint* renderbuffers);
export extern PFNGLCREATERENDERBUFFERSPROC glCreateRenderbuffers;
PFNGLCREATERENDERBUFFERSPROC glCreateRenderbuffers = nullptr;

export using PFNGLNAMEDRENDERBUFFERSTORAGEPROC = void (GL_CALL*)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorage;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorage = nullptr;

export using PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC = void (GL_CALL*)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glNamedRenderbufferStorageMultisample;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glNamedRenderbufferStorageMultisample = nullptr;

export using PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC = void (GL_CALL*)(GLuint renderbuffer, GLenum pname, GLint* params);
export extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glGetNamedRenderbufferParameteriv;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glGetNamedRenderbufferParameteriv = nullptr;

export using PFNGLCREATETEXTURESPROC = void (GL_CALL*)(GLenum target, GLsizei n, GLuint* textures);
export extern PFNGLCREATETEXTURESPROC glCreateTextures;
PFNGLCREATETEXTURESPROC glCreateTextures = nullptr;

export using PFNGLTEXTUREBUFFERPROC = void (GL_CALL*)(GLuint texture, GLenum internalformat, GLuint buffer);
export extern PFNGLTEXTUREBUFFERPROC glTextureBuffer;
PFNGLTEXTUREBUFFERPROC glTextureBuffer = nullptr;

export using PFNGLTEXTUREBUFFERRANGEPROC = void (GL_CALL*)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
export extern PFNGLTEXTUREBUFFERRANGEPROC glTextureBufferRange;
PFNGLTEXTUREBUFFERRANGEPROC glTextureBufferRange = nullptr;

export using PFNGLTEXTURESTORAGE1DPROC = void (GL_CALL*)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
export extern PFNGLTEXTURESTORAGE1DPROC glTextureStorage1D;
PFNGLTEXTURESTORAGE1DPROC glTextureStorage1D = nullptr;

export using PFNGLTEXTURESTORAGE2DPROC = void (GL_CALL*)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
export extern PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D;
PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D = nullptr;

export using PFNGLTEXTURESTORAGE3DPROC = void (GL_CALL*)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
export extern PFNGLTEXTURESTORAGE3DPROC glTextureStorage3D;
PFNGLTEXTURESTORAGE3DPROC glTextureStorage3D = nullptr;

export using PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC = void (GL_CALL*)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
export extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample = nullptr;

export using PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC = void (GL_CALL*)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
export extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glTextureStorage3DMultisample;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glTextureStorage3DMultisample = nullptr;

export using PFNGLTEXTURESUBIMAGE1DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXTURESUBIMAGE1DPROC glTextureSubImage1D;
PFNGLTEXTURESUBIMAGE1DPROC glTextureSubImage1D = nullptr;

export using PFNGLTEXTURESUBIMAGE2DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D;
PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = nullptr;

export using PFNGLTEXTURESUBIMAGE3DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
export extern PFNGLTEXTURESUBIMAGE3DPROC glTextureSubImage3D;
PFNGLTEXTURESUBIMAGE3DPROC glTextureSubImage3D = nullptr;

export using PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glCompressedTextureSubImage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glCompressedTextureSubImage1D = nullptr;

export using PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glCompressedTextureSubImage2D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glCompressedTextureSubImage2D = nullptr;

export using PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
export extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glCompressedTextureSubImage3D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glCompressedTextureSubImage3D = nullptr;

export using PFNGLCOPYTEXTURESUBIMAGE1DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
export extern PFNGLCOPYTEXTURESUBIMAGE1DPROC glCopyTextureSubImage1D;
PFNGLCOPYTEXTURESUBIMAGE1DPROC glCopyTextureSubImage1D = nullptr;

export using PFNGLCOPYTEXTURESUBIMAGE2DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLCOPYTEXTURESUBIMAGE2DPROC glCopyTextureSubImage2D;
PFNGLCOPYTEXTURESUBIMAGE2DPROC glCopyTextureSubImage2D = nullptr;

export using PFNGLCOPYTEXTURESUBIMAGE3DPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
export extern PFNGLCOPYTEXTURESUBIMAGE3DPROC glCopyTextureSubImage3D;
PFNGLCOPYTEXTURESUBIMAGE3DPROC glCopyTextureSubImage3D = nullptr;

export using PFNGLTEXTUREPARAMETERFPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLfloat param);
export extern PFNGLTEXTUREPARAMETERFPROC glTextureParameterf;
PFNGLTEXTUREPARAMETERFPROC glTextureParameterf = nullptr;

export using PFNGLTEXTUREPARAMETERFVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, const GLfloat* param);
export extern PFNGLTEXTUREPARAMETERFVPROC glTextureParameterfv;
PFNGLTEXTUREPARAMETERFVPROC glTextureParameterfv = nullptr;

export using PFNGLTEXTUREPARAMETERIPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLint param);
export extern PFNGLTEXTUREPARAMETERIPROC glTextureParameteri;
PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = nullptr;

export using PFNGLTEXTUREPARAMETERIIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, const GLint* params);
export extern PFNGLTEXTUREPARAMETERIIVPROC glTextureParameterIiv;
PFNGLTEXTUREPARAMETERIIVPROC glTextureParameterIiv = nullptr;

export using PFNGLTEXTUREPARAMETERIUIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, const GLuint* params);
export extern PFNGLTEXTUREPARAMETERIUIVPROC glTextureParameterIuiv;
PFNGLTEXTUREPARAMETERIUIVPROC glTextureParameterIuiv = nullptr;

export using PFNGLTEXTUREPARAMETERIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, const GLint* param);
export extern PFNGLTEXTUREPARAMETERIVPROC glTextureParameteriv;
PFNGLTEXTUREPARAMETERIVPROC glTextureParameteriv = nullptr;

export using PFNGLGENERATETEXTUREMIPMAPPROC = void (GL_CALL*)(GLuint texture);
export extern PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap;
PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap = nullptr;

export using PFNGLBINDTEXTUREUNITPROC = void (GL_CALL*)(GLuint unit, GLuint texture);
export extern PFNGLBINDTEXTUREUNITPROC glBindTextureUnit;
PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = nullptr;

export using PFNGLGETTEXTUREIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
export extern PFNGLGETTEXTUREIMAGEPROC glGetTextureImage;
PFNGLGETTEXTUREIMAGEPROC glGetTextureImage = nullptr;

export using PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLsizei bufSize, void* pixels);
export extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glGetCompressedTextureImage;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glGetCompressedTextureImage = nullptr;

export using PFNGLGETTEXTURELEVELPARAMETERFVPROC = void (GL_CALL*)(GLuint texture, GLint level, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXTURELEVELPARAMETERFVPROC glGetTextureLevelParameterfv;
PFNGLGETTEXTURELEVELPARAMETERFVPROC glGetTextureLevelParameterfv = nullptr;

export using PFNGLGETTEXTURELEVELPARAMETERIVPROC = void (GL_CALL*)(GLuint texture, GLint level, GLenum pname, GLint* params);
export extern PFNGLGETTEXTURELEVELPARAMETERIVPROC glGetTextureLevelParameteriv;
PFNGLGETTEXTURELEVELPARAMETERIVPROC glGetTextureLevelParameteriv = nullptr;

export using PFNGLGETTEXTUREPARAMETERFVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLfloat* params);
export extern PFNGLGETTEXTUREPARAMETERFVPROC glGetTextureParameterfv;
PFNGLGETTEXTUREPARAMETERFVPROC glGetTextureParameterfv = nullptr;

export using PFNGLGETTEXTUREPARAMETERIIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLint* params);
export extern PFNGLGETTEXTUREPARAMETERIIVPROC glGetTextureParameterIiv;
PFNGLGETTEXTUREPARAMETERIIVPROC glGetTextureParameterIiv = nullptr;

export using PFNGLGETTEXTUREPARAMETERIUIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLuint* params);
export extern PFNGLGETTEXTUREPARAMETERIUIVPROC glGetTextureParameterIuiv;
PFNGLGETTEXTUREPARAMETERIUIVPROC glGetTextureParameterIuiv = nullptr;

export using PFNGLGETTEXTUREPARAMETERIVPROC = void (GL_CALL*)(GLuint texture, GLenum pname, GLint* params);
export extern PFNGLGETTEXTUREPARAMETERIVPROC glGetTextureParameteriv;
PFNGLGETTEXTUREPARAMETERIVPROC glGetTextureParameteriv = nullptr;

export using PFNGLCREATEVERTEXARRAYSPROC = void (GL_CALL*)(GLsizei n, GLuint* arrays);
export extern PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays;
PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = nullptr;

export using PFNGLDISABLEVERTEXARRAYATTRIBPROC = void (GL_CALL*)(GLuint vaobj, GLuint index);
export extern PFNGLDISABLEVERTEXARRAYATTRIBPROC glDisableVertexArrayAttrib;
PFNGLDISABLEVERTEXARRAYATTRIBPROC glDisableVertexArrayAttrib = nullptr;

export using PFNGLENABLEVERTEXARRAYATTRIBPROC = void (GL_CALL*)(GLuint vaobj, GLuint index);
export extern PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib;
PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = nullptr;

export using PFNGLVERTEXARRAYELEMENTBUFFERPROC = void (GL_CALL*)(GLuint vaobj, GLuint buffer);
export extern PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer;
PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = nullptr;

export using PFNGLVERTEXARRAYVERTEXBUFFERPROC = void (GL_CALL*)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
export extern PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = nullptr;

export using PFNGLVERTEXARRAYVERTEXBUFFERSPROC = void (GL_CALL*)(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides);
export extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC glVertexArrayVertexBuffers;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC glVertexArrayVertexBuffers = nullptr;

export using PFNGLVERTEXARRAYATTRIBBINDINGPROC = void (GL_CALL*)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
export extern PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding;
PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = nullptr;

export using PFNGLVERTEXARRAYATTRIBFORMATPROC = void (GL_CALL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
export extern PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat;
PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = nullptr;

export using PFNGLVERTEXARRAYATTRIBIFORMATPROC = void (GL_CALL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
export extern PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat;
PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat = nullptr;

export using PFNGLVERTEXARRAYATTRIBLFORMATPROC = void (GL_CALL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
export extern PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat;
PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat = nullptr;

export using PFNGLVERTEXARRAYBINDINGDIVISORPROC = void (GL_CALL*)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
export extern PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor;
PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor = nullptr;

export using PFNGLGETVERTEXARRAYIVPROC = void (GL_CALL*)(GLuint vaobj, GLenum pname, GLint* param);
export extern PFNGLGETVERTEXARRAYIVPROC glGetVertexArrayiv;
PFNGLGETVERTEXARRAYIVPROC glGetVertexArrayiv = nullptr;

export using PFNGLGETVERTEXARRAYINDEXEDIVPROC = void (GL_CALL*)(GLuint vaobj, GLuint index, GLenum pname, GLint* param);
export extern PFNGLGETVERTEXARRAYINDEXEDIVPROC glGetVertexArrayIndexediv;
PFNGLGETVERTEXARRAYINDEXEDIVPROC glGetVertexArrayIndexediv = nullptr;

export using PFNGLGETVERTEXARRAYINDEXED64IVPROC = void (GL_CALL*)(GLuint vaobj, GLuint index, GLenum pname, GLint64* param);
export extern PFNGLGETVERTEXARRAYINDEXED64IVPROC glGetVertexArrayIndexed64iv;
PFNGLGETVERTEXARRAYINDEXED64IVPROC glGetVertexArrayIndexed64iv = nullptr;

export using PFNGLCREATESAMPLERSPROC = void (GL_CALL*)(GLsizei n, GLuint* samplers);
export extern PFNGLCREATESAMPLERSPROC glCreateSamplers;
PFNGLCREATESAMPLERSPROC glCreateSamplers = nullptr;

export using PFNGLCREATEPROGRAMPIPELINESPROC = void (GL_CALL*)(GLsizei n, GLuint* pipelines);
export extern PFNGLCREATEPROGRAMPIPELINESPROC glCreateProgramPipelines;
PFNGLCREATEPROGRAMPIPELINESPROC glCreateProgramPipelines = nullptr;

export using PFNGLCREATEQUERIESPROC = void (GL_CALL*)(GLenum target, GLsizei n, GLuint* ids);
export extern PFNGLCREATEQUERIESPROC glCreateQueries;
PFNGLCREATEQUERIESPROC glCreateQueries = nullptr;

export using PFNGLGETQUERYBUFFEROBJECTI64VPROC = void (GL_CALL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
export extern PFNGLGETQUERYBUFFEROBJECTI64VPROC glGetQueryBufferObjecti64v;
PFNGLGETQUERYBUFFEROBJECTI64VPROC glGetQueryBufferObjecti64v = nullptr;

export using PFNGLGETQUERYBUFFEROBJECTIVPROC = void (GL_CALL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
export extern PFNGLGETQUERYBUFFEROBJECTIVPROC glGetQueryBufferObjectiv;
PFNGLGETQUERYBUFFEROBJECTIVPROC glGetQueryBufferObjectiv = nullptr;

export using PFNGLGETQUERYBUFFEROBJECTUI64VPROC = void (GL_CALL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
export extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC glGetQueryBufferObjectui64v;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC glGetQueryBufferObjectui64v = nullptr;

export using PFNGLGETQUERYBUFFEROBJECTUIVPROC = void (GL_CALL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
export extern PFNGLGETQUERYBUFFEROBJECTUIVPROC glGetQueryBufferObjectuiv;
PFNGLGETQUERYBUFFEROBJECTUIVPROC glGetQueryBufferObjectuiv = nullptr;

export using PFNGLMEMORYBARRIERBYREGIONPROC = void (GL_CALL*)(GLbitfield barriers);
export extern PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegion;
PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegion = nullptr;

export using PFNGLGETTEXTURESUBIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
export extern PFNGLGETTEXTURESUBIMAGEPROC glGetTextureSubImage;
PFNGLGETTEXTURESUBIMAGEPROC glGetTextureSubImage = nullptr;

export using PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC = void (GL_CALL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels);
export extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glGetCompressedTextureSubImage;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glGetCompressedTextureSubImage = nullptr;

export using PFNGLGETGRAPHICSRESETSTATUSPROC = GLenum(GL_CALL*)();
export extern PFNGLGETGRAPHICSRESETSTATUSPROC glGetGraphicsResetStatus;
PFNGLGETGRAPHICSRESETSTATUSPROC glGetGraphicsResetStatus = nullptr;

export using PFNGLGETNCOMPRESSEDTEXIMAGEPROC = void (GL_CALL*)(GLenum target, GLint lod, GLsizei bufSize, void* pixels);
export extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC glGetnCompressedTexImage;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC glGetnCompressedTexImage = nullptr;

export using PFNGLGETNTEXIMAGEPROC = void (GL_CALL*)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
export extern PFNGLGETNTEXIMAGEPROC glGetnTexImage;
PFNGLGETNTEXIMAGEPROC glGetnTexImage = nullptr;

export using PFNGLGETNUNIFORMDVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei bufSize, GLdouble* params);
export extern PFNGLGETNUNIFORMDVPROC glGetnUniformdv;
PFNGLGETNUNIFORMDVPROC glGetnUniformdv = nullptr;

export using PFNGLGETNUNIFORMFVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei bufSize, GLfloat* params);
export extern PFNGLGETNUNIFORMFVPROC glGetnUniformfv;
PFNGLGETNUNIFORMFVPROC glGetnUniformfv = nullptr;

export using PFNGLGETNUNIFORMIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei bufSize, GLint* params);
export extern PFNGLGETNUNIFORMIVPROC glGetnUniformiv;
PFNGLGETNUNIFORMIVPROC glGetnUniformiv = nullptr;

export using PFNGLGETNUNIFORMUIVPROC = void (GL_CALL*)(GLuint program, GLint location, GLsizei bufSize, GLuint* params);
export extern PFNGLGETNUNIFORMUIVPROC glGetnUniformuiv;
PFNGLGETNUNIFORMUIVPROC glGetnUniformuiv = nullptr;

export using PFNGLREADNPIXELSPROC = void (GL_CALL*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data);
export extern PFNGLREADNPIXELSPROC glReadnPixels;
PFNGLREADNPIXELSPROC glReadnPixels = nullptr;

export using PFNGLGETNMAPDVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLsizei bufSize, GLdouble* v);
export extern PFNGLGETNMAPDVPROC glGetnMapdv;
PFNGLGETNMAPDVPROC glGetnMapdv = nullptr;

export using PFNGLGETNMAPFVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLsizei bufSize, GLfloat* v);
export extern PFNGLGETNMAPFVPROC glGetnMapfv;
PFNGLGETNMAPFVPROC glGetnMapfv = nullptr;

export using PFNGLGETNMAPIVPROC = void (GL_CALL*)(GLenum target, GLenum query, GLsizei bufSize, GLint* v);
export extern PFNGLGETNMAPIVPROC glGetnMapiv;
PFNGLGETNMAPIVPROC glGetnMapiv = nullptr;

export using PFNGLGETNPIXELMAPFVPROC = void (GL_CALL*)(GLenum map, GLsizei bufSize, GLfloat* values);
export extern PFNGLGETNPIXELMAPFVPROC glGetnPixelMapfv;
PFNGLGETNPIXELMAPFVPROC glGetnPixelMapfv = nullptr;

export using PFNGLGETNPIXELMAPUIVPROC = void (GL_CALL*)(GLenum map, GLsizei bufSize, GLuint* values);
export extern PFNGLGETNPIXELMAPUIVPROC glGetnPixelMapuiv;
PFNGLGETNPIXELMAPUIVPROC glGetnPixelMapuiv = nullptr;

export using PFNGLGETNPIXELMAPUSVPROC = void (GL_CALL*)(GLenum map, GLsizei bufSize, GLushort* values);
export extern PFNGLGETNPIXELMAPUSVPROC glGetnPixelMapusv;
PFNGLGETNPIXELMAPUSVPROC glGetnPixelMapusv = nullptr;

export using PFNGLGETNPOLYGONSTIPPLEPROC = void (GL_CALL*)(GLsizei bufSize, GLubyte* pattern);
export extern PFNGLGETNPOLYGONSTIPPLEPROC glGetnPolygonStipple;
PFNGLGETNPOLYGONSTIPPLEPROC glGetnPolygonStipple = nullptr;

export using PFNGLGETNCOLORTABLEPROC = void (GL_CALL*)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* table);
export extern PFNGLGETNCOLORTABLEPROC glGetnColorTable;
PFNGLGETNCOLORTABLEPROC glGetnColorTable = nullptr;

export using PFNGLGETNCONVOLUTIONFILTERPROC = void (GL_CALL*)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void* image);
export extern PFNGLGETNCONVOLUTIONFILTERPROC glGetnConvolutionFilter;
PFNGLGETNCONVOLUTIONFILTERPROC glGetnConvolutionFilter = nullptr;

export using PFNGLGETNSEPARABLEFILTERPROC = void (GL_CALL*)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void* row, GLsizei columnBufSize, void* column, void* span);
export extern PFNGLGETNSEPARABLEFILTERPROC glGetnSeparableFilter;
PFNGLGETNSEPARABLEFILTERPROC glGetnSeparableFilter = nullptr;

export using PFNGLGETNHISTOGRAMPROC = void (GL_CALL*)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values);
export extern PFNGLGETNHISTOGRAMPROC glGetnHistogram;
PFNGLGETNHISTOGRAMPROC glGetnHistogram = nullptr;

export using PFNGLGETNMINMAXPROC = void (GL_CALL*)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void* values);
export extern PFNGLGETNMINMAXPROC glGetnMinmax;
PFNGLGETNMINMAXPROC glGetnMinmax = nullptr;

export using PFNGLTEXTUREBARRIERPROC = void (GL_CALL*)();
export extern PFNGLTEXTUREBARRIERPROC glTextureBarrier;
PFNGLTEXTUREBARRIERPROC glTextureBarrier = nullptr;

// ==================== OpenGL 4.6 Functions ====================

export using PFNGLSPECIALIZESHADERPROC = void (GL_CALL*)(GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue);
export extern PFNGLSPECIALIZESHADERPROC glSpecializeShader;
PFNGLSPECIALIZESHADERPROC glSpecializeShader = nullptr;

export using PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC = void (GL_CALL*)(GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
export extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount = nullptr;

export using PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC = void (GL_CALL*)(GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
export extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount = nullptr;

export using PFNGLPOLYGONOFFSETCLAMPPROC = void (GL_CALL*)(GLfloat factor, GLfloat units, GLfloat clamp);
export extern PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp;
PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp = nullptr;

export class OpenGLLoader 
{
public:
    explicit OpenGLLoader(int major = 1, int minor = 1);
    ~OpenGLLoader() = default;

    OpenGLLoader(const OpenGLLoader&) = delete;
    OpenGLLoader& operator=(const OpenGLLoader&) = delete;
    OpenGLLoader(OpenGLLoader&& other) noexcept = default;
    OpenGLLoader& operator=(OpenGLLoader&& other) noexcept = default;

    [[nodiscard]] bool is_loaded() const noexcept { return m_loaded; }
    [[nodiscard]] std::pair<int, int> version() const noexcept { return { m_major, m_minor }; }

private:
    struct VersionEntry 
    {
        int major;
        int minor;
        void (*loader)(OpenGLLoader*);
    };

    void load_functions(int major, int minor);
    static void* get_proc_address(const char* name);

    static void load_version_1_0(OpenGLLoader* loader);
    static void load_version_1_1(OpenGLLoader* loader);
    static void load_version_1_2(OpenGLLoader* loader);
    static void load_version_1_3(OpenGLLoader* loader);
    static void load_version_1_4(OpenGLLoader* loader);
    static void load_version_1_5(OpenGLLoader* loader);
    static void load_version_2_0(OpenGLLoader* loader);
    static void load_version_2_1(OpenGLLoader* loader);
    static void load_version_3_0(OpenGLLoader* loader);
    static void load_version_3_1(OpenGLLoader* loader);
    static void load_version_3_2(OpenGLLoader* loader);
    static void load_version_3_3(OpenGLLoader* loader);
    static void load_version_4_0(OpenGLLoader* loader);
    static void load_version_4_1(OpenGLLoader* loader);
    static void load_version_4_2(OpenGLLoader* loader);
    static void load_version_4_3(OpenGLLoader* loader);
    static void load_version_4_4(OpenGLLoader* loader);
    static void load_version_4_5(OpenGLLoader* loader);
    static void load_version_4_6(OpenGLLoader* loader);

    bool m_loaded{ false };
    int m_major{ 0 };
    int m_minor{ 0 };
};

void* OpenGLLoader::get_proc_address(const char* name) 
{
#ifdef _WIN32
    static HMODULE opengl32 = LoadLibraryW(L"opengl32.dll");
    if (!opengl32) return nullptr;

    auto proc = reinterpret_cast<void*>(GetProcAddress(opengl32, name));

    if (!proc) {
        auto wglGetProcAddress = reinterpret_cast<void* (*)(const char*)>(
            GetProcAddress(opengl32, "wglGetProcAddress")
            );
        if (wglGetProcAddress) {
            proc = wglGetProcAddress(name);
        }
    }

    return proc;
#else

    return nullptr;
#endif
}

OpenGLLoader::OpenGLLoader(int major, int minor) : 
    m_major(major), m_minor(minor) 
{
    load_functions(major, minor);
}

void OpenGLLoader::load_functions(int major, int minor) 
{
    const VersionEntry versions[] =
    {
        {1, 0, load_version_1_0},
        {1, 1, load_version_1_1},
        {1, 2, load_version_1_2},
        {1, 3, load_version_1_3},
        {1, 4, load_version_1_4},
        {1, 5, load_version_1_5},
        {2, 0, load_version_2_0},
        {2, 1, load_version_2_1},
        {3, 0, load_version_3_0},
        {3, 1, load_version_3_1},
        {3, 2, load_version_3_2},
        {3, 3, load_version_3_3},
        {4, 0, load_version_4_0},
        {4, 1, load_version_4_1},
        {4, 2, load_version_4_2},
        {4, 3, load_version_4_3},
        {4, 4, load_version_4_4},
        {4, 5, load_version_4_5},
        {4, 6, load_version_4_6},
        {0, 0, nullptr}
    };

    for (const auto& entry : versions) 
    {
        if (entry.loader == nullptr) break;

        if ((entry.major < major) || (entry.major == major && entry.minor <= minor))
        {
            entry.loader(this);
        }
    }

    m_loaded = true;
}

// ==================== OpenGL 1.0 Functions ====================

void OpenGLLoader::load_version_1_0(OpenGLLoader* loader)
{
    glCullFace = reinterpret_cast<PFNGLCULLFACEPROC>(get_proc_address("glCullFace"));
    glFrontFace = reinterpret_cast<PFNGLFRONTFACEPROC>(get_proc_address("glFrontFace"));
    glHint = reinterpret_cast<PFNGLHINTPROC>(get_proc_address("glHint"));
    glLineWidth = reinterpret_cast<PFNGLLINEWIDTHPROC>(get_proc_address("glLineWidth"));
    glPointSize = reinterpret_cast<PFNGLPOINTSIZEPROC>(get_proc_address("glPointSize"));
    glPolygonMode = reinterpret_cast<PFNGLPOLYGONMODEPROC>(get_proc_address("glPolygonMode"));
    glScissor = reinterpret_cast<PFNGLSCISSORPROC>(get_proc_address("glScissor"));
    glTexParameterf = reinterpret_cast<PFNGLTEXPARAMETERFPROC>(get_proc_address("glTexParameterf"));
    glTexParameterfv = reinterpret_cast<PFNGLTEXPARAMETERFVPROC>(get_proc_address("glTexParameterfv"));
    glTexParameteri = reinterpret_cast<PFNGLTEXPARAMETERIPROC>(get_proc_address("glTexParameteri"));
    glTexParameteriv = reinterpret_cast<PFNGLTEXPARAMETERIVPROC>(get_proc_address("glTexParameteriv"));
    glTexImage1D = reinterpret_cast<PFNGLTEXIMAGE1DPROC>(get_proc_address("glTexImage1D"));
    glTexImage2D = reinterpret_cast<PFNGLTEXIMAGE2DPROC>(get_proc_address("glTexImage2D"));
    glDrawBuffer = reinterpret_cast<PFNGLDRAWBUFFERPROC>(get_proc_address("glDrawBuffer"));
    glClear = reinterpret_cast<PFNGLCLEARPROC>(get_proc_address("glClear"));
    glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(get_proc_address("glClearColor"));
    glClearStencil = reinterpret_cast<PFNGLCLEARSTENCILPROC>(get_proc_address("glClearStencil"));
    glClearDepth = reinterpret_cast<PFNGLCLEARDEPTHPROC>(get_proc_address("glClearDepth"));
    glStencilMask = reinterpret_cast<PFNGLSTENCILMASKPROC>(get_proc_address("glStencilMask"));
    glColorMask = reinterpret_cast<PFNGLCOLORMASKPROC>(get_proc_address("glColorMask"));
    glDepthMask = reinterpret_cast<PFNGLDEPTHMASKPROC>(get_proc_address("glDepthMask"));
    glDisable = reinterpret_cast<PFNGLDISABLEPROC>(get_proc_address("glDisable"));
    glEnable = reinterpret_cast<PFNGLENABLEPROC>(get_proc_address("glEnable"));
    glFinish = reinterpret_cast<PFNGLFINISHPROC>(get_proc_address("glFinish"));
    glFlush = reinterpret_cast<PFNGLFLUSHPROC>(get_proc_address("glFlush"));
    glBlendFunc = reinterpret_cast<PFNGLBLENDFUNCPROC>(get_proc_address("glBlendFunc"));
    glLogicOp = reinterpret_cast<PFNGLLOGICOPPROC>(get_proc_address("glLogicOp"));
    glStencilFunc = reinterpret_cast<PFNGLSTENCILFUNCPROC>(get_proc_address("glStencilFunc"));
    glStencilOp = reinterpret_cast<PFNGLSTENCILOPPROC>(get_proc_address("glStencilOp"));
    glDepthFunc = reinterpret_cast<PFNGLDEPTHFUNCPROC>(get_proc_address("glDepthFunc"));
    glPixelStoref = reinterpret_cast<PFNGLPIXELSTOREFPROC>(get_proc_address("glPixelStoref"));
    glPixelStorei = reinterpret_cast<PFNGLPIXELSTOREIPROC>(get_proc_address("glPixelStorei"));
    glReadBuffer = reinterpret_cast<PFNGLREADBUFFERPROC>(get_proc_address("glReadBuffer"));
    glReadPixels = reinterpret_cast<PFNGLREADPIXELSPROC>(get_proc_address("glReadPixels"));
    glGetBooleanv = reinterpret_cast<PFNGLGETBOOLEANVPROC>(get_proc_address("glGetBooleanv"));
    glGetDoublev = reinterpret_cast<PFNGLGETDOUBLEVPROC>(get_proc_address("glGetDoublev"));
    glGetError = reinterpret_cast<PFNGLGETERRORPROC>(get_proc_address("glGetError"));
    glGetFloatv = reinterpret_cast<PFNGLGETFLOATVPROC>(get_proc_address("glGetFloatv"));
    glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(get_proc_address("glGetIntegerv"));
    glGetString = reinterpret_cast<PFNGLGETSTRINGPROC>(get_proc_address("glGetString"));
    glGetTexImage = reinterpret_cast<PFNGLGETTEXIMAGEPROC>(get_proc_address("glGetTexImage"));
    glGetTexParameterfv = reinterpret_cast<PFNGLGETTEXPARAMETERFVPROC>(get_proc_address("glGetTexParameterfv"));
    glGetTexParameteriv = reinterpret_cast<PFNGLGETTEXPARAMETERIVPROC>(get_proc_address("glGetTexParameteriv"));
    glGetTexLevelParameterfv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERFVPROC>(get_proc_address("glGetTexLevelParameterfv"));
    glGetTexLevelParameteriv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>(get_proc_address("glGetTexLevelParameteriv"));
    glIsEnabled = reinterpret_cast<PFNGLISENABLEDPROC>(get_proc_address("glIsEnabled"));
    glDepthRange = reinterpret_cast<PFNGLDEPTHRANGEPROC>(get_proc_address("glDepthRange"));
    glViewport = reinterpret_cast<PFNGLVIEWPORTPROC>(get_proc_address("glViewport"));
    glNewList = reinterpret_cast<PFNGLNEWLISTPROC>(get_proc_address("glNewList"));
    glEndList = reinterpret_cast<PFNGLENDLISTPROC>(get_proc_address("glEndList"));
    glCallList = reinterpret_cast<PFNGLCALLLISTPROC>(get_proc_address("glCallList"));
    glCallLists = reinterpret_cast<PFNGLCALLLISTSPROC>(get_proc_address("glCallLists"));
    glDeleteLists = reinterpret_cast<PFNGLDELETELISTSPROC>(get_proc_address("glDeleteLists"));
    glGenLists = reinterpret_cast<PFNGLGENLISTSPROC>(get_proc_address("glGenLists"));
    glListBase = reinterpret_cast<PFNGLLISTBASEPROC>(get_proc_address("glListBase"));
    glBegin = reinterpret_cast<PFNGLBEGINPROC>(get_proc_address("glBegin"));
    glBitmap = reinterpret_cast<PFNGLBITMAPPROC>(get_proc_address("glBitmap"));
    glColor3b = reinterpret_cast<PFNGLCOLOR3BPROC>(get_proc_address("glColor3b"));
    glColor3bv = reinterpret_cast<PFNGLCOLOR3BVPROC>(get_proc_address("glColor3bv"));
    glColor3d = reinterpret_cast<PFNGLCOLOR3DPROC>(get_proc_address("glColor3d"));
    glColor3dv = reinterpret_cast<PFNGLCOLOR3DVPROC>(get_proc_address("glColor3dv"));
    glColor3f = reinterpret_cast<PFNGLCOLOR3FPROC>(get_proc_address("glColor3f"));
    glColor3fv = reinterpret_cast<PFNGLCOLOR3FVPROC>(get_proc_address("glColor3fv"));
    glColor3i = reinterpret_cast<PFNGLCOLOR3IPROC>(get_proc_address("glColor3i"));
    glColor3iv = reinterpret_cast<PFNGLCOLOR3IVPROC>(get_proc_address("glColor3iv"));
    glColor3s = reinterpret_cast<PFNGLCOLOR3SPROC>(get_proc_address("glColor3s"));
    glColor3sv = reinterpret_cast<PFNGLCOLOR3SVPROC>(get_proc_address("glColor3sv"));
    glColor3ub = reinterpret_cast<PFNGLCOLOR3UBPROC>(get_proc_address("glColor3ub"));
    glColor3ubv = reinterpret_cast<PFNGLCOLOR3UBVPROC>(get_proc_address("glColor3ubv"));
    glColor3ui = reinterpret_cast<PFNGLCOLOR3UIPROC>(get_proc_address("glColor3ui"));
    glColor3uiv = reinterpret_cast<PFNGLCOLOR3UIVPROC>(get_proc_address("glColor3uiv"));
    glColor3us = reinterpret_cast<PFNGLCOLOR3USPROC>(get_proc_address("glColor3us"));
    glColor3usv = reinterpret_cast<PFNGLCOLOR3USVPROC>(get_proc_address("glColor3usv"));
    glColor4b = reinterpret_cast<PFNGLCOLOR4BPROC>(get_proc_address("glColor4b"));
    glColor4bv = reinterpret_cast<PFNGLCOLOR4BVPROC>(get_proc_address("glColor4bv"));
    glColor4d = reinterpret_cast<PFNGLCOLOR4DPROC>(get_proc_address("glColor4d"));
    glColor4dv = reinterpret_cast<PFNGLCOLOR4DVPROC>(get_proc_address("glColor4dv"));
    glColor4f = reinterpret_cast<PFNGLCOLOR4FPROC>(get_proc_address("glColor4f"));
    glColor4fv = reinterpret_cast<PFNGLCOLOR4FVPROC>(get_proc_address("glColor4fv"));
    glColor4i = reinterpret_cast<PFNGLCOLOR4IPROC>(get_proc_address("glColor4i"));
    glColor4iv = reinterpret_cast<PFNGLCOLOR4IVPROC>(get_proc_address("glColor4iv"));
    glColor4s = reinterpret_cast<PFNGLCOLOR4SPROC>(get_proc_address("glColor4s"));
    glColor4sv = reinterpret_cast<PFNGLCOLOR4SVPROC>(get_proc_address("glColor4sv"));
    glColor4ub = reinterpret_cast<PFNGLCOLOR4UBPROC>(get_proc_address("glColor4ub"));
    glColor4ubv = reinterpret_cast<PFNGLCOLOR4UBVPROC>(get_proc_address("glColor4ubv"));
    glColor4ui = reinterpret_cast<PFNGLCOLOR4UIPROC>(get_proc_address("glColor4ui"));
    glColor4uiv = reinterpret_cast<PFNGLCOLOR4UIVPROC>(get_proc_address("glColor4uiv"));
    glColor4us = reinterpret_cast<PFNGLCOLOR4USPROC>(get_proc_address("glColor4us"));
    glColor4usv = reinterpret_cast<PFNGLCOLOR4USVPROC>(get_proc_address("glColor4usv"));
    glEdgeFlag = reinterpret_cast<PFNGLEDGEFLAGPROC>(get_proc_address("glEdgeFlag"));
    glEdgeFlagv = reinterpret_cast<PFNGLEDGEFLAGVPROC>(get_proc_address("glEdgeFlagv"));
    glEnd = reinterpret_cast<PFNGLENDPROC>(get_proc_address("glEnd"));
    glIndexd = reinterpret_cast<PFNGLINDEXDPROC>(get_proc_address("glIndexd"));
    glIndexdv = reinterpret_cast<PFNGLINDEXDVPROC>(get_proc_address("glIndexdv"));
    glIndexf = reinterpret_cast<PFNGLINDEXFPROC>(get_proc_address("glIndexf"));
    glIndexfv = reinterpret_cast<PFNGLINDEXFVPROC>(get_proc_address("glIndexfv"));
    glIndexi = reinterpret_cast<PFNGLINDEXIPROC>(get_proc_address("glIndexi"));
    glIndexiv = reinterpret_cast<PFNGLINDEXIVPROC>(get_proc_address("glIndexiv"));
    glIndexs = reinterpret_cast<PFNGLINDEXSPROC>(get_proc_address("glIndexs"));
    glIndexsv = reinterpret_cast<PFNGLINDEXSVPROC>(get_proc_address("glIndexsv"));
    glNormal3b = reinterpret_cast<PFNGLNORMAL3BPROC>(get_proc_address("glNormal3b"));
    glNormal3bv = reinterpret_cast<PFNGLNORMAL3BVPROC>(get_proc_address("glNormal3bv"));
    glNormal3d = reinterpret_cast<PFNGLNORMAL3DPROC>(get_proc_address("glNormal3d"));
    glNormal3dv = reinterpret_cast<PFNGLNORMAL3DVPROC>(get_proc_address("glNormal3dv"));
    glNormal3f = reinterpret_cast<PFNGLNORMAL3FPROC>(get_proc_address("glNormal3f"));
    glNormal3fv = reinterpret_cast<PFNGLNORMAL3FVPROC>(get_proc_address("glNormal3fv"));
    glNormal3i = reinterpret_cast<PFNGLNORMAL3IPROC>(get_proc_address("glNormal3i"));
    glNormal3iv = reinterpret_cast<PFNGLNORMAL3IVPROC>(get_proc_address("glNormal3iv"));
    glNormal3s = reinterpret_cast<PFNGLNORMAL3SPROC>(get_proc_address("glNormal3s"));
    glNormal3sv = reinterpret_cast<PFNGLNORMAL3SVPROC>(get_proc_address("glNormal3sv"));
    glRasterPos2d = reinterpret_cast<PFNGLRASTERPOS2DPROC>(get_proc_address("glRasterPos2d"));
    glRasterPos2dv = reinterpret_cast<PFNGLRASTERPOS2DVPROC>(get_proc_address("glRasterPos2dv"));
    glRasterPos2f = reinterpret_cast<PFNGLRASTERPOS2FPROC>(get_proc_address("glRasterPos2f"));
    glRasterPos2fv = reinterpret_cast<PFNGLRASTERPOS2FVPROC>(get_proc_address("glRasterPos2fv"));
    glRasterPos2i = reinterpret_cast<PFNGLRASTERPOS2IPROC>(get_proc_address("glRasterPos2i"));
    glRasterPos2iv = reinterpret_cast<PFNGLRASTERPOS2IVPROC>(get_proc_address("glRasterPos2iv"));
    glRasterPos2s = reinterpret_cast<PFNGLRASTERPOS2SPROC>(get_proc_address("glRasterPos2s"));
    glRasterPos2sv = reinterpret_cast<PFNGLRASTERPOS2SVPROC>(get_proc_address("glRasterPos2sv"));
    glRasterPos3d = reinterpret_cast<PFNGLRASTERPOS3DPROC>(get_proc_address("glRasterPos3d"));
    glRasterPos3dv = reinterpret_cast<PFNGLRASTERPOS3DVPROC>(get_proc_address("glRasterPos3dv"));
    glRasterPos3f = reinterpret_cast<PFNGLRASTERPOS3FPROC>(get_proc_address("glRasterPos3f"));
    glRasterPos3fv = reinterpret_cast<PFNGLRASTERPOS3FVPROC>(get_proc_address("glRasterPos3fv"));
    glRasterPos3i = reinterpret_cast<PFNGLRASTERPOS3IPROC>(get_proc_address("glRasterPos3i"));
    glRasterPos3iv = reinterpret_cast<PFNGLRASTERPOS3IVPROC>(get_proc_address("glRasterPos3iv"));
    glRasterPos3s = reinterpret_cast<PFNGLRASTERPOS3SPROC>(get_proc_address("glRasterPos3s"));
    glRasterPos3sv = reinterpret_cast<PFNGLRASTERPOS3SVPROC>(get_proc_address("glRasterPos3sv"));
    glRasterPos4d = reinterpret_cast<PFNGLRASTERPOS4DPROC>(get_proc_address("glRasterPos4d"));
    glRasterPos4dv = reinterpret_cast<PFNGLRASTERPOS4DVPROC>(get_proc_address("glRasterPos4dv"));
    glRasterPos4f = reinterpret_cast<PFNGLRASTERPOS4FPROC>(get_proc_address("glRasterPos4f"));
    glRasterPos4fv = reinterpret_cast<PFNGLRASTERPOS4FVPROC>(get_proc_address("glRasterPos4fv"));
    glRasterPos4i = reinterpret_cast<PFNGLRASTERPOS4IPROC>(get_proc_address("glRasterPos4i"));
    glRasterPos4iv = reinterpret_cast<PFNGLRASTERPOS4IVPROC>(get_proc_address("glRasterPos4iv"));
    glRasterPos4s = reinterpret_cast<PFNGLRASTERPOS4SPROC>(get_proc_address("glRasterPos4s"));
    glRasterPos4sv = reinterpret_cast<PFNGLRASTERPOS4SVPROC>(get_proc_address("glRasterPos4sv"));
    glRectd = reinterpret_cast<PFNGLRECTDPROC>(get_proc_address("glRectd"));
    glRectdv = reinterpret_cast<PFNGLRECTDVPROC>(get_proc_address("glRectdv"));
    glRectf = reinterpret_cast<PFNGLRECTFPROC>(get_proc_address("glRectf"));
    glRectfv = reinterpret_cast<PFNGLRECTFVPROC>(get_proc_address("glRectfv"));
    glRecti = reinterpret_cast<PFNGLRECTIPROC>(get_proc_address("glRecti"));
    glRectiv = reinterpret_cast<PFNGLRECTIVPROC>(get_proc_address("glRectiv"));
    glRects = reinterpret_cast<PFNGLRECTSPROC>(get_proc_address("glRects"));
    glRectsv = reinterpret_cast<PFNGLRECTSVPROC>(get_proc_address("glRectsv"));
    glTexCoord1d = reinterpret_cast<PFNGLTEXCOORD1DPROC>(get_proc_address("glTexCoord1d"));
    glTexCoord1dv = reinterpret_cast<PFNGLTEXCOORD1DVPROC>(get_proc_address("glTexCoord1dv"));
    glTexCoord1f = reinterpret_cast<PFNGLTEXCOORD1FPROC>(get_proc_address("glTexCoord1f"));
    glTexCoord1fv = reinterpret_cast<PFNGLTEXCOORD1FVPROC>(get_proc_address("glTexCoord1fv"));
    glTexCoord1i = reinterpret_cast<PFNGLTEXCOORD1IPROC>(get_proc_address("glTexCoord1i"));
    glTexCoord1iv = reinterpret_cast<PFNGLTEXCOORD1IVPROC>(get_proc_address("glTexCoord1iv"));
    glTexCoord1s = reinterpret_cast<PFNGLTEXCOORD1SPROC>(get_proc_address("glTexCoord1s"));
    glTexCoord1sv = reinterpret_cast<PFNGLTEXCOORD1SVPROC>(get_proc_address("glTexCoord1sv"));
    glTexCoord2d = reinterpret_cast<PFNGLTEXCOORD2DPROC>(get_proc_address("glTexCoord2d"));
    glTexCoord2dv = reinterpret_cast<PFNGLTEXCOORD2DVPROC>(get_proc_address("glTexCoord2dv"));
    glTexCoord2f = reinterpret_cast<PFNGLTEXCOORD2FPROC>(get_proc_address("glTexCoord2f"));
    glTexCoord2fv = reinterpret_cast<PFNGLTEXCOORD2FVPROC>(get_proc_address("glTexCoord2fv"));
    glTexCoord2i = reinterpret_cast<PFNGLTEXCOORD2IPROC>(get_proc_address("glTexCoord2i"));
    glTexCoord2iv = reinterpret_cast<PFNGLTEXCOORD2IVPROC>(get_proc_address("glTexCoord2iv"));
    glTexCoord2s = reinterpret_cast<PFNGLTEXCOORD2SPROC>(get_proc_address("glTexCoord2s"));
    glTexCoord2sv = reinterpret_cast<PFNGLTEXCOORD2SVPROC>(get_proc_address("glTexCoord2sv"));
    glTexCoord3d = reinterpret_cast<PFNGLTEXCOORD3DPROC>(get_proc_address("glTexCoord3d"));
    glTexCoord3dv = reinterpret_cast<PFNGLTEXCOORD3DVPROC>(get_proc_address("glTexCoord3dv"));
    glTexCoord3f = reinterpret_cast<PFNGLTEXCOORD3FPROC>(get_proc_address("glTexCoord3f"));
    glTexCoord3fv = reinterpret_cast<PFNGLTEXCOORD3FVPROC>(get_proc_address("glTexCoord3fv"));
    glTexCoord3i = reinterpret_cast<PFNGLTEXCOORD3IPROC>(get_proc_address("glTexCoord3i"));
    glTexCoord3iv = reinterpret_cast<PFNGLTEXCOORD3IVPROC>(get_proc_address("glTexCoord3iv"));
    glTexCoord3s = reinterpret_cast<PFNGLTEXCOORD3SPROC>(get_proc_address("glTexCoord3s"));
    glTexCoord3sv = reinterpret_cast<PFNGLTEXCOORD3SVPROC>(get_proc_address("glTexCoord3sv"));
    glTexCoord4d = reinterpret_cast<PFNGLTEXCOORD4DPROC>(get_proc_address("glTexCoord4d"));
    glTexCoord4dv = reinterpret_cast<PFNGLTEXCOORD4DVPROC>(get_proc_address("glTexCoord4dv"));
    glTexCoord4f = reinterpret_cast<PFNGLTEXCOORD4FPROC>(get_proc_address("glTexCoord4f"));
    glTexCoord4fv = reinterpret_cast<PFNGLTEXCOORD4FVPROC>(get_proc_address("glTexCoord4fv"));
    glTexCoord4i = reinterpret_cast<PFNGLTEXCOORD4IPROC>(get_proc_address("glTexCoord4i"));
    glTexCoord4iv = reinterpret_cast<PFNGLTEXCOORD4IVPROC>(get_proc_address("glTexCoord4iv"));
    glTexCoord4s = reinterpret_cast<PFNGLTEXCOORD4SPROC>(get_proc_address("glTexCoord4s"));
    glTexCoord4sv = reinterpret_cast<PFNGLTEXCOORD4SVPROC>(get_proc_address("glTexCoord4sv"));
    glVertex2d = reinterpret_cast<PFNGLVERTEX2DPROC>(get_proc_address("glVertex2d"));
    glVertex2dv = reinterpret_cast<PFNGLVERTEX2DVPROC>(get_proc_address("glVertex2dv"));
    glVertex2f = reinterpret_cast<PFNGLVERTEX2FPROC>(get_proc_address("glVertex2f"));
    glVertex2fv = reinterpret_cast<PFNGLVERTEX2FVPROC>(get_proc_address("glVertex2fv"));
    glVertex2i = reinterpret_cast<PFNGLVERTEX2IPROC>(get_proc_address("glVertex2i"));
    glVertex2iv = reinterpret_cast<PFNGLVERTEX2IVPROC>(get_proc_address("glVertex2iv"));
    glVertex2s = reinterpret_cast<PFNGLVERTEX2SPROC>(get_proc_address("glVertex2s"));
    glVertex2sv = reinterpret_cast<PFNGLVERTEX2SVPROC>(get_proc_address("glVertex2sv"));
    glVertex3d = reinterpret_cast<PFNGLVERTEX3DPROC>(get_proc_address("glVertex3d"));
    glVertex3dv = reinterpret_cast<PFNGLVERTEX3DVPROC>(get_proc_address("glVertex3dv"));
    glVertex3f = reinterpret_cast<PFNGLVERTEX3FPROC>(get_proc_address("glVertex3f"));
    glVertex3fv = reinterpret_cast<PFNGLVERTEX3FVPROC>(get_proc_address("glVertex3fv"));
    glVertex3i = reinterpret_cast<PFNGLVERTEX3IPROC>(get_proc_address("glVertex3i"));
    glVertex3iv = reinterpret_cast<PFNGLVERTEX3IVPROC>(get_proc_address("glVertex3iv"));
    glVertex3s = reinterpret_cast<PFNGLVERTEX3SPROC>(get_proc_address("glVertex3s"));
    glVertex3sv = reinterpret_cast<PFNGLVERTEX3SVPROC>(get_proc_address("glVertex3sv"));
    glVertex4d = reinterpret_cast<PFNGLVERTEX4DPROC>(get_proc_address("glVertex4d"));
    glVertex4dv = reinterpret_cast<PFNGLVERTEX4DVPROC>(get_proc_address("glVertex4dv"));
    glVertex4f = reinterpret_cast<PFNGLVERTEX4FPROC>(get_proc_address("glVertex4f"));
    glVertex4fv = reinterpret_cast<PFNGLVERTEX4FVPROC>(get_proc_address("glVertex4fv"));
    glVertex4i = reinterpret_cast<PFNGLVERTEX4IPROC>(get_proc_address("glVertex4i"));
    glVertex4iv = reinterpret_cast<PFNGLVERTEX4IVPROC>(get_proc_address("glVertex4iv"));
    glVertex4s = reinterpret_cast<PFNGLVERTEX4SPROC>(get_proc_address("glVertex4s"));
    glVertex4sv = reinterpret_cast<PFNGLVERTEX4SVPROC>(get_proc_address("glVertex4sv"));
    glClipPlane = reinterpret_cast<PFNGLCLIPPLANEPROC>(get_proc_address("glClipPlane"));
    glColorMaterial = reinterpret_cast<PFNGLCOLORMATERIALPROC>(get_proc_address("glColorMaterial"));
    glFogf = reinterpret_cast<PFNGLFOGFPROC>(get_proc_address("glFogf"));
    glFogfv = reinterpret_cast<PFNGLFOGFVPROC>(get_proc_address("glFogfv"));
    glFogi = reinterpret_cast<PFNGLFOGIPROC>(get_proc_address("glFogi"));
    glFogiv = reinterpret_cast<PFNGLFOGIVPROC>(get_proc_address("glFogiv"));
    glLightf = reinterpret_cast<PFNGLLIGHTFPROC>(get_proc_address("glLightf"));
    glLightfv = reinterpret_cast<PFNGLLIGHTFVPROC>(get_proc_address("glLightfv"));
    glLighti = reinterpret_cast<PFNGLLIGHTIPROC>(get_proc_address("glLighti"));
    glLightiv = reinterpret_cast<PFNGLLIGHTIVPROC>(get_proc_address("glLightiv"));
    glLightModelf = reinterpret_cast<PFNGLLIGHTMODELFPROC>(get_proc_address("glLightModelf"));
    glLightModelfv = reinterpret_cast<PFNGLLIGHTMODELFVPROC>(get_proc_address("glLightModelfv"));
    glLightModeli = reinterpret_cast<PFNGLLIGHTMODELIPROC>(get_proc_address("glLightModeli"));
    glLightModeliv = reinterpret_cast<PFNGLLIGHTMODELIVPROC>(get_proc_address("glLightModeliv"));
    glLineStipple = reinterpret_cast<PFNGLLINESTIPPLEPROC>(get_proc_address("glLineStipple"));
    glMaterialf = reinterpret_cast<PFNGLMATERIALFPROC>(get_proc_address("glMaterialf"));
    glMaterialfv = reinterpret_cast<PFNGLMATERIALFVPROC>(get_proc_address("glMaterialfv"));
    glMateriali = reinterpret_cast<PFNGLMATERIALIPROC>(get_proc_address("glMateriali"));
    glMaterialiv = reinterpret_cast<PFNGLMATERIALIVPROC>(get_proc_address("glMaterialiv"));
    glPolygonStipple = reinterpret_cast<PFNGLPOLYGONSTIPPLEPROC>(get_proc_address("glPolygonStipple"));
    glShadeModel = reinterpret_cast<PFNGLSHADEMODELPROC>(get_proc_address("glShadeModel"));
    glTexEnvf = reinterpret_cast<PFNGLTEXENVFPROC>(get_proc_address("glTexEnvf"));
    glTexEnvfv = reinterpret_cast<PFNGLTEXENVFVPROC>(get_proc_address("glTexEnvfv"));
    glTexEnvi = reinterpret_cast<PFNGLTEXENVIPROC>(get_proc_address("glTexEnvi"));
    glTexEnviv = reinterpret_cast<PFNGLTEXENVIVPROC>(get_proc_address("glTexEnviv"));
    glTexGend = reinterpret_cast<PFNGLTEXGENDPROC>(get_proc_address("glTexGend"));
    glTexGendv = reinterpret_cast<PFNGLTEXGENDVPROC>(get_proc_address("glTexGendv"));
    glTexGenf = reinterpret_cast<PFNGLTEXGENFPROC>(get_proc_address("glTexGenf"));
    glTexGenfv = reinterpret_cast<PFNGLTEXGENFVPROC>(get_proc_address("glTexGenfv"));
    glTexGeni = reinterpret_cast<PFNGLTEXGENIPROC>(get_proc_address("glTexGeni"));
    glTexGeniv = reinterpret_cast<PFNGLTEXGENIVPROC>(get_proc_address("glTexGeniv"));
    glFeedbackBuffer = reinterpret_cast<PFNGLFEEDBACKBUFFERPROC>(get_proc_address("glFeedbackBuffer"));
    glSelectBuffer = reinterpret_cast<PFNGLSELECTBUFFERPROC>(get_proc_address("glSelectBuffer"));
    glRenderMode = reinterpret_cast<PFNGLRENDERMODEPROC>(get_proc_address("glRenderMode"));
    glInitNames = reinterpret_cast<PFNGLINITNAMESPROC>(get_proc_address("glInitNames"));
    glLoadName = reinterpret_cast<PFNGLLOADNAMEPROC>(get_proc_address("glLoadName"));
    glPassThrough = reinterpret_cast<PFNGLPASSTHROUGHPROC>(get_proc_address("glPassThrough"));
    glPopName = reinterpret_cast<PFNGLPOPNAMEPROC>(get_proc_address("glPopName"));
    glPushName = reinterpret_cast<PFNGLPUSHNAMEPROC>(get_proc_address("glPushName"));
    glClearAccum = reinterpret_cast<PFNGLCLEARACCUMPROC>(get_proc_address("glClearAccum"));
    glClearIndex = reinterpret_cast<PFNGLCLEARINDEXPROC>(get_proc_address("glClearIndex"));
    glIndexMask = reinterpret_cast<PFNGLINDEXMASKPROC>(get_proc_address("glIndexMask"));
    glAccum = reinterpret_cast<PFNGLACCUMPROC>(get_proc_address("glAccum"));
    glPopAttrib = reinterpret_cast<PFNGLPOPATTRIBPROC>(get_proc_address("glPopAttrib"));
    glPushAttrib = reinterpret_cast<PFNGLPUSHATTRIBPROC>(get_proc_address("glPushAttrib"));
    glMap1d = reinterpret_cast<PFNGLMAP1DPROC>(get_proc_address("glMap1d"));
    glMap1f = reinterpret_cast<PFNGLMAP1FPROC>(get_proc_address("glMap1f"));
    glMap2d = reinterpret_cast<PFNGLMAP2DPROC>(get_proc_address("glMap2d"));
    glMap2f = reinterpret_cast<PFNGLMAP2FPROC>(get_proc_address("glMap2f"));
    glMapGrid1d = reinterpret_cast<PFNGLMAPGRID1DPROC>(get_proc_address("glMapGrid1d"));
    glMapGrid1f = reinterpret_cast<PFNGLMAPGRID1FPROC>(get_proc_address("glMapGrid1f"));
    glMapGrid2d = reinterpret_cast<PFNGLMAPGRID2DPROC>(get_proc_address("glMapGrid2d"));
    glMapGrid2f = reinterpret_cast<PFNGLMAPGRID2FPROC>(get_proc_address("glMapGrid2f"));
    glEvalCoord1d = reinterpret_cast<PFNGLEVALCOORD1DPROC>(get_proc_address("glEvalCoord1d"));
    glEvalCoord1dv = reinterpret_cast<PFNGLEVALCOORD1DVPROC>(get_proc_address("glEvalCoord1dv"));
    glEvalCoord1f = reinterpret_cast<PFNGLEVALCOORD1FPROC>(get_proc_address("glEvalCoord1f"));
    glEvalCoord1fv = reinterpret_cast<PFNGLEVALCOORD1FVPROC>(get_proc_address("glEvalCoord1fv"));
    glEvalCoord2d = reinterpret_cast<PFNGLEVALCOORD2DPROC>(get_proc_address("glEvalCoord2d"));
    glEvalCoord2dv = reinterpret_cast<PFNGLEVALCOORD2DVPROC>(get_proc_address("glEvalCoord2dv"));
    glEvalCoord2f = reinterpret_cast<PFNGLEVALCOORD2FPROC>(get_proc_address("glEvalCoord2f"));
    glEvalCoord2fv = reinterpret_cast<PFNGLEVALCOORD2FVPROC>(get_proc_address("glEvalCoord2fv"));
    glEvalMesh1 = reinterpret_cast<PFNGLEVALMESH1PROC>(get_proc_address("glEvalMesh1"));
    glEvalPoint1 = reinterpret_cast<PFNGLEVALPOINT1PROC>(get_proc_address("glEvalPoint1"));
    glEvalMesh2 = reinterpret_cast<PFNGLEVALMESH2PROC>(get_proc_address("glEvalMesh2"));
    glEvalPoint2 = reinterpret_cast<PFNGLEVALPOINT2PROC>(get_proc_address("glEvalPoint2"));
    glAlphaFunc = reinterpret_cast<PFNGLALPHAFUNCPROC>(get_proc_address("glAlphaFunc"));
    glPixelZoom = reinterpret_cast<PFNGLPIXELZOOMPROC>(get_proc_address("glPixelZoom"));
    glPixelTransferf = reinterpret_cast<PFNGLPIXELTRANSFERFPROC>(get_proc_address("glPixelTransferf"));
    glPixelTransferi = reinterpret_cast<PFNGLPIXELTRANSFERIPROC>(get_proc_address("glPixelTransferi"));
    glPixelMapfv = reinterpret_cast<PFNGLPIXELMAPFVPROC>(get_proc_address("glPixelMapfv"));
    glPixelMapuiv = reinterpret_cast<PFNGLPIXELMAPUIVPROC>(get_proc_address("glPixelMapuiv"));
    glPixelMapusv = reinterpret_cast<PFNGLPIXELMAPUSVPROC>(get_proc_address("glPixelMapusv"));
    glCopyPixels = reinterpret_cast<PFNGLCOPYPIXELSPROC>(get_proc_address("glCopyPixels"));
    glDrawPixels = reinterpret_cast<PFNGLDRAWPIXELSPROC>(get_proc_address("glDrawPixels"));
    glGetClipPlane = reinterpret_cast<PFNGLGETCLIPPLANEPROC>(get_proc_address("glGetClipPlane"));
    glGetLightfv = reinterpret_cast<PFNGLGETLIGHTFVPROC>(get_proc_address("glGetLightfv"));
    glGetLightiv = reinterpret_cast<PFNGLGETLIGHTIVPROC>(get_proc_address("glGetLightiv"));
    glGetMapdv = reinterpret_cast<PFNGLGETMAPDVPROC>(get_proc_address("glGetMapdv"));
    glGetMapfv = reinterpret_cast<PFNGLGETMAPFVPROC>(get_proc_address("glGetMapfv"));
    glGetMapiv = reinterpret_cast<PFNGLGETMAPIVPROC>(get_proc_address("glGetMapiv"));
    glGetMaterialfv = reinterpret_cast<PFNGLGETMATERIALFVPROC>(get_proc_address("glGetMaterialfv"));
    glGetMaterialiv = reinterpret_cast<PFNGLGETMATERIALIVPROC>(get_proc_address("glGetMaterialiv"));
    glGetPixelMapfv = reinterpret_cast<PFNGLGETPIXELMAPFVPROC>(get_proc_address("glGetPixelMapfv"));
    glGetPixelMapuiv = reinterpret_cast<PFNGLGETPIXELMAPUIVPROC>(get_proc_address("glGetPixelMapuiv"));
    glGetPixelMapusv = reinterpret_cast<PFNGLGETPIXELMAPUSVPROC>(get_proc_address("glGetPixelMapusv"));
    glGetPolygonStipple = reinterpret_cast<PFNGLGETPOLYGONSTIPPLEPROC>(get_proc_address("glGetPolygonStipple"));
    glGetTexEnvfv = reinterpret_cast<PFNGLGETTEXENVFVPROC>(get_proc_address("glGetTexEnvfv"));
    glGetTexEnviv = reinterpret_cast<PFNGLGETTEXENVIVPROC>(get_proc_address("glGetTexEnviv"));
    glGetTexGendv = reinterpret_cast<PFNGLGETTEXGENDVPROC>(get_proc_address("glGetTexGendv"));
    glGetTexGenfv = reinterpret_cast<PFNGLGETTEXGENFVPROC>(get_proc_address("glGetTexGenfv"));
    glGetTexGeniv = reinterpret_cast<PFNGLGETTEXGENIVPROC>(get_proc_address("glGetTexGeniv"));
    glIsList = reinterpret_cast<PFNGLISLISTPROC>(get_proc_address("glIsList"));
    glFrustum = reinterpret_cast<PFNGLFRUSTUMPROC>(get_proc_address("glFrustum"));
    glLoadIdentity = reinterpret_cast<PFNGLLOADIDENTITYPROC>(get_proc_address("glLoadIdentity"));
    glLoadMatrixf = reinterpret_cast<PFNGLLOADMATRIXFPROC>(get_proc_address("glLoadMatrixf"));
    glLoadMatrixd = reinterpret_cast<PFNGLLOADMATRIXDPROC>(get_proc_address("glLoadMatrixd"));
    glMatrixMode = reinterpret_cast<PFNGLMATRIXMODEPROC>(get_proc_address("glMatrixMode"));
    glMultMatrixf = reinterpret_cast<PFNGLMULTMATRIXFPROC>(get_proc_address("glMultMatrixf"));
    glMultMatrixd = reinterpret_cast<PFNGLMULTMATRIXDPROC>(get_proc_address("glMultMatrixd"));
    glOrtho = reinterpret_cast<PFNGLORTHOPROC>(get_proc_address("glOrtho"));
    glPopMatrix = reinterpret_cast<PFNGLPOPMATRIXPROC>(get_proc_address("glPopMatrix"));
    glPushMatrix = reinterpret_cast<PFNGLPUSHMATRIXPROC>(get_proc_address("glPushMatrix"));
    glRotated = reinterpret_cast<PFNGLROTATEDPROC>(get_proc_address("glRotated"));
    glRotatef = reinterpret_cast<PFNGLROTATEFPROC>(get_proc_address("glRotatef"));
    glScaled = reinterpret_cast<PFNGLSCALEDPROC>(get_proc_address("glScaled"));
    glScalef = reinterpret_cast<PFNGLSCALEFPROC>(get_proc_address("glScalef"));
    glTranslated = reinterpret_cast<PFNGLTRANSLATEDPROC>(get_proc_address("glTranslated"));
    glTranslatef = reinterpret_cast<PFNGLTRANSLATEFPROC>(get_proc_address("glTranslatef"));
}

// ==================== OpenGL 1.1 Functions ====================

void OpenGLLoader::load_version_1_1(OpenGLLoader* loader)
{
    glDrawArrays = reinterpret_cast<PFNGLDRAWARRAYSPROC>(get_proc_address("glDrawArrays"));
    glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(get_proc_address("glDrawElements"));
    glGetPointerv = reinterpret_cast<PFNGLGETPOINTERVPROC>(get_proc_address("glGetPointerv"));
    glPolygonOffset = reinterpret_cast<PFNGLPOLYGONOFFSETPROC>(get_proc_address("glPolygonOffset"));
    glCopyTexImage1D = reinterpret_cast<PFNGLCOPYTEXIMAGE1DPROC>(get_proc_address("glCopyTexImage1D"));
    glCopyTexImage2D = reinterpret_cast<PFNGLCOPYTEXIMAGE2DPROC>(get_proc_address("glCopyTexImage2D"));
    glCopyTexSubImage1D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>(get_proc_address("glCopyTexSubImage1D"));
    glCopyTexSubImage2D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE2DPROC>(get_proc_address("glCopyTexSubImage2D"));
    glTexSubImage1D = reinterpret_cast<PFNGLTEXSUBIMAGE1DPROC>(get_proc_address("glTexSubImage1D"));
    glTexSubImage2D = reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>(get_proc_address("glTexSubImage2D"));
    glBindTexture = reinterpret_cast<PFNGLBINDTEXTUREPROC>(get_proc_address("glBindTexture"));
    glDeleteTextures = reinterpret_cast<PFNGLDELETETEXTURESPROC>(get_proc_address("glDeleteTextures"));
    glGenTextures = reinterpret_cast<PFNGLGENTEXTURESPROC>(get_proc_address("glGenTextures"));
    glIsTexture = reinterpret_cast<PFNGLISTEXTUREPROC>(get_proc_address("glIsTexture"));
    glArrayElement = reinterpret_cast<PFNGLARRAYELEMENTPROC>(get_proc_address("glArrayElement"));
    glColorPointer = reinterpret_cast<PFNGLCOLORPOINTERPROC>(get_proc_address("glColorPointer"));
    glDisableClientState = reinterpret_cast<PFNGLDISABLECLIENTSTATEPROC>(get_proc_address("glDisableClientState"));
    glEdgeFlagPointer = reinterpret_cast<PFNGLEDGEFLAGPOINTERPROC>(get_proc_address("glEdgeFlagPointer"));
    glEnableClientState = reinterpret_cast<PFNGLENABLECLIENTSTATEPROC>(get_proc_address("glEnableClientState"));
    glIndexPointer = reinterpret_cast<PFNGLINDEXPOINTERPROC>(get_proc_address("glIndexPointer"));
    glInterleavedArrays = reinterpret_cast<PFNGLINTERLEAVEDARRAYSPROC>(get_proc_address("glInterleavedArrays"));
    glNormalPointer = reinterpret_cast<PFNGLNORMALPOINTERPROC>(get_proc_address("glNormalPointer"));
    glTexCoordPointer = reinterpret_cast<PFNGLTEXCOORDPOINTERPROC>(get_proc_address("glTexCoordPointer"));
    glVertexPointer = reinterpret_cast<PFNGLVERTEXPOINTERPROC>(get_proc_address("glVertexPointer"));
    glAreTexturesResident = reinterpret_cast<PFNGLARETEXTURESRESIDENTPROC>(get_proc_address("glAreTexturesResident"));
    glPrioritizeTextures = reinterpret_cast<PFNGLPRIORITIZETEXTURESPROC>(get_proc_address("glPrioritizeTextures"));
    glIndexub = reinterpret_cast<PFNGLINDEXUBPROC>(get_proc_address("glIndexub"));
    glIndexubv = reinterpret_cast<PFNGLINDEXUBVPROC>(get_proc_address("glIndexubv"));
    glPopClientAttrib = reinterpret_cast<PFNGLPOPCLIENTATTRIBPROC>(get_proc_address("glPopClientAttrib"));
    glPushClientAttrib = reinterpret_cast<PFNGLPUSHCLIENTATTRIBPROC>(get_proc_address("glPushClientAttrib"));
}

// ==================== OpenGL 1.2 Functions ====================

void OpenGLLoader::load_version_1_2(OpenGLLoader* loader)
{
    glDrawRangeElements = reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(get_proc_address("glDrawRangeElements"));
    glTexImage3D = reinterpret_cast<PFNGLTEXIMAGE3DPROC>(get_proc_address("glTexImage3D"));
    glTexSubImage3D = reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>(get_proc_address("glTexSubImage3D"));
    glCopyTexSubImage3D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>(get_proc_address("glCopyTexSubImage3D"));
}

// ==================== OpenGL 1.3 Functions ====================

void OpenGLLoader::load_version_1_3(OpenGLLoader* loader)
{
    glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(get_proc_address("glActiveTexture"));
    glSampleCoverage = reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>(get_proc_address("glSampleCoverage"));
    glCompressedTexImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(get_proc_address("glCompressedTexImage3D"));
    glCompressedTexImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(get_proc_address("glCompressedTexImage2D"));
    glCompressedTexImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(get_proc_address("glCompressedTexImage1D"));
    glCompressedTexSubImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(get_proc_address("glCompressedTexSubImage3D"));
    glCompressedTexSubImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(get_proc_address("glCompressedTexSubImage2D"));
    glCompressedTexSubImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>(get_proc_address("glCompressedTexSubImage1D"));
    glGetCompressedTexImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(get_proc_address("glGetCompressedTexImage"));
    glClientActiveTexture = reinterpret_cast<PFNGLCLIENTACTIVETEXTUREPROC>(get_proc_address("glClientActiveTexture"));
    glMultiTexCoord1d = reinterpret_cast<PFNGLMULTITEXCOORD1DPROC>(get_proc_address("glMultiTexCoord1d"));
    glMultiTexCoord1dv = reinterpret_cast<PFNGLMULTITEXCOORD1DVPROC>(get_proc_address("glMultiTexCoord1dv"));
    glMultiTexCoord1f = reinterpret_cast<PFNGLMULTITEXCOORD1FPROC>(get_proc_address("glMultiTexCoord1f"));
    glMultiTexCoord1fv = reinterpret_cast<PFNGLMULTITEXCOORD1FVPROC>(get_proc_address("glMultiTexCoord1fv"));
    glMultiTexCoord1i = reinterpret_cast<PFNGLMULTITEXCOORD1IPROC>(get_proc_address("glMultiTexCoord1i"));
    glMultiTexCoord1iv = reinterpret_cast<PFNGLMULTITEXCOORD1IVPROC>(get_proc_address("glMultiTexCoord1iv"));
    glMultiTexCoord1s = reinterpret_cast<PFNGLMULTITEXCOORD1SPROC>(get_proc_address("glMultiTexCoord1s"));
    glMultiTexCoord1sv = reinterpret_cast<PFNGLMULTITEXCOORD1SVPROC>(get_proc_address("glMultiTexCoord1sv"));
    glMultiTexCoord2d = reinterpret_cast<PFNGLMULTITEXCOORD2DPROC>(get_proc_address("glMultiTexCoord2d"));
    glMultiTexCoord2dv = reinterpret_cast<PFNGLMULTITEXCOORD2DVPROC>(get_proc_address("glMultiTexCoord2dv"));
    glMultiTexCoord2f = reinterpret_cast<PFNGLMULTITEXCOORD2FPROC>(get_proc_address("glMultiTexCoord2f"));
    glMultiTexCoord2fv = reinterpret_cast<PFNGLMULTITEXCOORD2FVPROC>(get_proc_address("glMultiTexCoord2fv"));
    glMultiTexCoord2i = reinterpret_cast<PFNGLMULTITEXCOORD2IPROC>(get_proc_address("glMultiTexCoord2i"));
    glMultiTexCoord2iv = reinterpret_cast<PFNGLMULTITEXCOORD2IVPROC>(get_proc_address("glMultiTexCoord2iv"));
    glMultiTexCoord2s = reinterpret_cast<PFNGLMULTITEXCOORD2SPROC>(get_proc_address("glMultiTexCoord2s"));
    glMultiTexCoord2sv = reinterpret_cast<PFNGLMULTITEXCOORD2SVPROC>(get_proc_address("glMultiTexCoord2sv"));
    glMultiTexCoord3d = reinterpret_cast<PFNGLMULTITEXCOORD3DPROC>(get_proc_address("glMultiTexCoord3d"));
    glMultiTexCoord3dv = reinterpret_cast<PFNGLMULTITEXCOORD3DVPROC>(get_proc_address("glMultiTexCoord3dv"));
    glMultiTexCoord3f = reinterpret_cast<PFNGLMULTITEXCOORD3FPROC>(get_proc_address("glMultiTexCoord3f"));
    glMultiTexCoord3fv = reinterpret_cast<PFNGLMULTITEXCOORD3FVPROC>(get_proc_address("glMultiTexCoord3fv"));
    glMultiTexCoord3i = reinterpret_cast<PFNGLMULTITEXCOORD3IPROC>(get_proc_address("glMultiTexCoord3i"));
    glMultiTexCoord3iv = reinterpret_cast<PFNGLMULTITEXCOORD3IVPROC>(get_proc_address("glMultiTexCoord3iv"));
    glMultiTexCoord3s = reinterpret_cast<PFNGLMULTITEXCOORD3SPROC>(get_proc_address("glMultiTexCoord3s"));
    glMultiTexCoord3sv = reinterpret_cast<PFNGLMULTITEXCOORD3SVPROC>(get_proc_address("glMultiTexCoord3sv"));
    glMultiTexCoord4d = reinterpret_cast<PFNGLMULTITEXCOORD4DPROC>(get_proc_address("glMultiTexCoord4d"));
    glMultiTexCoord4dv = reinterpret_cast<PFNGLMULTITEXCOORD4DVPROC>(get_proc_address("glMultiTexCoord4dv"));
    glMultiTexCoord4f = reinterpret_cast<PFNGLMULTITEXCOORD4FPROC>(get_proc_address("glMultiTexCoord4f"));
    glMultiTexCoord4fv = reinterpret_cast<PFNGLMULTITEXCOORD4FVPROC>(get_proc_address("glMultiTexCoord4fv"));
    glMultiTexCoord4i = reinterpret_cast<PFNGLMULTITEXCOORD4IPROC>(get_proc_address("glMultiTexCoord4i"));
    glMultiTexCoord4iv = reinterpret_cast<PFNGLMULTITEXCOORD4IVPROC>(get_proc_address("glMultiTexCoord4iv"));
    glMultiTexCoord4s = reinterpret_cast<PFNGLMULTITEXCOORD4SPROC>(get_proc_address("glMultiTexCoord4s"));
    glMultiTexCoord4sv = reinterpret_cast<PFNGLMULTITEXCOORD4SVPROC>(get_proc_address("glMultiTexCoord4sv"));
    glLoadTransposeMatrixf = reinterpret_cast<PFNGLLOADTRANSPOSEMATRIXFPROC>(get_proc_address("glLoadTransposeMatrixf"));
    glLoadTransposeMatrixd = reinterpret_cast<PFNGLLOADTRANSPOSEMATRIXDPROC>(get_proc_address("glLoadTransposeMatrixd"));
    glMultTransposeMatrixf = reinterpret_cast<PFNGLMULTTRANSPOSEMATRIXFPROC>(get_proc_address("glMultTransposeMatrixf"));
    glMultTransposeMatrixd = reinterpret_cast<PFNGLMULTTRANSPOSEMATRIXDPROC>(get_proc_address("glMultTransposeMatrixd"));
}

// ==================== OpenGL 1.4 Functions ====================

void OpenGLLoader::load_version_1_4(OpenGLLoader* loader)
{
    glBlendFuncSeparate = reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(get_proc_address("glBlendFuncSeparate"));
    glMultiDrawArrays = reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(get_proc_address("glMultiDrawArrays"));
    glMultiDrawElements = reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(get_proc_address("glMultiDrawElements"));
    glPointParameterf = reinterpret_cast<PFNGLPOINTPARAMETERFPROC>(get_proc_address("glPointParameterf"));
    glPointParameterfv = reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(get_proc_address("glPointParameterfv"));
    glPointParameteri = reinterpret_cast<PFNGLPOINTPARAMETERIPROC>(get_proc_address("glPointParameteri"));
    glPointParameteriv = reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>(get_proc_address("glPointParameteriv"));
    glFogCoordf = reinterpret_cast<PFNGLFOGCOORDFPROC>(get_proc_address("glFogCoordf"));
    glFogCoordfv = reinterpret_cast<PFNGLFOGCOORDFVPROC>(get_proc_address("glFogCoordfv"));
    glFogCoordd = reinterpret_cast<PFNGLFOGCOORDDPROC>(get_proc_address("glFogCoordd"));
    glFogCoorddv = reinterpret_cast<PFNGLFOGCOORDDVPROC>(get_proc_address("glFogCoorddv"));
    glFogCoordPointer = reinterpret_cast<PFNGLFOGCOORDPOINTERPROC>(get_proc_address("glFogCoordPointer"));
    glSecondaryColor3b = reinterpret_cast<PFNGLSECONDARYCOLOR3BPROC>(get_proc_address("glSecondaryColor3b"));
    glSecondaryColor3bv = reinterpret_cast<PFNGLSECONDARYCOLOR3BVPROC>(get_proc_address("glSecondaryColor3bv"));
    glSecondaryColor3d = reinterpret_cast<PFNGLSECONDARYCOLOR3DPROC>(get_proc_address("glSecondaryColor3d"));
    glSecondaryColor3dv = reinterpret_cast<PFNGLSECONDARYCOLOR3DVPROC>(get_proc_address("glSecondaryColor3dv"));
    glSecondaryColor3f = reinterpret_cast<PFNGLSECONDARYCOLOR3FPROC>(get_proc_address("glSecondaryColor3f"));
    glSecondaryColor3fv = reinterpret_cast<PFNGLSECONDARYCOLOR3FVPROC>(get_proc_address("glSecondaryColor3fv"));
    glSecondaryColor3i = reinterpret_cast<PFNGLSECONDARYCOLOR3IPROC>(get_proc_address("glSecondaryColor3i"));
    glSecondaryColor3iv = reinterpret_cast<PFNGLSECONDARYCOLOR3IVPROC>(get_proc_address("glSecondaryColor3iv"));
    glSecondaryColor3s = reinterpret_cast<PFNGLSECONDARYCOLOR3SPROC>(get_proc_address("glSecondaryColor3s"));
    glSecondaryColor3sv = reinterpret_cast<PFNGLSECONDARYCOLOR3SVPROC>(get_proc_address("glSecondaryColor3sv"));
    glSecondaryColor3ub = reinterpret_cast<PFNGLSECONDARYCOLOR3UBPROC>(get_proc_address("glSecondaryColor3ub"));
    glSecondaryColor3ubv = reinterpret_cast<PFNGLSECONDARYCOLOR3UBVPROC>(get_proc_address("glSecondaryColor3ubv"));
    glSecondaryColor3ui = reinterpret_cast<PFNGLSECONDARYCOLOR3UIPROC>(get_proc_address("glSecondaryColor3ui"));
    glSecondaryColor3uiv = reinterpret_cast<PFNGLSECONDARYCOLOR3UIVPROC>(get_proc_address("glSecondaryColor3uiv"));
    glSecondaryColor3us = reinterpret_cast<PFNGLSECONDARYCOLOR3USPROC>(get_proc_address("glSecondaryColor3us"));
    glSecondaryColor3usv = reinterpret_cast<PFNGLSECONDARYCOLOR3USVPROC>(get_proc_address("glSecondaryColor3usv"));
    glSecondaryColorPointer = reinterpret_cast<PFNGLSECONDARYCOLORPOINTERPROC>(get_proc_address("glSecondaryColorPointer"));
    glWindowPos2d = reinterpret_cast<PFNGLWINDOWPOS2DPROC>(get_proc_address("glWindowPos2d"));
    glWindowPos2dv = reinterpret_cast<PFNGLWINDOWPOS2DVPROC>(get_proc_address("glWindowPos2dv"));
    glWindowPos2f = reinterpret_cast<PFNGLWINDOWPOS2FPROC>(get_proc_address("glWindowPos2f"));
    glWindowPos2fv = reinterpret_cast<PFNGLWINDOWPOS2FVPROC>(get_proc_address("glWindowPos2fv"));
    glWindowPos2i = reinterpret_cast<PFNGLWINDOWPOS2IPROC>(get_proc_address("glWindowPos2i"));
    glWindowPos2iv = reinterpret_cast<PFNGLWINDOWPOS2IVPROC>(get_proc_address("glWindowPos2iv"));
    glWindowPos2s = reinterpret_cast<PFNGLWINDOWPOS2SPROC>(get_proc_address("glWindowPos2s"));
    glWindowPos2sv = reinterpret_cast<PFNGLWINDOWPOS2SVPROC>(get_proc_address("glWindowPos2sv"));
    glWindowPos3d = reinterpret_cast<PFNGLWINDOWPOS3DPROC>(get_proc_address("glWindowPos3d"));
    glWindowPos3dv = reinterpret_cast<PFNGLWINDOWPOS3DVPROC>(get_proc_address("glWindowPos3dv"));
    glWindowPos3f = reinterpret_cast<PFNGLWINDOWPOS3FPROC>(get_proc_address("glWindowPos3f"));
    glWindowPos3fv = reinterpret_cast<PFNGLWINDOWPOS3FVPROC>(get_proc_address("glWindowPos3fv"));
    glWindowPos3i = reinterpret_cast<PFNGLWINDOWPOS3IPROC>(get_proc_address("glWindowPos3i"));
    glWindowPos3iv = reinterpret_cast<PFNGLWINDOWPOS3IVPROC>(get_proc_address("glWindowPos3iv"));
    glWindowPos3s = reinterpret_cast<PFNGLWINDOWPOS3SPROC>(get_proc_address("glWindowPos3s"));
    glWindowPos3sv = reinterpret_cast<PFNGLWINDOWPOS3SVPROC>(get_proc_address("glWindowPos3sv"));
    glBlendColor = reinterpret_cast<PFNGLBLENDCOLORPROC>(get_proc_address("glBlendColor"));
    glBlendEquation = reinterpret_cast<PFNGLBLENDEQUATIONPROC>(get_proc_address("glBlendEquation"));
}

// ==================== OpenGL 1.5 Functions ====================

void OpenGLLoader::load_version_1_5(OpenGLLoader* loader)
{
    glGenQueries = reinterpret_cast<PFNGLGENQUERIESPROC>(get_proc_address("glGenQueries"));
    glDeleteQueries = reinterpret_cast<PFNGLDELETEQUERIESPROC>(get_proc_address("glDeleteQueries"));
    glIsQuery = reinterpret_cast<PFNGLISQUERYPROC>(get_proc_address("glIsQuery"));
    glBeginQuery = reinterpret_cast<PFNGLBEGINQUERYPROC>(get_proc_address("glBeginQuery"));
    glEndQuery = reinterpret_cast<PFNGLENDQUERYPROC>(get_proc_address("glEndQuery"));
    glGetQueryiv = reinterpret_cast<PFNGLGETQUERYIVPROC>(get_proc_address("glGetQueryiv"));
    glGetQueryObjectiv = reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(get_proc_address("glGetQueryObjectiv"));
    glGetQueryObjectuiv = reinterpret_cast<PFNGLGETQUERYOBJECTUIVPROC>(get_proc_address("glGetQueryObjectuiv"));
    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(get_proc_address("glBindBuffer"));
    glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(get_proc_address("glDeleteBuffers"));
    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(get_proc_address("glGenBuffers"));
    glIsBuffer = reinterpret_cast<PFNGLISBUFFERPROC>(get_proc_address("glIsBuffer"));
    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(get_proc_address("glBufferData"));
    glBufferSubData = reinterpret_cast<PFNGLBUFFERSUBDATAPROC>(get_proc_address("glBufferSubData"));
    glGetBufferSubData = reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(get_proc_address("glGetBufferSubData"));
    glMapBuffer = reinterpret_cast<PFNGLMAPBUFFERPROC>(get_proc_address("glMapBuffer"));
    glUnmapBuffer = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(get_proc_address("glUnmapBuffer"));
    glGetBufferParameteriv = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVPROC>(get_proc_address("glGetBufferParameteriv"));
    glGetBufferPointerv = reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(get_proc_address("glGetBufferPointerv"));
}

// ==================== OpenGL 2.0 Functions ====================

void OpenGLLoader::load_version_2_0(OpenGLLoader* loader)
{
    glBlendEquationSeparate = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>(get_proc_address("glBlendEquationSeparate"));
    glDrawBuffers = reinterpret_cast<PFNGLDRAWBUFFERSPROC>(get_proc_address("glDrawBuffers"));
    glStencilOpSeparate = reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(get_proc_address("glStencilOpSeparate"));
    glStencilFuncSeparate = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>(get_proc_address("glStencilFuncSeparate"));
    glStencilMaskSeparate = reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>(get_proc_address("glStencilMaskSeparate"));
    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(get_proc_address("glAttachShader"));
    glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(get_proc_address("glBindAttribLocation"));
    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(get_proc_address("glCompileShader"));
    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(get_proc_address("glCreateProgram"));
    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(get_proc_address("glCreateShader"));
    glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(get_proc_address("glDeleteProgram"));
    glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(get_proc_address("glDeleteShader"));
    glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(get_proc_address("glDetachShader"));
    glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(get_proc_address("glDisableVertexAttribArray"));
    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(get_proc_address("glEnableVertexAttribArray"));
    glGetActiveAttrib = reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>(get_proc_address("glGetActiveAttrib"));
    glGetActiveUniform = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(get_proc_address("glGetActiveUniform"));
    glGetAttachedShaders = reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>(get_proc_address("glGetAttachedShaders"));
    glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(get_proc_address("glGetAttribLocation"));
    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(get_proc_address("glGetProgramiv"));
    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(get_proc_address("glGetProgramInfoLog"));
    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(get_proc_address("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(get_proc_address("glGetShaderInfoLog"));
    glGetShaderSource = reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(get_proc_address("glGetShaderSource"));
    glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(get_proc_address("glGetUniformLocation"));
    glGetUniformfv = reinterpret_cast<PFNGLGETUNIFORMFVPROC>(get_proc_address("glGetUniformfv"));
    glGetUniformiv = reinterpret_cast<PFNGLGETUNIFORMIVPROC>(get_proc_address("glGetUniformiv"));
    glGetVertexAttribdv = reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>(get_proc_address("glGetVertexAttribdv"));
    glGetVertexAttribfv = reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(get_proc_address("glGetVertexAttribfv"));
    glGetVertexAttribiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIVPROC>(get_proc_address("glGetVertexAttribiv"));
    glGetVertexAttribPointerv = reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(get_proc_address("glGetVertexAttribPointerv"));
    glIsProgram = reinterpret_cast<PFNGLISPROGRAMPROC>(get_proc_address("glIsProgram"));
    glIsShader = reinterpret_cast<PFNGLISSHADERPROC>(get_proc_address("glIsShader"));
    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(get_proc_address("glLinkProgram"));
    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(get_proc_address("glShaderSource"));
    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(get_proc_address("glUseProgram"));
    glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(get_proc_address("glUniform1f"));
    glUniform2f = reinterpret_cast<PFNGLUNIFORM2FPROC>(get_proc_address("glUniform2f"));
    glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>(get_proc_address("glUniform3f"));
    glUniform4f = reinterpret_cast<PFNGLUNIFORM4FPROC>(get_proc_address("glUniform4f"));
    glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(get_proc_address("glUniform1i"));
    glUniform2i = reinterpret_cast<PFNGLUNIFORM2IPROC>(get_proc_address("glUniform2i"));
    glUniform3i = reinterpret_cast<PFNGLUNIFORM3IPROC>(get_proc_address("glUniform3i"));
    glUniform4i = reinterpret_cast<PFNGLUNIFORM4IPROC>(get_proc_address("glUniform4i"));
    glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>(get_proc_address("glUniform1fv"));
    glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FVPROC>(get_proc_address("glUniform2fv"));
    glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(get_proc_address("glUniform3fv"));
    glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(get_proc_address("glUniform4fv"));
    glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IVPROC>(get_proc_address("glUniform1iv"));
    glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IVPROC>(get_proc_address("glUniform2iv"));
    glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IVPROC>(get_proc_address("glUniform3iv"));
    glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IVPROC>(get_proc_address("glUniform4iv"));
    glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>(get_proc_address("glUniformMatrix2fv"));
    glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(get_proc_address("glUniformMatrix3fv"));
    glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(get_proc_address("glUniformMatrix4fv"));
    glValidateProgram = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(get_proc_address("glValidateProgram"));
    glVertexAttrib1d = reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(get_proc_address("glVertexAttrib1d"));
    glVertexAttrib1dv = reinterpret_cast<PFNGLVERTEXATTRIB1DVPROC>(get_proc_address("glVertexAttrib1dv"));
    glVertexAttrib1f = reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>(get_proc_address("glVertexAttrib1f"));
    glVertexAttrib1fv = reinterpret_cast<PFNGLVERTEXATTRIB1FVPROC>(get_proc_address("glVertexAttrib1fv"));
    glVertexAttrib1s = reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>(get_proc_address("glVertexAttrib1s"));
    glVertexAttrib1sv = reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>(get_proc_address("glVertexAttrib1sv"));
    glVertexAttrib2d = reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>(get_proc_address("glVertexAttrib2d"));
    glVertexAttrib2dv = reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>(get_proc_address("glVertexAttrib2dv"));
    glVertexAttrib2f = reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>(get_proc_address("glVertexAttrib2f"));
    glVertexAttrib2fv = reinterpret_cast<PFNGLVERTEXATTRIB2FVPROC>(get_proc_address("glVertexAttrib2fv"));
    glVertexAttrib2s = reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>(get_proc_address("glVertexAttrib2s"));
    glVertexAttrib2sv = reinterpret_cast<PFNGLVERTEXATTRIB2SVPROC>(get_proc_address("glVertexAttrib2sv"));
    glVertexAttrib3d = reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>(get_proc_address("glVertexAttrib3d"));
    glVertexAttrib3dv = reinterpret_cast<PFNGLVERTEXATTRIB3DVPROC>(get_proc_address("glVertexAttrib3dv"));
    glVertexAttrib3f = reinterpret_cast<PFNGLVERTEXATTRIB3FPROC>(get_proc_address("glVertexAttrib3f"));
    glVertexAttrib3fv = reinterpret_cast<PFNGLVERTEXATTRIB3FVPROC>(get_proc_address("glVertexAttrib3fv"));
    glVertexAttrib3s = reinterpret_cast<PFNGLVERTEXATTRIB3SPROC>(get_proc_address("glVertexAttrib3s"));
    glVertexAttrib3sv = reinterpret_cast<PFNGLVERTEXATTRIB3SVPROC>(get_proc_address("glVertexAttrib3sv"));
    glVertexAttrib4Nbv = reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>(get_proc_address("glVertexAttrib4Nbv"));
    glVertexAttrib4Niv = reinterpret_cast<PFNGLVERTEXATTRIB4NIVPROC>(get_proc_address("glVertexAttrib4Niv"));
    glVertexAttrib4Nsv = reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>(get_proc_address("glVertexAttrib4Nsv"));
    glVertexAttrib4Nub = reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(get_proc_address("glVertexAttrib4Nub"));
    glVertexAttrib4Nubv = reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>(get_proc_address("glVertexAttrib4Nubv"));
    glVertexAttrib4Nuiv = reinterpret_cast<PFNGLVERTEXATTRIB4NUIVPROC>(get_proc_address("glVertexAttrib4Nuiv"));
    glVertexAttrib4Nusv = reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>(get_proc_address("glVertexAttrib4Nusv"));
    glVertexAttrib4bv = reinterpret_cast<PFNGLVERTEXATTRIB4BVPROC>(get_proc_address("glVertexAttrib4bv"));
    glVertexAttrib4d = reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(get_proc_address("glVertexAttrib4d"));
    glVertexAttrib4dv = reinterpret_cast<PFNGLVERTEXATTRIB4DVPROC>(get_proc_address("glVertexAttrib4dv"));
    glVertexAttrib4f = reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>(get_proc_address("glVertexAttrib4f"));
    glVertexAttrib4fv = reinterpret_cast<PFNGLVERTEXATTRIB4FVPROC>(get_proc_address("glVertexAttrib4fv"));
    glVertexAttrib4iv = reinterpret_cast<PFNGLVERTEXATTRIB4IVPROC>(get_proc_address("glVertexAttrib4iv"));
    glVertexAttrib4s = reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>(get_proc_address("glVertexAttrib4s"));
    glVertexAttrib4sv = reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>(get_proc_address("glVertexAttrib4sv"));
    glVertexAttrib4ubv = reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>(get_proc_address("glVertexAttrib4ubv"));
    glVertexAttrib4uiv = reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>(get_proc_address("glVertexAttrib4uiv"));
    glVertexAttrib4usv = reinterpret_cast<PFNGLVERTEXATTRIB4USVPROC>(get_proc_address("glVertexAttrib4usv"));
    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(get_proc_address("glVertexAttribPointer"));
}

// ==================== OpenGL 2.1 Functions ====================

void OpenGLLoader::load_version_2_1(OpenGLLoader* loader)
{
    glUniformMatrix2x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FVPROC>(get_proc_address("glUniformMatrix2x3fv"));
    glUniformMatrix3x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>(get_proc_address("glUniformMatrix3x2fv"));
    glUniformMatrix2x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FVPROC>(get_proc_address("glUniformMatrix2x4fv"));
    glUniformMatrix4x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FVPROC>(get_proc_address("glUniformMatrix4x2fv"));
    glUniformMatrix3x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>(get_proc_address("glUniformMatrix3x4fv"));
    glUniformMatrix4x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FVPROC>(get_proc_address("glUniformMatrix4x3fv"));
}

// ==================== OpenGL 3.0 Functions ====================

void OpenGLLoader::load_version_3_0(OpenGLLoader* loader)
{
    glColorMaski = reinterpret_cast<PFNGLCOLORMASKIPROC>(get_proc_address("glColorMaski"));
    glGetBooleani_v = reinterpret_cast<PFNGLGETBOOLEANI_VPROC>(get_proc_address("glGetBooleani_v"));
    glGetIntegeri_v = reinterpret_cast<PFNGLGETINTEGERI_VPROC>(get_proc_address("glGetIntegeri_v"));
    glEnablei = reinterpret_cast<PFNGLENABLEIPROC>(get_proc_address("glEnablei"));
    glDisablei = reinterpret_cast<PFNGLDISABLEIPROC>(get_proc_address("glDisablei"));
    glIsEnabledi = reinterpret_cast<PFNGLISENABLEDIPROC>(get_proc_address("glIsEnabledi"));
    glBeginTransformFeedback = reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>(get_proc_address("glBeginTransformFeedback"));
    glEndTransformFeedback = reinterpret_cast<PFNGLENDTRANSFORMFEEDBACKPROC>(get_proc_address("glEndTransformFeedback"));
    glBindBufferRange = reinterpret_cast<PFNGLBINDBUFFERRANGEPROC>(get_proc_address("glBindBufferRange"));
    glBindBufferBase = reinterpret_cast<PFNGLBINDBUFFERBASEPROC>(get_proc_address("glBindBufferBase"));
    glTransformFeedbackVaryings = reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(get_proc_address("glTransformFeedbackVaryings"));
    glGetTransformFeedbackVarying = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(get_proc_address("glGetTransformFeedbackVarying"));
    glClampColor = reinterpret_cast<PFNGLCLAMPCOLORPROC>(get_proc_address("glClampColor"));
    glBeginConditionalRender = reinterpret_cast<PFNGLBEGINCONDITIONALRENDERPROC>(get_proc_address("glBeginConditionalRender"));
    glEndConditionalRender = reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>(get_proc_address("glEndConditionalRender"));
    glVertexAttribIPointer = reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>(get_proc_address("glVertexAttribIPointer"));
    glGetVertexAttribIiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIIVPROC>(get_proc_address("glGetVertexAttribIiv"));
    glGetVertexAttribIuiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>(get_proc_address("glGetVertexAttribIuiv"));
    glVertexAttribI1i = reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>(get_proc_address("glVertexAttribI1i"));
    glVertexAttribI2i = reinterpret_cast<PFNGLVERTEXATTRIBI2IPROC>(get_proc_address("glVertexAttribI2i"));
    glVertexAttribI3i = reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(get_proc_address("glVertexAttribI3i"));
    glVertexAttribI4i = reinterpret_cast<PFNGLVERTEXATTRIBI4IPROC>(get_proc_address("glVertexAttribI4i"));
    glVertexAttribI1ui = reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>(get_proc_address("glVertexAttribI1ui"));
    glVertexAttribI2ui = reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>(get_proc_address("glVertexAttribI2ui"));
    glVertexAttribI3ui = reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>(get_proc_address("glVertexAttribI3ui"));
    glVertexAttribI4ui = reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>(get_proc_address("glVertexAttribI4ui"));
    glVertexAttribI1iv = reinterpret_cast<PFNGLVERTEXATTRIBI1IVPROC>(get_proc_address("glVertexAttribI1iv"));
    glVertexAttribI2iv = reinterpret_cast<PFNGLVERTEXATTRIBI2IVPROC>(get_proc_address("glVertexAttribI2iv"));
    glVertexAttribI3iv = reinterpret_cast<PFNGLVERTEXATTRIBI3IVPROC>(get_proc_address("glVertexAttribI3iv"));
    glVertexAttribI4iv = reinterpret_cast<PFNGLVERTEXATTRIBI4IVPROC>(get_proc_address("glVertexAttribI4iv"));
    glVertexAttribI1uiv = reinterpret_cast<PFNGLVERTEXATTRIBI1UIVPROC>(get_proc_address("glVertexAttribI1uiv"));
    glVertexAttribI2uiv = reinterpret_cast<PFNGLVERTEXATTRIBI2UIVPROC>(get_proc_address("glVertexAttribI2uiv"));
    glVertexAttribI3uiv = reinterpret_cast<PFNGLVERTEXATTRIBI3UIVPROC>(get_proc_address("glVertexAttribI3uiv"));
    glVertexAttribI4uiv = reinterpret_cast<PFNGLVERTEXATTRIBI4UIVPROC>(get_proc_address("glVertexAttribI4uiv"));
    glVertexAttribI4bv = reinterpret_cast<PFNGLVERTEXATTRIBI4BVPROC>(get_proc_address("glVertexAttribI4bv"));
    glVertexAttribI4sv = reinterpret_cast<PFNGLVERTEXATTRIBI4SVPROC>(get_proc_address("glVertexAttribI4sv"));
    glVertexAttribI4ubv = reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>(get_proc_address("glVertexAttribI4ubv"));
    glVertexAttribI4usv = reinterpret_cast<PFNGLVERTEXATTRIBI4USVPROC>(get_proc_address("glVertexAttribI4usv"));
    glGetUniformuiv = reinterpret_cast<PFNGLGETUNIFORMUIVPROC>(get_proc_address("glGetUniformuiv"));
    glBindFragDataLocation = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>(get_proc_address("glBindFragDataLocation"));
    glGetFragDataLocation = reinterpret_cast<PFNGLGETFRAGDATALOCATIONPROC>(get_proc_address("glGetFragDataLocation"));
    glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UIPROC>(get_proc_address("glUniform1ui"));
    glUniform2ui = reinterpret_cast<PFNGLUNIFORM2UIPROC>(get_proc_address("glUniform2ui"));
    glUniform3ui = reinterpret_cast<PFNGLUNIFORM3UIPROC>(get_proc_address("glUniform3ui"));
    glUniform4ui = reinterpret_cast<PFNGLUNIFORM4UIPROC>(get_proc_address("glUniform4ui"));
    glUniform1uiv = reinterpret_cast<PFNGLUNIFORM1UIVPROC>(get_proc_address("glUniform1uiv"));
    glUniform2uiv = reinterpret_cast<PFNGLUNIFORM2UIVPROC>(get_proc_address("glUniform2uiv"));
    glUniform3uiv = reinterpret_cast<PFNGLUNIFORM3UIVPROC>(get_proc_address("glUniform3uiv"));
    glUniform4uiv = reinterpret_cast<PFNGLUNIFORM4UIVPROC>(get_proc_address("glUniform4uiv"));
    glTexParameterIiv = reinterpret_cast<PFNGLTEXPARAMETERIIVPROC>(get_proc_address("glTexParameterIiv"));
    glTexParameterIuiv = reinterpret_cast<PFNGLTEXPARAMETERIUIVPROC>(get_proc_address("glTexParameterIuiv"));
    glGetTexParameterIiv = reinterpret_cast<PFNGLGETTEXPARAMETERIIVPROC>(get_proc_address("glGetTexParameterIiv"));
    glGetTexParameterIuiv = reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>(get_proc_address("glGetTexParameterIuiv"));
    glClearBufferiv = reinterpret_cast<PFNGLCLEARBUFFERIVPROC>(get_proc_address("glClearBufferiv"));
    glClearBufferuiv = reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>(get_proc_address("glClearBufferuiv"));
    glClearBufferfv = reinterpret_cast<PFNGLCLEARBUFFERFVPROC>(get_proc_address("glClearBufferfv"));
    glClearBufferfi = reinterpret_cast<PFNGLCLEARBUFFERFIPROC>(get_proc_address("glClearBufferfi"));
    glGetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>(get_proc_address("glGetStringi"));
    glIsRenderbuffer = reinterpret_cast<PFNGLISRENDERBUFFERPROC>(get_proc_address("glIsRenderbuffer"));
    glBindRenderbuffer = reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>(get_proc_address("glBindRenderbuffer"));
    glDeleteRenderbuffers = reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>(get_proc_address("glDeleteRenderbuffers"));
    glGenRenderbuffers = reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>(get_proc_address("glGenRenderbuffers"));
    glRenderbufferStorage = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>(get_proc_address("glRenderbufferStorage"));
    glGetRenderbufferParameteriv = reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(get_proc_address("glGetRenderbufferParameteriv"));
    glIsFramebuffer = reinterpret_cast<PFNGLISFRAMEBUFFERPROC>(get_proc_address("glIsFramebuffer"));
    glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>(get_proc_address("glBindFramebuffer"));
    glDeleteFramebuffers = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>(get_proc_address("glDeleteFramebuffers"));
    glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>(get_proc_address("glGenFramebuffers"));
    glCheckFramebufferStatus = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(get_proc_address("glCheckFramebufferStatus"));
    glFramebufferTexture1D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DPROC>(get_proc_address("glFramebufferTexture1D"));
    glFramebufferTexture2D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>(get_proc_address("glFramebufferTexture2D"));
    glFramebufferTexture3D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>(get_proc_address("glFramebufferTexture3D"));
    glFramebufferRenderbuffer = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(get_proc_address("glFramebufferRenderbuffer"));
    glGetFramebufferAttachmentParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(get_proc_address("glGetFramebufferAttachmentParameteriv"));
    glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(get_proc_address("glGenerateMipmap"));
    glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>(get_proc_address("glBlitFramebuffer"));
    glRenderbufferStorageMultisample = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(get_proc_address("glRenderbufferStorageMultisample"));
    glFramebufferTextureLayer = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(get_proc_address("glFramebufferTextureLayer"));
    glMapBufferRange = reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>(get_proc_address("glMapBufferRange"));
    glFlushMappedBufferRange = reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(get_proc_address("glFlushMappedBufferRange"));
    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(get_proc_address("glBindVertexArray"));
    glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(get_proc_address("glDeleteVertexArrays"));
    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(get_proc_address("glGenVertexArrays"));
    glIsVertexArray = reinterpret_cast<PFNGLISVERTEXARRAYPROC>(get_proc_address("glIsVertexArray"));
}

// ==================== OpenGL 3.1 Functions ====================

void OpenGLLoader::load_version_3_1(OpenGLLoader* loader)
{
    glDrawArraysInstanced = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(get_proc_address("glDrawArraysInstanced"));
    glDrawElementsInstanced = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>(get_proc_address("glDrawElementsInstanced"));
    glTexBuffer = reinterpret_cast<PFNGLTEXBUFFERPROC>(get_proc_address("glTexBuffer"));
    glPrimitiveRestartIndex = reinterpret_cast<PFNGLPRIMITIVERESTARTINDEXPROC>(get_proc_address("glPrimitiveRestartIndex"));
    glCopyBufferSubData = reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>(get_proc_address("glCopyBufferSubData"));
    glGetUniformIndices = reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>(get_proc_address("glGetUniformIndices"));
    glGetActiveUniformsiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>(get_proc_address("glGetActiveUniformsiv"));
    glGetActiveUniformName = reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>(get_proc_address("glGetActiveUniformName"));
    glGetUniformBlockIndex = reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(get_proc_address("glGetUniformBlockIndex"));
    glGetActiveUniformBlockiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(get_proc_address("glGetActiveUniformBlockiv"));
    glGetActiveUniformBlockName = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(get_proc_address("glGetActiveUniformBlockName"));
    glUniformBlockBinding = reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>(get_proc_address("glUniformBlockBinding"));
}

// ==================== OpenGL 3.2 Functions ====================

void OpenGLLoader::load_version_3_2(OpenGLLoader* loader)
{
    glDrawElementsBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSBASEVERTEXPROC>(get_proc_address("glDrawElementsBaseVertex"));
    glDrawRangeElementsBaseVertex = reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(get_proc_address("glDrawRangeElementsBaseVertex"));
    glDrawElementsInstancedBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(get_proc_address("glDrawElementsInstancedBaseVertex"));
    glMultiDrawElementsBaseVertex = reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>(get_proc_address("glMultiDrawElementsBaseVertex"));
    glProvokingVertex = reinterpret_cast<PFNGLPROVOKINGVERTEXPROC>(get_proc_address("glProvokingVertex"));
    glFenceSync = reinterpret_cast<PFNGLFENCESYNCPROC>(get_proc_address("glFenceSync"));
    glIsSync = reinterpret_cast<PFNGLISSYNCPROC>(get_proc_address("glIsSync"));
    glDeleteSync = reinterpret_cast<PFNGLDELETESYNCPROC>(get_proc_address("glDeleteSync"));
    glClientWaitSync = reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>(get_proc_address("glClientWaitSync"));
    glWaitSync = reinterpret_cast<PFNGLWAITSYNCPROC>(get_proc_address("glWaitSync"));
    glGetInteger64v = reinterpret_cast<PFNGLGETINTEGER64VPROC>(get_proc_address("glGetInteger64v"));
    glGetSynciv = reinterpret_cast<PFNGLGETSYNCIVPROC>(get_proc_address("glGetSynciv"));
    glGetInteger64i_v = reinterpret_cast<PFNGLGETINTEGER64I_VPROC>(get_proc_address("glGetInteger64i_v"));
    glGetBufferParameteri64v = reinterpret_cast<PFNGLGETBUFFERPARAMETERI64VPROC>(get_proc_address("glGetBufferParameteri64v"));
    glFramebufferTexture = reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(get_proc_address("glFramebufferTexture"));
    glTexImage2DMultisample = reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>(get_proc_address("glTexImage2DMultisample"));
    glTexImage3DMultisample = reinterpret_cast<PFNGLTEXIMAGE3DMULTISAMPLEPROC>(get_proc_address("glTexImage3DMultisample"));
    glGetMultisamplefv = reinterpret_cast<PFNGLGETMULTISAMPLEFVPROC>(get_proc_address("glGetMultisamplefv"));
    glSampleMaski = reinterpret_cast<PFNGLSAMPLEMASKIPROC>(get_proc_address("glSampleMaski"));
}

// ==================== OpenGL 3.3 Functions ====================

void OpenGLLoader::load_version_3_3(OpenGLLoader* loader)
{
    glBindFragDataLocationIndexed = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>(get_proc_address("glBindFragDataLocationIndexed"));
    glGetFragDataIndex = reinterpret_cast<PFNGLGETFRAGDATAINDEXPROC>(get_proc_address("glGetFragDataIndex"));
    glGenSamplers = reinterpret_cast<PFNGLGENSAMPLERSPROC>(get_proc_address("glGenSamplers"));
    glDeleteSamplers = reinterpret_cast<PFNGLDELETESAMPLERSPROC>(get_proc_address("glDeleteSamplers"));
    glIsSampler = reinterpret_cast<PFNGLISSAMPLERPROC>(get_proc_address("glIsSampler"));
    glBindSampler = reinterpret_cast<PFNGLBINDSAMPLERPROC>(get_proc_address("glBindSampler"));
    glSamplerParameteri = reinterpret_cast<PFNGLSAMPLERPARAMETERIPROC>(get_proc_address("glSamplerParameteri"));
    glSamplerParameteriv = reinterpret_cast<PFNGLSAMPLERPARAMETERIVPROC>(get_proc_address("glSamplerParameteriv"));
    glSamplerParameterf = reinterpret_cast<PFNGLSAMPLERPARAMETERFPROC>(get_proc_address("glSamplerParameterf"));
    glSamplerParameterfv = reinterpret_cast<PFNGLSAMPLERPARAMETERFVPROC>(get_proc_address("glSamplerParameterfv"));
    glSamplerParameterIiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIIVPROC>(get_proc_address("glSamplerParameterIiv"));
    glSamplerParameterIuiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIUIVPROC>(get_proc_address("glSamplerParameterIuiv"));
    glGetSamplerParameteriv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIVPROC>(get_proc_address("glGetSamplerParameteriv"));
    glGetSamplerParameterIiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIIVPROC>(get_proc_address("glGetSamplerParameterIiv"));
    glGetSamplerParameterfv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERFVPROC>(get_proc_address("glGetSamplerParameterfv"));
    glGetSamplerParameterIuiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIUIVPROC>(get_proc_address("glGetSamplerParameterIuiv"));
    glQueryCounter = reinterpret_cast<PFNGLQUERYCOUNTERPROC>(get_proc_address("glQueryCounter"));
    glGetQueryObjecti64v = reinterpret_cast<PFNGLGETQUERYOBJECTI64VPROC>(get_proc_address("glGetQueryObjecti64v"));
    glGetQueryObjectui64v = reinterpret_cast<PFNGLGETQUERYOBJECTUI64VPROC>(get_proc_address("glGetQueryObjectui64v"));
    glVertexAttribDivisor = reinterpret_cast<PFNGLVERTEXATTRIBDIVISORPROC>(get_proc_address("glVertexAttribDivisor"));
    glVertexAttribP1ui = reinterpret_cast<PFNGLVERTEXATTRIBP1UIPROC>(get_proc_address("glVertexAttribP1ui"));
    glVertexAttribP1uiv = reinterpret_cast<PFNGLVERTEXATTRIBP1UIVPROC>(get_proc_address("glVertexAttribP1uiv"));
    glVertexAttribP2ui = reinterpret_cast<PFNGLVERTEXATTRIBP2UIPROC>(get_proc_address("glVertexAttribP2ui"));
    glVertexAttribP2uiv = reinterpret_cast<PFNGLVERTEXATTRIBP2UIVPROC>(get_proc_address("glVertexAttribP2uiv"));
    glVertexAttribP3ui = reinterpret_cast<PFNGLVERTEXATTRIBP3UIPROC>(get_proc_address("glVertexAttribP3ui"));
    glVertexAttribP3uiv = reinterpret_cast<PFNGLVERTEXATTRIBP3UIVPROC>(get_proc_address("glVertexAttribP3uiv"));
    glVertexAttribP4ui = reinterpret_cast<PFNGLVERTEXATTRIBP4UIPROC>(get_proc_address("glVertexAttribP4ui"));
    glVertexAttribP4uiv = reinterpret_cast<PFNGLVERTEXATTRIBP4UIVPROC>(get_proc_address("glVertexAttribP4uiv"));
    glVertexP2ui = reinterpret_cast<PFNGLVERTEXP2UIPROC>(get_proc_address("glVertexP2ui"));
    glVertexP2uiv = reinterpret_cast<PFNGLVERTEXP2UIVPROC>(get_proc_address("glVertexP2uiv"));
    glVertexP3ui = reinterpret_cast<PFNGLVERTEXP3UIPROC>(get_proc_address("glVertexP3ui"));
    glVertexP3uiv = reinterpret_cast<PFNGLVERTEXP3UIVPROC>(get_proc_address("glVertexP3uiv"));
    glVertexP4ui = reinterpret_cast<PFNGLVERTEXP4UIPROC>(get_proc_address("glVertexP4ui"));
    glVertexP4uiv = reinterpret_cast<PFNGLVERTEXP4UIVPROC>(get_proc_address("glVertexP4uiv"));
    glTexCoordP1ui = reinterpret_cast<PFNGLTEXCOORDP1UIPROC>(get_proc_address("glTexCoordP1ui"));
    glTexCoordP1uiv = reinterpret_cast<PFNGLTEXCOORDP1UIVPROC>(get_proc_address("glTexCoordP1uiv"));
    glTexCoordP2ui = reinterpret_cast<PFNGLTEXCOORDP2UIPROC>(get_proc_address("glTexCoordP2ui"));
    glTexCoordP2uiv = reinterpret_cast<PFNGLTEXCOORDP2UIVPROC>(get_proc_address("glTexCoordP2uiv"));
    glTexCoordP3ui = reinterpret_cast<PFNGLTEXCOORDP3UIPROC>(get_proc_address("glTexCoordP3ui"));
    glTexCoordP3uiv = reinterpret_cast<PFNGLTEXCOORDP3UIVPROC>(get_proc_address("glTexCoordP3uiv"));
    glTexCoordP4ui = reinterpret_cast<PFNGLTEXCOORDP4UIPROC>(get_proc_address("glTexCoordP4ui"));
    glTexCoordP4uiv = reinterpret_cast<PFNGLTEXCOORDP4UIVPROC>(get_proc_address("glTexCoordP4uiv"));
    glMultiTexCoordP1ui = reinterpret_cast<PFNGLMULTITEXCOORDP1UIPROC>(get_proc_address("glMultiTexCoordP1ui"));
    glMultiTexCoordP1uiv = reinterpret_cast<PFNGLMULTITEXCOORDP1UIVPROC>(get_proc_address("glMultiTexCoordP1uiv"));
    glMultiTexCoordP2ui = reinterpret_cast<PFNGLMULTITEXCOORDP2UIPROC>(get_proc_address("glMultiTexCoordP2ui"));
    glMultiTexCoordP2uiv = reinterpret_cast<PFNGLMULTITEXCOORDP2UIVPROC>(get_proc_address("glMultiTexCoordP2uiv"));
    glMultiTexCoordP3ui = reinterpret_cast<PFNGLMULTITEXCOORDP3UIPROC>(get_proc_address("glMultiTexCoordP3ui"));
    glMultiTexCoordP3uiv = reinterpret_cast<PFNGLMULTITEXCOORDP3UIVPROC>(get_proc_address("glMultiTexCoordP3uiv"));
    glMultiTexCoordP4ui = reinterpret_cast<PFNGLMULTITEXCOORDP4UIPROC>(get_proc_address("glMultiTexCoordP4ui"));
    glMultiTexCoordP4uiv = reinterpret_cast<PFNGLMULTITEXCOORDP4UIVPROC>(get_proc_address("glMultiTexCoordP4uiv"));
    glNormalP3ui = reinterpret_cast<PFNGLNORMALP3UIPROC>(get_proc_address("glNormalP3ui"));
    glNormalP3uiv = reinterpret_cast<PFNGLNORMALP3UIVPROC>(get_proc_address("glNormalP3uiv"));
    glColorP3ui = reinterpret_cast<PFNGLCOLORP3UIPROC>(get_proc_address("glColorP3ui"));
    glColorP3uiv = reinterpret_cast<PFNGLCOLORP3UIVPROC>(get_proc_address("glColorP3uiv"));
    glColorP4ui = reinterpret_cast<PFNGLCOLORP4UIPROC>(get_proc_address("glColorP4ui"));
    glColorP4uiv = reinterpret_cast<PFNGLCOLORP4UIVPROC>(get_proc_address("glColorP4uiv"));
    glSecondaryColorP3ui = reinterpret_cast<PFNGLSECONDARYCOLORP3UIPROC>(get_proc_address("glSecondaryColorP3ui"));
    glSecondaryColorP3uiv = reinterpret_cast<PFNGLSECONDARYCOLORP3UIVPROC>(get_proc_address("glSecondaryColorP3uiv"));
}

// ==================== OpenGL 4.0 Functions ====================

void OpenGLLoader::load_version_4_0(OpenGLLoader* loader)
{
    glMinSampleShading = reinterpret_cast<PFNGLMINSAMPLESHADINGPROC>(get_proc_address("glMinSampleShading"));
    glBlendEquationi = reinterpret_cast<PFNGLBLENDEQUATIONIPROC>(get_proc_address("glBlendEquationi"));
    glBlendEquationSeparatei = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIPROC>(get_proc_address("glBlendEquationSeparatei"));
    glBlendFunci = reinterpret_cast<PFNGLBLENDFUNCIPROC>(get_proc_address("glBlendFunci"));
    glBlendFuncSeparatei = reinterpret_cast<PFNGLBLENDFUNCSEPARATEIPROC>(get_proc_address("glBlendFuncSeparatei"));
    glDrawArraysIndirect = reinterpret_cast<PFNGLDRAWARRAYSINDIRECTPROC>(get_proc_address("glDrawArraysIndirect"));
    glDrawElementsIndirect = reinterpret_cast<PFNGLDRAWELEMENTSINDIRECTPROC>(get_proc_address("glDrawElementsIndirect"));
    glUniform1d = reinterpret_cast<PFNGLUNIFORM1DPROC>(get_proc_address("glUniform1d"));
    glUniform2d = reinterpret_cast<PFNGLUNIFORM2DPROC>(get_proc_address("glUniform2d"));
    glUniform3d = reinterpret_cast<PFNGLUNIFORM3DPROC>(get_proc_address("glUniform3d"));
    glUniform4d = reinterpret_cast<PFNGLUNIFORM4DPROC>(get_proc_address("glUniform4d"));
    glUniform1dv = reinterpret_cast<PFNGLUNIFORM1DVPROC>(get_proc_address("glUniform1dv"));
    glUniform2dv = reinterpret_cast<PFNGLUNIFORM2DVPROC>(get_proc_address("glUniform2dv"));
    glUniform3dv = reinterpret_cast<PFNGLUNIFORM3DVPROC>(get_proc_address("glUniform3dv"));
    glUniform4dv = reinterpret_cast<PFNGLUNIFORM4DVPROC>(get_proc_address("glUniform4dv"));
    glUniformMatrix2dv = reinterpret_cast<PFNGLUNIFORMMATRIX2DVPROC>(get_proc_address("glUniformMatrix2dv"));
    glUniformMatrix3dv = reinterpret_cast<PFNGLUNIFORMMATRIX3DVPROC>(get_proc_address("glUniformMatrix3dv"));
    glUniformMatrix4dv = reinterpret_cast<PFNGLUNIFORMMATRIX4DVPROC>(get_proc_address("glUniformMatrix4dv"));
    glUniformMatrix2x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3DVPROC>(get_proc_address("glUniformMatrix2x3dv"));
    glUniformMatrix2x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4DVPROC>(get_proc_address("glUniformMatrix2x4dv"));
    glUniformMatrix3x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2DVPROC>(get_proc_address("glUniformMatrix3x2dv"));
    glUniformMatrix3x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4DVPROC>(get_proc_address("glUniformMatrix3x4dv"));
    glUniformMatrix4x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2DVPROC>(get_proc_address("glUniformMatrix4x2dv"));
    glUniformMatrix4x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3DVPROC>(get_proc_address("glUniformMatrix4x3dv"));
    glGetUniformdv = reinterpret_cast<PFNGLGETUNIFORMDVPROC>(get_proc_address("glGetUniformdv"));
    glGetSubroutineUniformLocation = reinterpret_cast<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>(get_proc_address("glGetSubroutineUniformLocation"));
    glGetSubroutineIndex = reinterpret_cast<PFNGLGETSUBROUTINEINDEXPROC>(get_proc_address("glGetSubroutineIndex"));
    glGetActiveSubroutineUniformiv = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC>(get_proc_address("glGetActiveSubroutineUniformiv"));
    glGetActiveSubroutineUniformName = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC>(get_proc_address("glGetActiveSubroutineUniformName"));
    glGetActiveSubroutineName = reinterpret_cast<PFNGLGETACTIVESUBROUTINENAMEPROC>(get_proc_address("glGetActiveSubroutineName"));
    glUniformSubroutinesuiv = reinterpret_cast<PFNGLUNIFORMSUBROUTINESUIVPROC>(get_proc_address("glUniformSubroutinesuiv"));
    glGetUniformSubroutineuiv = reinterpret_cast<PFNGLGETUNIFORMSUBROUTINEUIVPROC>(get_proc_address("glGetUniformSubroutineuiv"));
    glGetProgramStageiv = reinterpret_cast<PFNGLGETPROGRAMSTAGEIVPROC>(get_proc_address("glGetProgramStageiv"));
    glPatchParameteri = reinterpret_cast<PFNGLPATCHPARAMETERIPROC>(get_proc_address("glPatchParameteri"));
    glPatchParameterfv = reinterpret_cast<PFNGLPATCHPARAMETERFVPROC>(get_proc_address("glPatchParameterfv"));
    glBindTransformFeedback = reinterpret_cast<PFNGLBINDTRANSFORMFEEDBACKPROC>(get_proc_address("glBindTransformFeedback"));
    glDeleteTransformFeedbacks = reinterpret_cast<PFNGLDELETETRANSFORMFEEDBACKSPROC>(get_proc_address("glDeleteTransformFeedbacks"));
    glGenTransformFeedbacks = reinterpret_cast<PFNGLGENTRANSFORMFEEDBACKSPROC>(get_proc_address("glGenTransformFeedbacks"));
    glIsTransformFeedback = reinterpret_cast<PFNGLISTRANSFORMFEEDBACKPROC>(get_proc_address("glIsTransformFeedback"));
    glPauseTransformFeedback = reinterpret_cast<PFNGLPAUSETRANSFORMFEEDBACKPROC>(get_proc_address("glPauseTransformFeedback"));
    glResumeTransformFeedback = reinterpret_cast<PFNGLRESUMETRANSFORMFEEDBACKPROC>(get_proc_address("glResumeTransformFeedback"));
    glDrawTransformFeedback = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKPROC>(get_proc_address("glDrawTransformFeedback"));
    glDrawTransformFeedbackStream = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC>(get_proc_address("glDrawTransformFeedbackStream"));
    glBeginQueryIndexed = reinterpret_cast<PFNGLBEGINQUERYINDEXEDPROC>(get_proc_address("glBeginQueryIndexed"));
    glEndQueryIndexed = reinterpret_cast<PFNGLENDQUERYINDEXEDPROC>(get_proc_address("glEndQueryIndexed"));
    glGetQueryIndexediv = reinterpret_cast<PFNGLGETQUERYINDEXEDIVPROC>(get_proc_address("glGetQueryIndexediv"));
}

// ==================== OpenGL 4.1 Functions ====================

void OpenGLLoader::load_version_4_1(OpenGLLoader* loader)
{
    glReleaseShaderCompiler = reinterpret_cast<PFNGLRELEASESHADERCOMPILERPROC>(get_proc_address("glReleaseShaderCompiler"));
    glShaderBinary = reinterpret_cast<PFNGLSHADERBINARYPROC>(get_proc_address("glShaderBinary"));
    glGetShaderPrecisionFormat = reinterpret_cast<PFNGLGETSHADERPRECISIONFORMATPROC>(get_proc_address("glGetShaderPrecisionFormat"));
    glDepthRangef = reinterpret_cast<PFNGLDEPTHRANGEFPROC>(get_proc_address("glDepthRangef"));
    glClearDepthf = reinterpret_cast<PFNGLCLEARDEPTHFPROC>(get_proc_address("glClearDepthf"));
    glGetProgramBinary = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC>(get_proc_address("glGetProgramBinary"));
    glProgramBinary = reinterpret_cast<PFNGLPROGRAMBINARYPROC>(get_proc_address("glProgramBinary"));
    glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>(get_proc_address("glProgramParameteri"));
    glUseProgramStages = reinterpret_cast<PFNGLUSEPROGRAMSTAGESPROC>(get_proc_address("glUseProgramStages"));
    glActiveShaderProgram = reinterpret_cast<PFNGLACTIVESHADERPROGRAMPROC>(get_proc_address("glActiveShaderProgram"));
    glCreateShaderProgramv = reinterpret_cast<PFNGLCREATESHADERPROGRAMVPROC>(get_proc_address("glCreateShaderProgramv"));
    glBindProgramPipeline = reinterpret_cast<PFNGLBINDPROGRAMPIPELINEPROC>(get_proc_address("glBindProgramPipeline"));
    glDeleteProgramPipelines = reinterpret_cast<PFNGLDELETEPROGRAMPIPELINESPROC>(get_proc_address("glDeleteProgramPipelines"));
    glGenProgramPipelines = reinterpret_cast<PFNGLGENPROGRAMPIPELINESPROC>(get_proc_address("glGenProgramPipelines"));
    glIsProgramPipeline = reinterpret_cast<PFNGLISPROGRAMPIPELINEPROC>(get_proc_address("glIsProgramPipeline"));
    glGetProgramPipelineiv = reinterpret_cast<PFNGLGETPROGRAMPIPELINEIVPROC>(get_proc_address("glGetProgramPipelineiv"));
    glProgramUniform1i = reinterpret_cast<PFNGLPROGRAMUNIFORM1IPROC>(get_proc_address("glProgramUniform1i"));
    glProgramUniform1iv = reinterpret_cast<PFNGLPROGRAMUNIFORM1IVPROC>(get_proc_address("glProgramUniform1iv"));
    glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FPROC>(get_proc_address("glProgramUniform1f"));
    glProgramUniform1fv = reinterpret_cast<PFNGLPROGRAMUNIFORM1FVPROC>(get_proc_address("glProgramUniform1fv"));
    glProgramUniform1d = reinterpret_cast<PFNGLPROGRAMUNIFORM1DPROC>(get_proc_address("glProgramUniform1d"));
    glProgramUniform1dv = reinterpret_cast<PFNGLPROGRAMUNIFORM1DVPROC>(get_proc_address("glProgramUniform1dv"));
    glProgramUniform1ui = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIPROC>(get_proc_address("glProgramUniform1ui"));
    glProgramUniform1uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIVPROC>(get_proc_address("glProgramUniform1uiv"));
    glProgramUniform2i = reinterpret_cast<PFNGLPROGRAMUNIFORM2IPROC>(get_proc_address("glProgramUniform2i"));
    glProgramUniform2iv = reinterpret_cast<PFNGLPROGRAMUNIFORM2IVPROC>(get_proc_address("glProgramUniform2iv"));
    glProgramUniform2f = reinterpret_cast<PFNGLPROGRAMUNIFORM2FPROC>(get_proc_address("glProgramUniform2f"));
    glProgramUniform2fv = reinterpret_cast<PFNGLPROGRAMUNIFORM2FVPROC>(get_proc_address("glProgramUniform2fv"));
    glProgramUniform2d = reinterpret_cast<PFNGLPROGRAMUNIFORM2DPROC>(get_proc_address("glProgramUniform2d"));
    glProgramUniform2dv = reinterpret_cast<PFNGLPROGRAMUNIFORM2DVPROC>(get_proc_address("glProgramUniform2dv"));
    glProgramUniform2ui = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIPROC>(get_proc_address("glProgramUniform2ui"));
    glProgramUniform2uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVPROC>(get_proc_address("glProgramUniform2uiv"));
    glProgramUniform3i = reinterpret_cast<PFNGLPROGRAMUNIFORM3IPROC>(get_proc_address("glProgramUniform3i"));
    glProgramUniform3iv = reinterpret_cast<PFNGLPROGRAMUNIFORM3IVPROC>(get_proc_address("glProgramUniform3iv"));
    glProgramUniform3f = reinterpret_cast<PFNGLPROGRAMUNIFORM3FPROC>(get_proc_address("glProgramUniform3f"));
    glProgramUniform3fv = reinterpret_cast<PFNGLPROGRAMUNIFORM3FVPROC>(get_proc_address("glProgramUniform3fv"));
    glProgramUniform3d = reinterpret_cast<PFNGLPROGRAMUNIFORM3DPROC>(get_proc_address("glProgramUniform3d"));
    glProgramUniform3dv = reinterpret_cast<PFNGLPROGRAMUNIFORM3DVPROC>(get_proc_address("glProgramUniform3dv"));
    glProgramUniform3ui = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIPROC>(get_proc_address("glProgramUniform3ui"));
    glProgramUniform3uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIVPROC>(get_proc_address("glProgramUniform3uiv"));
    glProgramUniform4i = reinterpret_cast<PFNGLPROGRAMUNIFORM4IPROC>(get_proc_address("glProgramUniform4i"));
    glProgramUniform4iv = reinterpret_cast<PFNGLPROGRAMUNIFORM4IVPROC>(get_proc_address("glProgramUniform4iv"));
    glProgramUniform4f = reinterpret_cast<PFNGLPROGRAMUNIFORM4FPROC>(get_proc_address("glProgramUniform4f"));
    glProgramUniform4fv = reinterpret_cast<PFNGLPROGRAMUNIFORM4FVPROC>(get_proc_address("glProgramUniform4fv"));
    glProgramUniform4d = reinterpret_cast<PFNGLPROGRAMUNIFORM4DPROC>(get_proc_address("glProgramUniform4d"));
    glProgramUniform4dv = reinterpret_cast<PFNGLPROGRAMUNIFORM4DVPROC>(get_proc_address("glProgramUniform4dv"));
    glProgramUniform4ui = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIPROC>(get_proc_address("glProgramUniform4ui"));
    glProgramUniform4uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIVPROC>(get_proc_address("glProgramUniform4uiv"));
    glProgramUniformMatrix2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>(get_proc_address("glProgramUniformMatrix2fv"));
    glProgramUniformMatrix3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>(get_proc_address("glProgramUniformMatrix3fv"));
    glProgramUniformMatrix4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(get_proc_address("glProgramUniformMatrix4fv"));
    glProgramUniformMatrix2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2DVPROC>(get_proc_address("glProgramUniformMatrix2dv"));
    glProgramUniformMatrix3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3DVPROC>(get_proc_address("glProgramUniformMatrix3dv"));
    glProgramUniformMatrix4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4DVPROC>(get_proc_address("glProgramUniformMatrix4dv"));
    glProgramUniformMatrix2x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>(get_proc_address("glProgramUniformMatrix2x3fv"));
    glProgramUniformMatrix3x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>(get_proc_address("glProgramUniformMatrix3x2fv"));
    glProgramUniformMatrix2x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>(get_proc_address("glProgramUniformMatrix2x4fv"));
    glProgramUniformMatrix4x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>(get_proc_address("glProgramUniformMatrix4x2fv"));
    glProgramUniformMatrix3x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>(get_proc_address("glProgramUniformMatrix3x4fv"));
    glProgramUniformMatrix4x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>(get_proc_address("glProgramUniformMatrix4x3fv"));
    glProgramUniformMatrix2x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC>(get_proc_address("glProgramUniformMatrix2x3dv"));
    glProgramUniformMatrix3x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC>(get_proc_address("glProgramUniformMatrix3x2dv"));
    glProgramUniformMatrix2x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC>(get_proc_address("glProgramUniformMatrix2x4dv"));
    glProgramUniformMatrix4x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC>(get_proc_address("glProgramUniformMatrix4x2dv"));
    glProgramUniformMatrix3x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC>(get_proc_address("glProgramUniformMatrix3x4dv"));
    glProgramUniformMatrix4x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC>(get_proc_address("glProgramUniformMatrix4x3dv"));
    glValidateProgramPipeline = reinterpret_cast<PFNGLVALIDATEPROGRAMPIPELINEPROC>(get_proc_address("glValidateProgramPipeline"));
    glGetProgramPipelineInfoLog = reinterpret_cast<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(get_proc_address("glGetProgramPipelineInfoLog"));
    glVertexAttribL1d = reinterpret_cast<PFNGLVERTEXATTRIBL1DPROC>(get_proc_address("glVertexAttribL1d"));
    glVertexAttribL2d = reinterpret_cast<PFNGLVERTEXATTRIBL2DPROC>(get_proc_address("glVertexAttribL2d"));
    glVertexAttribL3d = reinterpret_cast<PFNGLVERTEXATTRIBL3DPROC>(get_proc_address("glVertexAttribL3d"));
    glVertexAttribL4d = reinterpret_cast<PFNGLVERTEXATTRIBL4DPROC>(get_proc_address("glVertexAttribL4d"));
    glVertexAttribL1dv = reinterpret_cast<PFNGLVERTEXATTRIBL1DVPROC>(get_proc_address("glVertexAttribL1dv"));
    glVertexAttribL2dv = reinterpret_cast<PFNGLVERTEXATTRIBL2DVPROC>(get_proc_address("glVertexAttribL2dv"));
    glVertexAttribL3dv = reinterpret_cast<PFNGLVERTEXATTRIBL3DVPROC>(get_proc_address("glVertexAttribL3dv"));
    glVertexAttribL4dv = reinterpret_cast<PFNGLVERTEXATTRIBL4DVPROC>(get_proc_address("glVertexAttribL4dv"));
    glVertexAttribLPointer = reinterpret_cast<PFNGLVERTEXATTRIBLPOINTERPROC>(get_proc_address("glVertexAttribLPointer"));
    glGetVertexAttribLdv = reinterpret_cast<PFNGLGETVERTEXATTRIBLDVPROC>(get_proc_address("glGetVertexAttribLdv"));
    glViewportArrayv = reinterpret_cast<PFNGLVIEWPORTARRAYVPROC>(get_proc_address("glViewportArrayv"));
    glViewportIndexedf = reinterpret_cast<PFNGLVIEWPORTINDEXEDFPROC>(get_proc_address("glViewportIndexedf"));
    glViewportIndexedfv = reinterpret_cast<PFNGLVIEWPORTINDEXEDFVPROC>(get_proc_address("glViewportIndexedfv"));
    glScissorArrayv = reinterpret_cast<PFNGLSCISSORARRAYVPROC>(get_proc_address("glScissorArrayv"));
    glScissorIndexed = reinterpret_cast<PFNGLSCISSORINDEXEDPROC>(get_proc_address("glScissorIndexed"));
    glScissorIndexedv = reinterpret_cast<PFNGLSCISSORINDEXEDVPROC>(get_proc_address("glScissorIndexedv"));
    glDepthRangeArrayv = reinterpret_cast<PFNGLDEPTHRANGEARRAYVPROC>(get_proc_address("glDepthRangeArrayv"));
    glDepthRangeIndexed = reinterpret_cast<PFNGLDEPTHRANGEINDEXEDPROC>(get_proc_address("glDepthRangeIndexed"));
    glGetFloati_v = reinterpret_cast<PFNGLGETFLOATI_VPROC>(get_proc_address("glGetFloati_v"));
    glGetDoublei_v = reinterpret_cast<PFNGLGETDOUBLEI_VPROC>(get_proc_address("glGetDoublei_v"));
}

// ==================== OpenGL 4.2 Functions ====================

void OpenGLLoader::load_version_4_2(OpenGLLoader* loader)
{
    glDrawArraysInstancedBaseInstance = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC>(get_proc_address("glDrawArraysInstancedBaseInstance"));
    glDrawElementsInstancedBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC>(get_proc_address("glDrawElementsInstancedBaseInstance"));
    glDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>(get_proc_address("glDrawElementsInstancedBaseVertexBaseInstance"));
    glGetInternalformativ = reinterpret_cast<PFNGLGETINTERNALFORMATIVPROC>(get_proc_address("glGetInternalformativ"));
    glGetActiveAtomicCounterBufferiv = reinterpret_cast<PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC>(get_proc_address("glGetActiveAtomicCounterBufferiv"));
    glBindImageTexture = reinterpret_cast<PFNGLBINDIMAGETEXTUREPROC>(get_proc_address("glBindImageTexture"));
    glMemoryBarrier = reinterpret_cast<PFNGLMEMORYBARRIERPROC>(get_proc_address("glMemoryBarrier"));
    glTexStorage1D = reinterpret_cast<PFNGLTEXSTORAGE1DPROC>(get_proc_address("glTexStorage1D"));
    glTexStorage2D = reinterpret_cast<PFNGLTEXSTORAGE2DPROC>(get_proc_address("glTexStorage2D"));
    glTexStorage3D = reinterpret_cast<PFNGLTEXSTORAGE3DPROC>(get_proc_address("glTexStorage3D"));
    glDrawTransformFeedbackInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC>(get_proc_address("glDrawTransformFeedbackInstanced"));
    glDrawTransformFeedbackStreamInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC>(get_proc_address("glDrawTransformFeedbackStreamInstanced"));
}

// ==================== OpenGL 4.3 Functions ====================

void OpenGLLoader::load_version_4_3(OpenGLLoader* loader)
{
    glClearBufferData = reinterpret_cast<PFNGLCLEARBUFFERDATAPROC>(get_proc_address("glClearBufferData"));
    glClearBufferSubData = reinterpret_cast<PFNGLCLEARBUFFERSUBDATAPROC>(get_proc_address("glClearBufferSubData"));
    glDispatchCompute = reinterpret_cast<PFNGLDISPATCHCOMPUTEPROC>(get_proc_address("glDispatchCompute"));
    glDispatchComputeIndirect = reinterpret_cast<PFNGLDISPATCHCOMPUTEINDIRECTPROC>(get_proc_address("glDispatchComputeIndirect"));
    glCopyImageSubData = reinterpret_cast<PFNGLCOPYIMAGESUBDATAPROC>(get_proc_address("glCopyImageSubData"));
    glFramebufferParameteri = reinterpret_cast<PFNGLFRAMEBUFFERPARAMETERIPROC>(get_proc_address("glFramebufferParameteri"));
    glGetFramebufferParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>(get_proc_address("glGetFramebufferParameteriv"));
    glGetInternalformati64v = reinterpret_cast<PFNGLGETINTERNALFORMATI64VPROC>(get_proc_address("glGetInternalformati64v"));
    glInvalidateTexSubImage = reinterpret_cast<PFNGLINVALIDATETEXSUBIMAGEPROC>(get_proc_address("glInvalidateTexSubImage"));
    glInvalidateTexImage = reinterpret_cast<PFNGLINVALIDATETEXIMAGEPROC>(get_proc_address("glInvalidateTexImage"));
    glInvalidateBufferSubData = reinterpret_cast<PFNGLINVALIDATEBUFFERSUBDATAPROC>(get_proc_address("glInvalidateBufferSubData"));
    glInvalidateBufferData = reinterpret_cast<PFNGLINVALIDATEBUFFERDATAPROC>(get_proc_address("glInvalidateBufferData"));
    glInvalidateFramebuffer = reinterpret_cast<PFNGLINVALIDATEFRAMEBUFFERPROC>(get_proc_address("glInvalidateFramebuffer"));
    glInvalidateSubFramebuffer = reinterpret_cast<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(get_proc_address("glInvalidateSubFramebuffer"));
    glMultiDrawArraysIndirect = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTPROC>(get_proc_address("glMultiDrawArraysIndirect"));
    glMultiDrawElementsIndirect = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTPROC>(get_proc_address("glMultiDrawElementsIndirect"));
    glGetProgramInterfaceiv = reinterpret_cast<PFNGLGETPROGRAMINTERFACEIVPROC>(get_proc_address("glGetProgramInterfaceiv"));
    glGetProgramResourceIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>(get_proc_address("glGetProgramResourceIndex"));
    glGetProgramResourceName = reinterpret_cast<PFNGLGETPROGRAMRESOURCENAMEPROC>(get_proc_address("glGetProgramResourceName"));
    glGetProgramResourceiv = reinterpret_cast<PFNGLGETPROGRAMRESOURCEIVPROC>(get_proc_address("glGetProgramResourceiv"));
    glGetProgramResourceLocation = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONPROC>(get_proc_address("glGetProgramResourceLocation"));
    glGetProgramResourceLocationIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC>(get_proc_address("glGetProgramResourceLocationIndex"));
    glShaderStorageBlockBinding = reinterpret_cast<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>(get_proc_address("glShaderStorageBlockBinding"));
    glTexBufferRange = reinterpret_cast<PFNGLTEXBUFFERRANGEPROC>(get_proc_address("glTexBufferRange"));
    glTexStorage2DMultisample = reinterpret_cast<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>(get_proc_address("glTexStorage2DMultisample"));
    glTexStorage3DMultisample = reinterpret_cast<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>(get_proc_address("glTexStorage3DMultisample"));
    glTextureView = reinterpret_cast<PFNGLTEXTUREVIEWPROC>(get_proc_address("glTextureView"));
    glBindVertexBuffer = reinterpret_cast<PFNGLBINDVERTEXBUFFERPROC>(get_proc_address("glBindVertexBuffer"));
    glVertexAttribFormat = reinterpret_cast<PFNGLVERTEXATTRIBFORMATPROC>(get_proc_address("glVertexAttribFormat"));
    glVertexAttribIFormat = reinterpret_cast<PFNGLVERTEXATTRIBIFORMATPROC>(get_proc_address("glVertexAttribIFormat"));
    glVertexAttribLFormat = reinterpret_cast<PFNGLVERTEXATTRIBLFORMATPROC>(get_proc_address("glVertexAttribLFormat"));
    glVertexAttribBinding = reinterpret_cast<PFNGLVERTEXATTRIBBINDINGPROC>(get_proc_address("glVertexAttribBinding"));
    glVertexBindingDivisor = reinterpret_cast<PFNGLVERTEXBINDINGDIVISORPROC>(get_proc_address("glVertexBindingDivisor"));
    glDebugMessageControl = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>(get_proc_address("glDebugMessageControl"));
    glDebugMessageInsert = reinterpret_cast<PFNGLDEBUGMESSAGEINSERTPROC>(get_proc_address("glDebugMessageInsert"));
    glDebugMessageCallback = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>(get_proc_address("glDebugMessageCallback"));
    glGetDebugMessageLog = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGPROC>(get_proc_address("glGetDebugMessageLog"));
    glPushDebugGroup = reinterpret_cast<PFNGLPUSHDEBUGGROUPPROC>(get_proc_address("glPushDebugGroup"));
    glPopDebugGroup = reinterpret_cast<PFNGLPOPDEBUGGROUPPROC>(get_proc_address("glPopDebugGroup"));
    glObjectLabel = reinterpret_cast<PFNGLOBJECTLABELPROC>(get_proc_address("glObjectLabel"));
    glGetObjectLabel = reinterpret_cast<PFNGLGETOBJECTLABELPROC>(get_proc_address("glGetObjectLabel"));
    glObjectPtrLabel = reinterpret_cast<PFNGLOBJECTPTRLABELPROC>(get_proc_address("glObjectPtrLabel"));
    glGetObjectPtrLabel = reinterpret_cast<PFNGLGETOBJECTPTRLABELPROC>(get_proc_address("glGetObjectPtrLabel"));
}

// ==================== OpenGL 4.4 Functions ====================

void OpenGLLoader::load_version_4_4(OpenGLLoader* loader)
{
    glBufferStorage = reinterpret_cast<PFNGLBUFFERSTORAGEPROC>(get_proc_address("glBufferStorage"));
    glClearTexImage = reinterpret_cast<PFNGLCLEARTEXIMAGEPROC>(get_proc_address("glClearTexImage"));
    glClearTexSubImage = reinterpret_cast<PFNGLCLEARTEXSUBIMAGEPROC>(get_proc_address("glClearTexSubImage"));
    glBindBuffersBase = reinterpret_cast<PFNGLBINDBUFFERSBASEPROC>(get_proc_address("glBindBuffersBase"));
    glBindBuffersRange = reinterpret_cast<PFNGLBINDBUFFERSRANGEPROC>(get_proc_address("glBindBuffersRange"));
    glBindTextures = reinterpret_cast<PFNGLBINDTEXTURESPROC>(get_proc_address("glBindTextures"));
    glBindSamplers = reinterpret_cast<PFNGLBINDSAMPLERSPROC>(get_proc_address("glBindSamplers"));
    glBindImageTextures = reinterpret_cast<PFNGLBINDIMAGETEXTURESPROC>(get_proc_address("glBindImageTextures"));
    glBindVertexBuffers = reinterpret_cast<PFNGLBINDVERTEXBUFFERSPROC>(get_proc_address("glBindVertexBuffers"));
}

// ==================== OpenGL 4.5 Functions ====================

void OpenGLLoader::load_version_4_5(OpenGLLoader* loader)
{
    glClipControl = reinterpret_cast<PFNGLCLIPCONTROLPROC>(get_proc_address("glClipControl"));
    glCreateTransformFeedbacks = reinterpret_cast<PFNGLCREATETRANSFORMFEEDBACKSPROC>(get_proc_address("glCreateTransformFeedbacks"));
    glTransformFeedbackBufferBase = reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC>(get_proc_address("glTransformFeedbackBufferBase"));
    glTransformFeedbackBufferRange = reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC>(get_proc_address("glTransformFeedbackBufferRange"));
    glGetTransformFeedbackiv = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKIVPROC>(get_proc_address("glGetTransformFeedbackiv"));
    glGetTransformFeedbacki_v = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI_VPROC>(get_proc_address("glGetTransformFeedbacki_v"));
    glGetTransformFeedbacki64_v = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI64_VPROC>(get_proc_address("glGetTransformFeedbacki64_v"));
    glCreateBuffers = reinterpret_cast<PFNGLCREATEBUFFERSPROC>(get_proc_address("glCreateBuffers"));
    glNamedBufferStorage = reinterpret_cast<PFNGLNAMEDBUFFERSTORAGEPROC>(get_proc_address("glNamedBufferStorage"));
    glNamedBufferData = reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(get_proc_address("glNamedBufferData"));
    glNamedBufferSubData = reinterpret_cast<PFNGLNAMEDBUFFERSUBDATAPROC>(get_proc_address("glNamedBufferSubData"));
    glCopyNamedBufferSubData = reinterpret_cast<PFNGLCOPYNAMEDBUFFERSUBDATAPROC>(get_proc_address("glCopyNamedBufferSubData"));
    glClearNamedBufferData = reinterpret_cast<PFNGLCLEARNAMEDBUFFERDATAPROC>(get_proc_address("glClearNamedBufferData"));
    glClearNamedBufferSubData = reinterpret_cast<PFNGLCLEARNAMEDBUFFERSUBDATAPROC>(get_proc_address("glClearNamedBufferSubData"));
    glMapNamedBuffer = reinterpret_cast<PFNGLMAPNAMEDBUFFERPROC>(get_proc_address("glMapNamedBuffer"));
    glMapNamedBufferRange = reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEPROC>(get_proc_address("glMapNamedBufferRange"));
    glUnmapNamedBuffer = reinterpret_cast<PFNGLUNMAPNAMEDBUFFERPROC>(get_proc_address("glUnmapNamedBuffer"));
    glFlushMappedNamedBufferRange = reinterpret_cast<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC>(get_proc_address("glFlushMappedNamedBufferRange"));
    glGetNamedBufferParameteriv = reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERIVPROC>(get_proc_address("glGetNamedBufferParameteriv"));
    glGetNamedBufferParameteri64v = reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERI64VPROC>(get_proc_address("glGetNamedBufferParameteri64v"));
    glGetNamedBufferPointerv = reinterpret_cast<PFNGLGETNAMEDBUFFERPOINTERVPROC>(get_proc_address("glGetNamedBufferPointerv"));
    glGetNamedBufferSubData = reinterpret_cast<PFNGLGETNAMEDBUFFERSUBDATAPROC>(get_proc_address("glGetNamedBufferSubData"));
    glCreateFramebuffers = reinterpret_cast<PFNGLCREATEFRAMEBUFFERSPROC>(get_proc_address("glCreateFramebuffers"));
    glNamedFramebufferRenderbuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC>(get_proc_address("glNamedFramebufferRenderbuffer"));
    glNamedFramebufferParameteri = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC>(get_proc_address("glNamedFramebufferParameteri"));
    glNamedFramebufferTexture = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTUREPROC>(get_proc_address("glNamedFramebufferTexture"));
    glNamedFramebufferTextureLayer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC>(get_proc_address("glNamedFramebufferTextureLayer"));
    glNamedFramebufferDrawBuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC>(get_proc_address("glNamedFramebufferDrawBuffer"));
    glNamedFramebufferDrawBuffers = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC>(get_proc_address("glNamedFramebufferDrawBuffers"));
    glNamedFramebufferReadBuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC>(get_proc_address("glNamedFramebufferReadBuffer"));
    glInvalidateNamedFramebufferData = reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC>(get_proc_address("glInvalidateNamedFramebufferData"));
    glInvalidateNamedFramebufferSubData = reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC>(get_proc_address("glInvalidateNamedFramebufferSubData"));
    glClearNamedFramebufferiv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERIVPROC>(get_proc_address("glClearNamedFramebufferiv"));
    glClearNamedFramebufferuiv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC>(get_proc_address("glClearNamedFramebufferuiv"));
    glClearNamedFramebufferfv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFVPROC>(get_proc_address("glClearNamedFramebufferfv"));
    glClearNamedFramebufferfi = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFIPROC>(get_proc_address("glClearNamedFramebufferfi"));
    glBlitNamedFramebuffer = reinterpret_cast<PFNGLBLITNAMEDFRAMEBUFFERPROC>(get_proc_address("glBlitNamedFramebuffer"));
    glCheckNamedFramebufferStatus = reinterpret_cast<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC>(get_proc_address("glCheckNamedFramebufferStatus"));
    glGetNamedFramebufferParameteriv = reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC>(get_proc_address("glGetNamedFramebufferParameteriv"));
    glGetNamedFramebufferAttachmentParameteriv = reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(get_proc_address("glGetNamedFramebufferAttachmentParameteriv"));
    glCreateRenderbuffers = reinterpret_cast<PFNGLCREATERENDERBUFFERSPROC>(get_proc_address("glCreateRenderbuffers"));
    glNamedRenderbufferStorage = reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEPROC>(get_proc_address("glNamedRenderbufferStorage"));
    glNamedRenderbufferStorageMultisample = reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC>(get_proc_address("glNamedRenderbufferStorageMultisample"));
    glGetNamedRenderbufferParameteriv = reinterpret_cast<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC>(get_proc_address("glGetNamedRenderbufferParameteriv"));
    glCreateTextures = reinterpret_cast<PFNGLCREATETEXTURESPROC>(get_proc_address("glCreateTextures"));
    glTextureBuffer = reinterpret_cast<PFNGLTEXTUREBUFFERPROC>(get_proc_address("glTextureBuffer"));
    glTextureBufferRange = reinterpret_cast<PFNGLTEXTUREBUFFERRANGEPROC>(get_proc_address("glTextureBufferRange"));
    glTextureStorage1D = reinterpret_cast<PFNGLTEXTURESTORAGE1DPROC>(get_proc_address("glTextureStorage1D"));
    glTextureStorage2D = reinterpret_cast<PFNGLTEXTURESTORAGE2DPROC>(get_proc_address("glTextureStorage2D"));
    glTextureStorage3D = reinterpret_cast<PFNGLTEXTURESTORAGE3DPROC>(get_proc_address("glTextureStorage3D"));
    glTextureStorage2DMultisample = reinterpret_cast<PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC>(get_proc_address("glTextureStorage2DMultisample"));
    glTextureStorage3DMultisample = reinterpret_cast<PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC>(get_proc_address("glTextureStorage3DMultisample"));
    glTextureSubImage1D = reinterpret_cast<PFNGLTEXTURESUBIMAGE1DPROC>(get_proc_address("glTextureSubImage1D"));
    glTextureSubImage2D = reinterpret_cast<PFNGLTEXTURESUBIMAGE2DPROC>(get_proc_address("glTextureSubImage2D"));
    glTextureSubImage3D = reinterpret_cast<PFNGLTEXTURESUBIMAGE3DPROC>(get_proc_address("glTextureSubImage3D"));
    glCompressedTextureSubImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC>(get_proc_address("glCompressedTextureSubImage1D"));
    glCompressedTextureSubImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC>(get_proc_address("glCompressedTextureSubImage2D"));
    glCompressedTextureSubImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC>(get_proc_address("glCompressedTextureSubImage3D"));
    glCopyTextureSubImage1D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE1DPROC>(get_proc_address("glCopyTextureSubImage1D"));
    glCopyTextureSubImage2D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE2DPROC>(get_proc_address("glCopyTextureSubImage2D"));
    glCopyTextureSubImage3D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE3DPROC>(get_proc_address("glCopyTextureSubImage3D"));
    glTextureParameterf = reinterpret_cast<PFNGLTEXTUREPARAMETERFPROC>(get_proc_address("glTextureParameterf"));
    glTextureParameterfv = reinterpret_cast<PFNGLTEXTUREPARAMETERFVPROC>(get_proc_address("glTextureParameterfv"));
    glTextureParameteri = reinterpret_cast<PFNGLTEXTUREPARAMETERIPROC>(get_proc_address("glTextureParameteri"));
    glTextureParameterIiv = reinterpret_cast<PFNGLTEXTUREPARAMETERIIVPROC>(get_proc_address("glTextureParameterIiv"));
    glTextureParameterIuiv = reinterpret_cast<PFNGLTEXTUREPARAMETERIUIVPROC>(get_proc_address("glTextureParameterIuiv"));
    glTextureParameteriv = reinterpret_cast<PFNGLTEXTUREPARAMETERIVPROC>(get_proc_address("glTextureParameteriv"));
    glGenerateTextureMipmap = reinterpret_cast<PFNGLGENERATETEXTUREMIPMAPPROC>(get_proc_address("glGenerateTextureMipmap"));
    glBindTextureUnit = reinterpret_cast<PFNGLBINDTEXTUREUNITPROC>(get_proc_address("glBindTextureUnit"));
    glGetTextureImage = reinterpret_cast<PFNGLGETTEXTUREIMAGEPROC>(get_proc_address("glGetTextureImage"));
    glGetCompressedTextureImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC>(get_proc_address("glGetCompressedTextureImage"));
    glGetTextureLevelParameterfv = reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERFVPROC>(get_proc_address("glGetTextureLevelParameterfv"));
    glGetTextureLevelParameteriv = reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERIVPROC>(get_proc_address("glGetTextureLevelParameteriv"));
    glGetTextureParameterfv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERFVPROC>(get_proc_address("glGetTextureParameterfv"));
    glGetTextureParameterIiv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIIVPROC>(get_proc_address("glGetTextureParameterIiv"));
    glGetTextureParameterIuiv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIUIVPROC>(get_proc_address("glGetTextureParameterIuiv"));
    glGetTextureParameteriv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIVPROC>(get_proc_address("glGetTextureParameteriv"));
    glCreateVertexArrays = reinterpret_cast<PFNGLCREATEVERTEXARRAYSPROC>(get_proc_address("glCreateVertexArrays"));
    glDisableVertexArrayAttrib = reinterpret_cast<PFNGLDISABLEVERTEXARRAYATTRIBPROC>(get_proc_address("glDisableVertexArrayAttrib"));
    glEnableVertexArrayAttrib = reinterpret_cast<PFNGLENABLEVERTEXARRAYATTRIBPROC>(get_proc_address("glEnableVertexArrayAttrib"));
    glVertexArrayElementBuffer = reinterpret_cast<PFNGLVERTEXARRAYELEMENTBUFFERPROC>(get_proc_address("glVertexArrayElementBuffer"));
    glVertexArrayVertexBuffer = reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERPROC>(get_proc_address("glVertexArrayVertexBuffer"));
    glVertexArrayVertexBuffers = reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERSPROC>(get_proc_address("glVertexArrayVertexBuffers"));
    glVertexArrayAttribBinding = reinterpret_cast<PFNGLVERTEXARRAYATTRIBBINDINGPROC>(get_proc_address("glVertexArrayAttribBinding"));
    glVertexArrayAttribFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBFORMATPROC>(get_proc_address("glVertexArrayAttribFormat"));
    glVertexArrayAttribIFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBIFORMATPROC>(get_proc_address("glVertexArrayAttribIFormat"));
    glVertexArrayAttribLFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBLFORMATPROC>(get_proc_address("glVertexArrayAttribLFormat"));
    glVertexArrayBindingDivisor = reinterpret_cast<PFNGLVERTEXARRAYBINDINGDIVISORPROC>(get_proc_address("glVertexArrayBindingDivisor"));
    glGetVertexArrayiv = reinterpret_cast<PFNGLGETVERTEXARRAYIVPROC>(get_proc_address("glGetVertexArrayiv"));
    glGetVertexArrayIndexediv = reinterpret_cast<PFNGLGETVERTEXARRAYINDEXEDIVPROC>(get_proc_address("glGetVertexArrayIndexediv"));
    glGetVertexArrayIndexed64iv = reinterpret_cast<PFNGLGETVERTEXARRAYINDEXED64IVPROC>(get_proc_address("glGetVertexArrayIndexed64iv"));
    glCreateSamplers = reinterpret_cast<PFNGLCREATESAMPLERSPROC>(get_proc_address("glCreateSamplers"));
    glCreateProgramPipelines = reinterpret_cast<PFNGLCREATEPROGRAMPIPELINESPROC>(get_proc_address("glCreateProgramPipelines"));
    glCreateQueries = reinterpret_cast<PFNGLCREATEQUERIESPROC>(get_proc_address("glCreateQueries"));
    glGetQueryBufferObjecti64v = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTI64VPROC>(get_proc_address("glGetQueryBufferObjecti64v"));
    glGetQueryBufferObjectiv = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTIVPROC>(get_proc_address("glGetQueryBufferObjectiv"));
    glGetQueryBufferObjectui64v = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUI64VPROC>(get_proc_address("glGetQueryBufferObjectui64v"));
    glGetQueryBufferObjectuiv = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUIVPROC>(get_proc_address("glGetQueryBufferObjectuiv"));
    glMemoryBarrierByRegion = reinterpret_cast<PFNGLMEMORYBARRIERBYREGIONPROC>(get_proc_address("glMemoryBarrierByRegion"));
    glGetTextureSubImage = reinterpret_cast<PFNGLGETTEXTURESUBIMAGEPROC>(get_proc_address("glGetTextureSubImage"));
    glGetCompressedTextureSubImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC>(get_proc_address("glGetCompressedTextureSubImage"));
    glGetGraphicsResetStatus = reinterpret_cast<PFNGLGETGRAPHICSRESETSTATUSPROC>(get_proc_address("glGetGraphicsResetStatus"));
    glGetnCompressedTexImage = reinterpret_cast<PFNGLGETNCOMPRESSEDTEXIMAGEPROC>(get_proc_address("glGetnCompressedTexImage"));
    glGetnTexImage = reinterpret_cast<PFNGLGETNTEXIMAGEPROC>(get_proc_address("glGetnTexImage"));
    glGetnUniformdv = reinterpret_cast<PFNGLGETNUNIFORMDVPROC>(get_proc_address("glGetnUniformdv"));
    glGetnUniformfv = reinterpret_cast<PFNGLGETNUNIFORMFVPROC>(get_proc_address("glGetnUniformfv"));
    glGetnUniformiv = reinterpret_cast<PFNGLGETNUNIFORMIVPROC>(get_proc_address("glGetnUniformiv"));
    glGetnUniformuiv = reinterpret_cast<PFNGLGETNUNIFORMUIVPROC>(get_proc_address("glGetnUniformuiv"));
    glReadnPixels = reinterpret_cast<PFNGLREADNPIXELSPROC>(get_proc_address("glReadnPixels"));
    glGetnMapdv = reinterpret_cast<PFNGLGETNMAPDVPROC>(get_proc_address("glGetnMapdv"));
    glGetnMapfv = reinterpret_cast<PFNGLGETNMAPFVPROC>(get_proc_address("glGetnMapfv"));
    glGetnMapiv = reinterpret_cast<PFNGLGETNMAPIVPROC>(get_proc_address("glGetnMapiv"));
    glGetnPixelMapfv = reinterpret_cast<PFNGLGETNPIXELMAPFVPROC>(get_proc_address("glGetnPixelMapfv"));
    glGetnPixelMapuiv = reinterpret_cast<PFNGLGETNPIXELMAPUIVPROC>(get_proc_address("glGetnPixelMapuiv"));
    glGetnPixelMapusv = reinterpret_cast<PFNGLGETNPIXELMAPUSVPROC>(get_proc_address("glGetnPixelMapusv"));
    glGetnPolygonStipple = reinterpret_cast<PFNGLGETNPOLYGONSTIPPLEPROC>(get_proc_address("glGetnPolygonStipple"));
    glGetnColorTable = reinterpret_cast<PFNGLGETNCOLORTABLEPROC>(get_proc_address("glGetnColorTable"));
    glGetnConvolutionFilter = reinterpret_cast<PFNGLGETNCONVOLUTIONFILTERPROC>(get_proc_address("glGetnConvolutionFilter"));
    glGetnSeparableFilter = reinterpret_cast<PFNGLGETNSEPARABLEFILTERPROC>(get_proc_address("glGetnSeparableFilter"));
    glGetnHistogram = reinterpret_cast<PFNGLGETNHISTOGRAMPROC>(get_proc_address("glGetnHistogram"));
    glGetnMinmax = reinterpret_cast<PFNGLGETNMINMAXPROC>(get_proc_address("glGetnMinmax"));
    glTextureBarrier = reinterpret_cast<PFNGLTEXTUREBARRIERPROC>(get_proc_address("glTextureBarrier"));
}

// ==================== OpenGL 4.6 Functions ====================

void OpenGLLoader::load_version_4_6(OpenGLLoader* loader)
{
    glSpecializeShader = reinterpret_cast<PFNGLSPECIALIZESHADERPROC>(get_proc_address("glSpecializeShader"));
    glMultiDrawArraysIndirectCount = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC>(get_proc_address("glMultiDrawArraysIndirectCount"));
    glMultiDrawElementsIndirectCount = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC>(get_proc_address("glMultiDrawElementsIndirectCount"));
    glPolygonOffsetClamp = reinterpret_cast<PFNGLPOLYGONOFFSETCLAMPPROC>(get_proc_address("glPolygonOffsetClamp"));
}