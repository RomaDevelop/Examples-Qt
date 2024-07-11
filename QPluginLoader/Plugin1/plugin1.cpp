#include "plugin1.h"

Plugin1::Plugin1()
{
    Str=QString("Plugin 1");
}
Plugin1::~Plugin1()
{

}

QString Plugin1::GetString()
{
    return Str;
}
//Q_EXPORT_PLUGIN2(PluginInteface, Plugin1)
