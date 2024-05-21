#ifndef EMBEDDED_LIST_HPP_D2DS
#define EMBEDDED_LIST_HPP_D2DS

namespace d2ds {
// show your code

struct SinglyLink {
    struct SinglyLink *next;

    SinglyLink() : next { this } { }

public: // op
    static void insert(SinglyLink *prev, SinglyLink *target) {
        target->next = prev->next;
        prev->next = target;
    }

    static void remove(SinglyLink *prev, SinglyLink *target) {
        prev->next = target->next;
        target->next = target;
    }
};

struct DoublyLink {
    struct DoublyLink *next;
    struct DoublyLink *prev;

    DoublyLink() : prev { this }, next { this } { }

public: // op
    static void insert(DoublyLink *prev, DoublyLink *curr) {
        curr->next = prev->next;
        curr->prev = prev;
        if (prev->next)
            prev->next->prev = curr;
        prev->next = curr;
    }

    static void remove(DoublyLink *prev, DoublyLink *curr) {
        prev->next = curr->next;
        if (curr->next)
            curr->next->prev = prev;
        curr->prev = curr->next = curr;
    }
};

}

#endif