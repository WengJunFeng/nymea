/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stürz <simon.stuerz@guh.io>                   *
 *  Copyright (C) 2014 Michael Zanetti <michael_zanetti@gmx.net>           *
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

/*!
    \class nymeaserver::StateHandler
    \brief This subclass of \l{JsonHandler} processes the JSON requests for the \tt States namespace of the JSON-RPC API.

    \ingroup json
    \inmodule core

    This \l{JsonHandler} will be created in the \l{JsonRPCServer} and used to handle JSON-RPC requests
    for the \tt {States} namespace of the API.

    \sa State, JsonHandler, JsonRPCServer
*/

#include "statehandler.h"
#include "nymeacore.h"
#include "loggingcategories.h"

namespace nymeaserver {

/*! Constructs a new \l{StateHandler} with the given \a parent. */
StateHandler::StateHandler(QObject *parent) :
    JsonHandler(parent)
{
    QVariantMap params;
    QVariantMap returns;

    params.clear(); returns.clear();
    setDescription("GetStateType", "Get the StateType for the given stateTypeId.");
    params.insert("stateTypeId", JsonTypes::basicTypeToString(JsonTypes::Uuid));
    setParams("GetStateType", params);
    returns.insert("deviceError", JsonTypes::deviceErrorRef());
    returns.insert("o:stateType", JsonTypes::stateTypeRef());
    setReturns("GetStateType", returns);
}

/*! Returns the name of the \l{StateHandler}. In this case \b States.*/
QString StateHandler::name() const
{
    return "States";
}

JsonReply* StateHandler::GetStateType(const QVariantMap &params) const
{
    qCDebug(dcJsonRpc) << "asked for state type" << params;
    StateTypeId stateTypeId(params.value("stateTypeId").toString());
    foreach (const DeviceClass &deviceClass, NymeaCore::instance()->deviceManager()->supportedDevices()) {
        foreach (const StateType &stateType, deviceClass.stateTypes()) {
            if (stateType.id() == stateTypeId) {
                QVariantMap data = statusToReply(DeviceManager::DeviceErrorNoError);
                data.insert("stateType", JsonTypes::packStateType(stateType, deviceClass.pluginId(), params.value("locale").toLocale()));
                return createReply(data);
            }
        }
    }
    return createReply(statusToReply(DeviceManager::DeviceErrorStateTypeNotFound));
}

}
