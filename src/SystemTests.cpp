#include "SystemTests.h"

// Math Library Tests.
void tests_dot()
{
    std:: cout << "Dot Product Tests" << std::endl;
    Vector4f* a = new Vector4f(1,2,3,4);
    Vector4f* b = new Vector4f(1,5,7,9);
    float c = Vector4f::Dot(a,b);
    assert(c == 68);

    Vector3f* d = new Vector3f(1,2,3);
    Vector3f* e = new Vector3f(1,5,7);
    float f = Vector3f::Dot(d,e);
    assert(f == 32);

    Vector2f* g = new Vector2f(4,8);
    Vector2f* h = new Vector2f(12,3);
    float i = Vector2f::Dot(g,h);
    assert(i == 72);

    Vector2i* j = new Vector2i(7,9);
    Vector2i* k = new Vector2i(2,14);
    float l = Vector2i::Dot(j->xy(), k->xy());
    assert(l == 140);
}

void tests_vecadd()
{
    std:: cout << "Vector Addition Tests" << std::endl;
    Vector4f* a = new Vector4f(1,2,3,4);
    Vector4f* b = new Vector4f(1,5,7,9);
    Vector4f* c = Vector4f::Add(a,b);
    assert(c->x == 2 && c->y == 7 && c->z == 10 && c->w == 13);

    Vector3f* d = new Vector3f(1,2,3);
    Vector3f* e = new Vector3f(1,5,7);
    Vector3f* f = Vector3f::Add(d,e);
    assert(f->x == 2 && f->y == 7 && f->z == 10);

    Vector2f* g = new Vector2f(4,8);
    Vector2f* h = new Vector2f(12,3);
    Vector2f* i = Vector2f::Add(g,h);
    assert(i->x == 16 && i->y == 11);

    Vector2i* j = new Vector2i(7,9);
    Vector2i* k = new Vector2i(2,14);
    Vector2i* l = Vector2i::Add(j,k);
    assert(l->x == 9 && l->y == 23);

    Vector2i* m = new Vector2i(7,9);
    int n = 5;
    Vector2i* o = Vector2i::Add(m,n);
    assert(o->x == 12 && o->y == 14);
}

void tests_vecsub()
{
    std:: cout << "Vector Subtraction Tests" << std::endl;
    Vector4f* a = new Vector4f(1,2,3,4);
    Vector4f* b = new Vector4f(1,5,7,9);
    Vector4f* c = Vector4f::Subtract(a,b);
    assert(c->x == 0 && c->y == -3 && c->z == -4 && c->w == -5);

    Vector3f* d = new Vector3f(1,2,3);
    Vector3f* e = new Vector3f(1,5,7);
    Vector3f* f = Vector3f::Subtract(d,e);
    assert(f->x == 0 && f->y == -3 && f->z == -4);

    Vector2f* g = new Vector2f(4,8);
    Vector2f* h = new Vector2f(12,3);
    Vector2f* i = Vector2f::Subtract(g,h);
    assert(i->x == -8 && i->y == 5);

    Vector2i* j = new Vector2i(7,9);
    Vector2i* k = new Vector2i(2,14);
    Vector2i* l = Vector2i::Subtract(j,k);
    assert(l->x == 5 && l->y == -5);

    Vector2i* m = new Vector2i(7,9);
    int n = 5;
    Vector2i* o = Vector2i::Subtract(m,n);
    assert(o->x == 2 && o->y == 4);
}

void tests_mat4()
{
    std:: cout << "Matrix4 Tests" << std::endl;
    Matrix4* m = Matrix4::Identity();

    m->Translate(new Vector3f(2,3,4));
    Vector4f* Row3 = m->Row3();
    assert(Row3->x == 2 && Row3->y == 3 && Row3->z == 4);
}

void system_assertions()
{
    tests_dot(); // Dot Product Tests
    tests_vecadd(); // Vector Addition Tests
    tests_vecsub(); // Vector Subtraction Tests
    tests_mat4(); // Matrix4 Tests
    std:: cout << "Passed All Tests." << std::endl;
}
