#include "restaurant_checkstand_title_bar.h"

#include <QLabel>

namespace restaurant {
namespace checkstand_titlebar_private {
QLabel *icon_label;//窗口图标
QLabel *title_label;//窗口标题
QWidget* toolBar_seat;//标题中部占位
QLabel *cashier;//收银员
}//namespace checkstand_titlebar_private
}//namespace restaurant

namespace private_ = restaurant::checkstand_titlebar_private;

RestaurantCheckstandTitleBar::RestaurantCheckstandTitleBar(QWidget *parent) :
    QToolBar(parent) {
//    parent->addToolBar(this);//把标题栏添加到主窗口
    setMovable(false);//禁止拖动
    //左侧显示
    //图标
//    private_::icon_label = new QLabel(this);
//    private_::icon_label->setFixedSize(m_private->w->iconSize());
//    private_::icon_label->setScaledContents(true);
//    private_::icon_label->setPixmap(m_private->w->windowIcon().
//                                    pixmap(m_private->icon_label->size()));
//    addWidget(m_private->icon_label);
    //标题
    private_::title_label = new QLabel(this);
    private_::title_label->setText("Palmshop-餐饮收银系统");
    addWidget(private_::title_label);

    //中部占位
    private_::toolBar_seat = new QWidget(this);
    private_::toolBar_seat->setSizePolicy(QSizePolicy::Expanding,
                                          QSizePolicy::Expanding);//长宽自动扩展
    addWidget(private_::toolBar_seat);

    //右侧显示
    private_::cashier = new QLabel(this);
    private_::cashier->setText("操作员：");
}

RestaurantCheckstandTitleBar::~RestaurantCheckstandTitleBar() {
    //qt相关控件自动随此窗口销毁释放空间
}
