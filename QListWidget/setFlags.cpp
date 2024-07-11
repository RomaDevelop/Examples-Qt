QListWidgetItem *ListChannelsItem = ListChannels->item(ListChannels->count()-1);
ListChannelsItem->setFlags(ListChannelsItem->flags() ^ Qt::ItemIsEnabled);

// https://cpp.hotexamples.com/ru/examples/-/QTableWidgetItem/setFlags/cpp-qtablewidgetitem-setflags-method-examples.html