#ifndef TESTDIRECTORY_H
#define TESTDIRECTORY_H


#include <QString>
#include <QCoreApplication>


class TestDirectory {

    QString m_CurrentDirectory;

    QString getFreeFolderName( const QString &folderName );

public:
    TestDirectory();

    void setCurrentDirectory( const QString &directoryName );
    QString createFolder(const QString &folderName, QString path = NULL );
    bool createFile( const QString &fileName );
    bool removeFolder( const QString &folderName );
    bool removeFile( const QString &fileName );
    bool folderExist( const QString &folderName );
    bool writeInFile( const QString &fileName,
                      const QStringList &dataList );
    bool readFromFile( const QString &fileName,
                       QStringList &outputData );
    bool readFromFile( const QString &fileName,
                       QString &data );
    bool readFromFileByFullPath( const QString &filePath,
                                 QString &data );
};

#endif
