#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QString>
#include <QChar>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int i,j,count;
    bool IsRunning;
    bool IsPaused;
    Ui::MainWindow *ui;
    QGraphicsScene * Show;
    QGraphicsScene * Cmd;
    QString string;
    QString restring;
    QString result;
    QFont CharFont;
    QFont f;
    QList<QGraphicsTextItem *> CharItem;
    QGraphicsTextItem * charItem;
    QList<QString> IString;
    QList<QString> OString;
    QTimer * Timer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetDefault();
    void SetScence(QString text);
    int RowSpacing(int value);
    int ColSpacing(int value);
    int MaxValue(int a, int b);
    void ReverseString();
    void BuildCollum();
    void BuildRow();
    int SetPosition(int i, int j);
    void PushCharMatrix(int SetX, int SetY, int value);
    void PushCharMatrix(int SetX, int SetY, int value, int position,int color);
    int GetMatrixItemValue(int x, int y);
    void LightItem(int x);
    void LightItem(int x, int y);
    void LightItem(int x, int y, QString color);
    void DarkMatrix();
    void DisLightMatrixItem(int i, int j);
    void DisLightItem(int x);
    void DisLightItem(int x, int y);
    int GetTimeBuild();
    void WriteResultToFile();
    void BuildPalindrome();
    void WriteText(QGraphicsScene *S, int y, QString text);
    void WriteText(QGraphicsScene *S, int y);

private slots:
    void Tick_Matrix();
    void Tick_Matrix_2();
    void Tick_BuildPalindrome();
    void on_InputKeyBoard_clicked();
    void on_StartDemo_clicked();
    void on_OpenFile_clicked();
    void on_SaveToFile_clicked();
    void on_QuickFindDown_clicked();
    void on_SpeedDemo_valueChanged(int value);
    void on_ResetAll_clicked();
};

#endif // MAINWINDOW_H
