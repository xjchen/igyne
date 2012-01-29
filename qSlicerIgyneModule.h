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

#ifndef __qSlicerIgyneModule_h
#define __qSlicerIgyneModule_h

// SlicerQt includes
#include "qSlicerLoadableModule.h"

#include "qSlicerIgyneModuleExport.h"

class qSlicerIgyneModulePrivate;

/// \ingroup Slicer_QtModules_Igyne
class Q_SLICER_QTMODULES_IGYNE_EXPORT qSlicerIgyneModule :
  public qSlicerLoadableModule
{
  Q_OBJECT
  Q_INTERFACES(qSlicerLoadableModule);

public:

  typedef qSlicerLoadableModule Superclass;
  explicit qSlicerIgyneModule(QObject *parent=0);
  virtual ~qSlicerIgyneModule();

  qSlicerGetTitleMacro(QTMODULE_TITLE);
  
  virtual QString helpText()const;
  virtual QString acknowledgementText()const;
  virtual QStringList contributors()const;
  
  /// Return a custom icon for the module
  virtual QIcon icon()const;

  /// Return the category for the module
  virtual QString category()const;

protected:

  /// Initialize the module. Register the volumes reader/writer
  virtual void setup();

  /// Create and return the widget representation associated to this module
  virtual qSlicerAbstractModuleRepresentation * createWidgetRepresentation();

  /// Create and return the logic associated to this module
  virtual vtkMRMLAbstractLogic* createLogic();

protected:
  QScopedPointer<qSlicerIgyneModulePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerIgyneModule);
  Q_DISABLE_COPY(qSlicerIgyneModule);

};

#endif
