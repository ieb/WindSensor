#include <jdy40.h>
#include <unity.h>
#include <iostream>



using namespace fakeit;

void setUp(void) {
    ArduinoFakeReset();
}



void test_check_fail_crc() {
    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();

    TEST_ASSERT_EQUAL_INT16(-1, jdy.checkCRC(""));
    TEST_ASSERT_EQUAL_INT16(-1, jdy.checkCRC("12312,12312,"));
    TEST_ASSERT_EQUAL_INT16(-1, jdy.checkCRC("12312,12312,asaa"));

}

void test_write() {
    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();



    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(char))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(int, int))).AlwaysReturn();

    jdy.writeLine("testing,1,2,3");

    Verify(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *)).Using("testing,1,2,3")).Once();
    Verify(OverloadedMethod(ArduinoFake(Serial), print, size_t(char)).Using(',')).Once();
    Verify(OverloadedMethod(ArduinoFake(Serial), println, size_t(int, int)).Using(13080,HEX)).Once();
    
}

void test_read() {

    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();


    When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    // output line and chcksum in hex 13080 == 0x3318
    When(Method(ArduinoFake(Serial), read)).Return('t','e','s','t','i','n','g',',','1',',','2',',','3',',','3','3','1','8','\n');

    // error output
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();

    char * line = jdy.readLine();
    TEST_ASSERT_NOT_NULL(line);

    TEST_ASSERT_EQUAL_STRING("testing,1,2,3", line);

}


void test_read_badchecksum() {
    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();


    When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    // bad checksum
    When(Method(ArduinoFake(Serial), read)).Return('t','e','s','t','i','n','g',',','1',',','2',',','3',',','3','3','1','6','\n');

    // error output
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();

    char * line = jdy.readLine();
    TEST_ASSERT_NULL(line);

}



void test_read_emptyline() {
    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();


    When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    // Empty line
    When(Method(ArduinoFake(Serial), read)).Return('\n');
    
    // error output
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();

    char * line = jdy.readLine();
    TEST_ASSERT_NULL(line);
}


void test_read_comma() {
    When(Method(ArduinoFake(), pinMode)).Return();

    Serial_* output = ArduinoFakeMock(Serial);
    Serial_* debug = ArduinoFakeMock(Serial);

    Jdy40 jdy(10,9600, output, debug);

    Verify(Method(ArduinoFake(), pinMode).Using(10, OUTPUT)).Once();


    When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    // Comma
    When(Method(ArduinoFake(Serial), read)).Return(',','\n');
    
    // error output
    When(OverloadedMethod(ArduinoFake(Serial), print, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();

    char * line = jdy.readLine();
    TEST_ASSERT_NULL(line);
}



int main(int argc, char **argv) { 
    try {
        UNITY_BEGIN();
        RUN_TEST(test_check_fail_crc);
        RUN_TEST(test_write);
        RUN_TEST(test_read);
        RUN_TEST(test_read_badchecksum);
        RUN_TEST(test_read_emptyline);
        RUN_TEST(test_read_comma);
        return UNITY_END();
    } catch( UnexpectedMethodCallException e) {
            std::cout << "Exception:" << e << std::endl;

    }
}