#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qquickpalindrome.h"
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetScence("Please insert your string !");
    Timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetDefault()
{
    Timer->stop();
    disconnect(Timer,SIGNAL(timeout()),this,0);
    IsRunning = false; i=0;
    Show = new QGraphicsScene();
    ui->Shower->setScene(Show);
    if(ui->TextInput->toPlainText()=="")
        ui->TextInput->setText("pleaseinsertyourstring");
    string = ui->TextInput->toPlainText();
    CharItem.clear();
    ReverseString();
    CharFont.setPixelSize(20);
    BuildCollum();
    BuildRow();
    ui->ShowResult->setMaximumHeight(0);
    ui->InputLengh->display(string.length());
    ui->PalindromeLengh->display(0);
}

void MainWindow::SetScence(QString text)
{
    Show = new QGraphicsScene();
    ui->Shower->setScene(Show);
    charItem = new QGraphicsTextItem();
    charItem->setPlainText(text);
    CharFont.setPixelSize(35);
    charItem->setFont(CharFont);
    charItem->setDefaultTextColor(QColor(255,255,255,255));
    Show->addItem(charItem);
}



int MainWindow::RowSpacing(int value)
{
    return value*22+25;
}

int MainWindow::ColSpacing(int value)
{
    return value*34+30;
}

int MainWindow::MaxValue(int a, int b)
{
    return (a>b)?a:b;
}

void MainWindow::ReverseString()
{
    restring="";
    for(int i=string.length()-1;i>-1;i--)
    {
        restring.append(string.at(i));
    }
}

void MainWindow::BuildCollum()
{
    CharFont.setBold(true);
    for(int i=0;i<string.length();i++)
    {
        charItem = new QGraphicsTextItem();
        charItem->setPlainText(string.at(i));
        charItem->setFont(CharFont);
        charItem->setDefaultTextColor(QColor(255,255,255,255));
        charItem->setPos(0,RowSpacing(i));
        CharItem.append(charItem);
        Show->addItem(CharItem.value(i));
    }
}

void MainWindow::BuildRow()
{
    for(int i=0;i<string.length();i++)
    {
        charItem = new QGraphicsTextItem();
        charItem->setPlainText(restring.at(i));
        charItem->setFont(CharFont);
        charItem->setDefaultTextColor(QColor(255,255,255,255));
        charItem->setPos(ColSpacing(i),0);
        CharItem.append(charItem);
        Show->addItem(CharItem.value(string.length()+i));
    }
}

int MainWindow::SetPosition(int i, int j)
{
    return (i+2)*string.length()+j;
}

void MainWindow::PushCharMatrix(int SetX, int SetY, int value)
{
    charItem = new QGraphicsTextItem();
    charItem->setPlainText(QString::number(value));
    charItem->setPos(SetX,SetY);
    CharItem.append(charItem);
}

void MainWindow::PushCharMatrix(int SetX, int SetY, int value, int position,int color)
{
    charItem = new QGraphicsTextItem();
    if(color%2!=0)
    {
        charItem->setDefaultTextColor(QColor(0,204,153,255));
    }else
    {
        charItem->setDefaultTextColor(QColor(255,64,0,255));
    }
    charItem->setPlainText(QString::number(value));
    charItem->setFont(CharFont);
    charItem->setPos(SetX,SetY);
    CharItem.append(charItem);
    Show->addItem(CharItem.value(position));
}

int MainWindow::GetMatrixItemValue(int x, int y)
{
    QString value = CharItem.value((x+2)*string.length()+y)->toPlainText();
    return value.toInt();
}

void MainWindow::LightItem(int x)
{
    QGraphicsTextItem *temp = CharItem.at(x);
    temp->setDefaultTextColor(QColor(255,255,0,255));
}

void MainWindow::LightItem(int x, int y)
{
    QGraphicsTextItem *temp = CharItem.at((x+2)*string.length()+y);
    temp->setDefaultTextColor(QColor(0,255,0,255));

}

void MainWindow::LightItem(int x, int y, QString color)
{
    if(color == "yellow")
    {
        QGraphicsTextItem *temp = CharItem.at((x+2)*string.length()+y);
        temp->setDefaultTextColor(QColor(255,255,0,255));
    }else if(color == "blue")
    {
        QGraphicsTextItem *temp = CharItem.at((x+2)*string.length()+y);
        temp->setDefaultTextColor(QColor(0,0,255,255));
    }else
    {
        QGraphicsTextItem *temp = CharItem.at((x+2)*string.length()+y);
        temp->setDefaultTextColor(QColor(0,102,0,255));
    }
}

