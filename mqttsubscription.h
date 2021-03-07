#pragma once

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

class MqttSubscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)
public:
    MqttSubscription(QMqttSubscription *sub);
    ~MqttSubscription();

signals:
    void topicChanged(QString);
    void messageReceived(const QMqttMessage &mqttMessage);

private:
    QMqttSubscription *subscribe;
    QMqttTopicFilter m_topic;
};
