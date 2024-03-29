/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2008 Volker Lanz (vl@fidra.de)
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

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QString>
#include "ElevateMode.h"

class QSettings;
class SettingsDialog;

enum ProcessMode {
    Service,
    Desktop
};

class AppConfig: public QObject
{
    Q_OBJECT

    friend class SettingsDialog;
    friend class MainWindow;

    public:
        AppConfig(QSettings* settings);
        ~AppConfig();

    public:
        const QString& screenName() const;
        int port() const;
        const QString& networkInterface() const;
        int logLevel() const;
        bool logToFile() const;
        const QString& logFilename() const;
        const QString logFilenameCmd() const;
        QString logLevelText() const;
        ProcessMode processMode() const;
        const QString& language() const;
        bool startedBefore() const;

        QString server_name() const;
        QString client_name() const;
        QString program_dir() const;
        QString log_dir() const;

        void persistLogDir();
        ElevateMode elevateMode();

        void setCryptoEnabled(bool e);
        bool getCryptoEnabled() const;

        void setRequireClientCertificate(bool e);
        bool getRequireClientCertificate() const;

        void setAutoHide(bool b);
        bool getAutoHide();

        void setAutoStart(bool b);
        bool getAutoStart();

        void setMinimizeToTray(bool b);
        bool getMinimizeToTray();

        void saveSettings();

protected:
        QSettings& settings();
        void setScreenName(const QString& s);
        void setPort(int i);
        void setNetworkInterface(const QString& s);
        void setLogLevel(int i);
        void setLogToFile(bool b);
        void setLogFilename(const QString& s);
        void setLanguage(const QString language);
        void setStartedBefore(bool b);
        void setElevateMode(ElevateMode em);
        void loadSettings();

    private:
        QSettings* m_pSettings;
        QString m_ScreenName;
        int m_Port;
        QString m_Interface;
        int m_LogLevel;
        bool m_LogToFile;
        QString m_LogFilename;
        ProcessMode m_ProcessMode;
        QString m_Language;
        bool m_StartedBefore;
        ElevateMode m_ElevateMode;
        bool m_CryptoEnabled;
        bool m_RequireClientCertificate = false;
        bool m_AutoHide;
        bool m_AutoStart;
        bool m_MinimizeToTray;

        static const char server_name_[];
        static const char client_name_[];
        static const char log_dir_[];
};

#endif
