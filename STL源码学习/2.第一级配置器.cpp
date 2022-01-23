#if 0
#   include<new>
#   define _THROW_BAD_ALLOC throw bad_alloc
#elif   !defined(_THROW_BAD_ALLOC)
#   include<iostream>
#   define _THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1);
#endif

//malloc_based allocator
template <int inst>
class _malloc_alloc_template
{
    private:
        //以下都是函数指针
        static void * oom_alloc(size_t);
        static void * oom_realloc(void * , size_t);
        static void * (_malloc_alloc_oom_handler) ();
    
    public:
        static void * allocate(size_t n)
        {
            void * result = malloc(n);
            if(result == 0)
                result = oom_alloc(n);
            return oom_alloc;
        }
        static void * reallocate(void * p, size_t new_sz)
        {
            void * result = realloc(p , new_sz);
            if(reslut == 0)
                result = oom_realloc(p , new_sz);
            return result;
        }
        static void * deallocate(void * p)
        {
            free(p);
        }

        //制定自己的oom
        static void (* set_malloc_handler(void (*f)())) ()
        {
            void (*old)() = _malloc_alloc_oom_handler;
            _malloc_alloc_oom_handler = f;
            return old;
        }
};