void MainWindow::DarkMatrix()
{
    QColor c1 = QColor(0,0,255,255);
    QColor c2 = QColor(0,102,0,255);
    int n = (2 * string.length())+ string.length() * string.length();
    for(int i=2*string.length(); i<n;i++ )
    {
        if(CharItem.at(i)->defaultTextColor() != c1 && CharItem.at(i)->defaultTextColor() != c2)
        {
            CharItem.at(i)->setDefaultTextColor(QColor(51,51,0,255));
        }
    }
}

void MainWindow::DisLightMatrixItem(int i, int j)
{
    if(j>0 && i>0){
        if(restring.at(j-1)==string.at(i)){
            if(j==0) DisLightItem(i-1,j-2);
            else if(j>1) DisLightItem(i-1,j-2);
        }else{
            if(j>1) DisLightItem(i,j-2);
            if(j<string.length()) DisLightItem(i-1,j-1);
        }
    }
    else if(j>0){
        if(restring.at(j-1)!=string.at(i)){
            if(j>1) DisLightItem(i,j-2);
        }
    }else if(i>0){
        if(restring.at(string.length()-1)==string.at(i-1)){
            if(i>1) DisLightItem(i-2,string.length()-2);
        }
    }
}

void MainWindow::DisLightItem(int x)
{
    QGraphicsTextItem *temp = CharItem.at(x);
    temp->setDefaultTextColor(QColor(255,255,255,255));
}

void MainWindow::DisLightItem(int x, int y)
{
    QGraphicsTextItem *temp = CharItem.at((x+2)*string.length()+y);
    if(x%2!=0)
    {
        temp->setDefaultTextColor(QColor(0,204,153,255));
    }else
    {
        temp->setDefaultTextColor(QColor(255,64,0,255));
    }
}

int MainWindow::GetTimeBuild()
{
    int count=0;
    i=string.length()-1;
    j=i;
    while(i>-1 && j>-1 )
    {
        if(GetMatrixItemValue(i,j)==0) break;
        count++;
        if(string.at(i)==restring.at(j) && GetMatrixItemValue(i,j)!=0)
        {
            j--;i--;
        }else if(j==0)
        {
            i--;
        }
        else
        {
            if(GetMatrixItemValue(i,j-1)<GetMatrixItemValue(i-1,j)) i--;
            else j--;
        }
    }
    return count;
}

void MainWindow::BuildPalindrome()
{
    result="YOUR PALINDROME STING >>   ";
    ui->ProgressBar->setMaximum(GetTimeBuild());
    ui->ProgressBar->setValue(0);
    count=0;
    i=string.length()-1;
    j=i;
    disconnect(Timer,SIGNAL(timeout()),this,0);
    connect(Timer,SIGNAL(timeout()),this,SLOT(Tick_BuildPalindrome()));
    Timer->start(2100 - ui->SpeedDemo->value());
}

void MainWindow::WriteText(QGraphicsScene *S, int y, QString text)
{
    S->clear();
    f.setPixelSize(15);
    charItem = new QGraphicsTextItem();
    charItem->setPlainText(text);
    charItem->setFont(f);
    charItem->setPos(0,16*y);
    charItem->setDefaultTextColor(QColor(0,204,0,255));
    S->addItem(charItem);

}

void MainWindow::WriteText(QGraphicsScene *S, int y)
{
    charItem = new QGraphicsTextItem();
    charItem->setPlainText("Done:    "+IString.at(y));
    CharFont.setPixelSize(20);
    charItem->setFont(CharFont);
    charItem->setPos(0,80*y);
    charItem->setDefaultTextColor(QColor(0,204,0,255));
    S->addItem(charItem);
    charItem = new QGraphicsTextItem();
    charItem->setPlainText(QString::number(OString.at(y).length()));
    CharFont.setPixelSize(20);
    charItem->setFont(CharFont);
    charItem->setPos(80,80*y+20);
    charItem->setDefaultTextColor(QColor(0,204,0,255));
    S->addItem(charItem);
    charItem = new QGraphicsTextItem();
    charItem->setPlainText(OString.at(y));
    CharFont.setPixelSize(20);
    charItem->setFont(CharFont);
    charItem->setPos(80,80*y+40);
    charItem->setDefaultTextColor(QColor(0,204,0,255));
    S->addItem(charItem);
}

void MainWindow::Tick_Matrix()
{
    if(!IsRunning && i<string.length())
    {
        j=0;
        LightItem(i);
        LightItem(string.length()+j);
        Tick_Matrix_2();
    }else if(IsRunning && i<string.length())
    {
        Tick_Matrix_2();
        DisLightItem(string.length()+j-2);
    }else if(i>=string.length())
    {
        DisLightItem(i);
        Timer->stop();
        WriteText(Cmd,0,"Matrix was built.");
        BuildPalindrome();
    }
}

