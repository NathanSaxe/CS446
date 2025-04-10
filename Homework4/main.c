#include "mymalloc.h"

mlist_t mlist;
int main(int argc, char* arv[]){
    mlist.head = NULL;
    printMemList(mlist.head);
}