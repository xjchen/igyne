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
  and was partially funded by NIH grant P41EB015898, P41RR019703, R03EB013792, and U54EB005149.

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

//// VTK includes
//#include <vtkActor.h>
//#include <vtkPoints.h>
//#include <vtkSmartPointer.h>
//#include <vtkPolyData.h>
//#include <vtkMRMLModelNode.h>

// ITK includes
//#include <itkPointSet.h>

class qSlicerIgyneModuleWidgetPrivate;
//class vtkMRMLNode;

/// \ingroup Slicer_QtModules_Igyne
class Q_SLICER_QTMODULES_IGYNE_EXPORT qSlicerIgyneModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:
  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerIgyneModuleWidget(QWidget *parent=0);
  virtual ~qSlicerIgyneModuleWidget();

protected:
  QScopedPointer<qSlicerIgyneModuleWidgetPrivate> d_ptr;  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerIgyneModuleWidget);
  Q_DISABLE_COPY(qSlicerIgyneModuleWidget);
};

#endif
