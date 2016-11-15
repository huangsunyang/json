//
//  leptjson.hpp
//  json_1
//
//  Created by huangsunyang on 11/15/2016.
//  Copyright © 2016年 huangsunyang. All rights reserved.
//

#ifndef leptjson_hpp
#define leptjson_hpp
#include <stdio.h>
//JSON的基本类型
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//基本类型
struct lept_value {
    lept_type type;
    lept_type get_type();
};

struct lept_context{
    const char * json;
    //删除字符串的左侧空格？
    void lept_parse_whitespace();
};

//接受一个JSON字符串，将其类型赋值给lept_value
int lept_parse(lept_value * v, const char * json);
static int lept_parse_value(lept_context * c, lept_value * v);


//lept_type lept_get_type(const lept_value * v);


#endif /* leptjson_hpp */





























