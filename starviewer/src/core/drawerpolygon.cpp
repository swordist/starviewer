/***************************************************************************
 *   Copyright (C) 2005-2007 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#include "drawerpolygon.h"
#include "logging.h"
#include "q2dviewer.h"
// vtk
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkActor2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkLine.h>
#include "drawerline.h"
// qt
#include <QVector>

namespace udg {

DrawerPolygon::DrawerPolygon(QObject *parent)
 : DrawerPrimitive(parent), m_vtkPolydata(0), m_vtkPoints(0), m_vtkCellArray(0), m_vtkActor(0), m_vtkMapper(0)
{
}

DrawerPolygon::~DrawerPolygon()
{
    emit dying(this);
}

void DrawerPolygon::addVertix( double point[3] )
{
    this->addVertix( point[0], point[1], point[2] );
}

void DrawerPolygon::addVertix( double x, double y, double z )
{
    QVector<double> array(3);

    array[0] = x;
    array[1] = y;
    array[2] = z;

    m_pointsList << array;
    emit changed();
}

void DrawerPolygon::setVertix( int i, double point[3] )
{
    this->setVertix( i , point[0], point[1], point[2] );
}

void DrawerPolygon::setVertix( int i, double x, double y, double z )
{
    if( i >= m_pointsList.count() || i < 0 )
        addVertix( x, y, z );
    else
    {
        QVector<double> array(3);
        array = m_pointsList.takeAt(i);
        array[0] = x;
        array[1] = y;
        array[2] = z;

        m_pointsList.insert(i,array);
        emit changed();
    }
}

const double *DrawerPolygon::getVertix(int i)
{
    if( i >= m_pointsList.count() || i < 0 )
    {
        double *vertix = new double[3];
        return vertix;
    }
   else
    {
        return m_pointsList.at(i).data();
    }
}

vtkProp *DrawerPolygon::getAsVtkProp()
{
    if( !m_vtkActor )
    {
        buildVtkPoints();
        // creem el pipeline de l'm_vtkActor
        m_vtkActor = vtkActor2D::New();
        m_vtkMapper = vtkPolyDataMapper2D::New();

        m_vtkActor->SetMapper( m_vtkMapper );
        m_vtkMapper->SetInput( m_vtkPolydata );
        // li donem els atributs
        updateVtkActorProperties();
    }
    return m_vtkActor;
}

void DrawerPolygon::update( int representation )
{
    switch( representation )
    {
    case VTKRepresentation:
        updateVtkProp();
    break;

    case OpenGLRepresentation:
    break;

    }
}

void DrawerPolygon::updateVtkProp()
{
    if( m_vtkActor )
    {
        m_vtkPolydata->Reset();
        buildVtkPoints();
        updateVtkActorProperties();
        this->setModified(false);
    }
    else
    {
        DEBUG_LOG("No es pot actualitzar el polígon, ja que encara no s'ha creat!");
    }
}

void DrawerPolygon::buildVtkPoints()
{
    // primer comprovem si el polígon és tancat. En cas que l'últim i el primer no coincideixin, l'afegim
    // TODO es podria comprovar si com a mínim té tres punts, sinó, no es pot considerar polígon
    bool extraVertix = false;
    if( !m_pointsList.isEmpty() )
    {
        double *firstPoint = m_pointsList.first().data();
        double *lastPoint = m_pointsList.last().data();
        if ( ( firstPoint[0] != lastPoint[0] ) || ( firstPoint[1] != lastPoint[1] ) || ( firstPoint[2] != lastPoint[2] ) )
        {
            extraVertix = true;
        }
    }
    if( !m_vtkPolydata )
    {
        m_vtkPolydata = vtkPolyData::New();
        m_vtkPoints = vtkPoints::New();
        m_vtkCellArray = vtkCellArray::New();
    }

    //especifiquem el nombre de vèrtexs que té el polígon
    int numberOfVertices = m_pointsList.count() + ( extraVertix ? 1 : 0 );
    m_vtkCellArray->InsertNextCell( numberOfVertices );
    m_vtkPoints->SetNumberOfPoints( numberOfVertices );

    //donem els punts/vertexs
    int i = 0;
    foreach( QVector<double> vertix, m_pointsList )
    {
        m_vtkPoints->InsertPoint( i, vertix.data() );
        m_vtkCellArray->InsertCellPoint( i );
        i++;
    }
//     for ( int i = 0; i < numberOfVertices; i++ )
//     {
//         m_vtkPoints->InsertPoint( i, m_pointsList.at(i).data() );
//         m_vtkCellArray->InsertCellPoint( i );
//     }
    if( extraVertix )
    {
        // tornem a afegir el primer punt
        m_vtkPoints->InsertPoint( numberOfVertices-1, m_pointsList.at(0).data() );
        m_vtkCellArray->InsertCellPoint( numberOfVertices-1 );
    }
    //assignem els punts al polydata
    m_vtkPolydata->SetPoints( m_vtkPoints );
    // comprovem si la forma està "plena" o no
    if ( this->isFilled() )
        m_vtkPolydata->SetPolys( m_vtkCellArray );
    else
        m_vtkPolydata->SetLines( m_vtkCellArray );
}

void DrawerPolygon::updateVtkActorProperties()
{
    // sistema de coordenades
    m_vtkMapper->SetTransformCoordinate( this->getVtkCoordinateObject() );
    // estil de la línia
    m_vtkActor->GetProperty()->SetLineStipplePattern( m_linePattern );
    //Assignem gruix de la línia
    m_vtkActor->GetProperty()->SetLineWidth( m_lineWidth );
    //Assignem opacitat de la línia
    m_vtkActor->GetProperty()->SetOpacity( m_opacity );
    //mirem la visibilitat de l'm_vtkActor
    m_vtkActor->SetVisibility( this->isVisible() );

    //Assignem color
    QColor color = this->getColor();
    m_vtkActor->GetProperty()->SetColor( color.redF(), color.greenF(), color.blueF() );
}

int DrawerPolygon::getNumberOfPoints() const
{
    return m_pointsList.count();
}

double* DrawerPolygon::getBounds()
{
    return m_vtkPolydata->GetBounds();
}

double DrawerPolygon::getDistanceToPoint( double *point3D )
{
    double minDistanceLine = VTK_DOUBLE_MAX;
    double distance, *auxPoint;
    bool found = false;
    int j;

    if ( !m_pointsList.isEmpty() )
    {
        //mirem si el polígon conté com a últim punt el primer punt, és a dir, si està tancat o no.
        //ens cal que sigui tancat per a dibuixar tots els segments reals que el formen.
        QList< double* > auxList;

        foreach( QVector< double > point, m_pointsList )
        {
            auxPoint = new double[3];

            for( j=0; j < 3; j++ )
                auxPoint[j] = point[j];

            auxList << auxPoint;
        }

        if ( auxList.first()[0] != auxList.last()[0] || auxList.first()[1] != auxList.last()[1] || auxList.first()[2] != auxList.last()[2] )
        {
            //si el primer i últim punt no són iguals, dupliquem el primer punt.
            auxList << auxList.first();
        }

        for ( int i = 0; ( i < auxList.count() - 1 ) && !found ; i++ )
        {
            if ( isPointIncludedInLineBounds( point3D, auxList[i], auxList[i+1] ) )
            {
                minDistanceLine = 0.0;
                found = true;
            }
            else
            {
                distance = vtkLine::DistanceToLine( point3D , auxList[i] , auxList[i+1] );

                if ( ( minDistanceLine != VTK_DOUBLE_MAX ) && ( distance < minDistanceLine ) )
                        minDistanceLine = distance;
            }
        }
    }
    return minDistanceLine;
}

bool DrawerPolygon::isPointIncludedInLineBounds( double point[3], double *lineP1, double *lineP2 )
{
    double range = 5.0;

    /*
        mirem si la distància entre un dels extrems del segment i el punt dóna un valor igual o iferior a un llindar determinat.
        si és així, retornem cert, altrament retornem fals
    */
    return( ( ( fabs( point[0] - lineP1[0] ) <= range ) && ( fabs( point[1] - lineP1[1] ) <= range ) && ( fabs( point[2] - lineP1[2] ) <= range ) ) ||
            ( ( fabs( point[0] - lineP2[0] ) <= range ) && ( fabs( point[1] - lineP2[1] ) <= range ) && ( fabs(point[2] - lineP2[2] ) <= range ) ) );
}

