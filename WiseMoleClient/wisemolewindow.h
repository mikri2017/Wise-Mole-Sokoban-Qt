#ifndef WISEMOLEWINDOW_H
#define WISEMOLEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WiseMoleWindow; }
QT_END_NAMESPACE

class WiseMoleWindow : public QMainWindow
{
    Q_OBJECT

public:
    WiseMoleWindow(QWidget *parent = nullptr);
    ~WiseMoleWindow();

private:
    Ui::WiseMoleWindow *ui;
};
#endif // WISEMOLEWINDOW_H
