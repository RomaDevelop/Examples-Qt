#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <imagetextwidget.h>

class DragWidget : public ImageTextWidget {
    Q_OBJECT
public:
    explicit DragWidget( QWidget* parent = 0 );

protected:
    void mousePressEvent( QMouseEvent* event );
    void mouseMoveEvent( QMouseEvent* event );

private slots:
    void onLoadImage();

private:
    QPoint m_dragStart;
};

#endif // DRAGWIDGET_H
