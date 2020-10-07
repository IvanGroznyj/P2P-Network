/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MyTest_init = false;
#include "J:\GIT_Projects\P2P-Network\UnitTests\FirstFile.h"

static MyTest suite_MyTest;

static CxxTest::List Tests_MyTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTest( "UnitTests/FirstFile.h", 27, "MyTest", suite_MyTest, Tests_MyTest );

static class TestDescription_suite_MyTest_testClient_Addr : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testClient_Addr() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 29, "testClient_Addr" ) {}
 void runTest() { suite_MyTest.testClient_Addr(); }
} testDescription_suite_MyTest_testClient_Addr;

static class TestDescription_suite_MyTest_testClient_AddrTranform : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testClient_AddrTranform() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 41, "testClient_AddrTranform" ) {}
 void runTest() { suite_MyTest.testClient_AddrTranform(); }
} testDescription_suite_MyTest_testClient_AddrTranform;

static class TestDescription_suite_MyTest_testTranslator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testTranslator() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 47, "testTranslator" ) {}
 void runTest() { suite_MyTest.testTranslator(); }
} testDescription_suite_MyTest_testTranslator;

static class TestDescription_suite_MyTest_testCommandsTypes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandsTypes() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 54, "testCommandsTypes" ) {}
 void runTest() { suite_MyTest.testCommandsTypes(); }
} testDescription_suite_MyTest_testCommandsTypes;

static class TestDescription_suite_MyTest_testCommandHi : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandHi() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 67, "testCommandHi" ) {}
 void runTest() { suite_MyTest.testCommandHi(); }
} testDescription_suite_MyTest_testCommandHi;

static class TestDescription_suite_MyTest_testCommandEcho : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandEcho() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 82, "testCommandEcho" ) {}
 void runTest() { suite_MyTest.testCommandEcho(); }
} testDescription_suite_MyTest_testCommandEcho;

static class TestDescription_suite_MyTest_testCommandEchoShortAfterLong : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandEchoShortAfterLong() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 91, "testCommandEchoShortAfterLong" ) {}
 void runTest() { suite_MyTest.testCommandEchoShortAfterLong(); }
} testDescription_suite_MyTest_testCommandEchoShortAfterLong;

static class TestDescription_suite_MyTest_testCommandHash : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandHash() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 105, "testCommandHash" ) {}
 void runTest() { suite_MyTest.testCommandHash(); }
} testDescription_suite_MyTest_testCommandHash;

static class TestDescription_suite_MyTest_testCommandGetFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testCommandGetFile() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 113, "testCommandGetFile" ) {}
 void runTest() { suite_MyTest.testCommandGetFile(); }
} testDescription_suite_MyTest_testCommandGetFile;

static class TestDescription_suite_MyTest_testNATPMP : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTest_testNATPMP() : CxxTest::RealTestDescription( Tests_MyTest, suiteDescription_MyTest, 142, "testNATPMP" ) {}
 void runTest() { suite_MyTest.testNATPMP(); }
} testDescription_suite_MyTest_testNATPMP;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
