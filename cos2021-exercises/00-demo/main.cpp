#include <iostream>
#include <vector>
#include <cassert>
#include <list>

using namespace std;

//// Linked list implementation
//
//template <class T> class Link {
//public:
//    Link<T>* insert(T val) {
//        Link* newNode = new Link(val, ptrToNextLink);
//        ptrToNextLink = newNode;
//
//        assert(ptrToNextLink != 0);
//        return ptrToNextLink;
//    }
//private:
//    Link(T linkValue, Link* nextElPointer) : value(linkValue), ptrToNextLink(nextElPointer) { }
//    Link(const Link<T>& sourceLink) {
//        value = sourceLink.value;
//        ptrToNextLink = sourceLink.ptrToNextLink;
//    }
//
//    Link<T>* duplicate() const {
//        Link<T>* newLink;
//
//        if (ptrToNextLink != 0) {
//            newLink = new Link<T>(value, ptrToNextLink->duplicate());
//        } else {
//            newLink = new Link<T>(value, 0);
//        }
//
//        return newLink;
//    }
//    T value;
//    Link* ptrToNextLink;
//};
//
//template <class T> class LinkedList {
//public:
//    LinkedList() {}
//    LinkedList(const LinkedList<T>& source) {
//        if (source.isEmpty()) {
//            ptrToFirstLink = 0;
//        }
//        else {
//            Link<T>* firstLink = source.ptrToFirstLink;
//            ptrToFirstLink = firstLink->duplicate();
//        }
//    }
//
//    virtual ~LinkedList() {}
//
//    void add(T value) {
//        ptrToFirstLink = new Link<T>(value, ptrToFirstLink);
//        assert(ptrToFirstLink != 0);
//    }
//
//    void deleteAllValues() {
//        Link<T>* next;
//
//        for (Link<T>* p = ptrToFirstLink; p != 0; p = next) {
//            next = p->ptrToNextLink;
//            p->ptrToNextLink = 0;
//            delete p;
//        }
//
//        ptrToFirstLink = 0;
//    }
//protected:
//    Link<T>* ptrToFirstLink;
//
//};


// Stack implementation

template <class T> class Stack {
public:
    virtual void deleteAllValues() = 0;
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
};

template <class T> class StackVector : public Stack<T> {
public:
    StackVector(unsigned int size = 10) : nextSlot(0) {
        data.resize(size);
    }

    StackVector(const StackVector& originalVector) {

    }

    virtual bool isEmpty() const override {
        return nextSlot == 0;
    }

    virtual void deleteAllValues() override {
        nextSlot = 0;  // Reset nextSlot to 0, essentially clearing the stack
    }

    virtual T pop() {
        assert(!isEmpty());
        return data[--nextSlot];
    }

    virtual void push(T val) {
        if (nextSlot >= data.size()) {
            data.resize(data.size() + 5);
        }

        data[nextSlot++] = val;
    }

    virtual T top() const {
        assert(!isEmpty());
        return data[nextSlot - 1];
    }

protected:
    vector<T> data;
    unsigned int nextSlot;
};

template <class T> class StackList {
public:
    T pop() {
        T result = data.firstElement();
        data.removeFirst();
        return result;
    }

    void push(T val) {
        data.add(val);
    }

    T top() const {
        return data.firstElement();
    }
private:
    list<T> data;
};

template <class T> class queue {
public:
    virtual void deleteAllValues() = 0;
    virtual void enqueue(T value) = 0;
    virtual T dequeue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
};


template <class T> class QueueVector : public queue<T> {
public:
    QueueVector(unsigned int maxSize) : max(maxSize), nextSlot(0), nextUse(0) {
        data.resize(max);
    }

    virtual bool isEmpty() const override {
        return nextSlot == nextUse;
    }

    virtual void enqueue(T val) override {
        data[nextSlot++] = val;

        if (nextSlot >= max) nextSlot = 0;
        assert(nextSlot != nextUse);  // Ensure the queue is not full
    }

    virtual T front() const override {
        assert(!isEmpty());
        return data[nextUse];
    }

    virtual T dequeue() override {
        assert(!isEmpty());
        int dataloc = nextUse;
        nextUse++;

        if (nextUse >= max) nextUse = 0;

        return data[dataloc];
    }

    // Implementation of a pure virtual method from the base class
    virtual void deleteAllValues() override {
        nextSlot = 0;
        nextUse = 0;
    }

private:
    vector<T> data;
    const unsigned int max;
    unsigned int nextSlot;
    unsigned int nextUse;
};



