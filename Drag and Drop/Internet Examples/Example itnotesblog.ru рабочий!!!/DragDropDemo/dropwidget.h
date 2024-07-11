#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <imagetextwidget.h>

class DropWidget : public ImageTextWidget {
    Q_OBJECT
public:
    explicit DropWidget( QWidget* parent = 0 );

protected:
    void dragEnterEvent( QDragEnterEvent* event );
    void dropEvent( QDropEvent* event );
};

#endif // DROPWIDGET_H