bool DrawerPolygon::isInsideOfBounds( double p1[3], double p2[3], int view )
{
    double minX, maxX, minY, maxY;

    int numberOfPoints = m_pointsList.count();
    bool allPointsAreInside = true;

    //determinem x i y màximes i mínimes segons la vista
    switch( view )
    {
        case Q2DViewer::AxialPlane:
            if ( p1[0] < p2[0] )
            {
                minX = p1[0];
                maxX = p2[0];
            }
            else
            {
                maxX = p1[0];
                minX = p2[0];
            }

            if ( p1[1] < p2[1] )
            {
                minY = p1[1];
                maxY = p2[1];
            }
            else
            {
                maxY = p1[1];
                minY = p2[1];
            }

            for (int i = 0; i < numberOfPoints && allPointsAreInside; i++ )
            {
                QVector<double> currentPoint = m_pointsList.at( i );
                if ( currentPoint[0] >= maxX || currentPoint[0] <= minX || currentPoint[1] >= maxY || currentPoint[1] <= minY )
                    allPointsAreInside = false;
            }
            break;
        case Q2DViewer::SagitalPlane:
            if ( p1[2] < p2[2] )
            {
                minX = p1[2];
                maxX = p2[2];
            }
            else
            {
                maxX = p1[2];
                minX = p2[2];
            }

            if ( p1[1] < p2[1] )
            {
                minY = p1[1];
                maxY = p2[1];
            }
            else
            {
                maxY = p1[1];
                minY = p2[1];
            }

            for (int i = 0; i < numberOfPoints && allPointsAreInside; i++ )
            {
                QVector<double> currentPoint = m_pointsList.at( i );
                if ( currentPoint[2] >= maxX || currentPoint[2] <= minX || currentPoint[1] >= maxY || currentPoint[1] <= minY )
                    allPointsAreInside = false;
            }
            break;
        case Q2DViewer::CoronalPlane:
            if ( p1[0] < p2[0] )
            {
                minX = p1[0];
                maxX = p2[0];
            }
            else
            {
                maxX = p1[0];
                minX = p2[0];
            }

            if ( p1[2] < p2[2] )
            {
                minY = p1[2];
                maxY = p2[2];
            }
            else
            {
                maxY = p1[2];
                minY = p2[2];
            }
            for (int i = 0; i < numberOfPoints && allPointsAreInside; i++ )
            {
                QVector<double> currentPoint = m_pointsList.at( i );
                if ( currentPoint[0] >= maxX || currentPoint[0] <= minX || currentPoint[2] >= maxY || currentPoint[2] <= minY )
                    allPointsAreInside = false;
            }
            break;
    }

    return ( allPointsAreInside );
}

