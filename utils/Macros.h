#ifndef _NUMLEN_H
#define _NUMLEN_H

#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define PASTE2( a, b) a##b
#define PASTE( a, b) PASTE2( a, b)

#define lenptrstr(ptr) ((sizeof(ptr) * 2))

#endif