#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <sdbus-c++/IObject.h>
#include <sdbus-c++/IConnection.h>

#define OBJECT_PATH "/thai/vo/dinh/path"
#define SERVICE_NAME "thai.vo.dinh.service"
#define INTERFACE_NAME "thai.vo.dinh.interface"

int main()
{
    std::unique_ptr<sdbus::IConnection> connection = sdbus::createSessionBusConnection();
    std::string m_myname;
    if (connection) {
        std::unique_ptr<sdbus::IProxy> proxy = sdbus::createProxy(*connection, SERVICE_NAME, OBJECT_PATH);
        proxy->callMethod("getYourName").onInterface(INTERFACE_NAME).storeResultsTo(m_myname);
    }

    std::cout << m_myname << std::endl;

    connection->enterEventLoop();
    return 0;
}