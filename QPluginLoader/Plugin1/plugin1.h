#ifndef PLUGIN1_H
#define PLUGIN1_H


#include "Plugin1_global.h"
#include <QObject>
#include "plugininteface.h"

class PLUGIN1_EXPORT Plugin1: public PluginInteface
{
    Q_OBJECT
    Q_INTERFACES(PluginInteface)
    Q_PLUGIN_METADATA(IID "plugin")
public:
    Plugin1();
    ~Plugin1();
    QString GetString();
private:
    QString Str;
};


#endif // PLUGIN1_H
