#ifndef fff_catch_helper_H
#define fff_catch_helper_H

/*
 *  FFF helper macros for Catch.
 */


/*
 *  MATCHERS 
 */
#define CHECK_THAT_F(function_, matcher)                CHECK_THAT(function_ ## _fake, matcher)
#define REQUIRE_THAT_F(function_, matcher)              REQUIRE_THAT(function_ ## _fake, matcher)

/* 
 *  ORDERINGS
 */
#define REQUIRE_CALLED_IN_ORDER(index_, function_)      REQUIRE(fff.call_history[index_] == ((void *) function_))
#define CHECK_CALLED_IN_ORDER(index_, function_)        CHECK(fff.call_history[index_] == ((void *) function_))

/*  Internal macros for use with REQUIRE_CALLORDER && REQUIRE_CALLORDER_FROM  */
#define _NUM_ARGS2(X,X64,X63,X62,X61,X60,X59,X58,X57,X56,X55,X54,X53,X52,X51,X50,X49,X48,X47,X46,X45,X44,X43,X42,X41,X40,X39,X38,X37,X36,X35,X34,X33,X32,X31,X30,X29,X28,X27,X26,X25,X24,X23,X22,X21,X20,X19,X18,X17,X16,X15,X14,X13,X12,X11,X10,X9,X8,X7,X6,X5,X4,X3,X2,X1,N,...) N
#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define _REQUIRE_CALLORDER_1(index_, function_)         REQUIRE_CALLED_IN_ORDER(index_, function_)

#define _REQUIRE_CALLORDER_2(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_1(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_3(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_2(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_4(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_3(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_5(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_4(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_6(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_5(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_7(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_6(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_8(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_7(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_9(index_, function_, ...)    REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_8(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_10(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_9(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_11(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_10(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_12(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_11(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_13(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_12(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_14(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_13(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_15(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_14(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_16(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_15(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_17(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_16(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_18(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_17(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_19(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_18(index_ + 1, __VA_ARGS__)
#define _REQUIRE_CALLORDER_20(index_, function_, ...)   REQUIRE_CALLED_IN_ORDER(index_, function_);        \
                                                        _REQUIRE_CALLORDER_19(index_ + 1, __VA_ARGS__)

#define _REQUIRE_CALLORDER_N3(index_, N, ...)           _REQUIRE_CALLORDER_ ## N(index_, __VA_ARGS__)
#define _REQUIRE_CALLORDER_N2(index_, N, ...)           _REQUIRE_CALLORDER_N3(index_, N, __VA_ARGS__)


/*  Internal macros for use with CHECK_CALLORDER && CHECK_CALLORDER_FROM  */
#define _CHECK_CALLORDER_1(index_, function_)           CHECK_CALLED_IN_ORDER(index_, function)

#define _CHECK_CALLORDER_2(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_1(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_3(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_2(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_4(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_3(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_5(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_4(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_6(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_5(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_7(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_6(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_8(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_7(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_9(index_, function_, ...)      CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_8(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_10(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_9(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_11(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_10(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_12(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_11(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_13(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_12(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_14(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_13(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_15(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_14(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_16(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_15(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_17(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_16(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_18(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_17(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_19(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_18(index_ + 1, __VA_ARGS__)
#define _CHECK_CALLORDER_20(index_, function_, ...)     CHECK_CALLED_IN_ORDER(index_, function_);        \
                                                        _CHECK_CALLORDER_19(index_ + 1, __VA_ARGS__)

#define _CHECK_CALLORDER_N3(index_, N, ...)           _CHECK_CALLORDER_ ## N(index_, __VA_ARGS__)
#define _CHECK_CALLORDER_N2(index_, N, ...)           _CHECK_CALLORDER_N3(index_, N, __VA_ARGS__)


/*  Fail if the function was not called in this particular order.  */
#define REQUIRE_CALLORDER_FROM(index_, ...)             _REQUIRE_CALLORDER_N2(index_, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define REQUIRE_CALLORDER(...)                          REQUIRE_CALLORDER_FROM(0, __VA_ARGS__)

/*  Fail if the function was not called in this particular order, but continue.  */
#define CHECK_CALLORDER_FROM(index_, ...)               _CHECK_CALLORDER_N2(index_, NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define CHECK_CALLORDER(...)                            CHECK_CALLORDER_FROM(0, __VA_ARGS__)


#endif