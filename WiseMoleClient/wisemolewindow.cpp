#include "wisemolewindow.h"
#include "ui_wisemolewindow.h"

WiseMoleWindow::WiseMoleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WiseMoleWindow)
{
    ui->setupUi(this);
}

WiseMoleWindow::~WiseMoleWindow()
{
    delete ui;
}

