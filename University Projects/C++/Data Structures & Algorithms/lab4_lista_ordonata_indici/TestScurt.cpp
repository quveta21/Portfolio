#include <assert.h>
#include <exception>
#include "Iterator.h"
#include "LO.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator iterator = lo.iterator();
    assert(iterator.valid());
    iterator.prim();
    assert(iterator.element() == 1);
    iterator.urmator();
    assert(!iterator.valid());
    iterator.prim();
    assert(iterator.valid());
    assert(lo.cauta(1) == 0);
    assert(lo.sterge(0) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());
}

void test_stergeIntre() {
    LO lo = LO(relatie1);
    lo.adauga(1);
    lo.adauga(2);
    lo.adauga(3);
    lo.adauga(4);
    lo.adauga(5);
    lo.adauga(6);
    assert(lo.dim() == 6);
    try {
        lo.stergeIntre(-1, 10);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    try {
        lo.stergeIntre(10, -1);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    lo.stergeIntre(1, 3);
    assert(lo.cauta(2) == -1);
    assert(lo.cauta(3) == -1);
    assert(lo.cauta(4) == -1);
    assert(lo.dim() == 3);
}
