#ifndef CU_TEST_H
#define CU_TEST_H

#include <setjmp.h>
#include <stdarg.h>

// CuString

#define ALLOC(TYPE)		((TYPE*) malloc(sizeof(TYPE)))

char* StrAlloc(int size);
char* StrCopy(char* old);

#define STRING_MAX	256
#define STRING_INC	256

typedef struct
{
	int length;
	int size;
	char* buffer;
} CuString;

void CuStringInit(CuString* str);
CuString* CuStringNew(void);
void CuStringRead(CuString* str, char* path);
void CuStringAppend(CuString* str, char* text);
void CuStringAppendChar(CuString* str, char ch);
void CuStringAppendFormat(CuString* str, char* format, ...);
void CuStringResize(CuString* str, int newSize);

// CuTest

typedef void (*TestFunction)(void*);

typedef struct
{
	char* name;
	TestFunction function;
	int failed;
	int ran;
	char* message;
	jmp_buf *jumpBuf;
} CuTest;

void CuTestInit(CuTest* t, char* name, TestFunction function);
CuTest* CuTestNew(char* name, TestFunction function);
void CuFail(CuTest* tc, char* message);
void CuAssert(CuTest* tc, char* message, int condition);
void CuAssertTrue(CuTest* tc, int condition);
void CuAssertStrEquals(CuTest* tc, char* expected, char* actual);
void CuAssertIntEquals(CuTest* tc, int expected, int actual);
void CuTestRun(CuTest* tc);

// CuSuite

#define MAX_TEST_CASES	1024	

#define SUITE_ADD_TEST(SUITE,TEST)	\
	CuSuiteAdd(SUITE, CuTestNew(#TEST, TEST))

typedef struct
{
	int count;
	CuTest* list[MAX_TEST_CASES]; 
	int failCount;

} CuSuite;


void CuSuiteInit(CuSuite* testSuite);
CuSuite* CuSuiteNew();
void CuSuiteAdd(CuSuite* testSuite, CuTest *testCase);
void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2);
void CuSuiteRun(CuSuite* testSuite);
void CuSuiteSummary(CuSuite* testSuite, CuString* summary);
void CuSuiteDetails(CuSuite* testSuite, CuString* details);

#endif /* CU_TEST_H */
