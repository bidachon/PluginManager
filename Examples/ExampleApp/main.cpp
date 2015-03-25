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
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    plugin::PluginManager pm;

    if (argc != 2)
    {
        std::cerr << "Invalid parameters" << std::endl;
        std::cerr << "Please provide the path of the plugin .json file" << std::endl;
        return 1;
    }

    bool succeed = pm.load(argv[1]);

    if (!succeed)
    {
        qDebug() << pm.errorMessage();
        return 1;
    }
    QList<QSharedPointer<plugin::interfaces::IPluginInterface> > genMngList = pm.getExtensions(plugin::InterfaceId("IGeneratorManager"));

    if (genMngList.isEmpty())
        std::cerr << "Your plugin list does not provide an implementation of IGeneratorManager" << std::endl;

    QSharedPointer<plugin::interfaces::IPluginInterface> ptr = genMngList.at(0);
    QSharedPointer<plugin::interfaces::IGeneratorManager> genMgr = qSharedPointerCast<plugin::interfaces::IGeneratorManager>(ptr);
    genMgr->widget()->show();


    return a.exec();
}