template <class T> void removeStackTop(Stack<T>& a)
{
    if (a.isEmpty()) return;

    T topElement = a.top();
    StackVector<T> tempStack;

    while (!a.isEmpty()) {
        T currentElement = a.pop();

        if (currentElement != topElement)
            tempStack.push(currentElement);
    }

    while (!tempStack.isEmpty()) {
        a.push(tempStack.pop());
    }
}

template <class T> void reverseStackAvg(Stack<T>& a)
{
    QueueVector<T> tempQueue(100);
    T sum = 0;
    int count = 0;

    while (!a.isEmpty())
    {
        T curEl = a.pop();
        sum += curEl;
        count++;
        tempQueue.enqueue(curEl);
    }

    T avg = sum / count;

    a.push(avg);

    while (!tempQueue.isEmpty())
    {
        T curEl = tempQueue.dequeue();
        a.push(curEl);
    }
}

template <class T> void reverseQueueMax(queue<T>& a)
{
    StackVector<T> b;
    T max = a.front();

    while (!a.isEmpty())
    {
        T curEl = a.dequeue();
        b.push(curEl);

        if (curEl > max)
            max = curEl;
    }

    a.enqueue(max);

    while (!b.isEmpty())
    {
        T curEl = b.pop();
        a.enqueue(curEl);
    }
}

template <class T> void duplicateQueueMin(queue<T>& a)
{
    QueueVector<T> b(100);

    T min = a.front();

    while (!a.isEmpty())
    {
        T curEl = a.dequeue();
        b.enqueue(curEl);

        if (curEl < min)
            min = curEl;
    }

    while (!b.isEmpty())
    {
        T curEl = b.dequeue();
        a.enqueue(curEl);

        if (curEl == min)
            a.enqueue(curEl);
    }
}

template <class T> void removeStackRange(Stack<T>& a)
{
    StackVector<T> tempStack;
    T min = a.top();
    T max = a.top();

    while (!a.isEmpty())
    {
        T curEl = a.pop();

        if (curEl > max)
            max = curEl;

        if (curEl < min)
            min = curEl;

        tempStack.push(curEl);
    }

    T range = max - min;

    while (!tempStack.isEmpty())
    {
        T curEl = tempStack.pop();

        if (curEl != range)
            a.push(curEl);
    }
}

template <class T> void removeStackAverage(Stack<T>& a)
{
    StackVector<T> b;
    T sum = 0;
    int count = 0;

    while (!a.isEmpty())
    {
        T curEl = a.pop();
        b.push(curEl);
        sum += curEl;
        count++;
    }

    T avg = sum / count;

    while (!b.isEmpty())
    {
        T curEl = b.pop();

        if (curEl != avg)
            a.push(curEl);
    }
}

template <class T> void reverse_order(Stack<T>& a)
{
    QueueVector<T> b(100);
    T max = a.top();

    while (!a.isEmpty())
    {
        T curEl = a.pop();
        b.enqueue(curEl);

        if (curEl > max)
            max = curEl;
    }

    a.push(max);

    while (!b.isEmpty())
    {
        T curEl = b.dequeue();
        a.push(curEl);
    }
}

int main() {
    StackVector<int> myStack(4);

    myStack.push(2);
    myStack.push(6);
    myStack.push(4);

    QueueVector<int> myQueue(100);
    myQueue.enqueue(2);
    myQueue.enqueue(6);
    myQueue.enqueue(4);

//    reverseStackAvg(myStack);
//    removeStackTop(myStack);
    reverseQueueMax(myQueue);
//    duplicateQueueMin(myQueue);
//    removeStackRange(myStack);
//    removeStackAverage(myStack);
//    reverse_order(myStack);

//
//    while (!myStack.isEmpty()) {
//        cout << myStack.pop() << " ";  // Pop and print the top element
//    }

    while (!myQueue.isEmpty()) {
        cout << myQueue.dequeue() << " ";  // Pop and print the top element
    }

    return 0;
}