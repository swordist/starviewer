#include "applicationstylehelper.h"

#include <QDesktopWidget>
#include <QApplication>

#include "coresettings.h"
#include "mathtools.h"

namespace udg {

double ApplicationStyleHelper::m_scaleFactor = 1.0;

ApplicationStyleHelper::ApplicationStyleHelper()
{
}

void ApplicationStyleHelper::recomputeStyleToScreenOfWidget(QWidget *widget)
{
    //Per calcular l'style, calculem un factor d'escala a partir de la resolució de la pantalla a on s'està executant
    //el widget que ens passen. Aquest factor serà el que ens servirà per variar el tamany de les diferents fonts, etc.
    QDesktopWidget *desktop = QApplication::desktop();
    const QRect screen = desktop->screenGeometry(widget);

    if ((screen.width() * screen.height()) >= (5 * 1024 * 1024))
    {
        m_scaleFactor = 1.72; // Surt de fer 24/14 on 24 és el tamany de lletra desitjat i 14 és el "per defecte"
    }
    else if ((screen.width() * screen.height()) >= (3 * 1024 * 1024))
    {
        m_scaleFactor = 1.22; // Surt de fer 17/14
    }
    else
    {
        m_scaleFactor = 1.0; // Surt de fer 14/14
    }
}

int ApplicationStyleHelper::getToolsFontSize() const
{
    return this->getFontSize(14.0, CoreSettings::ToolsFontSize);
}

int ApplicationStyleHelper::getWorkInProgressFontSize() const
{
    return this->getToolsFontSize();
}

int ApplicationStyleHelper::getPatientMenuBrowserFontSize() const
{
    // Al ser text de Qt, agafem el tamany de font del sistema com a predeterminat
    return this->getFontSize(QApplication::font().pointSizeF(), CoreSettings::PatientBrowserMenuFontSize);
}

int ApplicationStyleHelper::getFontSize(double defaultFontSize, const QString &settingsBackdoorKey) const
{
    double toolsFontSize = defaultFontSize * m_scaleFactor;

    //TODO de moment es deixa un "backdoor" per poder especificar un text arbitrari a partir de configuració
    // caldrà treure'l un cop comprovat que no hi ha problemes
    Settings settings;
    if (settings.contains(settingsBackdoorKey))
    {
        toolsFontSize = settings.getValue(settingsBackdoorKey).toInt();
    }

    return MathTools::roundToNearestInteger(toolsFontSize);
}

} // Ens namespace udg
