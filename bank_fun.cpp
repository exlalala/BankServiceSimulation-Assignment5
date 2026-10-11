#include "bank1.h"
#define CounterNum 3

int cmp(Event a, Event b)
{
    return a.occurTime - b.occurTime;
}

void InitList(EventList& L)
{
    L = new LNode;
    L->next = nullptr;
}

bool OrderInsert(EventList& L, Event ev, int(*cmp)(Event, Event))
{
    if (!L)  return false;
    LNode* pre, * p;
    pre = L;
    p = pre->next;
    while (p && cmp(ev, p->data) > 0)
    {
        pre = p;
        p = p->next;
    }
    LNode* s = new LNode;
    s->data = ev;
    s->next = pre->next;
    pre->next = s;
    return true;
}

bool DelFirstElem(EventList& L, Event& e)
{
    if (L->next == nullptr) return false;
    LNode* p = L->next;
    e = p->data;
    L->next = p->next;
    delete p;
    return true;
}

void InitQueue_L(LinkQueue& Q)
{
    Q.front = Q.rear = new QNode;
    Q.front->next = nullptr;
}

bool EnQueue_L(LinkQueue& Q, QElemType e)
{
    QNode* s = new QNode;
    s->data = e;
    s->next = nullptr;
    Q.rear->next = s;
    Q.rear = s;
    return true;
}

bool DeQueue_L(LinkQueue& Q, QElemType& e)
{
    if (QueueEmpty(Q)) return false;
    QNode* p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    delete p;
    return true;
}

bool QueueEmpty(LinkQueue Q)
{
    return Q.front == Q.rear;
}

int QueueLen(LinkQueue q)
{
    int cnt = 0;
    QNode* p = q.front->next;
    while (p != nullptr)
    {
        cnt++;
        p = p->next;
    }
    return cnt;
}


bool GetHead_L(LinkQueue Q, QElemType& e)
{
    if (QueueEmpty(Q)) return false;
    e = Q.front->next->data;
    return true;
}

void Random(int* duration, int* interval)
{
    *duration = rand() % 11 + 6;
    *interval = rand() % 9;
}

int Shortest(LinkQueue Q[])
{
    int i, j, minlen;
    minlen = QueueLen(Q[1]);
    i = 1;
    for (j = 2; j <= CounterNum; j++)
    {
        if (QueueLen(Q[j]) < minlen)
        {
            minlen = QueueLen(Q[j]);
            i = j;
        }
    }
    return i;
}


void OpenForDay(EventList& evList, LinkQueue Q[])
{
    InitList(evList);
    srand((unsigned)time(NULL));
    Event ev = { 0,0,1 };
    OrderInsert(evList, ev, cmp);
    for (int i = 1; i <= 3; i++)
    {
        InitQueue_L(Q[i]);
    }
}

void CustomerArrival(EventList& evList, LinkQueue Q[], Event ev, int& custNum)
{
    int duration=0, interval=0, t=0, i=0;
    QElemType c = { ev.occurTime, duration, ev.num };
    custNum++;
    Random(&duration, &interval);
    t = ev.occurTime + interval;
    if (t < 80)
    {
        Event ne = { t, 0, custNum + 1 };
        OrderInsert(evList, ne, cmp);
    }
    i = Shortest(Q);
    EnQueue_L(Q[i], c);
    if (GetHead_L(Q[i], c) && (Q[i].front->next == Q[i].rear))
    {
        Event leaveEv = { ev.occurTime + c.duration, i, c.num };
        OrderInsert(evList, leaveEv, cmp);
    }
}

void CustomerDeparture(EventList& evList, LinkQueue Q[], Event ev)
{
    QElemType c;
    int i = ev.kind;
    DeQueue_L(Q[i], c);
    cout << c.num << "\t\t" << c.arriveTime << "\t\t" << ev.occurTime << endl;
    if (!QueueEmpty(Q[i]))
    {
        GetHead_L(Q[i], c);
        Event newLeave = { ev.occurTime + c.duration, i, c.num };
        OrderInsert(evList, newLeave, cmp);
    }
}

bool MoreEvent(EventList& evList, Event& ev)
{
    if (evList->next == nullptr) return false;
    DelFirstElem(evList, ev);
    return true;
}

char EventKind(Event ev)
{
    if (ev.kind == 0) return 'A';
    else return 'D';
}