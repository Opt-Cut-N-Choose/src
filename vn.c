//
//  vn.c
//
//
//  Created by Sourgroup on 11/2/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openssl/rand.h>
#include "vn.h"

struct node
{
    double value;
    long long position;
    struct node *next;
};
struct dividepoint
{
    long long position;
    long long p1;
    int sign;
    struct dividepoint *next;
};
struct dividelink
{
    int num;
    struct dividepoint *point;
    struct dividelink *next;
    struct dividelink *pvs;
};
struct dividelink *divlink;
int S;
long long N;
long long N1=2;
struct node  *headF;
struct node  *headH;
double r;
double cost=-1;
int sign;
 
/*
 compute F_{n+1} and H_{n+1} from F_{n} and H_{n}, which are stored in headF and headH. And compute the indexes, which is used for generate strategies.
 
 Input dlink - the pointer pointing to the indexes.
 
 This function will precompute the data used for strategies generation and put them in the memory pointed by dlink.
 
 F_n and H_n are put in the memory pointed by headF and headH
*/

void merge(struct dividelink *dlink)
{
    long long count=0;
   struct node *p1,*p2,*p0,*p;
    int sign=1;
    p1=headF;
    p2=headF;
    p=headH;
    p->position=0;
    p->value=0;
    long long j1=0,j2=0,j0=-1;
    double s1=0,s2=0,t=0;
    struct dividepoint *divpoint;
    dlink->point=(struct dividepoint*) malloc(sizeof (struct dividepoint));
    divpoint=dlink->point;
    divpoint->sign=1;
    divpoint->p1=0;
    divpoint->position=0;
    divpoint->next=NULL;
   do{
       if((p1->next!=NULL)&&(s1+p1->next->value<s2+p2->next->value+r-1))
       {
           if(sign==0){
               divpoint->next=(struct dividepoint*) malloc(sizeof (struct dividepoint));
               divpoint->next->position=j0+1;
               divpoint->next->p1=divpoint->p1;
               divpoint->next->sign=1;
               divpoint=divpoint->next;
               divpoint->next=NULL;
               sign=1;
           }
           
           if(s1+p1->next->value-t>0)
       {
            s1+=p1->next->value;
           if(p->next==NULL) {p->next=(struct node *) malloc(sizeof(struct node));
               p->next->next=NULL;}
            p->next->value=s1-t;
            t=s1;
            p->next->position=j0+1;
           if(p1->next->next==NULL)j0=j0+N1-p1->next->position;
           else j0=j0+p1->next->next->position-p1->next->position;
            p1=p1->next;
            p=p->next;

       }
           else{
           if(p1->next->next==NULL)j0=j0+N1-p1->next->position;
           else j0=j0+p1->next->next->position-p1->next->position;
           s1+=p1->next->value;
           p1=p1->next;
       }
       
       
       
       }
           else
           {
               if(sign==1){
                   divpoint->next=(struct dividepoint*) malloc(sizeof (struct dividepoint));
                   divpoint->next->position=j0+1;
                   divpoint->next->p1=divpoint->p1+divpoint->next->position-divpoint->position;
                   divpoint->next->sign=0;
                   divpoint=divpoint->next;
                   
                   sign=0;
                   divpoint->next=NULL;
               }
           if(s2+p2->next->value+r-1-t>0)
           {
               divpoint->position=j0+1;
               divpoint->sign=0;
        
               count++;
               s2+=p2->next->value;
               if(p->next==NULL) {p->next=(struct node *) malloc(sizeof(struct node));
                   p->next->next=NULL;}
               p->next->value=s2-t+r-1;
               t=s2+r-1;
               p->next->position=j0+1;
               if(p2->next->next==NULL)j0=j0+N1-p2->next->position;
               else j0=j0+p2->next->next->position-p2->next->position;
               p2=p2->next;
               p=p->next;
                }
       else{
           if(p2->next->next==NULL)j0=j0+N1-p2->next->position;
           else j0=j0+p2->next->next->position-p2->next->position;
           s2+=p2->next->value;
           p2=p2->next;
       }
   }
    }while((p2->next!=NULL)&&(j0<=N));
    p1=headH;
    p2=headF;
    do{
        if(p2->next==NULL) {p2->next=(struct node *) malloc(sizeof(struct node));
            p2->next->next=NULL;}
        p2->next->value=p1->next->value;
        p2->next->position=p1->next->position;
        p2=p2->next;
        p1=p1->next;
    }while (p1->next!=NULL);
    p=headF;
    if(r!=1){if(p->next->next!=NULL) {p->next->next->value=r+1;
        if(p->next->next->next!=NULL) p->next->next->next->value=1;}}
        else{p1=(struct node *) malloc(sizeof(struct node));
            p1->value=2;
            p1->position=1;
            p1->next=p->next->next;
            p1->next->value=1;
            p->next->next=p1;}
}


