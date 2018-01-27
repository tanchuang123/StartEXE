#ifndef STARTEXE_H
#define STARTEXE_H

#include <QWidget>
#include <QFileInfoList>
#include <QProcess>
namespace Ui {
class startExe;
}

class startExe : public QWidget
{
    Q_OBJECT

public:
    explicit startExe(QWidget *parent = 0);
    ~startExe();
    void initExe();
//    void contextMenuEvent(QContextMenuEvent *event);
    int getRow(int row);
signals:

private slots:
    void on_pushButton_clicked();
    int show_menu(const QPoint pos);
    void start_process();
    void close_process();
    void close_c();
    void checkRowSlot();
//    QList<QProcess*> creatProcess(int row);
private:
    Ui::startExe *ui;
    QProcess *process;
    int row_;
    QString filePath;
    QStringList filePathList;
//    QList<QProcess*> list_process;
};

#endif // STARTEXE_H
