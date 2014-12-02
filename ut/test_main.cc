#include <fstream>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>

#include <cppunit/extensions/TestFactoryRegistry.h>

int main()
{
    CppUnit::TestResult controller;

    CppUnit::TestResultCollector result;
    controller.addListener(&result);        

    CppUnit::BriefTestProgressListener progress;
    controller.addListener(&progress);      

    CppUnit::TestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    runner.run(controller);

    CppUnit::CompilerOutputter console_outputter(&result, std::cerr);
    console_outputter.write(); 

    std::ofstream output_file ("testresults.xml");
    CppUnit::XmlOutputter xml_outputter(&result, output_file);
    xml_outputter.write(); 

    return not result.wasSuccessful();
}

