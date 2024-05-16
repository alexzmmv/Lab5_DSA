#include <cstring>
#include "Set.h"
#include "SetITerator.h"

Set::Set() {
    elements = new Node[10];
    capacity = 10;
    _size = 0;
    head = -1;
    firstEmpty = 0;
}

void Set::resize() {
    Node* newElements = new Node[capacity << 1];
    memcpy(newElements, elements, capacity * sizeof(Node));
    delete[] elements;

    elements = newElements;
    capacity <<= 1;
}

int Set::nextEmpty() {
    for(int i = firstEmpty; i < capacity; i++) {
        if (elements[i].next == -2) {
            return i;
        }
    }
    for(int i = 0; i < firstEmpty; i++) {
        if (elements[i].next == -2) {
            return i;
        }
    }
    return -1;
}

bool Set::add(TElem elem) {
    if (_size +1 == capacity) {
        resize();
    }
    // if the set is empty
    if (head == -1) {
            head = firstEmpty;
            elements[firstEmpty].value = elem;
            elements[firstEmpty].next = -1;
            firstEmpty++;
            _size++;
            return true;
    }
    // if the element is not already in the set
    if(!search(elem)) {
        int current = head;
        while (elements[current].next != -1) {
            current = elements[current].next;
        }
        elements[current].next = firstEmpty;
        elements[firstEmpty].value = elem;
        elements[firstEmpty].next = -1;
        firstEmpty=nextEmpty();
        _size++;
        return true;
    }
    return false;
}


bool Set::remove(TElem elem) {
    if (head == -1) {
        return false;
    }
    // if the element is the head
    if (elements[head].value == elem) {
        int current = head;
        head = elements[head].next;
        elements[current].next = -2;
        elements[current].value = NULL_TELEM;
        firstEmpty = current;
        _size--;
        return true;
    }
    // if the element is not the head
    int current = head;
    while (elements[current].next != -1) {
        if (elements[elements[current].next].value == elem) {
            int toDelete = elements[current].next;
            elements[current].next = elements[toDelete].next;
            elements[toDelete].next = -2;
            elements[toDelete].value = NULL_TELEM;
            firstEmpty = toDelete;
            _size--;
            return true;
        }
        current = elements[current].next;
    }
	return false;
}

bool Set::search(TElem elem) const {
    int current = head;
    while (current != -1) {
        if (elements[current].value == elem) {
            return true;
        }
        current = elements[current].next;
    }
    return false;
}


int Set::size() const {
    return _size;
}


bool Set::isEmpty() const {
    return _size == 0;
}


Set::~Set() {
    delete[] elements;
}

void Set::filter(Condition cond) {
    auto current=elements[head];
    while (current.next!=-1){
        if(!cond(current.value))
            remove(current.value);
        current=elements[current.next];
    }
    if(!cond(current.value))
        remove(current.value);
}

SetIterator Set::iterator() const {
	return SetIterator(*this);
}