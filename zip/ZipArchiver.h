#ifndef ZIPARCHIVER_H
#define ZIPARCHIVER_H

#include <QString>
#include <QByteArray>
#include <QBuffer>

class ZipArchiver {

public:
    ZipArchiver();

    bool unpackIntoSpecifyPath( QByteArray fileZipBuffer, const QString &path );
    bool packDirectory( const QString &directory, QByteArray &byteArray );
};

#endif
