#include "plugin2.h"

Plugin2::Plugin2()
{
	Str=QString("Plugin 2222");
}
Plugin2::~Plugin2()
{

}
QString Plugin2::GetString()
{
    return Str;
}
