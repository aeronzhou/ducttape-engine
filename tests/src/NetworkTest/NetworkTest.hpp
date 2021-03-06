
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_TESTS_NETWORKTEST
#define DUCTTAPE_ENGINE_TESTS_NETWORKTEST

#define SERVER_PORT 20501
#define CLIENT_PORT 20502
#define DATA_INCREMENT 42

#include <Config.hpp>

#include "Test.hpp"

#include <Core/Root.hpp>
#include <Network/NetworkManager.hpp>
#include <Utils/Utils.hpp>

/**
  * @file
  * A test for the Event system sending Events over network. The client connects to the server, and sends
  * a CustomNetworkEvent. The server receives that Event, adds DATA_INCREMENT to the data value and sends
  * a new CustomNetworkEvent back to the client. The client calculates the difference of the data value
  * and checks against DATA_INCREMENT.
  */

namespace NetworkTest {

class NetworkTest : public Test {
    bool run(int argc, char** argv);
    bool runServer();
    bool runClient();
    QString getTestName();
};

////////////////////////////////////////////////////////////////

class CustomNetworkEvent : public dt::NetworkEvent {
public:
    enum Sender {
        CLIENT = 1,
        SERVER = 2
    };

    CustomNetworkEvent(int data, Sender e);
    const QString getType() const;
    std::shared_ptr<dt::NetworkEvent> clone() const;
    void serialize(dt::IOPacket& p);

public:
    uint32_t mData;
    Sender mEnum;
};

////////////////////////////////////////////////////////////////

class CustomServerEventListener/* : public dt::EventListener*/ : public QObject {
    Q_OBJECT
public:
    CustomServerEventListener();

private slots:
    void _handleEvent(std::shared_ptr<dt::NetworkEvent> e);

    void _initialize();

public:
    uint32_t mDataReceived;
};

////////////////////////////////////////////////////////////////

class CustomClientEventListener : public QObject {
    Q_OBJECT
public:
    CustomClientEventListener();

private slots:
    void _handleEvent(std::shared_ptr<dt::NetworkEvent> e);

    void _initialize();

public:
    uint32_t mDataReceived;
};


} // namespace NetworkTest

#endif
