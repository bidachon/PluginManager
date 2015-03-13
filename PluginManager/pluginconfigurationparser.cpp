#include "pluginconfigurationparser.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace plugin {


PluginConfigurationParser::PluginConfigurationParser(QObject *parent) : QObject(parent)
{
    m_isValid = false;
}

PluginConfigurationParser::~PluginConfigurationParser()
{

}

QStringList PluginConfigurationParser::pluginList() const
{
    return m_pluginList;
}

QString PluginConfigurationParser::errorMessage() const
{
    return m_errorMsg;
}


bool PluginConfigurationParser::parse(const QString& filename)
{
      QString val;
      QFile file;
      file.setFileName(filename);
      if (!file.exists())
      {
          m_errorMsg = "File does not exist: " + filename;
          m_isValid = false;
          return m_isValid;
      }
      file.open(QIODevice::ReadOnly | QIODevice::Text);

      if (!file.exists())
      {
          m_errorMsg = "File cannot be opened: " + filename;
          m_isValid = false;
          return m_isValid;
      }

      val = file.readAll();
      file.close();
      QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
      QJsonObject root = d.object();
      QJsonObject conf = root.value("configuration").toObject();
      if (conf.empty())
      {
        m_errorMsg = "Missing json object attribute /configuration/: ";
        m_isValid = false;
        return m_isValid;
      }
      QString author = conf["author"].toString();
      if (author.isEmpty())
      {
        m_errorMsg = "Missing or empty json string attribute /author/: ";
        m_isValid = false;
        return m_isValid;
      }

      QString descr = conf["description"].toString();
      if (descr.isEmpty())
      {
        m_errorMsg = "Missing or empty json string attribute /description/: ";
        m_isValid = false;
        return m_isValid;
      }

      QJsonArray plugins = root.value("plugins").toArray();
      if (plugins.isEmpty())
      {
        m_errorMsg = "Missing or empty json array attribute /plugins/: ";
        m_isValid = false;
        return m_isValid;
      }

      for (int i = 0; i < plugins.count(); i++)
      {
          QString pluginName = plugins.at(i).toString();
          m_pluginList.append(pluginName);
      }
      m_isValid = true;
      return m_isValid;
}

}

