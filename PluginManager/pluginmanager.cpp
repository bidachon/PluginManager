#include "pluginmanager.h"
#include <pluginconfigurationparser.h>
#include <QDebug>
#include <QPluginLoader>
#include <Interfaces/ipluginlib.h>
//#include <interfaceid.h>

namespace plugin {

namespace interfaces {
class InterfaceId;
class IPluginInterface;
}

PluginManager::PluginManager()
{
}

bool PluginManager::load(const QString & filename)
{
    PluginConfigurationParser parser;
    bool status = parser.parse(filename);
    if (!status)
    {
        qDebug() << "Error parsing the json file:" << filename;
        m_errorMsg = parser.errorMessage();
        return false;
    }
    QStringList pluginList = parser.pluginList();

    bool isValid;
    foreach(QString p, pluginList)
    {
        QPluginLoader pl;
        pl.setFileName(p);
        pl.load();
        isValid = true;
        qDebug() << "Processing plugin file " + p;
        if (!pl.isLoaded())
        {
            qDebug() << "Error loading plugin";
            m_errorMsg = p + " " + pl.errorString();
            isValid = false;
            return isValid;
        }

        interfaces::IPluginLib *ngplugin = qobject_cast<interfaces::IPluginLib *>( pl.instance());
        if (!ngplugin)
        {
            m_errorMsg = "This plugin does not contain a valid IPluginLib implementation";
            isValid = false;
            return isValid;
        }
        m_pluginLibs.append(ngplugin);
        qDebug() << "Extracting Extensions";
        const std::list<Extension *> exts = ngplugin->extensions();
        for (std::list<Extension *>::const_iterator it = exts.begin(); it != exts.end(); it++ )
        {
            QString name = QString::fromStdString((*it)->interface()->id().name());
            qDebug() << "\t" << name;
            m_extensionMap[name].push_back((*it)->interface());
        }
    }

    foreach(plugin::interfaces::IPluginLib*pl, m_pluginLibs)
    {

        qDebug() << "Extracting Dependencies";
        const std::list<Dependency *> deps = pl->dependencies();
        for (std::list<Dependency *>::const_iterator it = deps.begin(); it != deps.end(); it++ )
        {
            QString name = QString::fromStdString((*it)->interfaceId().name());
            qDebug() << "\t" << name;
            if (m_extensionMap[name].size() < (*it)->minExt())
            {
                m_errorMsg = "This plugin configuration could not provide enough extensions of type /" + name+"/ ";
                isValid = false;
                return isValid;
            }
            if (m_extensionMap[name].size() > (*it)->maxExt())
            {
                m_errorMsg = "This plugin configuration provided too many extensions of type /" + name+"/ ";
                isValid = false;
                return isValid;
            }
            foreach(QSharedPointer<plugin::interfaces::IPluginInterface> pi, m_extensionMap[name])
                pl->connectExtension(pi);
        }

    }

    return isValid;
}

QList<QSharedPointer<interfaces::IPluginInterface> > PluginManager::getExtensions(const InterfaceId& id) const
{
    QString name = QString::fromStdString(id.name());
    return m_extensionMap[name];
}

}
