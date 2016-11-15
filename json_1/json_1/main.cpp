//
//  main.cpp
//  json_1
//
//  Created by huangsunyang on 11/15/2016.
//  Copyright © 2016年 huangsunyang. All rights reserved.
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "leptjson.hpp"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if(equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
__FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
            }\
        } while(0)

#define EXPECT_EQ_INT(expect, actual) \
EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null() {
    lept_value v;
    v.type = LEPT_TRUE;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
    EXPECT_EQ_INT(LEPT_NULL, v.get_type());
}

static void test_parse_true() {
    lept_value v;
    v.type = LEPT_NULL;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "true"));
    EXPECT_EQ_INT(LEPT_TRUE, v.get_type());
}

static void test_parse_false() {
    lept_value v;
    v.type = LEPT_NULL;
    EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "false"));
    EXPECT_EQ_INT(LEPT_FALSE, v.get_type());
}

static void test_parse() {
    test_parse_null();
    test_parse_true();
    test_parse_false();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 1.0 / test_count * 100);
    return 0;
}
