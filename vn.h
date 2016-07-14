//
//  vn-example.h
//  
//
//  Created by Sourgroup on 7/5/16.
//
//

#ifndef vn_example_h
#define vn_example_h

#include <stdio.h>
/*extern struct node
{
    double value;
    long long position;
    struct node *next;
};
extern struct dividepoint
{
    long long position;
    long long p1;
    int sign;
    struct dividepoint *next;
};
extern struct dividelink
{
    int num;
    struct dividepoint *point;
    struct dividelink *next;
    struct dividelink *pvs;
};*/
extern struct dividelink *divlink;
extern int S;
extern long long N;
extern long long N1 ;
extern struct node  *headF;
extern struct node  *headH;
extern double r;
extern double cost;
extern int sign;
 
void merge(struct dividelink *dlink);
long long divide (long long m, struct dividelink *dlink);
void generate_next_step (long long m, struct dividelink *dlink);
void evaluate(int s);
void scost(int s, double ratio);
#endif /* vn_example_h */
