#include "bank1.h"

int main()
{
    EventList evList;
    LinkQueue Q[4];
    Event ev;
    int custNum = 0;
    OpenForDay(evList, Q);
    cout << "Customer No." << "  " << "Arrival Time" << "  " << "Depature Time" << endl;
    while (MoreEvent(evList, ev))
    {
        if (EventKind(ev) == 'A')
        {
            CustomerArrival(evList, Q, ev, custNum);
        }
        else
        {
            CustomerDeparture(evList, Q, ev);
        }
    }
    return 0;
}
