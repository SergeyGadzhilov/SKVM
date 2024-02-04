/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2024 Hadzhilov Serhii
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "Updater.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

namespace skvm {
namespace updater {

Updater::Updater(std::string version) :
    m_current(version)
{
}

void Updater::CheckForUpdate()
{
    connect(&m_network, &QNetworkAccessManager::finished, this, [this](QNetworkReply* reply) {
        if (!reply)
        {
            std::cerr<<"bad response from the update server"<<std::endl;
            return;
        }

        const auto payload = reply->readAll();
        reply->deleteLater();
        if (payload.isEmpty())
        {
            std::cerr<<"empty response from the update server"<<std::endl;
            return;
        }

        const QJsonDocument response = QJsonDocument::fromJson(payload);
        if (response.isNull() || response.isEmpty())
        {
            std::cerr<<"fail to parse response from the update server"<<std::endl;
            return;
        }

        const auto tag = response.object().value("tag_name");
        if (tag.isUndefined())
        {
            std::cerr<<"field tag_name doesn't exist in the response from update server"<<std::endl;
            return;
        }

        Version latest(tag.toString().toStdString());
        if (latest > m_current)
        {
            std::cout<<"new version "<<latest<<" is available"<<std::endl;
            emit NewVersionAvailable(latest);
        }
    });

    QNetworkRequest request(QUrl("https://api.github.com/repos/SergeyGadzhilov/SKVM/releases/latest"));
    m_network.get(request);
}

} //namespace updates
} //namespace skvm
