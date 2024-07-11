#include "dropwidget.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

DropWidget::DropWidget( QWidget* parent ) : ImageTextWidget( parent ) {
    setAcceptDrops( true );
}

void DropWidget::dragEnterEvent( QDragEnterEvent* event ) {
    qDebug() << event->mimeData()->formats();
    if( event->mimeData()->hasImage() && event->mimeData()->hasText() ) {
        event->acceptProposedAction();
    }
}

void DropWidget::dropEvent( QDropEvent* event ) {
    setPixmap( QPixmap::fromImage( event->mimeData()->imageData().value< QImage >() ) );
    setText( event->mimeData()->text() );
    event->acceptProposedAction();
}
