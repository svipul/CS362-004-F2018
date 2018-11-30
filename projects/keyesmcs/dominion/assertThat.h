#ifndef ASSERT_THAT
#define ASSERT_THAT 1

enum ASSERTION {
    isFalse = 0,
    isTrue
};


int assertThat(char* assertionText, int assertion, int testResult);

#endif