void MainWindow::Tick_Matrix_2()
{
    if(!IsPaused){
        if(j<string.length())
        {
            IsRunning = true;
            LightItem(string.length()+j);
            DisLightMatrixItem(i,j);
            if(restring.at(j) == string.at(i))
            {
                if(j==0)
                {
                    PushCharMatrix(ColSpacing(j),RowSpacing(i),1,SetPosition(i,j),i);
                    WriteText(Cmd,0,(QString)string.at(i)+" = "
                              +(QString)restring.at(j)+"   >> 0+1");
                }else
                {
                    //DisLightItem(string.length()+j-1);
                    if(i==0)
                    {
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       1,SetPosition(i,j),i);
                        WriteText(Cmd,0,(QString)string.at(i)+" = "
                                  +(QString)restring.at(j)+"   >> 0+1");
                    }else
                    {
                        LightItem(i-1,j-1);
                        WriteText(Cmd,0,(QString)string.at(i)+" = "
                                  +(QString)restring.at(j)+"   >> "+QString::number(GetMatrixItemValue(i-1,j-1))+"+1");
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       GetMatrixItemValue(i-1,j-1)+1,SetPosition(i,j),i);
                    }
                }
            }else
            {
                if(j==0)
                {
                    if(i==0)
                    {
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       0,SetPosition(i,j),i);
                        WriteText(Cmd,0,(QString)string.at(i)+" != "
                                  +(QString)restring.at(j)+"   >> "+"max(0,0)");
                    }else
                    {
                        LightItem(i-1,j);
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       MaxValue(0,GetMatrixItemValue(i-1,j)),
                                       SetPosition(i,j),i);
                        WriteText(Cmd,0,(QString)string.at(i)+" != "
                                  +(QString)restring.at(j)+"   >> "+"max(0,"+QString::number(GetMatrixItemValue(i-1,j))+")");
                    }
                }else
                {
                    if(i==0)
                    {
                        LightItem(i,j-1);
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       MaxValue(GetMatrixItemValue(i,j-1),0),
                                       SetPosition(i,j),i);
                        WriteText(Cmd,0,(QString)string.at(i)+" != "
                                  +(QString)restring.at(j)+"   >> "+"max("+QString::number(GetMatrixItemValue(i,j-1))
                                  +",0)");
                    }else
                    {
                        LightItem(i-1,j); LightItem(i,j-1);
                        //DisLightItem(string.length()+j-1);
                        PushCharMatrix(ColSpacing(j),RowSpacing(i),
                                       MaxValue(GetMatrixItemValue(i-1,j),GetMatrixItemValue(i,j-1)),
                                       SetPosition(i,j),i);
                        WriteText(Cmd,0,(QString)string.at(i)+" != "
                                  +(QString)restring.at(j)+"   >> "+"max("+QString::number(GetMatrixItemValue(i,j-1))
                                  +","+QString::number(GetMatrixItemValue(i-1,j))+")");
                    }
                }
            }
            ui->ProgressBar->setValue(i*string.length()+j);
            ui->ProgressBar->setFormat("[1/2] Buiding Matrix  %p%");
            ui->PalindromeLengh->display(MaxValue(GetMatrixItemValue(i,j),ui->PalindromeLengh->value()));
            ui->ItemsCount->display(CharItem.size());
            ui->MemnoryCount->display(CharItem.size()* (int)sizeof(charItem));
            j++;
        }else{
            IsRunning = false;
            DisLightItem(string.length()+j-1);
            DisLightItem(i);
            if(i>0)
            {
                DisLightItem(i-1,j-1);
                DisLightItem(i-1,j-1);
            }
            DisLightItem(i,j-2);
            i++;
        }
    }
}

void MainWindow::Tick_BuildPalindrome()
{
    if(i>-1 && j>-1 && GetMatrixItemValue(i,j)!=0)
    {
        count++;
        if(string.at(i)==restring.at(j))
        {
            result.append(string.at(i));
            LightItem(i);  LightItem(string.length() + j);
            LightItem(i,j,"blue");
            j--;i--;
        }else if(j==0)
        {
            LightItem(i,j,"green");
            i--;
        }
        else
        {
            LightItem(i,j,"green");
            if(GetMatrixItemValue(i,j-1)<GetMatrixItemValue(i-1,j)) i--;
            else j--;
        }
        ui->ProgressBar->setValue(count);
        ui->ProgressBar->setFormat("[2/2] Finding Palindrome String  %p%");
    }else
    {
        Timer->stop();
        ui->ShowResult->setMaximumHeight(30);
        ui->ShowResult->setText(result);
        DarkMatrix();
        ui->ProgressBar->setFormat("Completed !");
        ui->StartDemo->setText("Normal Run");
        ui->QuickFindDown->setEnabled(true);
    }
}

