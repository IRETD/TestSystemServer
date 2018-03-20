#include "TestDirectory.h"
#include <QDir>
#include <thread/MyMutex.h>
#include <QMutex>
#include <QTextStream>


QString TestDirectory::getFreeFolderName( const QString &folderName ) {

    QString newFolderName = folderName;
    QDir directory;

    for ( quint32 num = 2; directory.exists( m_CurrentDirectory + "/" + newFolderName ); num++ ) {
        newFolderName = folderName + " (" + QString::number( num ) + ")";
    }

    return newFolderName;
}


TestDirectory::TestDirectory() {

    m_CurrentDirectory = QCoreApplication::applicationDirPath();
}


void TestDirectory::setCurrentDirectory( const QString &directoryName ) {

    m_CurrentDirectory = directoryName;
}


QString TestDirectory::createFolder( const QString &folderName, QString path /*= NULL*/ ) {

    QMutex *mutex = MyMutex::getInstane() -> getMutex();
    mutex -> lock();

    QString availableFolderName = getFreeFolderName( folderName );

    QDir directory;

    if ( path.isEmpty() ) {
        path = m_CurrentDirectory;
    }

    bool result = directory.mkdir( path + "/" + availableFolderName );

    mutex -> unlock();

    if ( result ) {
        return availableFolderName;
    }

    return NULL;
}


bool TestDirectory::createFile( const QString &fileName ) {

    QFile file( m_CurrentDirectory + "/" + fileName );

    if ( !file.open( QIODevice::ReadWrite ) ) {
        return false;
    }

    file.close();

    return true;
}


bool TestDirectory::removeFolder( const QString &nameFolder ) {

    QDir directory;
    return directory.rmdir( m_CurrentDirectory + "/" + nameFolder );
}


bool TestDirectory::removeFile(const QString &fileName ) {

    QFile file( m_CurrentDirectory + "/" + fileName );

    return file.remove();
}


bool TestDirectory::folderExist( const QString &folderName ) {

    QDir directory;

    return directory.exists( m_CurrentDirectory + "/" + folderName );
}


bool TestDirectory::writeInFile( const QString &fileName,
                                 const QStringList &dataList ) {

    bool result = false;

    QFile file( m_CurrentDirectory + "/" + fileName );

    if ( file.open( QIODevice::ReadWrite ) ) {

        QTextStream writeData( &file );
        foreach( QString str, dataList ) {

            writeData << str;
        }

        file.close();
        result = true;
    }

    return result;
}

bool TestDirectory::readFromFile( const QString &fileName,
                                  QStringList &outputData ) {

    bool result = false;

    QFile file( m_CurrentDirectory + "/" + fileName );
    if ( file.open( QIODevice::ReadOnly ) ) {

        QTextStream readData( &file );
        ///ЧИТАЕМ ПОСТРОЧНО!
        while( !readData.atEnd() ) {

            QString line = readData.readLine();
            outputData.append( line );
        }

        file.close();

        result = true;
    }

    return result;
}


///ИМЯ ФАЙЛА!!!!
/// НЕ ПУТЬ!!!!!
bool TestDirectory::readFromFile( const QString &fileName,
                                  QString &data ) {

    bool result = false;

    QFile file( m_CurrentDirectory + "/" + fileName );
    if ( file.open( QIODevice::ReadOnly ) ) {

        QTextStream readData( &file );
        data = readData.readAll();
        file.close();

        result = true;
    }

    return result;
}

bool TestDirectory::readFromFileByFullPath( const QString &filePath,
                                            QString &data ) {

    bool result = false;

    //ДУБЛЬ КОД, ДА-ДА!!!
    QFile file( filePath );
    if ( file.open( QIODevice::ReadOnly ) ) {

        QTextStream readData( &file );
        data = readData.readAll();
        file.close();

        result = true;
    }

    return result;
}