double DrawerPolygon::computeArea( int view )
{
    // Mètode extret de http://alienryderflex.com/polygon_area/
    
    // Obtenim els índexs x,y depenent de la vista en que estan projectats els punts
    // TODO eliminar aquesta dependència amb la vista del 2D Viewer
    int xIndex, yIndex;
    switch( view )
    {
        case Q2DViewer::Axial:
            xIndex = 0;
            yIndex = 1;
            break;

        case Q2DViewer::Sagital:
            xIndex = 2;
            yIndex = 1;
            break;

        case Q2DViewer::Coronal:
            xIndex = 0;
            yIndex = 2;
            break;
    }

    // Realitzem el càlcul de l'àrea
    double area = 0.0;
    int j = 0;
    int numberOfPoints = m_pointsList.count();
    for( int i=0; i<numberOfPoints; i++ ) 
    {
        j++; 
        if( j == numberOfPoints ) 
            j = 0;
    
        area += (m_pointsList.at(i)[xIndex] + m_pointsList.at(j)[xIndex]) * (m_pointsList.at(i)[yIndex] - m_pointsList.at(j)[yIndex]);
    }

    // En el cas de que l'àrea de la polilínia ens doni negativa, vol dir que hem anotat els punts en sentit antihorari,
    // per això cal girar-los per tenir una disposició correcta. Cal girar-ho del vtkPoints i de la QList de la ROI
    if ( area < 0 )
    {
        // Donem el resultat el valor absolut
        area *= -1;
        // Intercanviem els punts de la QList
        // TODO Cal realment fer això?
        for ( int i = 0; i < (int)(numberOfPoints/2); i++ )
            m_pointsList.swap( i, (numberOfPoints-1)-i );
    }

    return area*0.5;
}

}
