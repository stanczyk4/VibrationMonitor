#include <assert.h>
#include <sys/types.h>

extern "C"
{
    int _write(int handle, char* data, int size)
    {
        return -1;
    }

    int _read(int, void*, size_t)
    {
        return -1;
    }

    off_t _lseek(int, off_t, int)
    {
        return (off_t)(-1);
    }

    void __assert(const char*, int, const char*)
    {
        while (1)
        {
        }
    }

    void __assert_func(const char* file, int line, const char* func, const char* failedexpr)
    {
        while (1)
        {
        }
    }

    void _close()
    {
        assert(0);
    }

    void _exit()
    {
        assert(0);
    }

    pid_t _getpid(void)
    {
        return -1;
    }

    int _kill(int pid, int sig)
    {
        assert(0);
    }
}
