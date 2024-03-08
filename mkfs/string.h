typedef unsigned long size_t;

void	*memset(void *, int, size_t)
		__attribute__ ((__bounded__(__buffer__,1,3)));
