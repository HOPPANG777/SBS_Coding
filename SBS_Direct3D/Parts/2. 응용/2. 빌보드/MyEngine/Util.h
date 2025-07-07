#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


#ifndef MAINBODY
#define DECLARE extern
#else
#define DECLARE
#endif

#ifndef S_DEL
#define S_DEL(p)		{ if(p) { delete (p); (p) = NULL; } }
#endif

#ifndef S_DELS
#define S_DELS(p)		{ if(p) { delete[] (p); (p) = NULL; } }
#endif

#ifndef S_REL
#define S_REL(p)		{ if(p) { (p)->Release(); (p) = NULL; } }
#endif

#define IS_IN_RANGE(value,r0,r1) (( ((r0) <= (value)) && ((value) <= (r1)) ) ? 1 : 0)


#endif