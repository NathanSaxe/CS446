#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

typedef struct _mblock_t{
	struct _mblock_t* prev;
	struct _mblock_t* next;
	size_t size;
	int status;
	void* payload;
} mblock_t;

typedef struct _m_list_t{
	mblock_t* head;
} mlist_t;

void* mymalloc(size_t);
void myfree(void*);
void printMemList(const mblock_t*);
mblock_t* findLastMemListBlock();
mblock_t* findFreeBlockOfSize(size_t);
void splitBlockAtSize(mblock_t*, size_t);
void coallesceBlockPrev(mblock_t*);
void coallesceBlockNext(mblock_t*);
mblock_t* growHeapBySize(size_t size);