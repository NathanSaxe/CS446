#include "mymalloc.h"
//these repos are connected
mlist_t mlist;
int main(int argc, char* arv[]){
    mlist.head = NULL;
    printMemList(mlist.head);
}