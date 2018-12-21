# 1 "jpeg.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "jpeg.c"

# 1 "E:/OS/compilers/MinGW/include/stdio.h" 1 3
# 19 "E:/OS/compilers/MinGW/include/stdio.h" 3
# 1 "E:/OS/compilers/MinGW/include/_mingw.h" 1 3
# 32 "E:/OS/compilers/MinGW/include/_mingw.h" 3
       
# 33 "E:/OS/compilers/MinGW/include/_mingw.h" 3
# 20 "E:/OS/compilers/MinGW/include/stdio.h" 2 3






# 1 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 1 3 4
# 216 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 3 4

# 216 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 3 4
typedef unsigned int size_t;
# 328 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 3 4
typedef short unsigned int wchar_t;
# 357 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 3 4
typedef short unsigned int wint_t;
# 27 "E:/OS/compilers/MinGW/include/stdio.h" 2 3

# 1 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stdarg.h" 1 3 4
# 40 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 29 "E:/OS/compilers/MinGW/include/stdio.h" 2 3
# 129 "E:/OS/compilers/MinGW/include/stdio.h" 3
typedef struct _iobuf
{
 char* _ptr;
 int _cnt;
 char* _base;
 int _flag;
 int _file;
 int _charbuf;
 int _bufsiz;
 char* _tmpfname;
} FILE;
# 154 "E:/OS/compilers/MinGW/include/stdio.h" 3
extern __attribute__ ((__dllimport__)) FILE _iob[];
# 169 "E:/OS/compilers/MinGW/include/stdio.h" 3
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fopen (const char*, const char*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) freopen (const char*, const char*, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fflush (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fclose (FILE*);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) remove (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rename (const char*, const char*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tmpfile (void);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tmpnam (char*);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _rmtmp(void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _unlink (const char*);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rmtmp(void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) unlink (const char*);



 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) setvbuf (FILE*, char*, int, size_t);

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) setbuf (FILE*, char*);
# 204 "E:/OS/compilers/MinGW/include/stdio.h" 3
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_fprintf(FILE*, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_printf(const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_sprintf(char*, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_snprintf(char*, size_t, const char*, ...);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vfprintf(FILE*, const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vprintf(const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vsprintf(char*, const char*, __gnuc_va_list);
extern int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __mingw_vsnprintf(char*, size_t, const char*, __gnuc_va_list);
# 293 "E:/OS/compilers/MinGW/include/stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fprintf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) printf (const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) sprintf (char*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfprintf (FILE*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vprintf (const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsprintf (char*, const char*, __gnuc_va_list);
# 308 "E:/OS/compilers/MinGW/include/stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_fprintf(FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_printf(const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_sprintf(char*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vfprintf(FILE*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vprintf(const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __msvcrt_vsprintf(char*, const char*, __gnuc_va_list);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _snprintf (char*, size_t, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vsnprintf (char*, size_t, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vscprintf (const char*, __gnuc_va_list);
# 331 "E:/OS/compilers/MinGW/include/stdio.h" 3
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) snprintf (char *, size_t, const char *, ...);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsnprintf (char *, size_t, const char *, __gnuc_va_list);

int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vscanf (const char * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfscanf (FILE * __restrict__, const char * __restrict__,
       __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsscanf (const char * __restrict__,
       const char * __restrict__, __gnuc_va_list);







 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fscanf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) scanf (const char*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) sscanf (const char*, const char*, ...);




 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetc (FILE*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgets (char*, int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputc (int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputs (const char*, FILE*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) gets (char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) puts (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ungetc (int, FILE*);







 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _filbuf (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _flsbuf (int, FILE*);



extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getc (FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) *__F->_ptr++
    : _filbuf (__F);
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putc (int __c, FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) (*__F->_ptr++ = (char)__c)
    : _flsbuf (__c, __F);
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getchar (void)
{
  return (--(&_iob[0])->_cnt >= 0)
    ? (int) (unsigned char) *(&_iob[0])->_ptr++
    : _filbuf ((&_iob[0]));
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putchar(int __c)
{
  return (--(&_iob[1])->_cnt >= 0)
    ? (int) (unsigned char) (*(&_iob[1])->_ptr++ = (char)__c)
    : _flsbuf (__c, (&_iob[1]));}
# 412 "E:/OS/compilers/MinGW/include/stdio.h" 3
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fread (void*, size_t, size_t, FILE*);
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwrite (const void*, size_t, size_t, FILE*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fseek (FILE*, long, int);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ftell (FILE*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rewind (FILE*);
# 455 "E:/OS/compilers/MinGW/include/stdio.h" 3
typedef long long fpos_t;




 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetpos (FILE*, fpos_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fsetpos (FILE*, const fpos_t*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) feof (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ferror (FILE*);
# 480 "E:/OS/compilers/MinGW/include/stdio.h" 3
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) clearerr (FILE*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) perror (const char*);






 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _popen (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _pclose (FILE*);


 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) popen (const char*, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) pclose (FILE*);





 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _flushall (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fgetchar (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fputchar (int);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fdopen (int, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fileno (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fcloseall (void);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fsopen (const char*, const char*, int);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getmaxstdio (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _setmaxstdio (int);
# 522 "E:/OS/compilers/MinGW/include/stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetchar (void);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputchar (int);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fdopen (int, const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fileno (FILE*);
# 534 "E:/OS/compilers/MinGW/include/stdio.h" 3
# 1 "E:/OS/compilers/MinGW/include/sys/types.h" 1 3
# 21 "E:/OS/compilers/MinGW/include/sys/types.h" 3
# 1 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 1 3 4
# 149 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 22 "E:/OS/compilers/MinGW/include/sys/types.h" 2 3





typedef long __time32_t;




typedef long long __time64_t;
# 45 "E:/OS/compilers/MinGW/include/sys/types.h" 3
typedef __time32_t time_t;






typedef long _off_t;


typedef _off_t off_t;







typedef unsigned int _dev_t;





typedef _dev_t dev_t;






typedef short _ino_t;


typedef _ino_t ino_t;






typedef int _pid_t;


typedef _pid_t pid_t;






typedef unsigned short _mode_t;


typedef _mode_t mode_t;






typedef int _sigset_t;


typedef _sigset_t sigset_t;





typedef int _ssize_t;


typedef _ssize_t ssize_t;





typedef long long fpos64_t;




typedef long long off64_t;



typedef unsigned int useconds_t;
# 535 "E:/OS/compilers/MinGW/include/stdio.h" 2 3
extern inline __attribute__((__gnu_inline__)) FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fopen64 (const char* filename, const char* mode)
{
  return fopen (filename, mode);
}

int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fseeko64 (FILE*, off64_t, int);






extern inline __attribute__((__gnu_inline__)) off64_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ftello64 (FILE * stream)
{
  fpos_t pos;
  if (fgetpos(stream, &pos))
    return -1LL;
  else
   return ((off64_t) pos);
}
# 563 "E:/OS/compilers/MinGW/include/stdio.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwprintf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wprintf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _snwprintf (wchar_t*, size_t, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfwprintf (FILE*, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vwprintf (const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vsnwprintf (wchar_t*, size_t, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _vscwprintf (const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fwscanf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wscanf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) swscanf (const wchar_t*, const wchar_t*, ...);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetwc (FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputwc (wchar_t, FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ungetwc (wchar_t, FILE*);



 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) swprintf (wchar_t*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vswprintf (wchar_t*, const wchar_t*, __gnuc_va_list);



 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetws (wchar_t*, int, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputws (const wchar_t*, FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getwc (FILE*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getwchar (void);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getws (wchar_t*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putwc (wint_t, FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putws (const wchar_t*);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putwchar (wint_t);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfdopen(int, const wchar_t *);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfopen (const wchar_t*, const wchar_t*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfreopen (const wchar_t*, const wchar_t*, FILE*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfsopen (const wchar_t*, const wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtmpnam (wchar_t*);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtempnam (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wrename (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wremove (const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wperror (const wchar_t*);
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wpopen (const wchar_t*, const wchar_t*);



int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) snwprintf (wchar_t* s, size_t n, const wchar_t* format, ...);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, __gnuc_va_list arg);





int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vwscanf (const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vfwscanf (FILE * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) vswscanf (const wchar_t * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
# 625 "E:/OS/compilers/MinGW/include/stdio.h" 3
 FILE* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wpopen (const wchar_t*, const wchar_t*);






 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fgetwchar (void);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fputwchar (wint_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _getw (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putw (int, FILE*);


 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fgetwchar (void);
 wint_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fputwchar (wint_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getw (FILE*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putw (int, FILE*);
# 3 "jpeg.c" 2
# 1 "E:/OS/compilers/MinGW/include/stdlib.h" 1 3
# 21 "E:/OS/compilers/MinGW/include/stdlib.h" 3
# 1 "E:/OS/compilers/MinGW/lib/gcc/mingw32/5.1.0/include/stddef.h" 1 3 4
# 22 "E:/OS/compilers/MinGW/include/stdlib.h" 2 3
# 71 "E:/OS/compilers/MinGW/include/stdlib.h" 3
extern int _argc;
extern char** _argv;




extern int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___argc(void);
extern char*** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___argv(void);
extern wchar_t*** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p___wargv(void);
# 112 "E:/OS/compilers/MinGW/include/stdlib.h" 3
   extern __attribute__ ((__dllimport__)) int __mb_cur_max;
# 137 "E:/OS/compilers/MinGW/include/stdlib.h" 3
 int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _errno(void);


 int* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __doserrno(void);
# 149 "E:/OS/compilers/MinGW/include/stdlib.h" 3
  extern char *** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__environ(void);
  extern wchar_t *** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__wenviron(void);
# 172 "E:/OS/compilers/MinGW/include/stdlib.h" 3
  extern __attribute__ ((__dllimport__)) int _sys_nerr;
# 196 "E:/OS/compilers/MinGW/include/stdlib.h" 3
extern __attribute__ ((__dllimport__)) char* _sys_errlist[];
# 209 "E:/OS/compilers/MinGW/include/stdlib.h" 3
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__osver(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winver(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winmajor(void);
extern unsigned __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) int* __p__winminor(void);







extern __attribute__ ((__dllimport__)) unsigned int _osver;
extern __attribute__ ((__dllimport__)) unsigned int _winver;
extern __attribute__ ((__dllimport__)) unsigned int _winmajor;
extern __attribute__ ((__dllimport__)) unsigned int _winminor;
# 260 "E:/OS/compilers/MinGW/include/stdlib.h" 3
 char** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__pgmptr(void);

 wchar_t** __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __p__wpgmptr(void);
# 293 "E:/OS/compilers/MinGW/include/stdlib.h" 3
extern __attribute__ ((__dllimport__)) int _fmode;
# 303 "E:/OS/compilers/MinGW/include/stdlib.h" 3
 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atof (const char*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atoi (const char*);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atol (const char*);

 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtof (const wchar_t *);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtoi (const wchar_t *);
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtol (const wchar_t *);


double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __strtod (const char*, char**);
extern double __attribute__((__cdecl__)) __attribute__ ((__nothrow__))
strtod (const char* __restrict__ __nptr, char** __restrict__ __endptr);
float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtof (const char * __restrict__, char ** __restrict__);
long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtold (const char * __restrict__, char ** __restrict__);




 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtol (const char*, char**, int);
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoul (const char*, char**, int);



 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstol (const wchar_t*, wchar_t**, int);
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstoul (const wchar_t*, wchar_t**, int);
 double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstod (const wchar_t*, wchar_t**);

float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstof( const wchar_t * __restrict__, wchar_t ** __restrict__);
long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstold (const wchar_t * __restrict__, wchar_t ** __restrict__);


 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wgetenv(const wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wputenv(const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsearchenv(const wchar_t*, const wchar_t*, wchar_t*);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsystem(const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wmakepath(wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wsplitpath (const wchar_t*, wchar_t*, wchar_t*, wchar_t*, wchar_t*);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wfullpath (wchar_t*, const wchar_t*, size_t);




 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wcstombs (char*, const wchar_t*, size_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wctomb (char*, wchar_t);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mblen (const char*, size_t);
 size_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mbstowcs (wchar_t*, const char*, size_t);
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mbtowc (wchar_t*, const char*, size_t);

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) rand (void);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) srand (unsigned int);

 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) calloc (size_t, size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) malloc (size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) realloc (void*, size_t);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) free (void*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) abort (void) __attribute__ ((__noreturn__));
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit (int) __attribute__ ((__noreturn__));


int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atexit (void (*)(void));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) system (const char*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) getenv (const char*);


 void* __attribute__((__cdecl__)) bsearch (const void*, const void*, size_t, size_t,
          int (*)(const void*, const void*));
 void __attribute__((__cdecl__)) qsort(void*, size_t, size_t,
      int (*)(const void*, const void*));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) abs (int) __attribute__ ((__const__));
 long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) labs (long) __attribute__ ((__const__));
# 385 "E:/OS/compilers/MinGW/include/stdlib.h" 3
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

 div_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) div (int, int) __attribute__ ((__const__));
 ldiv_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ldiv (long, long) __attribute__ ((__const__));







 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _beep (unsigned int, unsigned int) __attribute__ ((__deprecated__));

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _seterrormode (int) __attribute__ ((__deprecated__));
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _sleep (unsigned long) __attribute__ ((__deprecated__));

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit (int) __attribute__ ((__noreturn__));



typedef int (* _onexit_t)(void);
_onexit_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _onexit( _onexit_t );

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _putenv (const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _searchenv (const char*, const char*, char*);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _gcvt (double, int, char*);

 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _makepath (char*, const char*, const char*, const char*, const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _splitpath (const char*, char*, char*, char*, char*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fullpath (char*, const char*, size_t);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _itoa (int, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ltoa (long, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ultoa(unsigned long, char*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _itow (int, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ltow (long, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ultow (unsigned long, wchar_t*, int);


 long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _atoi64(const char *);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _i64toa(long long, char *, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ui64toa(unsigned long long, char *, int);
 long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _wtoi64(const wchar_t *);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _i64tow(long long, wchar_t *, int);
 wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _ui64tow(unsigned long long, wchar_t *, int);

 unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_rotl)(unsigned int, int) __attribute__ ((__const__));
 unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_rotr)(unsigned int, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_lrotl)(unsigned long, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) (_lrotr)(unsigned long, int) __attribute__ ((__const__));

 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _set_error_mode (int);
# 477 "E:/OS/compilers/MinGW/include/stdlib.h" 3
 int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) putenv (const char*);
 void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) searchenv (const char*, const char*, char*);

 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) itoa (int, char*, int);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ltoa (long, char*, int);


 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) gcvt (double, int, char*);
# 497 "E:/OS/compilers/MinGW/include/stdlib.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _Exit(int) __attribute__ ((__noreturn__));





typedef struct { long long quot, rem; } lldiv_t;

lldiv_t __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lldiv (long long, long long) __attribute__ ((__const__));

long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) llabs(long long);





long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoll (const char* __restrict__, char** __restrict, int);
unsigned long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtoull (const char* __restrict__, char** __restrict__, int);


long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) atoll (const char *);


long long __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) wtoll (const wchar_t *);
char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lltoa (long long, char *, int);
char* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ulltoa (unsigned long long , char *, int);
wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) lltow (long long, wchar_t *, int);
wchar_t* __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) ulltow (unsigned long long, wchar_t *, int);
# 4 "jpeg.c" 2
# 13 "jpeg.c"

# 13 "jpeg.c"
int handle(void * a) {

}
unsigned short bswap16(unsigned short q)
{
 return ((q & 0xFF) << 8) + ((q >> 8) & 0xff);
}
unsigned char zigzag_table8[8][8];
 unsigned char quant[16][16][16];
unsigned char scan[16][16][256];
unsigned char huf_codes[4096][16][2];
short huf_len[16][16][2];
short dct[256];
short zigzagx[64];
short zigzagy[64];
double sqrt(double x) {
 double r;
 __asm__ __volatile__("fsqrt": "=t"(r) : "0"(x) : "memory");
 return r;
}

double cos(double x) {
 double r;
 __asm__ __volatile__("fcos": "=t"(r) : "0"(x) : "memory");
 return r;
}
double pi = 0.196349540849362;
typedef struct _btree {
 short val, len;
 struct _btree * l;
 struct _btree * r;
 struct _btree * parent;
} btree;

void ptree(btree *p, int indent, btree * el)
{
 if (p != 
# 49 "jpeg.c" 3 4
         ((void *)0)
# 49 "jpeg.c"
             ) {
  if (p->r) {
   ptree(p->r, indent + 4, el);
  }
  if (indent) {
   for (int i = 0; i < indent; i++)
    printf(" ");
  }
  if (p->r) {
   printf(" /\n"); for (int i = 0; i < indent; i++)
    printf(" ");
  }
  if (p != el)
   printf("%02x \n", p->val);
  else
   printf("!%02x! \n", p->val);
  if (p->l) {
   for (int i = 0; i < indent; i++)
    printf(" ");
   printf(" \\\n");
   ptree(p->l, indent + 4, el);
  }
 }
}
btree * huffs[16][2] = { 0 };
btree * last_insert;
btree * huf_insert(btree * where, int val, int clen, int nlen)
{
 if (!where)
 {
  where = malloc(sizeof(btree));
  where->l = 0;
  where->r = 0;
  where->parent = 0;
  where->val = val;
  where->len = clen;
  if (clen == nlen) {
   last_insert = where;
   return where;
  }

 }

 if (!where->l)
 {
  where->l = huf_insert(where->l, val, clen + 1, nlen);
  where->l->parent = where;
  return where;
 }
 if (!where->r)
 {
  where->r = huf_insert(where->r, val, clen + 1, nlen);
  where->r->parent = where;
  return where;
 }
 return huf_insert(where->parent, val, clen - 1, nlen);
}
float matrix[16][16][8][8];
int mcnt[16] = { 0 };
float sx[16][16][16][16];
static btree *init_branches(btree *racine)
{
 btree *fils = malloc(sizeof(btree));
 fils->parent = racine;
 fils->r = 
# 113 "jpeg.c" 3 4
          ((void *)0)
# 113 "jpeg.c"
              ;
 fils->l = 
# 114 "jpeg.c" 3 4
          ((void *)0)
# 114 "jpeg.c"
              ;
 return fils;
}




#pragma GCC push_options
#pragma GCC optimize ("Ofast")


float sxx[16][16][8][8];
typedef struct {
 float a[8][8];
} wow;
typedef struct {
 float a[8][8];
} wow1;
float table[64];
float compute(int x, int y, wow * matrix1)
{
 float tmp[4]={50};
 float tmp2[4]={0};

 wow1 * sxx1 = &sxx[x][y];
# 148 "jpeg.c"
 __asm__("	push %%esi\n	push %%edi\n	movl %1, %%esi\n	movl %0, %%edi\n	movups (%%esi),%%xmm0\n	movups %%xmm0,(%%edi)\n	pop %%edi\n	pop %%esi\n	"::"r"(&tmp),"r"(&tmp2));
# 159 "jpeg.c"
 return tmp[0]+tmp[1]+tmp[2]+tmp[3];
}

void preo(int j, int curcnt1)
{
 wow * matrix1 = &matrix[curcnt1][j];

 for (unsigned char x = 0; x < 8; x++) {
  for (unsigned char y = 0; y < 8; y++) {

   sx[y][x][curcnt1][j] = compute(x, y, matrix1) / 4;
  }
 }
}Window *w;
int Imgsx = 0, Imgsy = 0;
void draw(int ofx, int ofy)
{
 for (int i = 0; i < 16; i++) {
  if (ofy + i < Imgsy)
   for (int j = 0; j < 16; j++)
   {
    if (ofx + j >= 719 || ofx + j >= Imgsx)
     break;
    float valr = sx[j & 7][i & 7][(i >> 3) * 2 + (j >> 3)][0] + sx[j >> 1][i >> 1][0][2] * 1.402 + 128;
    if (valr > 255)
     valr = 255;
    if (valr < 0)
     valr = 0;

    float valg = sx[j & 7][i & 7][(i >> 3) * 2 + (j >> 3)][0] - sx[j >> 1][i >> 1][0][1] * 0.34414 - sx[j >> 1][i >> 1][0][2] * 0.71414 + 128;
    if (valg > 255)
     valg = 255;
    if (valg < 0)
     valg = 0;

    int valb = sx[j & 7][i & 7][(i >> 3) * 2 + (j >> 3)][0] + sx[j >> 1][i >> 1][0][1] * 1.772 + 128;
    if (valb > 255)
     valb = 255;
    if (valb < 0)
     valb = 0;







   }
 }
}

   int comp[16];
int lcoef, lcoef1, lcoef2;
int prep(int j, int *cpos1, int *mask1, unsigned char *fs)
{
 int cpos = *cpos1;
 short mask = *mask1;
      int curcnt1 = mcnt[j];

     int matrixpos = 0;
     for (; matrixpos < 64;)
     {
      sx[zigzagx[matrixpos]][zigzagy[matrixpos]][curcnt1][j] = 0;
      matrix[curcnt1][j][zigzagx[matrixpos]][zigzagy[matrixpos]] = 0;
      matrixpos++;
     }
     matrixpos = 0;

     int idxd = (comp[j] >> 4) & 0xF;
     int idxa = (comp[j]) & 0xF;

     btree * cur = huffs[idxd][0];

     while (cur->r || cur->l)
     {
      if (mask&fs[cpos])
       cur = cur->r;
      else
       cur = cur->l;
      if (mask == 1) {
       mask = 0x100;
       cpos++;
      }
      if (!cur)
       return 1;
      mask >>= 1;

     }

     int coef = 0;
     int fwer = (fs[cpos] & mask ? 1 : 0);
     for (int i = 0; i < cur->val; i++)
     {
      coef = coef * 2 + (fs[cpos] & mask ? 1 : 0);
      if (mask == 1) {
       mask = 0x100;
       cpos++;
      }
      mask >>= 1;
     }
     if (!fwer&&cur->val > 0)
      coef = coef - (1 << cur->val) + 1;
     if (j == 0) {
      coef += lcoef;
      lcoef = coef;
     }
     if (j == 1) {
      coef += lcoef1;
      lcoef1 = coef;
     }
     if (j == 2) {
      coef += lcoef2;
      lcoef2 = coef;
     }
     wow * matrix1=&matrix[curcnt1][j];
     matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = coef;
     matrixpos++;


     while (matrixpos < 64) {

      cur = huffs[idxa][1];

      while (cur->r || cur->l)
      {
       if (mask&fs[cpos])
        cur = cur->r;
       else
        cur = cur->l;
       if (mask == 1) {
        mask = 0x100;
        cpos++;
       }
       mask >>= 1;

      }

      if (!cur->val)
       break;
      for (int i = 0; i < (cur->val) >> 4; i++) {
       if (matrixpos > 63)
        break;
       matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = 0;
       matrixpos++;
      }
      int coeflen = cur->val & 0xF;
      int acoef = 0;
      fwer = (fs[cpos] & mask ? 1 : 0);
      for (int i = 0; i < coeflen; i++)
      {
       acoef = acoef * 2 + (fs[cpos] & mask ? 1 : 0);
       if (mask == 1) {
        mask = 0x100;
        cpos++;
       }
       mask >>= 1;
      }

      if (!fwer)
       acoef = acoef - (1 << coeflen) + 1;
      if (matrixpos > 63)
       break;
      matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = acoef;
      matrixpos++;
     }
     for (int i = 0; i < 8; i++) {
      for (int ou = 0; ou < 8; ou++) {
       matrix1->a[ou][i]*= quant[ou][i][dct[j] & 0xFF];
      }
     }



     preo(j, curcnt1);
     mcnt[j]++;
*mask1 = mask;
 *cpos1 = cpos;
     if (mcnt[j] == ((dct[j] >> 12) & 0xF)*((dct[j] >> 8) & 0xF))
      return 1;



 return 0;
}
#pragma GCC pop_options

int main(int argc, char ** argv)
{



 _zzk(argc, argv);
}
#pragma GCC push_options
#pragma GCC optimize ("Ofast")
void _zzk(int argc, char ** argv) {

 FILE * z = fopen(argv[1], "rb");
 if (!z)
 {
  printf("Can't find file %s!\n", argv[1]);
  return;
 }

 fseek(z, 0, 2);
 int sz = ftell(z);
 rewind(z);
 unsigned short current = 0;
 fread(&current, 1, 2, z);

 if (current != 0xD8FF)
  return 0;



 int cursz = 8; int q = 0;
 for (int i = 0; i <= cursz * 2 - 1; i++)
 {
  if ((i % 2))
  {
   int x = -1, y = i;
   for (int t = 0; t < i; t++)
   {
    x++;
    y--;
    if ((x >= 0) && (x < cursz) && (y >= 0) && (y < cursz))
    {
     q++; zigzag_table8[x][y] = q;
    }
   }
  }
  else
  {
   int y = -1, x = i;
   for (int t = 0; t < i; t++)
   {
    y++; x--;
    if ((x >= 0) && (x < cursz) && (y >= 0) && (y < cursz))
    {
     q++; zigzag_table8[x][y] = q;
    }
   }
  }
 }
 for (int i = 0; i < 8; i++)
  for (int j = 0; j < 8; j++)
  {
   zigzagx[zigzag_table8[j][i] - 1] = j;
   zigzagy[zigzag_table8[j][i] - 1] = i;

  }
 float sqrt2 = sqrt(2) / 2;
 for (int x = 0; x < 8; x++) {
  for (int y = 0; y < 8; y++) {
   for (int u = 0; u < 8; u++)
    for (int v = 0; v < 8; v++)
    {
     float v1 = 1;
     if (u == 0)
      v1 = sqrt2;
     float v2 = 1;
     if (v == 0)
      v2 = sqrt2;
     sxx[x][y][u][v] = cos(((x + x) + 1)*u*pi)*cos(((y + y) + 1)*v*pi)*v1*v2;
    }
  }
 }

 conread:
  if (ftell(z) >= sz)
   goto endread;
  fread(&current, 2, 1, z);
  current = bswap16(current);
  if (current == 0xFFFE)
  {
   fread(&current, 2, 1, z);
   current = bswap16(current);
   current -= 2;


   fseek(z, current, 1);



   goto conread;
  }
  if (current == 0xFFDB)
  {
   fread(&current, 2, 1, z);
   current = bswap16(current);
   current -= 3;
   int mask = 0;
   fread(&mask, 1, 1, z);
   int len = 1 + ((mask >> 4) & 0xF);
   int idx = mask & 0xF;
   int sx = (current);
   unsigned char * data = malloc(sx);
   fread(data, sx, 1, z);


   for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
     quant[j][i][idx] = (int)data[zigzag_table8[j][i] - 1];

    }

   }
   free(data);
   goto conread;
  }
  if (current == 0xffc0)
  {
   fread(&current, 2, 1, z);
   current = bswap16(current);
   int precis = 0;
   fread(&precis, 1, 1, z);
   fread(&Imgsy, 2, 1, z);
   Imgsy = bswap16(Imgsy);
   fread(&Imgsx, 2, 1, z);
   Imgsx = bswap16(Imgsx);
   int cnt = 0;
   fread(&cnt, 1, 1, z);
   for (int i = 0; i < cnt; i++)
   {
    int wz;
    fread(&wz, 1, 3, z);
    dct[i] = bswap16(wz >> 8);

   }
   goto conread;
  }
  if (current == 0xFFC4)
  {

   fread(&current, 2, 1, z);
   current = bswap16(current);
   int q = 0;
   fread(&q, 1, 1, z);
   int cnt = 0;
   int dest[16] = { 0 };
   for (int i = 0; i < 16; i++)
   {
    unsigned char coef = 0;
    fread(&coef, 1, 1, z);
    dest[i] = coef;
    huf_len[i][q & 0xF][q >> 4] = coef;
    cnt += coef;

   }
   btree * huffman_table = init_branches(0);
   huffs[q & 0xF][q >> 4] = huffman_table;
   huffs[q & 0xF][q >> 4]->l = 0;
   huffs[q & 0xF][q >> 4]->r = 0;
   huffs[q & 0xF][q >> 4]->parent = 0;
   huffs[q & 0xF][q >> 4]->val = 0;
   huffs[q & 0xF][q >> 4]->len = 0;
   int *symbole = malloc(4 * cnt + 20);
   for (int i = 0; i < cnt; i++) {
    unsigned char wsz;
    fread(&wsz, 1, 1, z);
    symbole[i] = wsz;
   }
   unsigned char k = 0;
   unsigned char descendu = 0;
   for (unsigned char i = 0; i < 16; i++) {
    unsigned int nombre_symboles = dest[i];
    unsigned char a_descendre = i + 1 - descendu;
    for (unsigned char j = 0; j < nombre_symboles; j++) {
     while (a_descendre > 0) {
      if (huffman_table->l == 
# 528 "jpeg.c" 3 4
                             ((void *)0)
# 528 "jpeg.c"
                                 ) {
       btree *huffman_tablefg = init_branches(huffman_table);
       huffman_table->l = huffman_tablefg;
       huffman_table = huffman_table->l;
       a_descendre = a_descendre - 1;
       descendu += 1;
      }
      else if (huffman_table->r == 
# 535 "jpeg.c" 3 4
                                  ((void *)0)
# 535 "jpeg.c"
                                      ) {
       btree *huffman_tablefd = init_branches(huffman_table);
       huffman_table->r = huffman_tablefd;
       huffman_table = huffman_table->r;
       a_descendre = a_descendre - 1;
       descendu += 1;
      }
      else {
       huffman_table = huffman_table->parent;
       a_descendre = a_descendre + 1;
       descendu -= 1;
      }
     }

     huffman_table->val = symbole[k];
     k = k + 1;
     huffman_table = huffman_table->parent;
     a_descendre = a_descendre + 1;
     descendu -= 1;
    }
   }

   goto conread;
  }
  if (current == 0xFFDA)
  {
   int hlen = 0;
   fread(&hlen, 2, 1, z);
   hlen = bswap16(hlen);
   int scanC = 0;
   fread(&scanC, 1, 1, z);
   char * s = malloc(9);
   for (int i = 0; i < scanC; i++)
   {
    int q;
    fread(&q, 2, 1, z);
    comp[i] = q >> 8;
   }
   int pos[10];

   fread(&pos, hlen - (scanC * 2) - 2 - 1, 1, z);

   int spos = ftell(z);
   int cnt = 0;
   int juye = 1;
   int lsval = 0;
   unsigned char * nuf = malloc(4096*16*4);
   unsigned char * fss=0;;
   int wok = 0;
   while (juye) {
    fread(nuf, 4096*16*4, 1, z);
    wok+=4096*16*4;
    unsigned char * lp = malloc(wok);
    memcpy(lp, fss, wok - 4096*16*4);
    if(fss) free(fss);
    fss=lp;
    memcpy((uint)fss+wok-4096*16*4, nuf, 4096*16*4);
    for (int i = 0; i < 4096*16*4; i++)
    {
     if (lsval == 0xFF && nuf[i] == 0xD9)
     {
      juye = 0;
      break;
     }
     lsval = nuf[i];
     cnt++;
    }

   }

   cnt--;



   unsigned char * fs = malloc(2 + cnt);
   int c2 = 0;
   int clenn = 0, cntw = 0;
   for (clenn = 0; c2 < cnt; clenn++)
   {
    fs[clenn] = fss[c2];
    if (fss[c2] == 0xFF) {
     if (fss[c2 + 1] == 0 && c2 < cnt)c2++;

     cntw++;
    }
    c2++;
   }


   free(fss);
   cnt = clenn;

   int mask = 0x80;
   int cpos = 0;
   int ofx = 0; int ofy = 0; cpos = 0;

  treutr:

   for (int i = 0; i < 16; i++) {
    mcnt[i] = 0;
   }
   for (int j = 0; j < scanC; j++) {

    while (!prep(j, &cpos, &mask, fs)) {

    }
   }
   draw(ofx, ofy);
   ofx += 16;
   if (ofx >= Imgsx)
   {
    ofx = 0;
    ofy += 16;
   }
   if (cpos < cnt)
    goto treutr;

  }

  goto conread;
 endread:


 return 0;
}
