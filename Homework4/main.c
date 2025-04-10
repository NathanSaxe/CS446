#include "mymalloc.c"

int main(int argc, char* arv[]){
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