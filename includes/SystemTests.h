// uncomment to disable assert()
// #define NDEBUG

#ifndef SYSTEM_TESTS_H
#define SYSTEM_TESTS_H

#include <assert.h>
#include <iostream>
#include "Vector4f.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Vector2i.h"
#include "Colour.h"
#include "ColourRGBA.h"
#include "Matrix4.h"
#include "Transform.h"

void tests_dot();
void tests_vecadd();
void tests_vecsub();
void tests_mat4();
void system_assertions();

#endif
