#include "decode.hpp"



Decode::Decode(QString i_fileName)
{

        QImage image  = loadImageFromFile(i_fileName);
        QString text = translateImagetoText(image);

        saveTextToFile(text);

}


QImage Decode::loadImageFromFile(QString &fileName) const
{
    return QImage(fileName, "PNG");
}


QString Decode::translateImagetoText(QImage &image)
{
    QString text="";

    for(int i=0; i<image.height(); i++)//y
    {
        for(int j=0; j<image.width(); j++)//x
        {
            QColor pointColor = image.pixelColor(j, i);

            text+=static_cast<QChar>(pointColor.red());
            text+=static_cast<QChar>(pointColor.green());
            text+=static_cast<QChar>(pointColor.blue());
            //alpha channel
            text+=getAlphaChannel( pointColor.alpha() );

        }
    }

    fixPolishCharacters(text);
    return text;
}


void Decode::fixPolishCharacters(QString &text)
{
    // Ą, Ć, Ę, Ł, Ń, Ó, Ś, Ź, Ż, ą, ć, ę, ł, ń, ó, ś, ź, ż
    unsigned const short int polishUnicode[]      = {260, 262, 280, 321, 323, 211, 346, 377, 379, 261, 263, 281, 322, 324, 243, 347, 378, 380};
    unsigned const short int fixedPolishUnicode[] = {128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145};

    for(auto &p : text)
    {
        if( p>=128 && p<=145 )
        {
            unsigned short int indexTable = std::distance(fixedPolishUnicode, std::find(fixedPolishUnicode, fixedPolishUnicode+18, p.unicode()));

            if(indexTable>0 && indexTable<18)
                p=static_cast<QChar>(polishUnicode[indexTable]);
            else
                p=static_cast<QChar>( 0 );
        }
    }


}

void Decode::saveTextToFile(QString text)
{
    if(!text.isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(Q_NULLPTR,
                ("Save encoded text"), "",
                ("Text (*.txt);;All Files (*)"));

        QFile f( fileName );
        //QFile f("output_col.txt");
        f.open( QIODevice::WriteOnly );

        // store data in f
        QTextStream outStream(&f);
        outStream<<text;

        f.close();

        QSettings settings("MarekChoinski","Colorizer" );
        if( settings.value("pref/s_openAfterCoding").toBool() )
            QDesktopServices::openUrl(QUrl("file:///"+fileName, QUrl::TolerantMode));

    }
}

QChar Decode::getAlphaChannel(int alphaChannel)
{
    if(alphaChannel == 255) return NULL;
    else return static_cast<QChar>(alphaChannel);
}



