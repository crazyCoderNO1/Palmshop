#ifndef RESTAURANT_CHECKSTAND_TITLE_BAR_H
#define RESTAURANT_CHECKSTAND_TITLE_BAR_H

#include <QToolBar>
/**
 * @brief 餐饮类收银台标题栏
 */
class RestaurantCheckstandTitleBar : public QToolBar {
    Q_OBJECT
  public:
    explicit RestaurantCheckstandTitleBar(QWidget *parent = Q_NULLPTR);
    ~RestaurantCheckstandTitleBar();

};

#endif // RESTAURANT_CHECKSTAND_TITLE_BAR_H
