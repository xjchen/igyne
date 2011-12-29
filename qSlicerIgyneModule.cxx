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

// Qt includes
#include <QtPlugin>

// Igyne Logic includes
#include <vtkSlicerIgyneLogic.h>

// Igyne includes
#include "qSlicerIgyneModule.h"
#include "qSlicerIgyneModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerIgyneModule, qSlicerIgyneModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Igyne
class qSlicerIgyneModulePrivate
{
public:
  qSlicerIgyneModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerIgyneModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerIgyneModulePrivate::qSlicerIgyneModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerIgyneModule methods

//-----------------------------------------------------------------------------
qSlicerIgyneModule::qSlicerIgyneModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerIgyneModulePrivate)
{
}

//-----------------------------------------------------------------------------
QString qSlicerIgyneModule::category()const
{
  return "Developer Tools";
}

//-----------------------------------------------------------------------------
qSlicerIgyneModule::~qSlicerIgyneModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerIgyneModule::helpText()const
{
  QString help = 
    "This module is used for Image-guided gynecology.";
  return help;
}

//-----------------------------------------------------------------------------
QString qSlicerIgyneModule::acknowledgementText()const
{
  return "This work was supported by NAMIC, NAC, and the Slicer Community...";
}

//-----------------------------------------------------------------------------
QIcon qSlicerIgyneModule::icon()const
{
  return QIcon(":/Icons/Igyne.png");
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerIgyneModule::createWidgetRepresentation()
{
  return new qSlicerIgyneModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerIgyneModule::createLogic()
{
  return vtkSlicerIgyneLogic::New();
}
