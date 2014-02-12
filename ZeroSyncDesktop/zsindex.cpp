/* =========================================================================
   ZSIndex - Filesystem indexing class for the ZeroSync desktop client


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


#include "zsindex.h"

ZSIndex::ZSIndex(QObject *parent) :
    QObject(parent)
{
    latestState = ZSDatabase::getInstance()->getLatestState();
}


void ZSIndex::slotUpdateIndex()
{
    latestState = ZSDatabase::getInstance()->getLatestState();
    QSqlQuery *query = ZSDatabase::getInstance()->fetchAllChangedEntriesInFilesTable();
    if(query == NULL)
    {
        qDebug("Error - ZSIndex::slotUpdateIndex() failed: QSqlQuery object \"query\" is NULL");
        return;
    }
    query->last();
    query->first();
    query->previous();
    while(query->next())
    {
        QString newPath = query->value(4).toString();
        int updated = query->value(6).toInt();
        int renamed = query->value(7).toInt();
        int deleted = query->value(8).toInt();

        if(updated == 1)
        {
            ZSDatabase::getInstance()->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "UPD", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(deleted == 1)
        {
            ZSDatabase::getInstance()->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "DEL", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(renamed == 1)
        {
            ZSDatabase::getInstance()->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "REN", query->value(1).toLongLong(), query->value(3).toInt(), newPath, query->value(2).toString());
        }

    }
    ZSDatabase::getInstance()->resetFileMetaData();
    qDebug() << "Information - ZSIndex::slotUpdateIndex() succeeded: Fileindex updated";
}

