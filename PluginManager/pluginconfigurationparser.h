#ifndef PLUGINCONFIGURATIONPARSER_H
#define PLUGINCONFIGURATIONPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>

namespace plugin {

class PluginConfigurationParser : public QObject
{
    Q_OBJECT
    friend class PluginManager;
protected:
    explicit PluginConfigurationParser(QObject *parent = 0);
    ~PluginConfigurationParser();

    bool parse(const QString& filename);
    QString errorMessage() const;
    bool isValid() const;
    QStringList pluginList() const;
signals:

public slots:

private:
    QStringList m_pluginList;
    QString m_errorMsg;
    bool m_isValid;
};

}

#endif // PLUGINCONFIGURATIONPARSER_H
