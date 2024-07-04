
#ifndef WTLIB_EXPORT_H
#define WTLIB_EXPORT_H

#ifdef WTLIB_STATIC_DEFINE
#  define WTLIB_EXPORT
#  define WTLIB_NO_EXPORT
#else
#  ifndef WTLIB_EXPORT
#    ifdef sources_EXPORTS
        /* We are building this library */
#      define WTLIB_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define WTLIB_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef WTLIB_NO_EXPORT
#    define WTLIB_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef WTLIB_DEPRECATED
#  define WTLIB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef WTLIB_DEPRECATED_EXPORT
#  define WTLIB_DEPRECATED_EXPORT WTLIB_EXPORT WTLIB_DEPRECATED
#endif

#ifndef WTLIB_DEPRECATED_NO_EXPORT
#  define WTLIB_DEPRECATED_NO_EXPORT WTLIB_NO_EXPORT WTLIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef WTLIB_NO_DEPRECATED
#    define WTLIB_NO_DEPRECATED
#  endif
#endif

#endif /* WTLIB_EXPORT_H */
