#include "mymalloc.h"
#define MBLOCK_HEADER_SZ offsetof(mblock_t, payload)

mlist_t mlist;

int main(int argc, char* arv[]){
  printf("%p\n", mlist.head);
  void * p1 = mymalloc(10);
  printMemList(mlist.head);
  void * p2 = mymalloc(100);
  printMemList(mlist.head);
  void * p3 = mymalloc(200);
  printMemList(mlist.head);
  void * p4 = mymalloc(500);
  printMemList(mlist.head);
  myfree(p3); p3 = NULL;
  printMemList(mlist.head);
  myfree(p2); p2 = NULL;
  printMemList(mlist.head);
  void * p5 = mymalloc(150);
  printMemList(mlist.head);
  void * p6 = mymalloc(500);
  printMemList(mlist.head);
  myfree(p4); p4 = NULL;
  printMemList(mlist.head);
  myfree(p5); p5 = NULL;
  printMemList(mlist.head);
  myfree(p6); p6 = NULL;
  printMemList(mlist.head);
  myfree(p1); p1 = NULL;
  printMemList(mlist.head);
}

void* mymalloc(size_t size){
  mblock_t* freeBlock = findFreeBlockOfSize(size);
  splitBlockAtSize(freeBlock, size);
  return freeBlock->payload;
}

void myfree(void* ptr){
  mblock_t* temp = mlist.head;
	//ptr is, theoretically, located somewhere within a mblock
  while(temp!=NULL){
    if(temp->payload == ptr){
      break;
    }
  }

}

void printMemList(const mblock_t* head) {
  const mblock_t* p = head;
  
  size_t i = 0;
  while(p != NULL) {
    printf("[%ld] p: %p\n", i, (void*)p);
    printf("[%ld] p->size: %ld\n", i, p->size);
    printf("[%ld] p->status: %s\n", i, p->status > 0 ? "allocated" : "free");
    printf("[%ld] p->prev: %p\n", i, (void*)p->prev);
    printf("[%ld] p->next: %p\n", i, (void*)p->next);
    printf("___________________________\n");
    ++i;
    p = p->next;
  }
  printf("===========================\n");
}
//Returns last block of memory
mblock_t* findLastMemListBlock(){
  mblock_t* temp = mlist.head;
  while(temp!=NULL){
    temp = temp->next;
  }
  return temp;
}
//Finds the first block of memory of that specified size
mblock_t* findFreeBlockOfSize(size_t size){
  mblock_t* temp = mlist.head;
  mblock_t* lastNode = findLastMemListBlock();
  while(temp!=lastNode){
    if(temp->status == 0 && temp->size<size){
      return temp;
    }
    temp = temp->next;
  }
  return growHeapBySize(size);
}
//Splits one block into two, First one being of size newSize, Second one being the remainder. Update doubly linked list
void splitBlockAtSize(mblock_t* block, size_t newSize){
  int freeBlockMemSize = MBLOCK_HEADER_SZ + block->size;
  mblock_t* remainingBlock;
  remainingBlock->status = 0;
  remainingBlock->size = freeBlockMemSize - newSize;
  remainingBlock->payload = NULL;
  remainingBlock->next = block->next;
  remainingBlock->prev = block;
  block->next = remainingBlock;
  block->status = 1;
}
//Take a block of memory and merge it with the previous block
void coallesceBlockPrev(mblock_t* freedBlock){
  mblock_t* freeBlockNext = freedBlock->next;
  freedBlock->prev->size += freedBlock->size;
  freedBlock = freedBlock->prev;
  freedBlock->next = freeBlockNext;
}
//Take a block of memory and merge it with the next block
void coallesceBlockNext(mblock_t* freedBlock){
  mblock_t* freeBlockPrev = freedBlock->prev;
  freedBlock->next->size += freedBlock->size;
  freedBlock = freedBlock->next;
  freedBlock = freeBlockPrev;
}
//Increase heap allocation and create a new memory block in the VA Space
mblock_t* growHeapBySize(size_t size){
  mblock_t* lastNode = findLastMemListBlock();
  if(lastNode == mlist.head){
   sbrk(sizeof(mblock_t)); 
  }
  void* p = sbrk(size + MBLOCK_HEADER_SZ);
  
  if(p==(void*)-1){
    printf("%s", strerror(errno));
    return NULL;
  }
  mblock_t* temp = (mblock_t*)p;
  temp->next = NULL;
  temp->prev = lastNode;
  lastNode->next = temp;
  temp->status = 0;
  temp->payload = sbrk(0)-size;
  temp->size = 0;
  return temp;
}
