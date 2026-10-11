#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef struct {
    int occurTime;
    int kind;
    int num;
}Event, ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
typedef LinkList EventList;

typedef struct {
    int arriveTime;
    int duration;
    int num;
}QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int cmp(Event a, Event b);
void InitList(EventList& L);
bool OrderInsert(EventList& L, Event ev, int(*cmp)(Event, Event));
bool DelFirstElem(EventList& L, Event& e);

void InitQueue_L(LinkQueue& Q);
bool EnQueue_L(LinkQueue& Q, QElemType e);
bool DeQueue_L(LinkQueue& Q, QElemType& e);
bool QueueEmpty(LinkQueue Q);
bool GetHead_L(LinkQueue Q, QElemType& e);

void OpenForDay(EventList& evList, LinkQueue Q[]);
void CustomerArrival(EventList& evList, LinkQueue Q[], Event ev, int& custNum);
void CustomerDeparture(EventList& evList, LinkQueue Q[], Event ev);
bool MoreEvent(EventList& evList, Event& ev);
char EventKind(Event ev);
void Random(int* duration, int* interval);
int QueueLen(LinkQueue q);
int Shortest(LinkQueue Q[]);
