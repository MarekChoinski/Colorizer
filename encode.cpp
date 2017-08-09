#include "encode.hpp"



Encode::Encode(QString i_fileName)
{
    QSettings settings("MarekChoinski","Colorizer" );

    m_useAlphaChannel = settings.value("pref/s_useAlphaChannel").toBool();

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

    int amountOfPixels = checkAmountOfPixels( text.size() );

    QImage image(widthOfImage( amountOfPixels ),
                 heightOfImage( amountOfPixels ),
                 QImage::Format_ARGB32);
    //TODO not sure if there are faster formats


    image.fill(QColor(255,255,255,255));

    int textIndex=0;

    #define isInCharset text[textIndex]>=0 && text[textIndex]<=145

    for(int i=0;i<image.height();i++)//y
    {
        for(int j=0;j<image.width();j++)//x
        {
            int r=0;
            int g=0;
            int b=0;
            int a=255;

            if(isInCharset)
            {
                r = text[textIndex].unicode();

            }textIndex++;

            if(isInCharset)
            {
                g = text[textIndex].unicode();

            }textIndex++;

            if(isInCharset)
            {
                b = text[textIndex].unicode();

            }textIndex++;


            //alpha channel
            if(m_useAlphaChannel && isInCharset)
            {
                a = text[textIndex].unicode();

            }
            if(m_useAlphaChannel) textIndex++;


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

void Encode::saveImage(QImage image)
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

//TODO fixRussianCharacters also
void Encode::fixPolishCharacters(QString &text)
{

    //TODO std::map?
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
