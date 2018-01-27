#include "startexe.h"
#include "ui_startexe.h"
#include <QFileDialog>
#include <QtDebug>
#include <QDesktopWidget>
#include <QMenu>
#include <QMenuBar>
startExe::startExe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startExe)
{
    ui->setupUi(this);
    setWindowTitle("任务管理器");
    process=new QProcess;
    ui->tableWidget->setContextMenuPolicy (Qt::CustomContextMenu);
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu(QPoint)));
}

startExe::~startExe()
{
    delete ui;
}

void startExe::on_pushButton_clicked()
{



   initExe();
   ui->tableWidget->show();

}
void startExe::initExe()
{

//     QTableWidgetItem item;
     int row= ui->tableWidget->rowCount();
     QStringList filenames=QFileDialog::getOpenFileNames(this,tr("文件选择"),tr("F:/work/WORK/123/EXE"),

                                                        tr("exe File(* exe);"));




//     qDebug()<<filenames.size();
     int width = qApp->desktop()->availableGeometry().width() - 120;//设置软件在桌面显示的位置居中
     ui->tableWidget->setRowCount(filenames.size()+row); //设置行数为10
     ui->tableWidget->setColumnCount(2); //设置列数为5
     ui->tableWidget->setColumnWidth(0, width * 0.06);//第一列宽度
     ui->tableWidget->setColumnWidth(1, width * 0.10);
     ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);//设置行高
     ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择行为时每次选择一行
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
     ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//不可多选
     ui->tableWidget->setAlternatingRowColors(true);//隔行变色
     ui->tableWidget->verticalHeader()->setVisible(false);//设置垂直头不可见
     ui->tableWidget->horizontalHeader()->setStretchLastSection(true);/*设置表格是否充满，即行末不留空*/

     ui->tableWidget->resize(350, 200); //设置表格
     QStringList header;
     header<<"进程"<<"状态";
     ui->tableWidget->setHorizontalHeaderLabels(header);

         for(int i=0;i<filenames.size();i++)
         {
             QString fileName = filenames.at(i);
             filePath=fileName;
             filePathList.append(fileName);
             QString curFile = fileName.right(fileName.size() - fileName.lastIndexOf('/') -1 );//待发送文件名。
//             QString state;
//             qDebug()<<curFile<<"xxx";
//              for(int r=0;dataList.size();r++)
//              {
//                  if(curFile==dataList.at(r))
//                  {
//                      qDebug()<<dataList.at(r);
//                      break;
//                  }

//              }
             ui->tableWidget->setItem(row+i,0,new QTableWidgetItem(QString(tr("%1").arg(curFile))));
             ui->tableWidget->setItem(row+i,1,new QTableWidgetItem(QString(tr("%1").arg("是否启动进程"))));
         }



//  qDebug()<<ui->tableWidget->rowCount();
//  QString data= ui->tableWidget->item(1,0)->text();

//  qDebug()<<dataList.at(1);

}




int startExe::show_menu(const QPoint pos)
{
        //设置菜单选项
        QMenu *menu = new QMenu(ui->tableWidget);
        QAction *all_start_action=new QAction("全选启用",ui->tableWidget);
        QAction *pnew = new QAction("启用",ui->tableWidget);
        QAction *pnew1 = new QAction("禁用",ui->tableWidget);
        QAction *newAction = new QAction(tr("退出"),this);


        menu->addAction(all_start_action);
        menu->addAction(pnew);
        menu->addAction(pnew1);
        menu->addAction(newAction);
        all_start_action->setShortcut(QKeySequence(QLatin1String("R")));
        pnew->setShortcut(QKeySequence(QLatin1String("Y")));
        pnew1->setShortcut(QKeySequence(QLatin1String("G")));
        newAction->setShortcut(QKeySequence(QLatin1String("N")));

        menu->move (cursor().pos ());
        connect (pnew,SIGNAL(triggered()),this,SLOT(start_process()));
        connect (pnew1,SIGNAL(triggered()),this,SLOT(close_process()));
        connect(newAction,SIGNAL(triggered()),this,SLOT(close_c()));
        connect(all_start_action,SIGNAL(triggered()),this,SLOT(checkRowSlot()));
        //获得鼠标点击的x，y坐标点
        int x = pos.x ();
        int y = pos.y ();
        QModelIndex index = ui->tableWidget->indexAt (QPoint(x,y));
        int row = index.row ();//获得QTableWidget列表点击的行数
//        qDebug()<<row<<"xxxxxxx";
        if(row<0)
        {
            return 0;
        }
        else {
            menu->show ();
        }
        return getRow(row);
}
void startExe::close_c()
{

   this->close();
}

void startExe::start_process()
{

    QString path="F:/work/WORK/123/EXE";
    qDebug()<<"path"<<filePath;
    int row=row_;
    QString filename=ui->tableWidget->item(row,0)->text();
    qDebug()<<row<<"row"<<filename;
    QString exe=path+"/"+filename;
    qDebug()<<exe<<"exe";
    if(exe==filePath)
    {
        process->start(exe);

    }
    else
    {

        process->start(filePath);
    }
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString(tr("%1").arg("禁用"))));
}
void startExe::close_process()
{
    int row=row_;
    process->kill();
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString(tr("%1").arg("启用"))));

}
int startExe::getRow(int row)
{
    row_=row;
    return row_;
}
void startExe::checkRowSlot()
{
    int row=ui->tableWidget->rowCount();

//    qDebug()<<row<<"rowCount()";
     for(int i=0;i<row;i++)
     {
         QString path="F:/work/WORK/123/EXE";
         QString filename=ui->tableWidget->item(i,0)->text();
         QString exe=path+"/"+filename;
         if(exe==filePathList.at(i))
         {
//            qDebug()<<filePathList.at(row)<<i<<""<<row;
           process->start(exe);
         }
         else
         {
            process->start(filePathList.at(i));
//             qDebug()<<filePathList.at(i)<<i<<""<<row;
         }
         ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(tr("%1").arg("禁用"))));
     }


}

//QList<QProcess*> startExe::creatProcess(int row)
//{
//    row = row_;
//    qDebug()<<row<<"row_creat";
//    QList<QProcess*> list;
//    for(int i=0;i<row;i++)
//    {
//        QProcess *process = new QProcess;

//        list.append(process);
//    }

////    for(int i = 0;i< list.size();++i){
////       QProcess *process =  list.at(i);
////    }

//    list_process=list;
//    qDebug()<<list.size()<<"size";
//    return list_process;

//}
