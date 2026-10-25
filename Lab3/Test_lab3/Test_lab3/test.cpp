#include "pch.h"
#include <gtest/gtest.h>

TEST(Lab3Tests, ArrayInitializationTest) {
    int size = 10;
    int* arr = new int[size];

    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }

    ASSERT_NE(arr, nullptr);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], 0);
    }

    delete[] arr;
}

TEST(Lab3Tests, MarkerCounterLogicTest) {
    int size = 5;
    int* arr = new int[size];

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 1;
    arr[3] = 0;
    arr[4] = 1;

    int marker_id = 1;
    int counter = 0;

    for (int i = 0; i < size; ++i) {
        if (arr[i] == marker_id) {
            ++counter;
        }
    }

    EXPECT_EQ(counter, 3);

    delete[] arr;
}

TEST(Lab3Tests, ThreadCleanupLogicTest) {
    int size = 5;
    int* arr = new int[size];

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 1;
    arr[3] = 0;
    arr[4] = 2;

    int target_marker = 1;

    for (int i = 0; i < size; ++i) {
        if (arr[i] == target_marker) {
            arr[i] = 0;
        }
    }

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 2);

    delete[] arr;
}