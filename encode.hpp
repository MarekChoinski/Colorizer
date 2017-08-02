#ifndef ENCODE_HPP
#define ENCODE_HPP

#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QSettings>
#include <QIODevice>
#include <vector>
#include <string>
#include <QDesktopServices>

class Encode
{
public:
    Encode(QString i_fileName);

private:
    bool m_useAlphaChannel;

    QString loadTextFromFile(QString fileName) const;
    void drawTextOnImage(QString strings);

    int heightOfImage(int a) const;
    inline int widthOfImage(int a) const;

    QString fileName;
    void saveImage(QImage image);
    void fixPolishCharacters(QString &text);
    void lastPixelFix(QImage& image);
    int checkAmountOfPixels(int textSize);
};

#endif // ENCODE_HPP
