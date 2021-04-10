#ifndef AA_LinkedList
#define AA_LinkedList

#include <Arduino.h>

/* #define __FPRINT__                                                  \
       if (Serial) {                                                   \
           Serial.printf("%s \t%s \n", __FILE__, __PRETTY_FUNCTION__); \
           while (!Serial) {                                           \
           }                                                           \
     }*/

template <typename T>
class LinkedList {
   private:
    struct node {
        struct node* next;
        const T* data;
        node(const T* data) : next(nullptr), data(data) {}
    };
    node* head;

   public:
    LinkedList() : head(nullptr) {}
    LinkedList(const node& other) = delete;
    ~LinkedList() {
        node *ptrlast, *ptr = head;
        while (ptr) {
            ptrlast = ptr;
            ptr = ptr->next;
            delete ptrlast;
        }
    };

    LinkedList& push(const T* element) {
        if (head) {
            node* last = head;
            while (last->next)
                last = last->next;
            last->next = new node(element);
        } else {
            head = new node(element);
        }
        return *this;
    }

    LinkedList& remove(const T* element) {
        if (!head)
            return *this;  //todo assert array empty
        node* ptr = head;
        if (ptr->data == element) {
            head = ptr->next;
            delete ptr;
        } else {
            while (ptr->next->data != element && ptr->next->next)
                ptr = ptr->next;
            if (ptr->next->data != element)
                return *this;  //todo assert element doesn't exist
            node* tdelete = ptr->next;
            ptr->next = ptr->next->next;
            delete tdelete;
        }
        return *this;
    }

    T* item(const int i) {
        if (!head)
            return nullptr;  //todo assert array empty
        node* ptr = head;
        for (int I = 0; I < i && ptr; I++)
            ptr = ptr->next;
        if (!ptr)
            return nullptr;  //todo assert i out of range
        return (T*)ptr->data;
    };

    LinkedList& forEach(void (*f)(const int, T*)) {
        if (!head)
            return *this;
        int i = 0;
        for (node* ptr = head; ptr; ptr = ptr->next, i++) {
            f(i, (T*)ptr->data);
        }
        return *this;
    }

    template <typename S>
    LinkedList& forEach(S* self, void (*f)(const int, T*, S*)) {
        if (!head)
            return *this;
        int i = 0;
        for (node* ptr = head; ptr; ptr = ptr->next, i++) {
            f(i, (T*)ptr->data, self);
        }
        return *this;
    }
    // template <typename F>
    // LinkedList& forEach(F& f) {  //? why is this an error
    //     if (!head)
    //         return *this;
    //     int i = 0;
    //     for (node* ptr = head; ptr; ptr = ptr->next, i++) {
    //         f(i, (T*)ptr->data);
    //     }
    // }

    int length() {
        int length = 0;
        for (node* ptr = head; ptr; ptr = ptr->next)
            length++;
        return length;
    }

    LinkedList& operator<<(const T* element) { return push(element); }
    LinkedList& operator<<(const T& element) { return push(&element); }
    LinkedList& operator>>(const T* element) { return remove(element); }
    LinkedList& operator>>(const T& element) { return remove(&element); }
    T* operator[](const int i) { return item(i); }
    int operator()() { return length(); }
};

#endif
