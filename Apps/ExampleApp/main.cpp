#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QtPlugin>
#include <QPluginLoader>
#include "Interfaces/ipluginlib.h"
#include "Interfaces/inumbergenerator.h"
#include "Interfaces/igeneratormanager.h"
#include <QDebug>
#include <QStringList>
#include <pluginmanager.h>
#include <QSharedPointer>
#include <QSharedData>
#include <QSharedDataPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    plugin::PluginManager pm;
    bool succeed = pm.load("pluginlist.json");
    if (!succeed)
    {
        qDebug() << pm.errorMessage();
        return 1;
    }
    QList<QSharedPointer<plugin::interfaces::IPluginInterface> > genMngList = pm.getExtensions(plugin::InterfaceId("IGeneratorManager"));

    //QSharedPointer<plugin::interfaces::IGeneratorManager> genMng = qobject_cast<plugin::interfaces::IGeneratorManager>(genMngList.at(0));
    QSharedPointer<plugin::interfaces::IPluginInterface> ptr = genMngList.at(0);
    QSharedPointer<plugin::interfaces::IGeneratorManager> genMgr = qSharedPointerCast<plugin::interfaces::IGeneratorManager>(ptr);
    genMgr->widget()->show();
    //QPushButton btn("Helloworld");
    //btn.show();
    //w.show();

    return a.exec();
}
