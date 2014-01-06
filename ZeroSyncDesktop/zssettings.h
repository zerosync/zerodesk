/* =========================================================================
   ZSSettings - User settings class for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
   Copyright other contributors as noted in the AUTHORS file.

   This file is part of ZeroSync, see http://zerosync.org.

   This is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.
   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
   BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program. If not, see http://www.gnu.org/licenses/.
   =========================================================================
*/


#ifndef ZSSETTINGS_H
#define ZSSETTINGS_H

#include <QObject>
#include <QSettings>

class ZSSettings : public QObject
{
    Q_OBJECT

public:
    explicit ZSSettings(QObject *parent = 0);
    bool existSettings();
    void setZeroSyncDirectory(QString);
    void setSyncInterval(int);
    QString getZeroSyncDirectory();
    int getSyncInterval();

private:
    QSettings *settings;

signals:

public slots:

};

#endif // ZSSETTINGS_H
