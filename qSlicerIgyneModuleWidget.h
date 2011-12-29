/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Xiaojun Chen, SPL.

==============================================================================*/

#ifndef __qSlicerIgyneModuleWidget_h
#define __qSlicerIgyneModuleWidget_h

// Qt includes
//#include <QFileDialog>
#include <QtGui/QMainWindow>
#include <QtGui>

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerIgyneModuleExport.h"

// VTK includes
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>

// ITK includes
#include <itkPointSet.h>

class qSlicerIgyneModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_Igyne
class Q_SLICER_QTMODULES_IGYNE_EXPORT qSlicerIgyneModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerIgyneModuleWidget(QWidget *parent=0);
  virtual ~qSlicerIgyneModuleWidget();

public slots:
  void loadTemplate();
  void showIuNeedle();
  void showAaNeedle();
  void showAbNeedle();
  void showAcNeedle();
  void showAdNeedle();
  void showAeNeedle();
  void showAfNeedle();
  void showBaNeedle();
  void showBbNeedle();
  void showBcNeedle();
  void showBdNeedle();
  void showBeNeedle();
  void showBfNeedle();
  void showBgNeedle();
  void showBhNeedle();
  void showBiNeedle();
  void showBjNeedle();
  void showBkNeedle();
  void showBlNeedle();
  void showCaNeedle();
  void showCbNeedle();
  void showCcNeedle();
  void showCdNeedle();
  void showCeNeedle();
  void showCfNeedle();
  void showCgNeedle();
  void showChNeedle();
  void showCiNeedle();
  void showCjNeedle();
  void showCkNeedle();
  void showClNeedle();
  void showCmNeedle();
  void showCnNeedle();
  void showCoNeedle();
  void showCpNeedle();
  void showCqNeedle();
  void showCrNeedle();
  void showDaNeedle();
  void showDbNeedle();
  void showDcNeedle();
  void showDdNeedle();
  void showDeNeedle();
  void showDfNeedle();
  void showDgNeedle();
  void showDhNeedle();
  void showDiNeedle();
  void showDjNeedle();
  void showEaNeedle();
  void showEbNeedle();
  void showEcNeedle();
  void showEdNeedle();
  void showEeNeedle();
  void showEfNeedle();
  void showEgNeedle();
  void showEhNeedle();
  void registerNeedles();
  void hideNeedles();
  void addVolume();
  void registerCADmodelToImage();
  void pushIuNeedle(int nDepth);
  void pushAaNeedle(int nDepth);
  void pushAbNeedle(int nDepth);
  void pushAcNeedle(int nDepth);
  void pushAdNeedle(int nDepth);
  void pushAeNeedle(int nDepth);
  void pushAfNeedle(int nDepth);
  void pushBaNeedle(int nDepth);
  void pushBbNeedle(int nDepth);
  void pushBcNeedle(int nDepth);
  void pushBdNeedle(int nDepth);
  void pushBeNeedle(int nDepth);
  void pushBfNeedle(int nDepth);
  void pushBgNeedle(int nDepth);
  void pushBhNeedle(int nDepth);
  void pushBiNeedle(int nDepth);
  void pushBjNeedle(int nDepth);
  void pushBkNeedle(int nDepth);
  void pushBlNeedle(int nDepth);
  void pushCaNeedle(int nDepth);
  void pushCbNeedle(int nDepth);
  void pushCcNeedle(int nDepth);
  void pushCdNeedle(int nDepth);
  void pushCeNeedle(int nDepth);
  void pushCfNeedle(int nDepth);
  void pushCgNeedle(int nDepth);
  void pushChNeedle(int nDepth);
  void pushCiNeedle(int nDepth);
  void pushCjNeedle(int nDepth);
  void pushCkNeedle(int nDepth);
  void pushClNeedle(int nDepth);
  void pushCmNeedle(int nDepth);
  void pushCnNeedle(int nDepth);
  void pushCoNeedle(int nDepth);
  void pushCpNeedle(int nDepth);
  void pushCqNeedle(int nDepth);
  void pushCrNeedle(int nDepth);
  void pushDaNeedle(int nDepth);
  void pushDbNeedle(int nDepth);
  void pushDcNeedle(int nDepth);
  void pushDdNeedle(int nDepth);
  void pushDeNeedle(int nDepth);
  void pushDfNeedle(int nDepth);
  void pushDgNeedle(int nDepth);
  void pushDhNeedle(int nDepth);
  void pushDiNeedle(int nDepth);
  void pushDjNeedle(int nDepth);
  void pushEaNeedle(int nDepth);
  void pushEbNeedle(int nDepth);
  void pushEcNeedle(int nDepth);
  void pushEdNeedle(int nDepth);
  void pushEeNeedle(int nDepth);
  void pushEfNeedle(int nDepth);
  void pushEgNeedle(int nDepth);
  void pushEhNeedle(int nDepth);

  void setIuColor();
  void setAaColor();
  void setAbColor();
  void setAcColor();
  void setAdColor();
  void setAeColor();
  void setAfColor();
  void setBaColor();
  void setBbColor();
  void setBcColor();
  void setBdColor();
  void setBeColor();
  void setBfColor();
  void setBgColor();
  void setBhColor();
  void setBiColor();
  void setBjColor();
  void setBkColor();
  void setBlColor();
  void setCaColor();
  void setCbColor();
  void setCcColor();
  void setCdColor();
  void setCeColor();
  void setCfColor();
  void setCgColor();
  void setChColor();
  void setCiColor();
  void setCjColor();
  void setCkColor();
  void setClColor();
  void setCmColor();
  void setCnColor();
  void setCoColor();
  void setCpColor();
  void setCqColor();
  void setCrColor();
  void setDaColor();
  void setDbColor();
  void setDcColor();
  void setDdColor();
  void setDeColor();
  void setDfColor();
  void setDgColor();
  void setDhColor();
  void setDiColor();
  void setDjColor();
  void setEaColor();
  void setEbColor();
  void setEcColor();
  void setEdColor();
  void setEeColor();
  void setEfColor();
  void setEgColor();
  void setEhColor();

protected:
  QScopedPointer<qSlicerIgyneModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

protected:
  vtkActor *LineActor[55];
  vtkActor *axesActor;
  void showOneNeedle(vtkActor *Actor,QRadioButton *RadioButton);
  void pushOneNeedle(int i, int nDepth);
  void setOneNeedleColor(int i,QPushButton *ColorPushButton);
  void setNeedleCoordinates(int i,vtkPoints *Points, double z1, double z2);

  typedef itk::PointSet< double, 3 > PointSetType;
  PointSetType::Pointer m_pointSet;
  void setPointData(double fHoleOriginX,double fHoleOriginY,vtkSmartPointer<vtkMatrix4x4> vtkmatInitial,
											unsigned int *pointId,PointSetType::Pointer pointSet);

private:
  Q_DECLARE_PRIVATE(qSlicerIgyneModuleWidget);
  Q_DISABLE_COPY(qSlicerIgyneModuleWidget);
};

#endif
