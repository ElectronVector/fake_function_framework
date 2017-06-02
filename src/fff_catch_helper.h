#ifndef fff_catch_helper_H
#define fff_catch_helper_H

#include "catch.hpp"
/*
 *  FFF helper macros && matchers for Catch.
 */

template<typename T>
class T_Range : public Catch::MatcherBase<T> {
    T m_begin, m_end;
public:
    T_Range( T begin, T end ) : m_begin( begin ), m_end( end ) {}

    virtual bool match( T const& i ) const override {
        return i >= m_begin && i <= m_end;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is between " << m_begin << " and " << m_end;
        return ss.str();
    }
};

template<typename T>
class T_EQUAL_TO : public Catch::MatcherBase<T> {
    T m_value;
public:
    T_EQUAL_TO( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i == m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class T_NOT_EQUAL_TO : public Catch::MatcherBase<T> {
    T m_value;
public:
    T_NOT_EQUAL_TO( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i != m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is not equal to " << m_value;
        return ss.str();
    }
};

template<typename T>
class T_IS_GREATER_THAN : public Catch::MatcherBase<T> {
    T m_value;
public:
    T_IS_GREATER_THAN( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i > m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is greater than " << m_value;
        return ss.str();
    }
};

template<typename T>
class T_IS_SMALLER_THAN : public Catch::MatcherBase<T> {
    T m_value;
public:
    T_IS_SMALLER_THAN( T value ) : m_value( value ) {}

    virtual bool match( T const& i ) const override {
        return i < m_value;
    }

    virtual std::string describe() const {
        std::ostringstream ss;
        ss << "is smaller than " << m_value;
        return ss.str();
    }
};

// The builder functions
template<typename T>
inline T_Range<T> IsBetween( T begin, T end ) {
    return T_Range<T>( begin, end );
}

template<typename T>
inline T_EQUAL_TO<T> IsEqualTo( T value ) {
    return T_EQUAL_TO<T>( value );
}

template<typename T>
inline T_NOT_EQUAL_TO<T> IsNotEqualTo( T value ) {
    return T_NOT_EQUAL_TO<T>( value );
}

template<typename T>
inline T_IS_GREATER_THAN<T> IsGreaterThan( T value ) {
    return T_IS_GREATER_THAN<T>( value );
}

template<typename T>
inline T_IS_SMALLER_THAN<T> IsSmallerThan( T value ) {
    return T_IS_SMALLER_THAN<T>( value );
}

/*
 *  MATCHER MACROS
 */
#define CHECK_THAT_F(function_, matcher_)                CHECK_THAT(function_ ## _fake, matcher_)
#define REQUIRE_THAT_F(function_, matcher_)              REQUIRE_THAT(function_ ## _fake, matcher_)

#define CHECK_CALLCOUNT(function_, matcher_)             CHECK_THAT(function_ ## _fake.call_count, matcher_)
#define REQUIRE_CALLCOUNT(function_, matcher_)           CHECK_THAT(function_ ## _fake.call_count, matcher_)

#define CHECK_ARG0(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg0_val, matcher_)
#define CHECK_ARG1(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg1_val, matcher_)
#define CHECK_ARG2(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg2_val, matcher_)
#define CHECK_ARG3(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg3_val, matcher_)
#define CHECK_ARG4(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg4_val, matcher_)
#define CHECK_ARG5(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg5_val, matcher_)
#define CHECK_ARG6(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg6_val, matcher_)
#define CHECK_ARG7(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg7_val, matcher_)
#define CHECK_ARG8(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg8_val, matcher_)
#define CHECK_ARG9(function_, matcher_)                  CHECK_THAT(function_ ## _fake.arg9_val, matcher_)
#define CHECK_ARG10(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg10_val, matcher_)
#define CHECK_ARG11(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg11_val, matcher_)
#define CHECK_ARG12(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg12_val, matcher_)
#define CHECK_ARG13(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg13_val, matcher_)
#define CHECK_ARG14(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg14_val, matcher_)
#define CHECK_ARG15(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg15_val, matcher_)
#define CHECK_ARG16(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg16_val, matcher_)
#define CHECK_ARG17(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg17_val, matcher_)
#define CHECK_ARG18(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg18_val, matcher_)
#define CHECK_ARG19(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg19_val, matcher_)
#define CHECK_ARG20(function_, matcher_)                 CHECK_THAT(function_ ## _fake.arg20_val, matcher_)


#define REQUIRE_ARG0(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg0_val, matcher_)
#define REQUIRE_ARG1(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg1_val, matcher_)
#define REQUIRE_ARG2(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg2_val, matcher_)
#define REQUIRE_ARG3(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg3_val, matcher_)
#define REQUIRE_ARG4(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg4_val, matcher_)
#define REQUIRE_ARG5(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg5_val, matcher_)
#define REQUIRE_ARG6(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg6_val, matcher_)
#define REQUIRE_ARG7(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg7_val, matcher_)
#define REQUIRE_ARG8(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg8_val, matcher_)
#define REQUIRE_ARG9(function_, matcher_)                REQUIRE_THAT(function_ ## _fake.arg9_val, matcher_)
#define REQUIRE_ARG10(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg10_val, matcher_)
#define REQUIRE_ARG11(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg11_val, matcher_)
#define REQUIRE_ARG12(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg12_val, matcher_)
#define REQUIRE_ARG13(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg13_val, matcher_)
#define REQUIRE_ARG14(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg14_val, matcher_)
#define REQUIRE_ARG15(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg15_val, matcher_)
#define REQUIRE_ARG16(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg16_val, matcher_)
#define REQUIRE_ARG17(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg17_val, matcher_)
#define REQUIRE_ARG18(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg18_val, matcher_)
#define REQUIRE_ARG19(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg19_val, matcher_)
#define REQUIRE_ARG20(function_, matcher_)               REQUIRE_THAT(function_ ## _fake.arg20_val, matcher_)

/*
 * SETTERS
 */
 #define SET_RETURN(function_, value_)    function_ ## _fake.return_val = (value_)
 #define SET_RETURNS(function_, array_)   SET_RETURN_SEQ(function, (array_).data(), (array_).size())


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