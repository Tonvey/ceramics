#pragma once
#include <iostream>
#define TEST_ASSERT(exp) do{                  \
        if(!(exp)){                                 \
            std::cerr<<"TEST Failed At "<< __FILE__ \
                     <<':'<<__LINE__<<':'<<#exp;   \
            abort();                                \
        }                                           \
    }while(0)
#define TEST_ASSERT_STATE(exp,state) do{                  \
        if(!(exp)){                                      \
            std::cerr<<"TEST Failed At "<< __FILE__ \
                     <<':'<<__LINE__<<':'<<state;   \
            abort();                                \
        }                                           \
    }while(0)
