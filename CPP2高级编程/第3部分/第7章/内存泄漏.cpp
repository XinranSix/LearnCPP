#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ()
#endif
#endif

class Simple {
public:
    Simple() { m_intPtr = new int{}; }
    ~Simple() { delete m_intPtr; }

    void setValue(int value) { *m_intPtr = value; }

private:
    int *m_intPtr;
};

void doSomething(Simple *&outSimplePtr) {
    // 内存泄漏了
    outSimplePtr = new Simple();
}

int main(int argc, char *argv[]) {

    Simple *simplePtr{new Simple{}};
    doSomething(simplePtr);

    delete simplePtr;

    return 0;
}
