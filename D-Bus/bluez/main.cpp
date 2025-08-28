#include <iostream>
#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/sdbus-c++.h>
#include <memory>

int main() 
{
    std::unique_ptr<sdbus::IConnection> connection = sdbus::createSystemBusConnection();
    std::unique_ptr<sdbus::IProxy> proxy = sdbus::createProxy(*connection.get(), "org.bluez", "/org/bluez/hci0");
    if (proxy) {
        std::cout << "Create proxy successfully" <<  std::endl;
    }

    std::string name = proxy->getProperty("Name").onInterface("org.bluez.Adapter1");
    std::cout << name;

    return 0;
}