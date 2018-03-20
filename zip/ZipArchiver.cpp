#include "ZipArchiver.h"
#include <private/qzipreader_p.h>
#include <private/qzipwriter_p.h>
#include <QBuffer>
#include <QDir>
#include <QDirIterator>

ZipArchiver::ZipArchiver() {
}


bool ZipArchiver::unpackIntoSpecifyPath( QByteArray fileZipBuffer, const QString &path ) {

    QBuffer buffer( &fileZipBuffer );
    buffer.open( QIODevice::ReadWrite );
    QZipReader zipReader( &buffer );

    if ( zipReader.exists() ) {
        zipReader.extractAll( path );
        return true;
    }

    return false;
}

bool ZipArchiver::packDirectory( const QString &directory , QByteArray &byteArray ) {

    QBuffer bufferZip( &byteArray );

    if ( !bufferZip.open( QIODevice::ReadWrite) )
        return false;

    QZipWriter zip( &bufferZip );
    if ( zip.status() != QZipWriter::NoError )
        return false;

    zip.setCompressionPolicy( QZipWriter::AutoCompress );

    QString path = directory +  "/";
//    QString path = QLatin1String( directory );
    QDirIterator it( path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,
                     QDirIterator::Subdirectories );

    while ( it.hasNext() ) {
        QString file_path = it.next();

        if ( it.fileInfo().isDir() ) {
            zip.setCreationPermissions( QFile::permissions( file_path ) );
            zip.addDirectory( file_path.remove( path ) );
        }
        else
            if ( it.fileInfo().isFile() ) {
                QFile file( file_path );

                if ( !file.open( QIODevice::ReadOnly ) )
                    continue;

                zip.setCreationPermissions( QFile::permissions( file_path ) );
                QByteArray ba = file.readAll();
                zip.addFile( file_path.remove( path ), ba );
            }
    }

    zip.close();

    return true;
}
