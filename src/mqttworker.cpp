#include "mqttworker.h"

MqttWorker::MqttWorker(QObject *parent) :
    QMqttClient(parent)
{}

QStringList MqttWorker::getPublishers() const
{
    return m_publishers.keys();
}

QStringList MqttWorker::getSubscribers() const
{
    return m_subscribers.keys();
}

void MqttWorker::addSubscriber(const QString &topicName)
{
    qDebug() << "Add subscriber" << topicName;
    if (m_subscribers.contains(topicName)) {
        qCritical() << "Subscriber already exists" << topicName;
        return;
    }

    auto *subscription = new MqttSubscription(QMqttClient::subscribe(topicName));
    connect(subscription, &MqttSubscription::messageReceived, this, &MqttWorker::subscriptionMessage);

    m_subscribers[topicName] = subscription;
    emit subscribersChanged();
}

void MqttWorker::removeSubscriber(const QString &topicName)
{
    qDebug() << "Remove subscriber" << topicName;
    if (!m_subscribers.contains(topicName)) {
        qCritical() << "Subscriber not created" << topicName;
        return;
    }

    delete m_subscribers.find(topicName).value();
    m_subscribers.remove(topicName);
    emit subscribersChanged();
}

void MqttWorker::addPublisher(const QString &topicName)
{
    qDebug() << "Add publisher" << topicName;
    if (m_publishers.contains(topicName)) {
        qCritical() << "Publisher already exists" << topicName;
        return;
    }

    m_publishers[topicName] = QMqttTopicName(topicName);
    emit publishersChanged();
}

void MqttWorker::removePublisher(const QString &topicName)
{
    qDebug() << "Remove publisher" << topicName;
    if (!m_publishers.contains(topicName)) {
        qCritical() << "Publisher not created" << topicName;
        return;
    }

    m_publishers.remove(topicName);
    emit publishersChanged();
}

quint32 MqttWorker::publishMessage(const QString &topicName, const QString &message)
{
    qDebug() << "Publish message" << topicName << message;
    const auto topic = m_publishers[topicName];
    if (!topic.isValid()) {
        qCritical() << "Topic name is invalid" << topicName;
        return 0;
    }
    return publish(topic, message.toUtf8());
}

void MqttWorker::subscriptionMessage(const QMqttMessage &mqttMessage)
{
    qDebug() << "Message Mqtt" << mqttMessage.topic() << mqttMessage.payload();
    emit newMessage(mqttMessage.topic().name(), mqttMessage.payload());
}
