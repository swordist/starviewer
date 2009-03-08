/***************************************************************************
 *   Copyright (C) 2006-2007 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.edu/GGG/index.html                                    *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/


#ifndef UDGOPTIMALVIEWPOINTINPUTPARAMETERSFORM_H
#define UDGOPTIMALVIEWPOINTINPUTPARAMETERSFORM_H


#include "ui_optimalviewpointinputparametersformbase.h"

#include "transferfunction.h"

namespace udg {

class OptimalViewpointParameters;
class Volume;

/**
 * Interfície per definir tots els paràmetres del mètode de visualització del
 * Punt de Vista Òptim.
 */
class OptimalViewpointInputParametersForm : public QWidget, private ::Ui::OptimalViewpointInputParametersFormBase
{
Q_OBJECT
public:
    OptimalViewpointInputParametersForm( QWidget * parent = 0 );
    virtual ~OptimalViewpointInputParametersForm();

    /// Assigna l'objecte que guardarà els paràmetres.
    void setParameters( OptimalViewpointParameters * parameters );

public slots:
    /**
     * Slot que ens serveix per indicar que hem d'actualitzar el paràmetre que
     * ens diguin mitjançant un identificador (que, en realitat, serà un enum).
     * Serveix per canviar els valors a partir d'una classe Parameters.
     */
    void readParameter( int index );

    /**
     * Escriu tots els valors de paràmetres que té actualment al Parameters
     * associat.
     */
    void writeAllParameters();

    /// Assigna la funció de transferència actual.
    void setTransferFunction( const TransferFunction & transferFunction );

    void setNumberOfSlices( unsigned short numberOfSlices );

    void setRangeMax( unsigned char rangeMax );

protected:
    /**
     * Mètode reimplementat per inicialitzar la funció de transferència quan es
     * mostra el widget per primer cop. Si no es fa així hi ha problemes amb el
     * GradientEditor.
     */
    virtual void showEvent( QShowEvent * event );

private slots:

    void setAdjustedTransferFunction( const TransferFunction & adjustedTransferFunction );
    void loadTransferFunction();
    void saveTransferFunction();
    void setClusterFirst( int slice );
    void setClusterLast( int slice );

    void requestNewMethod();

signals:

    /// Demana que es carregui la segmentació des d'un fitxer.
    void loadSegmentationRequested();
    /// Demana que s'executi la segmentació automàtica.
    void automaticSegmentationRequested();
    void executionRequested();

    /// Demana que s'executi un dels nous mètodes.
    void newMethod2Requested( int step, bool normalized );

    void renderPlaneRequested( short plane );

private:

    /// Objecte que guardarà els paràmetres.
    OptimalViewpointParameters * m_parameters;

    /// Funció de transferència actual.
    TransferFunction m_transferFunction;

    /// Cert si s'ha inicialitzat la funció de transferència i fals altrament.
    bool m_inited;

};


};


#endif