void MainWindow::on_InputKeyBoard_clicked()
{
    if(ui->InputKeyBoard->text()=="From File")
    {
        ui->groupBox->setMaximumHeight(90);
        ui->LinkInput->setEnabled(true);
        ui->OpenFile->setEnabled(true);
        ui->InputKeyBoard->setText("From Keyboard");
    }
    else
    {
        ui->LinkInput->setText("Load from file");
        ui->LinkInput->setEnabled(false);
        ui->OpenFile->setEnabled(false);
        ui->groupBox->setMaximumHeight(170);
        ui->TextInput->setFocus();
        ui->InputKeyBoard->setText("From File");
    }
}

void MainWindow::on_StartDemo_clicked()
{
    if(ui->StartDemo->text()=="Normal Run")
    {
        SetDefault();
        if(string.length()<25)
        {
            ui->StartDemo->setText("Pause");
            Cmd = new QGraphicsScene();
            ui->cmd->setScene(Cmd);
            connect(Timer,SIGNAL(timeout()),this,SLOT(Tick_Matrix()));
            ui->ProgressBar->setMaximum(string.length()*(string.length())-1);
            ui->ProgressBar->setValue(0);
            Timer->start(2100 - ui->SpeedDemo->value());
            ui->QuickFindDown->setEnabled(false);
        }else
        {
            SetScence("Your string too long to run, try Quick run !");
        }

    }else if(ui->StartDemo->text()=="Pause")
    {
        ui->StartDemo->setText("Resume");
        IsPaused=true;
    }else
    {
        ui->StartDemo->setText("Pause");
        IsPaused=false;
    }

}

void MainWindow::on_OpenFile_clicked()
{
    ui->LinkInput->setText(QFileDialog::
                   getOpenFileName(this,"Open File","./","Text file: (*.txt)"));
    QFile file(ui->LinkInput->text());
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream input(&file);
       IString.clear();
       OString.clear();
       while (!input.atEnd())
       {
          IString.append(input.readLine());
       }
       file.close();
       ui->TextInput->setPlainText(IString.at(0));
       ui->Waiting->display(IString.count());
    } 
}

void MainWindow::WriteResultToFile()
{
    QFile file(ui->LinkOutput->text());
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream output(&file);
        for(int i=0;i<OString.count();i++)
        {
            output << IString.at(i) << "\r\n" << OString.at(i).length() << "\r\n"
                    << OString.at(i) << "\r\n==========//==========\r\n\r\n";
        }
        file.close();
    }
}

void MainWindow::on_SaveToFile_clicked()
{
    ui->LinkOutput->setText(QFileDialog::getSaveFileName(this,
                  "Save Result to file","./",".txt")+".txt");
    if(OString.count()>0) WriteResultToFile();
}

void MainWindow::on_QuickFindDown_clicked()
{
    Show->clear();
    OString.clear();
    QFile file(ui->LinkInput->text());
    if(file.exists())
    for(int i=0;i<IString.count();i++)
    {

        string = IString.at(i);
        ui->InputLengh->display(string.length());
        QQuickPalindrome qq;
        OString.append(qq.GetPalindrome(string));
        ui->PalindromeLengh->display(OString.at(i).length());
        ui->Waiting->display(IString.count()-i-1);
        WriteText(Show,i);
    }else if(ui->InputKeyBoard->text()=="From File")
    {
        IString.clear();
        IString.append(ui->TextInput->toPlainText());
        string = IString.at(0);
        ui->InputLengh->display(string.length());
        QQuickPalindrome qq;
        OString.append(qq.GetPalindrome(string));
        ui->PalindromeLengh->display(OString.at(0).length());
        WriteText(Show,0);
    }else if(IString.count()<1)
        SetScence("Can not found any string to run !");
    ui->Done->display(OString.count());
    WriteResultToFile();
}

void MainWindow::on_SpeedDemo_valueChanged(int value)
{
    ui->SpeedShow->display(value);
    Timer->stop();
    Timer->start(2100 - value);
}

void MainWindow::on_ResetAll_clicked()
{
    Timer->stop();
    disconnect(Timer,SIGNAL(timeout()),this,0);
    IsRunning = false; i=0;
    IsPaused=false;
    ui->QuickFindDown->setEnabled(true);
    SetScence("Please insert your string !");
    CharItem.clear();
    ui->StartDemo->setText("Normal Run");
    ui->ItemsCount->display(0);
    ui->MemnoryCount->display(0);
    ui->InputLengh->display(0);
    ui->PalindromeLengh->display(0);
    ui->ShowResult->setMaximumHeight(0);
    ui->ProgressBar->setFormat("Ready !");
    ui->ProgressBar->setValue(0);
    ui->TextInput->setText("");
}
