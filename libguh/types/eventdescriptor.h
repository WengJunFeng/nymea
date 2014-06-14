/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  This file is part of guh.                                              *
 *                                                                         *
 *  Guh is free software: you can redistribute it and/or modify            *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 2 of the License.                *
 *                                                                         *
 *  Guh is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh. If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef EVENTDESCRIPTOR_H
#define EVENTDESCRIPTOR_H

#include "typeutils.h"
#include "paramdescriptor.h"
#include "event.h"

#include <QString>
#include <QVariantList>
#include <QDebug>

class EventDescriptor
{
public:
    EventDescriptor(const EventDescriptorId &id, const EventTypeId &eventTypeId, const DeviceId &deviceId, const QList<ParamDescriptor> &paramDescriptors = QList<ParamDescriptor>());

    EventDescriptorId id() const;

    EventTypeId eventTypeId() const;
    DeviceId deviceId() const;

    QList<ParamDescriptor> paramDescriptors() const;
    void setParamDescriptors(const QList<ParamDescriptor> &paramDescriptors);
    ParamDescriptor paramDescriptor(const QString &paramDescriptorName) const;

    bool operator ==(const EventDescriptor &other) const;

    bool operator ==(const Event &event) const;

private:
    EventDescriptorId m_id;
    EventTypeId m_eventTypeId;
    DeviceId m_deviceId;
    QList<ParamDescriptor> m_paramDescriptors;
};
QDebug operator<<(QDebug dbg, const EventDescriptor &eventDescriptor);
QDebug operator<<(QDebug dbg, const QList<EventDescriptor> &eventDescriptors);

#endif // EVENTDESCRIPTOR_H