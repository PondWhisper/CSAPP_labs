#include "cachelab.h"
#include "limits.h"

typedef struct{
    int valid;
    long tag;
    int lru;
}cacheLine;

int main()
{
    int s, e, b;
    char* trace=NULL;
    while((opt=getopt(argc,argv,"s:e:b:t:"))!=-1 ){
        switch(opt){
            case 's':
                s=atoi(optarg);
                break;
            case 'b':
                b=atoi(optarg);
                break;
            case 'e':
                e=atoi(optarg);
                break;
            case 't':
                trace=optarg;
                break;
        }
    }
    int S=1<<s;
    cacheLine** cache=(cacheLine **) malloc((S)* sizeof(cacheLine*   ));
    for(int i =0;i<S;i++){
        cache[i]=(cacheLine*) malloc(e* sizeof(cacheLine));
    }
    char op;
    unsigned long addr;
    int size;
    FILE* pFile=fopen(trace, "r");
    int hitCount=0;
    int missCount=0;
    int counter=0;
    while((fsanf(*trace, " %c %lx,%d", &op, &addr, &size)) >0){
           swithc(op){
            case 'L':
            case 'M':
                update(add, &hitCount, &missCount, &counter);               
                break;
            case 'S' :
                update(add, &hitCount, &missCount, &counter);
                update(add, &hitCount, &missCount, &counter);
                break;
        }
    }
    printSummary(0, 0, 0);
    return 0;
}

void update(unsigned long addr, int *hitCount, int *missCount, int * counter){
    long tag=addr>>(b+s);
    long setIndex=(addr>>b) &((1<<s)-1);
    for(int i=0;i<e;i++){
        if(cache[setIndex][i].valid==1&&cache[setIndex][i].tag==tag){
            hit=1;
            (hitCount)++;
            cache[setIndex][i].lru=counter++;
            return ;
        }
    }

        (missCount)++;
        int min=INT_MAX;
        int position=0;
        for(int i=0;i<e;i++ ){
            if(cache[setIndex][i].valid==0){
                cache[setIndex][i].valid==1;
                cache[setIndex][i].tag=tag;
                cache[setIndex][i].lru=counter++;
                return ;
            }
            if(cache[setIndex][i].lru<min){
                min=cache[setIndex][i];
                position=i;
            }
        }
        if(x==e){
            cache[setIndex][i].valid=1;
            cache[setIndex][i].tag=tag;
            cache[setIndex][i].lru=counter++;
        }
}
