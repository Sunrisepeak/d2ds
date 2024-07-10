#ifndef EMBEDDED_LIST_HPP_D2DS
#define EMBEDDED_LIST_HPP_D2DS

namespace d2ds {
// show your code

struct DoublyLink {
    struct DoublyLink *prev, *next;

    static void init(DoublyLink *link) {
        link->prev = link->next = link;
    }

    static void insert(DoublyLink *prev, DoublyLink *target) {
        target->next = prev->next;
        target->prev = prev;
        prev->next->prev = target;
        prev->next = target;
    }

    static void del(DoublyLink *prev, DoublyLink *target) {
        prev->next = target->next;
        target->next->prev = prev;
    }
};

}

#endif