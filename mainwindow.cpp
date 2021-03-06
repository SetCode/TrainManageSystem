#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "traindata/database.h"
#include "traininfoselect/traininfoselect.h"
#include "userinfoinsert/userinfoinsert.h"
#include "userinfoselect/userinfoselect.h"
#include "messagebox/messagedialog.h"
#include "globaldef.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("列车票务管理系统"));

    this->initControl();
    this->initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initControl()
{
    /*************************          车次           ***********************/
    lineEditTrainNumber = new QLineEdit(this);
    lineEditTrainNumber->setMinimumHeight(25);
    QWidget *widgetTrainNumber = new QWidget(this);
    QHBoxLayout *hboxLayoutTrainNumber = new QHBoxLayout(this);
    hboxLayoutTrainNumber->addWidget(lineEditTrainNumber);
    hboxLayoutTrainNumber->setAlignment(widgetTrainNumber,Qt::AlignCenter);
    widgetTrainNumber->setLayout(hboxLayoutTrainNumber);


    /*************************           分类           ***********************/
    comboBoxTrainType = new QComboBox(this);
    QWidget * widgetTrainType=new QWidget(this);
    QHBoxLayout * hboxLayoutTrainType=new QHBoxLayout(this);

    comboBoxTrainType->addItem("普快");
    comboBoxTrainType->addItem("特快");
    comboBoxTrainType->addItem("高铁");
    comboBoxTrainType->setEditable(true);

    hboxLayoutTrainType->addWidget(comboBoxTrainType);
    hboxLayoutTrainType->setAlignment(widgetTrainType,Qt::AlignCenter);
    widgetTrainType->setLayout(hboxLayoutTrainType);


    /*************************             起始站          ***********************/
    lineEditStartStation = new QLineEdit(this);
    lineEditStartStation->setMinimumHeight(25);
    QWidget *widgetStartStation = new QWidget(this);
    QHBoxLayout *hboxLayoutStartStation = new QHBoxLayout(this);
    hboxLayoutStartStation->addWidget(lineEditStartStation);
    hboxLayoutStartStation->setAlignment(widgetStartStation,Qt::AlignCenter);
    widgetStartStation->setLayout(hboxLayoutStartStation);


    /*************************              终点站         ***********************/
    lineEditEndStation = new QLineEdit(this);
    lineEditEndStation->setMinimumHeight(25);
    QWidget *widgetEndStation = new QWidget(this);
    QHBoxLayout *hboxLayoutEndStation = new QHBoxLayout(this);
    hboxLayoutEndStation->addWidget(lineEditEndStation);
    hboxLayoutEndStation->setAlignment(widgetEndStation,Qt::AlignCenter);
    widgetEndStation->setLayout(hboxLayoutEndStation);

    /*************************               发车时间     ***********************/
    dateEditStartTime = new QDateEdit(this);
    dateEditStartTime->setMinimumHeight(25);
    QWidget *widgetStartTime = new QWidget(this);
    QHBoxLayout *hboxLayoutStartTime = new QHBoxLayout(this);
    hboxLayoutStartTime->addWidget(dateEditStartTime);
    hboxLayoutStartTime->setAlignment(widgetStartTime,Qt::AlignCenter);
    widgetStartTime->setLayout(hboxLayoutStartTime);
    dateEditStartTime->setDisplayFormat("yyyy-MM-dd");
    dateEditStartTime->setDateTime(QDateTime::currentDateTime());


    /*************************到站时间***********************/
    dateEditEndTime = new QDateEdit(this);
    dateEditEndTime->setMinimumHeight(25);
    QWidget *widgetEndTime = new QWidget(this);
    QHBoxLayout *hboxLayoutEndTime = new QHBoxLayout(this);
    hboxLayoutEndTime->addWidget(dateEditEndTime);
    hboxLayoutEndTime->setAlignment(widgetEndTime,Qt::AlignCenter);
    widgetEndTime->setLayout(hboxLayoutEndTime);
    dateEditEndTime->setDisplayFormat("yyyy-MM-dd");
    dateEditEndTime->setDateTime(QDateTime::currentDateTime());

    /*************************可用座位硬座***********************/
    lineEditHardSeat = new QLineEdit(this);
    lineEditHardSeat->setMinimumHeight(25);
    QWidget *widgetHardSeat = new QWidget(this);
    QHBoxLayout *hboxLayoutHardSeat = new QHBoxLayout(this);
    hboxLayoutHardSeat->addWidget(lineEditHardSeat);
    hboxLayoutHardSeat->setAlignment(widgetHardSeat,Qt::AlignCenter);
    widgetHardSeat->setLayout(hboxLayoutHardSeat);


    /*************************可用座位卧铺***********************/
    lineEditSleepSeat = new QLineEdit(this);
    lineEditSleepSeat->setMinimumHeight(25);
    QWidget *widgetSleepSeat = new QWidget(this);
    QHBoxLayout *hboxLayoutSleepSeat = new QHBoxLayout(this);
    hboxLayoutSleepSeat->addWidget(lineEditSleepSeat);
    hboxLayoutSleepSeat->setAlignment(widgetSleepSeat,Qt::AlignCenter);
    widgetSleepSeat->setLayout(hboxLayoutSleepSeat);

    /*************************票价***********************/
    lineEditSeatMoney = new QLineEdit(this);
    lineEditSeatMoney->setMinimumHeight(25);
    QWidget *widgetSeatMoney = new QWidget(this);
    QHBoxLayout *hboxLayoutSeatMoney = new QHBoxLayout(this);
    hboxLayoutSeatMoney->addWidget(lineEditSeatMoney);
    hboxLayoutSeatMoney->setAlignment(widgetSeatMoney,Qt::AlignCenter);
    widgetSeatMoney->setLayout(hboxLayoutSeatMoney);


    /*************************录入数据信息***********************/
    insertButton=new QPushButton(this);
    QWidget *widgetButton = new QWidget(this);
    QHBoxLayout *hboxLayoutButton = new QHBoxLayout(this);
    hboxLayoutButton->addWidget(insertButton);
    hboxLayoutButton->setAlignment(widgetButton,Qt::AlignCenter);
    widgetButton->setLayout(hboxLayoutButton);
    insertButton->setText("信息录入");

    QFont font("宋体", 14, QFont::Bold, true);
    insertButton->setFont(font);
    insertButton->setIcon(QIcon(":/image/image/indexedDB.png"));
    insertButton->setIconSize(QSize(25, 25));
    insertButton->setMinimumHeight(50);

    //添加控件
    ui->tableWidgetInsert->setCellWidget(0, 1, widgetTrainNumber);
    ui->tableWidgetInsert->setCellWidget(0, 3, widgetTrainType);
    ui->tableWidgetInsert->setCellWidget(0, 5, widgetStartStation);
    ui->tableWidgetInsert->setCellWidget(1, 1, widgetEndStation);
    ui->tableWidgetInsert->setCellWidget(1, 3, widgetStartTime);
    ui->tableWidgetInsert->setCellWidget(1, 5, widgetEndTime);
    ui->tableWidgetInsert->setCellWidget(2, 1, widgetHardSeat);
    ui->tableWidgetInsert->setCellWidget(2, 3, widgetSleepSeat);
    ui->tableWidgetInsert->setCellWidget(2, 5, widgetSeatMoney);
    ui->tableWidgetInsert->setCellWidget(3, 5, widgetButton);

    //把表头上面去掉
    ui->tableWidgetInsert->horizontalHeader()->setVisible(false);
    ui->tableWidgetInsert->verticalHeader()->setVisible(false);

    //设置列表控件等宽显示
    QHeaderView *headerView=ui->tableWidgetInsert->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    //设置列表控件等高显示
    QHeaderView *leftHeaderView=ui->tableWidgetInsert->verticalHeader();
    leftHeaderView->setSectionResizeMode(QHeaderView::Stretch);

    //设置不能选择
    ui->tableWidgetInsert->setSelectionMode(QAbstractItemView::NoSelection);

    //设置无边框
    ui->tableWidgetInsert->setFrameShape(QFrame::NoFrame);

    //设置为不可编辑
    ui->tableWidgetInsert->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QTableWidgetItem *textTrainNumber = new QTableWidgetItem("车次：");
    textTrainNumber->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(0, 0, textTrainNumber);

    QTableWidgetItem *textTrainType = new QTableWidgetItem("分类：");
    textTrainType->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(0, 2, textTrainType);


    QTableWidgetItem *textStartStation = new QTableWidgetItem("起始站：");
    textStartStation->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(0, 4, textStartStation);


    QTableWidgetItem *textEndStation = new QTableWidgetItem("终点站：");
    textEndStation->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(1, 0, textEndStation);


    QTableWidgetItem *textStartTime = new QTableWidgetItem("发车时间：");
    textStartTime->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(1, 2, textStartTime);


    QTableWidgetItem *textEndTime = new QTableWidgetItem("到站时间：");
    textEndTime->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(1, 4, textEndTime);


    QTableWidgetItem *textHardSeat = new QTableWidgetItem("硬座：");
    textHardSeat->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(2, 0, textHardSeat);


    QTableWidgetItem *textSleepSeat = new QTableWidgetItem("卧铺：");
    textSleepSeat->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(2, 2, textSleepSeat);

    QTableWidgetItem *textSeatMoney = new QTableWidgetItem("票价：");
    textSeatMoney->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetInsert->setItem(2, 4, textSeatMoney);

    connect(insertButton,SIGNAL(clicked()), this, SLOT(insertData()));
}

