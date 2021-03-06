/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** Copyright (c) 2012-2013 LG Electronics, Inc.
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QPlatformIntegrationPlugin>
#include <QDebug>
#if defined(TARGET_DEVICE)
#include "qeglfsintegration.h"
#else
#include "emulatorfbintegration.h"
#endif


QT_BEGIN_NAMESPACE

class QEglIntegrationPlugin : public QPlatformIntegrationPlugin
{
public:
    QStringList keys() const;
    QPlatformIntegration *create(const QString&, const QStringList&);
};

QStringList QEglIntegrationPlugin::keys() const
{
    QStringList list;
    list << "Palm";
#if defined(TARGET_DEVICE)
    list << "Palm-soft";
#endif
    return list;
}

QPlatformIntegration* QEglIntegrationPlugin::create(const QString& system, const QStringList& paramList)
{
    Q_UNUSED(paramList);
    if (system.toLower() == "palm") {
#if defined(TARGET_DEVICE)
        return new QEglFSIntegration(false);
    } else if(system.toLower() == "palm-soft") {
        return new QEglFSIntegration(true);
#else
    return new EmulatorFbIntegration;
#endif
    }

    return 0;
}

Q_EXPORT_PLUGIN2(eglintegration, QEglIntegrationPlugin)

QT_END_NAMESPACE
