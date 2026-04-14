#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QDateTime>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
};

