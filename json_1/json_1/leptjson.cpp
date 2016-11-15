//
//  leptjson.cpp
//  json_1
//
//  Created by huangsunyang on 11/15/2016.
//  Copyright © 2016年 huangsunyang. All rights reserved.
//

#include "leptjson.hpp"
#include <cassert>
#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

int lept_parse(lept_value * v, const char * json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    c.lept_parse_whitespace();
    return lept_parse_value(&c, v);
}

//删除左侧的空格
void lept_context::lept_parse_whitespace() {
    const char * ptr = json;
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r') {
        ptr++;
    }
    json = ptr;
}

lept_type lept_value::get_type() {
    return type;
}

//判断字符串是否为null
static int lept_parse_null(lept_context * c, lept_value * v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = LEPT_NULL;
    //判断其后是否还有别的非空白单词
    c->lept_parse_whitespace();
    if (*c->json != '\0') {
        return LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context * c, lept_value * v) {
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = LEPT_TRUE;
    //判断其后是否还有别的非空白单词
    c->lept_parse_whitespace();
    if (*c->json != '\0') {
        return LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return LEPT_PARSE_OK;
}

static int lept_parse_false(lept_context * c, lept_value * v) {
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = LEPT_FALSE;
    //判断其后是否还有别的非空白单词
    c->lept_parse_whitespace();
    if (*c->json != '\0') {
        return LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return LEPT_PARSE_OK;
}


//通过这个字符串判断是null true 还是 false
static int lept_parse_value(lept_context * c, lept_value * v) {
    switch (*c->json) {
        case 'n': return lept_parse_null(c, v);
        case 't': return lept_parse_true(c, v);
        case 'f': return lept_parse_false(c, v);
        case '\0':return LEPT_PARSE_EXPECT_VALUE;
        default: return LEPT_PARSE_INVALID_VALUE;
    }
}



