#ifndef PLUGININTEFACE_H
#define PLUGININTEFACE_H

#include "PluginInteface_global.h"
#include <QObject>
#include <QtPlugin>

class /*PLUGININTEFACE_EXPORT*/ PluginInteface:public QObject
{
public:
    virtual ~PluginInteface(){};
    virtual QString GetString()=0;

};
Q_DECLARE_INTERFACE(PluginInteface,"plugin")

#endif // PLUGININTEFACE_H
