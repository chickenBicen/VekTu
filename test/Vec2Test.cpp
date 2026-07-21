#include "VekTu/Linear/Vec2.h"

#include "VekTu/Common.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace vk;
template <VectorElement T> using Answers = std::vector<Vec2<T>>;

// Integer test vectors
const Vec2i i1{1, 2};
const Vec2i i2{3, 4};
const Vec2i i3{10, 82};
const Vec2i i4{3242, 18923};
const Vec2i i5{34, 423};
const Vec2i i6{76, 123087};
const Vec2i i7{-5, 8};
const Vec2i i8{-20, -30};
const Vec2i i9{0, 0};
const Vec2i i10{100, -100};


// Float test vectors
const Vec2f f1{1.0f, 2.0f};
const Vec2f f2{1.234f, 9.876f};
const Vec2f f3{1.0f, 10.0f};
const Vec2f f4{213.123f, 9271.324f};
const Vec2f f5{34.5f, 423.25f};
const Vec2f f6{76.75f, 123.125f};
const Vec2f f7{-5.5f, 8.25f};
const Vec2f f8{-20.75f, -30.5f};
const Vec2f f9{0.0f, 0.0f};
const Vec2f f10{100.25f, -100.75f};


// Double test vectors
const Vec2d d1{1.0, 2.0};
const Vec2d d2{1.234567, 9.876543};
const Vec2d d3{1.0, 10.0};
const Vec2d d4{213.123456, 9271.324567};
const Vec2d d5{34.5, 423.25};
const Vec2d d6{76.75, 123.125};
const Vec2d d7{-5.5, 8.25};
const Vec2d d8{-20.75, -30.5};
const Vec2d d9{0.0, 0.0};
const Vec2d d10{100.25, -100.75};

// Long test vectors
const Vec2<long> l0{1l, 2l};
const Vec2<long> l2{30000l, 40000l};
const Vec2<long> l3{100000l, 820000l};
const Vec2<long> l4{3242342l, 18923423l};
const Vec2<long> l5{340000l, 423000l};
const Vec2<long> l6{760000l, 123087000l};
const Vec2<long> l7{-500l, 800l};
const Vec2<long> l8{-20000l, -30000l};
const Vec2<long> l9{0l, 0l};
const Vec2<long> l10{100000000l, -100000000l};


// uint8_t test vectors
const Vec2u u0{1, 2};
const Vec2u u2{3, 4};
const Vec2u u3{10, 82};
const Vec2u u4{25, 100};
const Vec2u u5{34, 123};
const Vec2u u6{76, 200};
const Vec2u u7{5, 8};
const Vec2u u8{20, 30};
const Vec2u u9{0, 0};
const Vec2u u10{255, 128};

void runTest(const char* name, void (*testFunc)())
{
    std::cout << "Running " << name << "...";
    testFunc();
    std::cout << "OK\n";
}

void testVec2Addition()
{
    // ================= Integer =================

    {
        const Vec2i iexpected1{4, 6};
        const Vec2i result1 = i1 + i2;

        assert(result1 == iexpected1);
    }

    {
        const Vec2i iexpected2{13, 86};
        const Vec2i result2 = i2 + i3;

        assert(result2 == iexpected2);
    }

    {
        const Vec2i iexpected3{80, -130};
        const Vec2i result3 = i8 + i10;

        assert(result3 == iexpected3);
    }

    // ================= Float =================

    {
        const Vec2f fexpected1{2.234f, 11.876f};
        const Vec2f result1 = f1 + f2;

        assert(result1 == fexpected1);
    }

    {
        const Vec2f fexpected2{2.234f, 19.876f};
        const Vec2f result2 = f2 + f3;

        assert(result2 == fexpected2);
    }

    {
        const Vec2f fexpected3{94.75f, -92.5};
        const Vec2f result3 = f7 + f10;

        assert(result3 == fexpected3);
    }

    // ================= Double =================

    {
        const Vec2d dexpected1{2.234567, 11.876543};
        const Vec2d result1 = d1 + d2;

        assert(result1 == dexpected1);
    }

    {
        const Vec2d dexpected2{2.234567, 19.876543};
        const Vec2d result2 = d2 + d3;

        assert(result2 == dexpected2);
    }


    // ================= Long =================

    {
        const Vec2<long> lexpected1{30001l, 40002l};
        const Vec2<long> result1 = l0 + l2;

        assert(result1 == lexpected1);
    }

    {
        const Vec2<long> lexpected2{130000l, 860000l};
        const Vec2<long> result2 = l2 + l3;

        assert(result2 == lexpected2);
    }


    // ================= uint8_t =================

    {
        const Vec2u uexpected1{4, 6};
        const Vec2u result1 = u0 + u2;

        assert(result1 == uexpected1);
    }

    {
        const Vec2u uexpected2{44, 205};
        const Vec2u result2 = u3 + u5;

        assert(result2 == uexpected2);
    }
}

void testVec2ScalarAddition()
{
    // ================= Integer =================

    {
        const Vec2i expected{6, 7};
        const Vec2i iresult = i1 + 5;

        assert(iresult == expected);
    }

    {
        const Vec2i expected{-15, -25};
        const Vec2i iresult = i8 + 5;

        assert(iresult == expected);
    }


    // ================= Float =================

    {
        const Vec2f expected{6.0f, 7.0f};
        const Vec2f fresult1 = f1 + 5.0f;

        assert(fresult1 == expected);
    }

    {
        const Vec2f expected{94.75f, -106.25};
        const Vec2f fresult2 = f10 + (-5.5f);

        assert(fresult2 == expected);
    }


    // ================= Double =================

    {
        const Vec2d expected{11.0, 12.0};
        const Vec2d dresult = d1 + 10.0;

        assert(dresult == expected);
    }


    // ================= Long =================

    {
        const Vec2<long> expected{101, 102};
        const Vec2<long> lresult = l0 + 100l;

        assert(lresult == expected);
    }


    // ================= uint8_t =================

    {
        const Vec2u expected{11, 12};
        const Vec2u uresult = u0 + 10;

        assert(uresult == expected);
    }
}

void testVec2Scaling()
{
    // ===================== Integer =====================
    {
        const Vec2i iExpected1{2, 4};
        const Vec2i iExpected2{33, 270};

        const Vec2i result1 = i1 * 2;
        const Vec2i result2 = i3 * 3.3;

        assert(result1 == iExpected1);
        assert(result2 == iExpected2);
    }

    // ====================== float ======================

    {
        const Vec2f fExpected1{1.5f, 3.0f};

        const Vec2f result1 = f1 * 1.5;
    }

    // ===================== doubles =====================

    {
        const Vec2d dExpected1{1.5, 3};

        const Vec2d result1 = d1 * 1.5;
    }

    // ====================== Longs ======================

    {
    }

    // ===================== uint8_t =====================

    {
    }
}

void runVec2Tests()
{
    runTest("Vec2 addition test", testVec2Addition);
    runTest("Vec2 scalar addition", testVec2ScalarAddition);
    runTest("Vec2 scaling test", testVec2Scaling);

    std::cout << "Vector 2d tests passed" << "\n\n";
}
