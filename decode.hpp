#ifndef DECODE_HPP
#define DECODE_HPP

#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QFileDevice>
#include <QIODevice>
#include <vector>
#include <string>

class Decode
{
public:
    Decode(QString i_fileName);
private:
    inline QImage loadImageFromFile(QString &fileName) const;
    QString translateImagetoText(QImage &image);
    void fixPolishCharacters(QString &text);
    void saveTextToFile(QString text);
    QChar getAlphaChannel(int alphaChannel);

};

#endif // DECODE_HPP
