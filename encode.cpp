#include "encode.hpp"



Encode::Encode(QString i_fileName)
{
    QSettings settings("MarekChoinski","Colorizer" );

    qDebug()<<"bool value: "<<settings.value("pref/s_useAlphaChannel").toBool();
    qDebug()<<"int value: "<<settings.value("pref/s_useAlphaChannel").toInt();

    m_useAlphaChannel = settings.value("pref/s_useAlphaChannel").toBool();
    //qDebug()<<"m_useAlphaChannel "<<m_useAlphaChannel;

    drawTextOnImage (loadTextFromFile(i_fileName));


}

QString Encode::loadTextFromFile(QString fileName) const
{
    QFile file(fileName);
    QStringList strings;
    QString text;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            text+=in.readLine();
        }
    }

    return text;

}


void Encode::drawTextOnImage(QString text)
{


    fixPolishCharacters(text);
    qDebug()<<"Fixed text: "<<text;
    qDebug()<<"Size of text: "<<text.size();

    int amountOfPixels = checkAmountOfPixels( text.size() );
    qDebug()<<"amountOfPixels: "<< amountOfPixels;

    QImage image(widthOfImage( amountOfPixels ),
                 heightOfImage( amountOfPixels ),
                 QImage::Format_ARGB32);//TODO check also others formats


    image.fill(QColor(255,255,255,255));
    qDebug()<<"Size of image: "<< image.width()<<" X " << image.height();

    int textIndex=0;

    //TODO make it work XD
    //#define isInCharset text[textIndex]>=0 && text[textIndex]<=145

    for(int i=0;i<image.height();i++)//y
    {
        for(int j=0;j<image.width();j++)//x
        {
            int r=0;
            int g=0;
            int b=0;
            int a=255;

            if(text[textIndex].unicode()>=0 && text[textIndex].unicode()<=145)
            {
                r = text[textIndex].unicode();
                qDebug()<<textIndex<< "R"<<text[textIndex]<<text[textIndex].unicode();

            }textIndex++;

            if(text[textIndex].unicode()>=0 && text[textIndex].unicode()<=145)
            {
                g = text[textIndex].unicode();
                qDebug()<<textIndex<< "G"<<text[textIndex]<<text[textIndex].unicode();

            }textIndex++;

            if(text[textIndex].unicode()>=0 && text[textIndex].unicode()<=145)
            {
                b = text[textIndex].unicode();
                qDebug()<<textIndex<< "B"<<text[textIndex]<<text[textIndex].unicode();

            }textIndex++;

            if((text[textIndex].unicode()>=0 && text[textIndex].unicode()<=145) && m_useAlphaChannel)
            {
                a = text[textIndex].unicode();
                qDebug()<<textIndex<< "A"<<text[textIndex]<<text[textIndex].unicode();

            }if(m_useAlphaChannel) textIndex++;

                qDebug()<<"Color"<<r<<g<<b<<a<<"at"<<j<<i;
                qDebug()<<" ";
                image.setPixelColor(j, i, QColor(r, g ,b, a));
        }
    }


    saveImage(image);



}


int Encode::heightOfImage(int a) const
{
    std::vector<int> dividers;

    //1 is divider of every integer
    dividers.push_back(1);

        for(int i=1; i<=a/2; i++)
        {
            if(a%i == 0)
            {
                dividers.push_back(i);
            }
        }

    if(dividers.back() == sqrt(a))
    {
        return sqrt(a); //square
    }

    return dividers[dividers.size()/2]; //median
}

int Encode::widthOfImage(int a) const
{
    return ( a/heightOfImage(a) );
}

void Encode::saveImage(QImage image)//TODO ? DontUseNativeDialog
{
    QSettings settings("MarekChoinski","Colorizer" );

    QString fileName = QFileDialog::getSaveFileName(
    Q_NULLPTR,
    ("Save image"),
    QDir::currentPath(),
    ("Image (*.png)") );

        if(!fileName.isEmpty())
        {
            image.save(fileName, "PNG", 100 );

            if( settings.value("pref/s_openAfterCoding").toBool() )
                QDesktopServices::openUrl(QUrl("file:///"+fileName, QUrl::TolerantMode));
        }

}
//TODO fixRussianCharacters
void Encode::fixPolishCharacters(QString &text)
{

    // Ą, Ć, Ę, Ł, Ń, Ó, Ś, Ź, Ż, ą, ć, ę, ł, ń, ó, ś, ź, ż
    unsigned const short int polishUnicode[]      = {260, 262, 280, 321, 323, 211, 346, 377, 379, 261, 263, 281, 322, 324, 243, 347, 378, 380};
    unsigned const short int fixedPolishUnicode[] = {128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145};

    for(auto &p : text)
    {
        //TODO not sure if (p<=255) better. Now is not non-standard unicode support. But idk if it is necessary
        bool isNotAscii = !(p>=0 && p<=127);
        if( isNotAscii )
        {
            unsigned short int indexTable = std::distance(polishUnicode, std::find(polishUnicode, polishUnicode+18, p.unicode()));

            if(indexTable>0 && indexTable<18)
                p=static_cast<QChar>(fixedPolishUnicode[indexTable]);
            else
                p=static_cast<QChar>( 0 );
        }

    }


}

void Encode::lastPixelFix(QImage& image)
{
    QColor lastPixelColor = image.pixelColor(image.width()-1,image.height()-1);

    if((lastPixelColor.red()>=0 && lastPixelColor.red()<=255) == false )
       lastPixelColor.setRed(0);

    if((lastPixelColor.green()>=0 && lastPixelColor.green()<=255) == false )
       lastPixelColor.setGreen(0);

    if((lastPixelColor.blue()>=0 && lastPixelColor.blue()<=255) == false )
       lastPixelColor.setBlue(0);

    image.setPixelColor(image.width()-1,
                        image.height()-1,
                        lastPixelColor);

}

int Encode::checkAmountOfPixels(int textSize)
{

    if(m_useAlphaChannel)
    {
        if(textSize%4 == 0) return textSize/4;
        else return textSize/4 + 1;
    }

    else
    {
        if(textSize%3 == 0) return textSize/3;
        else return textSize/3 + 1;
    }

}
