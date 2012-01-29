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
    "This module is used for MR-guided gynecologic brachytherapy.<br>"
		"For more information see: <a href=\"http://www.na-mic.org/Wiki/index.php/2012_Summer_Project_Week:iGyne\">iGyne</a> <br>";
  return help;
}

//-----------------------------------------------------------------------------
QString qSlicerIgyneModule::acknowledgementText()const
{
  QString acknowledgement =
    "This work was partially funded by NIH grant P41EB015898, P41RR019703, R03EB013792, and U54EB005149."
    "<br>"
    "See <a href=\"http://www.na-mic.org/Wiki/index.php/2012_Summer_Project_Week:iGyne\">iGyne</a> for details.<br>"
    "The module was contributed by Xiaojun Chen (SPL, BWH), "
    "with help from Jan Egger (SPL, BWH),Tina Kapur (SPL, BWH),Akila Viswanathan (BWH) and Steve Pieper (Isomics). ";
  return acknowledgement;
}

//-----------------------------------------------------------------------------
QStringList qSlicerIgyneModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Xiaojun Chen (SPL, BWH)");
	moduleContributors << QString("Jan Egger (SPL, BWH)");
	moduleContributors << QString("Tina Kapur (SPL, BWH)");
	moduleContributors << QString("Akila Viswanathan (BWH)");
  moduleContributors << QString("Steve Pieper (Isomics)");  
  return moduleContributors;
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
