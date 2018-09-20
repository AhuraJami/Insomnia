#ifndef INSOMNIA_EXPORTS_H
#define INSOMNIA_EXPORTS_H

#ifdef _WIN32
    #ifndef INSOMNIA_API
        #ifdef INSOMNIA_DLL_EXPORTS
            /* We are building this library */
            #define INSOMNIA_API       __declspec(dllexport)
            #define INSOMNIA_EXPORT    __declspec(dllexport)
        #else
            /* We are using this library */
            #define INSOMNIA_API       __declspec(dllimport)
            #define INSOMNIA_EXPORT
        #endif // INSOMNIA_DLL_EXPORTS
    #endif // INSOMNIA_API
#else
    #define INSOMNIA_API
    #define INSOMNIA_EXPORT
#endif // _WIN32

#endif /* INSOMNIA_EXPORTS_H */
