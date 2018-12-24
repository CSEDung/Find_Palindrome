#ifndef QQUICKPALINDROME_H
#define QQUICKPALINDROME_H
#include <QString>
#include <QList>

class QQuickPalindrome
{
private:
    int i,j,items;
    QString string;
    QString restring;
    QList<int> CharItem;


public:
    QQuickPalindrome();
    int MaxValue(int a, int b);
    void SetString(QString str);
    QString GetString();
    void ReverseString();
    void BuildMatrix();
    int GetMatrixItemValue(int x, int y);
    QString GetPalindrome(QString str);
};

#endif // QQUICKPALINDROME_H
