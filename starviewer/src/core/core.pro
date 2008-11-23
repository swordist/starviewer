# Fitxer generat pel gestor de qmake de kdevelop. 
# ------------------------------------------- 
# Subdirectori relatiu al directori principal del projecte: ./src/core
# L'objectiu �s una biblioteca:  

FORMS += qlogviewerbase.ui \
         qcustomwindowleveldialogbase.ui \
         qdicomdumpbase.ui \
         qdicomdumpcthelixwidgetbase.ui \
         qdicomdumpctlocalizerwidgetbase.ui \
         qdicomdumpmrwidgetbase.ui \
         qdicomdumpctwidgetbase.ui \
         qtransferfunctioneditorbyvaluesbase.ui \
         qtransferfunctionintervaleditorbase.ui \
         qcinecontrollerbase.ui \
         qthickslabwidgetbase.ui \
         q2dviewerwidgetbase.ui 
TRANSLATIONS += core_ca_ES.ts \
                core_es_ES.ts \
                core_en_GB.ts 
HEADERS += extensionfactory.h \
           genericfactory.h \
           singleton.h \
           genericsingletonfactoryregister.h \
           extensionfactoryregister.h \
           extensionmediator.h \
           extensionmanager.h \
           displayableid.h \
           extensionmediatorfactory.h \
           extensionmediatorfactoryregister.h \
           installextension.h \
           itkImageToVTKImageFilter.h \
           itkVTKImageToImageFilter.h \
           mathtools.h \
           itkQtAdaptor.h \
           harddiskinformation.h \
           logging.h \
           deletedirectory.h \
           volume.h \
           volumerepository.h \
           identifier.h \
           repositorybase.h \
           repository.h \
           q2dviewer.h \
           q3dmprviewer.h \
           q3dviewer.h \
           qviewer.h \
           patient.h \
           series.h \
           study.h \
           parameters.h \
           qinputparameters.h \
           oldtool.h \
           output.h \
           q3dorientationmarker.h \
           slicing2dtool.h \
           oldtoolmanager.h \
           q2dviewertoolmanager.h \
           toolsactionfactory.h \
           oldzoomtool.h \
           zoomtool.h \
           oldtranslatetool.h \
           qlogviewer.h \
           strokesegmentationmethod.h \
           itkErfcLevelSetFunction.h \
           itkErfcLevelSetImageFilter.h \
           itkVolumeCalculatorImageFilter.h \
           keyimagenotefilereader.h \
           keyimagenote.h \
           q2dviewerkeyimagenoteattacher.h \
           q2dviewerblackboard.h \
           vtkAtamaiPolyDataToImageStencil2.h \
           shutterfilter.h \
           q2dviewerpresentationstateattacher.h \
           image.h \
           dicomtagreader.h \
           patientfiller.h \
           patientfillerstep.h \
           patientfillerinput.h \
           dicomfileclassifierfillerstep.h \
           imagefillerstep.h \
           presentationstatefillerstep.h \
           extensioncontext.h \
           keyimagenotefillerstep.h \
           dcmdatasetcache.h \
           temporaldimensionfillerstep.h \
           dicomimagereader.h \
           dicomimagereaderitkgdcm.h \
           dicomimagereadervtk.h \
           dicomimagereaderdcmtk.h \
           patientbrowsermenu.h \
           patientbrowsermenubasicitem.h \
           patientbrowsermenuextendeditem.h \
           patientbrowsermenulist.h \
           colorpalette.h \
           qcustomwindowleveldialog.h \
           qwindowlevelcombobox.h \
           mhdfileclassifierstep.h \
           orderimagesfillerstep.h \
           toolregistry.h \
           toolmanager.h \
           toolconfiguration.h \
           tool.h \
           toolproxy.h \
           tooldata.h \
           referencelinestool.h \
           referencelinestooldata.h \
           imageplane.h \
           slicingtool.h \
           translatetool.h \
           oldwindowleveltool.h \
           oldseedtool.h \
           voxelinformationtool.h \
           windowleveltool.h \
           seedtool.h \
           rotate3dtool.h \
           screenshottool.h \
           synchronizetool.h \
           synchronizetooldata.h \
           windowlevelpresetstool.h \
           drawer.h \
           drawerprimitive.h \
           drawerpolygon.h \
           drawerline.h \
           drawertext.h \
           drawerpolyline.h \
           polylineroitool.h \
           distancetool.h \
           windowlevelpresetstooldata.h \
           qviewercinecontroller.h \
           qdicomdumpcthelixwidget.h \
           qdicomdumpctlocalizerwidget.h \
           qdicomdump.h \
           qdicomdumpmrwidget.h \
           qdicomdumpctwidget.h \
           qcinecontroller.h \
           hoverpoints.h \
           qcolorspinbox.h \
           qtransferfunctioneditorbyvalues.h \
           qtransferfunctionintervaleditor.h \
           shadewidget.h \
           transferfunction.h \
           transferfunctionio.h \
           qtransferfunctioneditor.h \
           qtransferfunctioneditorbygradient.h \
           accumulator.h \
           averageaccumulator.h \
           minimumaccumulator.h \
           maximumaccumulator.h \
           vtkProjectionImageFilter.h \
           slicingkeyboardtool.h \
           qthickslabwidget.h \
           erasertool.h \
           patientitem.h \
           patientitemmodel.h \
           drawerpoint.h \
           seedtooldata.h \
           cursor3dtool.h \
           cursor3dtooldata.h \
           angletool.h \
           drawercrosshair.h \
           starviewerapplication.h \
           viewerslayout.h \
           q2dviewerwidget.h \
           hangingprotocol.h \
           hangingprotocollayout.h \
           hangingprotocolsloader.h \
           hangingprotocolsrepository.h \
           hangingprotocolmanager.h \
           hangingprotocolmask.h \
           hangingprotocolimageset.h \
           hangingprotocoldisplayset.h \
           hangingprotocolxmlreader.h \
           ambientvoxelshader.h \
           contourvoxelshader.h \
           directilluminationvoxelshader.h \
           voxelshader.h \
           hdrcolor.h \
           trilinearinterpolator.h \
           vector3.h \
           vtkVolumeRayCastVoxelShaderCompositeFunction.h \
           sphereuniformpointcloudgenerator.h \
           obscurancemainthread.h \
           obscurancethread.h \
           obscurancevoxelshader.h \
           vtk4DLinearRegressionGradientEstimator.h \
           combiningvoxelshader.h \
           vtkVolumeRayCastSingleVoxelShaderCompositeFunction.h \
           obscurance.h \
           viewpointgenerator.h \
           thumbnailcreator.h \
 abortrendercommand.h
