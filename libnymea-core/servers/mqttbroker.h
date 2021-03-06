/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2018 Michael Zanetti <michael.zanetti@nymea.io>          *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  nymea is free software: you can redistribute it and/or modify          *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 2 of the License.                *
 *                                                                         *
 *  nymea is distributed in the hope that it will be useful,               *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with nymea. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MQTTBROKER_H
#define MQTTBROKER_H

#include <QObject>
#include <QHostAddress>
#include <QSslConfiguration>

#include "nymea-mqtt/mqtt.h"
#include "nymeaconfiguration.h"

class MqttServer;

namespace nymeaserver {

class NymeaMqttAuthorizer;

class MqttBroker : public QObject
{
    Q_OBJECT
public:
    explicit MqttBroker(QObject *parent = nullptr);
    ~MqttBroker();

    bool startServer(const ServerConfiguration &config, const QSslConfiguration &sslConfiguration = QSslConfiguration());
    bool isRunning(const QString &configId) const;
    bool isRunning() const;
    QList<ServerConfiguration> configurations() const;
    void stopServer(const QString &configId);

    QList<MqttPolicy> policies();
    MqttPolicy policy(const QString &clientId);
    void updatePolicy(const MqttPolicy &policy);
    void updatePolicies(const QList<MqttPolicy> &policies);
    bool removePolicy(const QString &clientId);

    void publish(const QString &topic, const QByteArray &payload);

private slots:
    void onClientConnected(int serverAddressId, const QString &clientId, const QString &username, const QHostAddress &clientAddress);
    void onClientDisconnected(const QString &clientId);
    void onPublishReceived(const QString &clientId, quint16 packetId, const QString &topic, const QByteArray &payload);
    void onClientSubscribed(const QString &clientId, const QString &topicFilter, Mqtt::QoS requestedQoS);
    void onClientUnsubscribed(const QString &clientId, const QString &topicFilter);

signals:
    void clientConnected(const QString &clientId);
    void clientDisconnected(const QString &clientId);
    void publishReceived(const QString &clientId, const QString &topic, const QByteArray &payload);
    void clientSubscribed(const QString &clientId, const QString &topicFilter);
    void clientUnsubscribed(const QString &clientId, const QString &topicFilter);
    void policyAdded(const MqttPolicy &policy);
    void policyChanged(const MqttPolicy &policy);
    void policyRemoved(const MqttPolicy &policy);

private:
    MqttServer* m_server = nullptr;
    NymeaMqttAuthorizer *m_authorizer = nullptr;
    QHash<int, ServerConfiguration> m_configs;
    QHash<QString, MqttPolicy> m_policies;


    friend class NymeaMqttAuthorizer;
};
}

#endif // MQTTBROKER_H
