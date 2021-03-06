/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2014 Michael Zanetti <michael_zanetti@gmx.net>           *
 *  Copyright (C) 2015 Simon Stürz <simon.stuerz@guh.io>                   *
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

#ifndef LOGENGINE_H
#define LOGENGINE_H

#include "logentry.h"
#include "logfilter.h"
#include "types/event.h"
#include "types/action.h"
#include "rule.h"

#include <QObject>
#include <QSqlDatabase>
#include <QTimer>

namespace nymeaserver {

class LogEngine: public QObject
{
    Q_OBJECT
public:
    LogEngine(const QString &driver, const QString &dbName, const QString &hostname = QString("127.0.0.1"), const QString &username = QString(), const QString &password = QString(), int maxDBSize = 50000, QObject *parent = 0);
    ~LogEngine();

    QList<LogEntry> logEntries(const LogFilter &filter = LogFilter()) const;

    void setMaxLogEntries(int maxLogEntries, int overflow);
    void clearDatabase();

    void logSystemEvent(const QDateTime &dateTime, bool active, Logging::LoggingLevel level = Logging::LoggingLevelInfo);
    void logEvent(const Event &event);
    void logAction(const Action &action, Logging::LoggingLevel level = Logging::LoggingLevelInfo, int errorCode = 0);
    void logRuleTriggered(const Rule &rule);
    void logRuleActiveChanged(const Rule &rule);
    void logRuleEnabledChanged(const Rule &rule, const bool &enabled);
    void logRuleActionsExecuted(const Rule &rule);
    void logRuleExitActionsExecuted(const Rule &rule);
    void removeDeviceLogs(const DeviceId &deviceId);
    void removeRuleLogs(const RuleId &ruleId);
    QList<DeviceId> devicesInLogs() const;

signals:
    void logEntryAdded(const LogEntry &logEntry);
    void logDatabaseUpdated();

private:
    bool initDB(const QString &username, const QString &password);
    void appendLogEntry(const LogEntry &entry);
    void rotate(const QString &dbName);


    bool migrateDatabaseVersion2to3();

private slots:
    void checkDBSize();

private:
    QSqlDatabase m_db;
    int m_dbMaxSize;
    int m_overflow;
    bool m_trimWarningPrinted = false;
    int m_entryCount = 0;
    QTimer m_housekeepingTimer;
};

}

#endif
