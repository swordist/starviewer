/***************************************************************************
 *   Copyright (C) 2005-2006 by Grup de Gràfics de Girona                 *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#include "qlogviewer.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTextCodec>
#include <QFileDialog>
#include <QSettings>

#include "logging.h"
#include "starviewerapplication.h"

namespace udg {

QLogViewer::QLogViewer(QWidget *parent)
 : QDialog(parent)
{
    setupUi( this );
	readSettings();
//     // carreguem l'arxiu de log
//     updateData();
    createConnections();
}

QLogViewer::~QLogViewer()
{
	writeSettings();
}

void QLogViewer::updateData()
{
    // \TODO aquest directori s'hauria de guardar en alguna mena de qsettings o similar
    QFile logFile( udg::UserLogsFile );
    if ( !logFile.open( QFile::ReadOnly | QFile::Text) )
    {
        ERROR_LOG( "No s'ha pogut obrir l'arxiu de logs" );
        m_logBrowser->setPlainText( tr("ERROR: No Log file found at this path: %1\nEnvironment variable(logFilePath): %2").arg( udg::UserLogsFile ).arg( getenv("logFilePath") ) );
    }
    else
    {
        INFO_LOG( "S'ha obert amb èxit l'arxiu de logs" );
        m_logBrowser->setReadOnly( true );
        m_logBrowser->setPlainText( logFile.readAll() );
    }
}

void QLogViewer::createConnections()
{
    connect( m_closeButton , SIGNAL( clicked() ) , this , SLOT( close() ) );
    connect( m_saveButton , SIGNAL( clicked() ) , this , SLOT( saveLogFileAs() ) );
}

void QLogViewer::saveLogFileAs()
{
    QString fileName = QFileDialog::getSaveFileName( this, tr("Save as..."), QString(), tr("Log Files (*.log)") );

    if ( fileName.isEmpty() )
        return;

    QFile file( fileName );
    if ( !file.open( QFile::WriteOnly ) )
        return;

    QTextStream logStream( &file );
    logStream << m_logBrowser->document()->toPlainText();
}

void QLogViewer::writeSettings()
{
	QSettings settings;
    settings.setValue("logViewerDialogGeometry", saveGeometry());
}

void QLogViewer::readSettings()
{
    QSettings settings;
    this->restoreGeometry(settings.value("logViewerDialogGeometry").toByteArray());
}

}
