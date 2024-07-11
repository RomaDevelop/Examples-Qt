#ifndef PLUGIN2_H
#define PLUGIN2_H

#include "Plugin2_global.h"
#include "plugininteface.h"
#include <QtPlugin>
#include <QObject>


class /*PLUGIN2_EXPORT*/ Plugin2: public PluginInteface
{
    Q_OBJECT
    Q_INTERFACES(PluginInteface)
    Q_PLUGIN_METADATA(IID "plugin")
public:
    Plugin2();
    ~Plugin2();
    QString GetString();
private:
    QString Str;
};

#endif // PLUGIN2_H
