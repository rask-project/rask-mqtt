#include "mqttsubscription.h"
#include <QDebug>

MqttSubscription::MqttSubscription(QMqttSubscription *sub) :
    subscribe(sub)
{
    connect(subscribe, &QMqttSubscription::messageReceived, this, &MqttSubscription::messageReceived);
    m_topic = subscribe->topic();
}

MqttSubscription::~MqttSubscription()
{
    subscribe->unsubscribe();
}
