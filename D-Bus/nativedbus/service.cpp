#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <sdbus-c++/IObject.h>
#include <sdbus-c++/IConnection.h>

#define OBJECT_PATH "/thai/vo/dinh/path"
#define SERVICE_NAME "thai.vo.dinh.service"
#define INTERFACE_NAME "thai.vo.dinh.interface"

class ServiceObject 
{
public:
    ServiceObject()
    : m_object(sdbus::createObject(*m_connection, OBJECT_PATH))
        , m_connection(sdbus::createSessionBusConnection())
    {
        std::cout << "THAIVD";
        m_connection->requestName(SERVICE_NAME);
    }

    void registerMethod() {
        if (m_object) {
            m_object->registerMethod("getYourName").onInterface(INTERFACE_NAME).implementedAs(
                [this]() -> std::string {
                    std::string name;
                    std::cout << "Enter your name: ";
                    std::cin >> name;
                    return name;
                }
            );
        }

        m_object->finishRegistration();
    }

    void run() {
        m_connection->enterEventLoop();
    }
private:
std::unique_ptr<sdbus::IConnection> m_connection;
std::unique_ptr<sdbus::IObject> m_object;
};

int main() {
    ServiceObject object;
    object.registerMethod();
    object.run();
    return 0;
}