#include "qquickpalindrome.h"
#include <QString>
#include <QList>

QQuickPalindrome::QQuickPalindrome()
{

}

int QQuickPalindrome::MaxValue(int a, int b)
{
    return (a>b)?a:b;
}

void QQuickPalindrome::SetString(QString str)
{
    string = str;
}

QString QQuickPalindrome::GetString()
{
    return string;
}

void QQuickPalindrome::ReverseString()
{
    restring="";
    for(int i=string.length()-1;i>-1;i--)
    {
        restring.append(string.at(i));
    }
}

void QQuickPalindrome::BuildMatrix()
{
    for(int i=0; i<string.length();i++)
    {
        for(int j=0;j<string.length();j++)
        {
            if(restring.at(j) == string.at(i))
            {
                if(j==0)
                {
                    CharItem.append(1);
                }else
                {
                    if(i==0)
                    {
                        CharItem.append(1);
                    }else
                    {
                        CharItem.append(GetMatrixItemValue(i-1,j-1)+1);
                    }
                }
            }else
            {
                if(j==0)
                {
                    if(i==0)
                    {
                        CharItem.append(0);
                    }else
                    {
                        CharItem.append(MaxValue(0,GetMatrixItemValue(i-1,j)));
                    }
                }else if(j==string.length())
                {
                    CharItem.append(MaxValue(0,GetMatrixItemValue(i,j-1)));
                }else
                {
                    CharItem.append(MaxValue(GetMatrixItemValue(i-1,j),
                                             GetMatrixItemValue(i,j-1)));
                }
            }
        }
    }
}

int QQuickPalindrome::GetMatrixItemValue(int x, int y)
{
    return CharItem.value((x*string.length()+y));
}

QString QQuickPalindrome::GetPalindrome(QString str)
{
    string = str;
    ReverseString();
    BuildMatrix();
    QString s="";
    i=string.length()-1;
    j=i;
    while(i>-1 && j>-1)
    {
        if(GetMatrixItemValue(i,j)==0) break;
        if(string.at(i)==restring.at(j))
        {
            s.append(string.at(i));
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
    return s;
}
