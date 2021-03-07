#pragma once

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QtMqtt/QMqttMessage>

#include <QMap>
#include <map>
#include <memory>

#include "mqttsubscription.h"

class MqttWorker : public QMqttClient
{
    Q_OBJECT
    Q_PROPERTY(QStringList subscribers READ getSubscribers NOTIFY subscribersChanged)
    Q_PROPERTY(QStringList publishers READ getPublishers NOTIFY publishersChanged)
public:
    explicit MqttWorker(QObject *parent = nullptr);

    QStringList getPublishers() const;
    QStringList getSubscribers() const;

public slots:
    void addSubscriber(const QString &topicName);
    void removeSubscriber(const QString &topicName);

    void addPublisher(const QString &topicName);
    void removePublisher(const QString &topicName);

    quint32 publishMessage(const QString &topicName, const QString &message);

signals:
    void subscribersChanged();
    void publishersChanged();
    void newMessage(const QString &topicName, const QString &message);

private:
    std::map<QString, std::unique_ptr<MqttSubscription>> m_subscribers;
    std::map<QString, QMqttTopicName> m_publishers;

    void subscriptionMessage(const QMqttMessage &mqttMessage);
};
