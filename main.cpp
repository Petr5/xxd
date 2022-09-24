#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>
#include <QLatin1String>
#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>
QString HexToAscii(QString Str);
QString AsciiToHex(QString Str);
using std::string; using std::fstream;
using std::cout; using std::endl;

QString HexToAscii(QString String)

{

QByteArray ByteArray1=String.toUtf8();

const char* chArr1=ByteArray1.constData();

QByteArray ByteArray2=QByteArray::fromHex(chArr1);

const char* chArr2=ByteArray2.constData();

return QString::fromUtf8(chArr2);

}


QString AsciiToHex(QString String)

{

QByteArray ByteArray1=String.toUtf8();

QByteArray ByteArray2=ByteArray1.toHex();

const char* chArr1=ByteArray2.constData();

return QString::fromUtf8(chArr1);

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    QString filename = "Data.txt";
    QPlainTextEdit edit;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QByteArray inData = file.readAll();
    QByteArray outData = inData.toHex();

    QString str = QString(outData);
    string str2 = str.toStdString();
    int i = 0;
    int base = 16;
    QString s;
    cout << "symbol new line " << HexToAscii("0a").toStdString() << endl;

    while ( i < str2.size()){

        if (!(i % base) && i){
            edit.moveCursor (QTextCursor::End);
            edit.insertPlainText("\t" + HexToAscii(s).replace("\n", "*"));
//            edit.appendPlainText(HexToAscii(s).replace("\n", "*"));
            edit.appendPlainText("");
            s.clear();
        }
        if (!(i % 4)){
            edit.moveCursor (QTextCursor::End);
            edit.insertPlainText(QChar(' '));
        }
//        edit.appendPlainText(QChar(str2[i]));
        edit.moveCursor (QTextCursor::End);
        edit.insertPlainText(QChar(str2[i]));
        s.append(str2[i]);
        cout << "i " << i << "s " << s.toStdString() << endl;
        qDebug() << s;
        ++i;
    }

    cout << "!!!!!!   " << s.toStdString() <<endl;
    if ((i % base) && i){
        edit.moveCursor (QTextCursor::End);
        edit.insertPlainText("\t" + HexToAscii(s).replace("\n", "*"));
//            edit.appendPlainText(HexToAscii(s).replace("\n", "*"));
        edit.appendPlainText("");
        s.clear();
    }

//    edit.appendPlainText(line);
    edit.show();
    file.close();
    return a.exec();
}
