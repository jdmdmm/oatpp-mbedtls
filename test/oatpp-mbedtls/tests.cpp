
#include "oatpp-test/UnitTest.hpp"

#include "FullTest.hpp"
#include "FullAsyncTest.hpp"
#include "FullAsyncClientTest.hpp"

#include "oatpp/concurrency/SpinLock.hpp"
#include "oatpp/Environment.hpp"

#include <iostream>

namespace {

void runTests() {

  {

    oatpp::test::mbedtls::FullTest test_virtual(0, 100);
    test_virtual.run();

    oatpp::test::mbedtls::FullTest test_port(8443, 10);
    test_port.run();

  }

  {

    oatpp::test::mbedtls::FullAsyncTest test_virtual(0, 100);
    test_virtual.run();

    oatpp::test::mbedtls::FullAsyncTest test_port(8443, 10);
    test_port.run();

  }

  {

    oatpp::test::mbedtls::FullAsyncClientTest test_virtual(0, 10);
    test_virtual.run(20); // - run this test 20 times.

    oatpp::test::mbedtls::FullAsyncClientTest test_port(8443, 10);
    test_port.run(1);

  }

}

}

int main() {

  oatpp::Environment::init();

  runTests();

  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::Environment::getObjectsCount() == 0);

  oatpp::Environment::destroy();

  return 0;
}