void MainWindow::initData()
{
    trainInfoSelect = new TrainInfoSelect();
    userInfoInsert = new UserInfoInsert();
    userInfoSelect = new UserInfoSelect();
}

void MainWindow::insertData()
{
    TrainInfo trainInfo;

    trainInfo.trainNumber            = lineEditTrainNumber->text();       //车次
    trainInfo.trainType              = comboBoxTrainType->currentText();  //分类
    trainInfo.startStation           = lineEditStartStation->text();      //起始站
    trainInfo.endStation             = lineEditEndStation->text();        //终点站
    trainInfo.startTime              = dateEditStartTime->text();         //发车时间
    trainInfo.endTime                = dateEditEndTime->text();           //到站时间
    trainInfo.hardSeadNumber         = lineEditHardSeat->text();          //硬座
    trainInfo.sleeperSeatNumber      = lineEditSleepSeat->text();         //卧铺
    trainInfo.seatMoney              = lineEditSeatMoney->text();         //票价
    trainInfo.totalHardSeadNumber    = lineEditHardSeat->text();          //硬座
    trainInfo.totalSleeperSeatNumber = lineEditSleepSeat->text();         //卧铺

    if(DATABASE->insertTrainData(trainInfo))
    {
        MESSAGEBOX->setInfo("系统提示", "录入成功", QPixmap(GLOBALDEF::SUCCESSIMAGE), true, this);
    }
    else
    {
        MESSAGEBOX->setInfo("系统提示", "录入失败", QPixmap(GLOBALDEF::SUCCESSIMAGE), true, this);
    }


}

void MainWindow::on_actionTrainInfoSelect_triggered()
{
    SETCENTRALWIDGET(trainInfoSelect);

    trainInfoSelect->show();
}

void MainWindow::on_actionTrainInfoInsert_triggered()
{
    SETCENTRALWIDGET(ui->centralWidget);

    ui->centralWidget->show();
}

void MainWindow::on_actionUserInfoInsert_triggered()
{
    SETCENTRALWIDGET(userInfoInsert);

    userInfoInsert->show();
}

void MainWindow::on_actionUserInfoSelect_triggered()
{
    SETCENTRALWIDGET(userInfoSelect);

    userInfoSelect->show();
}
