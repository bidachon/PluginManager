#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginmanager_global.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include "interfaces/iplugininterface.h"
#include "Interfaces/ipluginlib.h"

namespace plugin {
class PLUGINMANAGERSHARED_EXPORT PluginManager
{
//friend class PluginConfigurationParser;
public:
    PluginManager();
    bool load(const QString & filename);
    QString errorMessage() const {return m_errorMsg;}

    virtual QList< QSharedPointer<interfaces::IPluginInterface> > getExtensions(const InterfaceId& id) const;

private:
    QString m_errorMsg;
    QList<plugin::interfaces::IPluginLib *> m_pluginLibs;
    QMap< QString, QList< QSharedPointer<interfaces::IPluginInterface> > > m_extensionMap;
};
}
#endif // PLUGINMANAGER_H
