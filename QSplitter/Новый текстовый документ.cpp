#include <QSplitter>

auto loMain = new QVBoxLayout(this);
auto splCenter = new QSplitter(Qt::Horizontal);
loMain->addWidget(splCenter);

tree = new QTreeWidget;
table = new QTableWidget;
splCenter->addWidget(tree);
splCenter->addWidget(table);