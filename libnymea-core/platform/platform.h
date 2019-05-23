/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2019 Michael Zanetti <michael.zanetti@nymea.io>          *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class PlatformSystemController;
class PlatformUpdateController;
class PlatformZeroConfController;

namespace nymeaserver {

class Platform : public QObject
{
    Q_OBJECT
public:
    explicit Platform(QObject *parent = nullptr);

    PlatformSystemController *systemController() const;
    PlatformUpdateController *updateController() const;
    PlatformZeroConfController *zeroConfController() const;

private:
    QStringList pluginSearchDirs() const;

    void loadSystemPlugin(const QString &file);
    void loadUpdatePlugin(const QString &file);
    void loadZeroConfPlugin(const QString &file);

private:
    PlatformSystemController *m_platformSystemController = nullptr;
    PlatformUpdateController *m_platformUpdateController = nullptr;
    PlatformZeroConfController *m_platformZeroConfController = nullptr;
};

}

#endif // PLATFORM_H
