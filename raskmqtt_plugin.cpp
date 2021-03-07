#include "raskmqtt_plugin.h"
#include "mqttworker.h"

#include <QtQml>

void RaskMqttPlugin::registerTypes(const char *uri)
{
    // @uri Rask.Mqtt
    qmlRegisterType<MqttWorker>(uri, 1, 0, "MqttWorker");
}