SOURCES += extensionmediator.cpp \
           extensionmanager.cpp \
           displayableid.cpp \
           mathtools.cpp \
           harddiskinformation.cpp \
           deletedirectory.cpp \
           volume.cpp \
           volumerepository.cpp \
           identifier.cpp \
           repositorybase.cpp \
           repository.cpp \
           q2dviewer.cpp \
           q3dmprviewer.cpp \
           q3dviewer.cpp \
           qviewer.cpp \
           patient.cpp \
           series.cpp \
           study.cpp \
           parameters.cpp \
           qinputparameters.cpp \
           oldtool.cpp \
           output.cpp \
           q3dorientationmarker.cpp \
           slicing2dtool.cpp \
           oldtoolmanager.cpp \
           q2dviewertoolmanager.cpp \
           toolsactionfactory.cpp \
           oldzoomtool.cpp \
           zoomtool.cpp \
           oldtranslatetool.cpp \
           qlogviewer.cpp \
           strokesegmentationmethod.cpp \
           itkErfcLevelSetFunction.cpp \
           itkErfcLevelSetImageFilter.cpp \
           itkVolumeCalculatorImageFilter.cpp \
           keyimagenote.cpp \
           keyimagenotefilereader.cpp \
           q2dviewerkeyimagenoteattacher.cpp \
           q2dviewerblackboard.cpp \
           vtkAtamaiPolyDataToImageStencil2.cxx \
           shutterfilter.cpp \
           q2dviewerpresentationstateattacher.cpp \
           image.cpp \
           dicomtagreader.cpp \
           patientfiller.cpp \
           patientfillerstep.cpp \
           patientfillerinput.cpp \
           dicomfileclassifierfillerstep.cpp \
           imagefillerstep.cpp \
           presentationstatefillerstep.cpp \
           extensioncontext.cpp \
           keyimagenotefillerstep.cpp \
           dcmdatasetcache.cpp \
           temporaldimensionfillerstep.cpp \
           dicomimagereader.cpp \
           dicomimagereaderitkgdcm.cpp \
           dicomimagereadervtk.cpp \
           dicomimagereaderdcmtk.cpp \
           patientbrowsermenu.cpp \
           patientbrowsermenubasicitem.cpp \
           patientbrowsermenuextendeditem.cpp \
           patientbrowsermenulist.cpp \
           colorpalette.cpp \
           qcustomwindowleveldialog.cpp \
           qwindowlevelcombobox.cpp \
           mhdfileclassifierstep.cpp \
           orderimagesfillerstep.cpp \
           toolregistry.cpp \
           toolmanager.cpp \
           toolconfiguration.cpp \
           tool.cpp \
           toolproxy.cpp \
           tooldata.cpp \
           referencelinestool.cpp \
           referencelinestooldata.cpp \
           imageplane.cpp \
           translatetool.cpp \
           slicingtool.cpp \
           oldwindowleveltool.cpp \
           oldseedtool.cpp \
           voxelinformationtool.cpp \
           windowleveltool.cpp \
           seedtool.cpp \
           rotate3dtool.cpp \
           screenshottool.cpp \
           synchronizetool.cpp \
           synchronizetooldata.cpp \
           windowlevelpresetstool.cpp \
           drawer.cpp \
           drawerprimitive.cpp \
           drawerpolygon.cpp \
           drawerline.cpp \
           drawertext.cpp \
           drawerpolyline.cpp \
           polylineroitool.cpp \
           distancetool.cpp \
           windowlevelpresetstooldata.cpp \
           qviewercinecontroller.cpp \
           qdicomdump.cpp \
           qdicomdumpcthelixwidget.cpp \
           qdicomdumpctlocalizerwidget.cpp \
           qdicomdumpmrwidget.cpp \
           qdicomdumpctwidget.cpp \
           qcinecontroller.cpp \
           hoverpoints.cpp \
           qcolorspinbox.cpp \
           qtransferfunctioneditorbyvalues.cpp \
           qtransferfunctionintervaleditor.cpp \
           shadewidget.cpp \
           transferfunction.cpp \
           transferfunctionio.cpp \
           qtransferfunctioneditor.cpp \
           qtransferfunctioneditorbygradient.cpp \
           accumulator.cpp \
           vtkProjectionImageFilter.cxx \
           slicingkeyboardtool.cpp \
           qthickslabwidget.cpp \
           erasertool.cpp \
           patientitem.cpp \
           patientitemmodel.cpp \
           drawerpoint.cpp \
           seedtooldata.cpp \
           cursor3dtool.cpp \
           cursor3dtooldata.cpp \
           angletool.cpp \
           drawercrosshair.cpp \
           viewerslayout.cpp \
           q2dviewerwidget.cpp \
           hangingprotocol.cpp \
           hangingprotocollayout.cpp \
           hangingprotocolsloader.cpp \
           hangingprotocolsrepository.cpp \
           hangingprotocolmanager.cpp \
           hangingprotocolmask.cpp \
           hangingprotocolimageset.cpp \
           hangingprotocoldisplayset.cpp \
           hangingprotocolxmlreader.cpp \
           ambientvoxelshader.cpp \
           contourvoxelshader.cpp \
           directilluminationvoxelshader.cpp \
           voxelshader.cpp \
           trilinearinterpolator.cpp \
           vtkVolumeRayCastVoxelShaderCompositeFunction.cxx \
           sphereuniformpointcloudgenerator.cpp \
           obscurancemainthread.cpp \
           obscurancethread.cpp \
           obscurancevoxelshader.cpp \
           vtk4DLinearRegressionGradientEstimator.cxx \
           combiningvoxelshader.cpp \
           vtkVolumeRayCastSingleVoxelShaderCompositeFunction.cxx \
           obscurance.cpp \
           viewpointgenerator.cpp  \
           thumbnailcreator.cpp \
 abortrendercommand.cpp
TEMPLATE = lib
DESTDIR = ./
include(../corelibsconfiguration.inc)
include(../itk.inc)
include(../vtk.inc)
include(../dcmtk.inc)
include(../log4cxx.inc)
include(../compilationtype.inc)
include(../translations.inc)
QT += xml