/*
 *compute how many of the potential strategies will continued with 0;
 * input m - number of potential strategies, dlink - pre-computed data
 * output number of potential strategies which will continue with 0;
 */
long long divide (long long m, struct dividelink *dlink)
{
    if (m<dlink->point->next->position) return 1;
    struct dividepoint *dpoint;
    dpoint=dlink->point;
    do{
        dpoint=dpoint->next;
    }while ((dpoint->next!=NULL)&&(dpoint->next->position<m));
        return (dpoint->p1+(m-dpoint->position)*dpoint->sign);
}

/*
 * generate the next step : check or evaluate
 * input m - number of potential strategies, dlink - pre-computed data
 * checking will be represented as 0 while evaluating will be 1.
 */

void generate_next_step (long long m, struct dividelink *dlink)
{
    if (m<2) return;
    long long m1,m2;
    m1=divide(m,dlink);
    unsigned char tmp[7];
    RAND_bytes(tmp, 7);
    int i;
    m2=0;
    for(i=0;i<7;i++)
        m2=m2*256+tmp[i];
    m2=m2%m;
    if(m2>=m1){
        printf("1 ");
        generate_next_step(m-m1,dlink->pvs);
    }
    else{
        printf("0 ");
        generate_next_step(m1,dlink->pvs);
    }
    return;
}
/*
 * Compute the cost to reach s bits security if there are at most n circuits, n corresponds to F_n and H_n just computed by merge().
 * The cost is stored in c.
 * If this is the lowest cost so far, it will be stored in cost. If the cost stop decreasing, then stop searching. This will be denoted in sign.
 */
void evaluate(int s)
{
    long long n=pow(2,s);
    double c=0;
    struct node *p;
    p=headF->next;
    for(;(p->next!=NULL)&&(p->next->position<=n);)
    {
        c=c+p->next->value*((n-p->next->position)*(1.0)/n);
        p=p->next;
    }
    if (cost==c) sign++;
    if((cost==-1)||(c<cost))cost=c;
}
/*
  search for the lowest cost to reach s bits secruity with given cost ratio
 Input: s--- sercurity parameter
        ratio-- cost ratio
 */
void scost(int s, double ratio)
{
    divlink=(struct dividelink*) malloc(sizeof (struct dividelink));
    divlink->pvs=NULL;
    struct dividelink *divhead;
    divhead=divlink;
    cost=-1;
    r=ratio;
    headF=(struct node *) malloc(sizeof(struct node));
    headH=(struct node *) malloc(sizeof(struct node));
    headH->next=NULL;
    headH->value=0;
    headF->next=(struct node *) malloc(sizeof(struct node));
    headF->next->next=(struct node *) malloc(sizeof(struct node));
    headF->next->value=1;
    headF->next->position=0;
    headF->next->next->value=r+1;
    headF->next->next->position=1;
    headF->next->next->next=NULL;
    int n=9000;
    S=s;
    N=pow(2,S);
    int i=1;
    sign=0;
    for(;i<90000;i+=1)
    {
        merge(divhead);
        if (i>=S) evaluate(S);
        if(sign>2)break;
        divhead->num=i;
        struct dividepoint *dpoint;
        dpoint=divhead->point;
        do{
            dpoint=dpoint->next;
        }while(dpoint!=NULL);
        divhead->next=(struct dividelink*) malloc(sizeof (struct dividelink));
        divhead->next->pvs=divhead;
        divhead=divhead->next;
    }
    printf("%d %d %lf %lf \nStrategy: ",S,i-2,r,cost);
    divhead=divhead->pvs;
    free(divhead->next);
    divhead=divhead->pvs;
    free(divhead->next);
    generate_next_step(N,divhead);
    printf("\n");
    free(headF);
    free(headH);
    return;
}
/*
int main()
{
    int i;
    scost(20,4);
}
 */
