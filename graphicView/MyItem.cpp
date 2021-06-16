#include "MyItem.h"
#include <QLineF> 
#include <QApplication>

MyItem::MyItem(QGraphicsItem *parent)
	:QGraphicsItem(parent)
{
	setToolTip("Click and drag me!");
	setCursor(Qt::OpenHandCursor);
	m_Color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

MyItem::~MyItem()
{

}

QRectF MyItem::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
		20 + penWidth, 20 + penWidth);
}

void MyItem::paint(QPainter* painter,
	const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	painter->setBrush(m_Color);
	painter->drawEllipse(0, 0, 20, 20);
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
	{
		event->ignore();
		return;
	}
	setCursor(Qt::ClosedHandCursor);
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (QLineF(event->screenPos(), event->buttonDownScenePos(Qt::LeftButton)).length()
		<QApplication::startDragDistance())
	{
		//如果鼠标按下的点到现在的点的距离小于程序默认的拖动距离，表明没有拖动，则返回
		return;
	}

	QDrag* pDrag = new QDrag(event->widget());
	QMimeData* pMime = new QMimeData;
	pDrag->setMimeData(pMime);
	pMime->setColorData(m_Color);

	QPixmap pix(21, 21);
	pix.fill(Qt::red);
	QPainter painter(&pix);
	paint(&painter, 0, 0);
	pDrag->setPixmap(pix);

	pDrag->setHotSpot(QPoint(10, 15));
	pDrag->exec();
	setCursor(Qt::OpenHandCursor);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	Q_UNUSED(event);
	setCursor(Qt::OpenHandCursor);
}