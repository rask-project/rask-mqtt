#include "mqttworker.h"

MqttWorker::MqttWorker(QObject *parent) :
    QMqttClient(parent)
{}

QStringList MqttWorker::getPublishers() const
{
    QStringList publishers;

    for (const auto&[key, value] : m_publishers)
        publishers.append(key);

    return publishers;
}

QStringList MqttWorker::getSubscribers() const
{
    QStringList subscribers;

    for (const auto &[key, value] : m_subscribers)
        subscribers.append(key);

    return subscribers;
}

void MqttWorker::addSubscriber(const QString &topicName)
{
    if (m_subscribers.contains(topicName)) {
        qInfo() << "Subscriber already exists" << topicName;
        return;
    }

    auto sub = std::make_unique<MqttSubscription>(QMqttClient::subscribe(topicName));
    auto [it, result] = m_subscribers.try_emplace(topicName, std::move(sub));
    if (!result) {
        qCritical() << "Error trying subscribe topic" << topicName;
        return;
    }

    qDebug() << "Added subscriber" << topicName;
    connect(it->second.get(), &MqttSubscription::messageReceived, this, &MqttWorker::subscriptionMessage);
    emit subscribersChanged();
}

void MqttWorker::removeSubscriber(const QString &topicName)
{
    if (!m_subscribers.contains(topicName)) {
        qCritical() << "Subscriber not created" << topicName;
        return;
    }

    m_subscribers.erase(topicName);
    qDebug() << "Removed subscriber" << topicName;
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
    if (!m_publishers.contains(topicName)) {
        qCritical() << "Publisher not created" << topicName;
        return;
    }

    m_publishers.erase(topicName);
    qDebug() << "Removed publisher" << topicName;
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
