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
#include <QFileDialog>
#include <QtGui/QMainWindow>
#include <QtGui>

// SlicerQt includes
#include "qSlicerIgyneModuleWidget.h"
#include "qSlicerApplication.h"
#include "qSlicerIOManager.h"
#include "qSlicerLayoutManager.h"
#include "ui_qSlicerIgyneModule.h"

// MRML includes
#include <vtkMRMLLinearTransformNode.h>
#include <vtkMRMLModelNode.h>
#include <vtkMRMLScene.h>
#include <vtkMRMLAnnotationHierarchyNode.h>
#include <vtkMRMLModelNode.h>

// VTK includes
#include <vtkColorTransferFunction.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkProperty.h>
#include <vtkMatrix4x4.h>
#include <vtkPolyData.h>
#include <vtkAxes.h>
#include <vtkTubeFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkCylinderSource.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkTriangleFilter.h>
#include <vtkDelaunay3D.h>

// ITK includes
#include <itkImage.h>
#include <itkPointSetToImageRegistrationMethod.h>
#include <itkPointSet.h>
#include <itkVersorRigid3DTransform.h>
#include <itkVersorRigid3DTransformOptimizer.h>
#include <itkNormalizedCorrelationPointSetToImageMetric.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkImageFileReader.h>
#include <itkGradientMagnitudeImageFilter.h>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Igyne
class qSlicerIgyneModuleWidgetPrivate: public Ui_qSlicerIgyneModule
{
public:
  qSlicerIgyneModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerIgyneModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerIgyneModuleWidgetPrivate::qSlicerIgyneModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerIgyneModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerIgyneModuleWidget::qSlicerIgyneModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerIgyneModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerIgyneModuleWidget::~qSlicerIgyneModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::setup()
{
  Q_D(qSlicerIgyneModuleWidget);
  d->setupUi(this);

  this->connect(d->LoadTemplatePushButton, SIGNAL(clicked()),
                SLOT(loadTemplate()));
  this->connect(d->IuRadioButton, SIGNAL(clicked()),
                SLOT(showIuNeedle()));
  this->connect(d->AaRadioButton, SIGNAL(clicked()),
                SLOT(showAaNeedle()));
  this->connect(d->AbRadioButton, SIGNAL(clicked()),
                SLOT(showAbNeedle()));
  this->connect(d->AcRadioButton, SIGNAL(clicked()),
                SLOT(showAcNeedle()));
  this->connect(d->AdRadioButton, SIGNAL(clicked()),
                SLOT(showAdNeedle()));
  this->connect(d->AeRadioButton, SIGNAL(clicked()),
                SLOT(showAeNeedle()));
  this->connect(d->AfRadioButton, SIGNAL(clicked()),
                SLOT(showAfNeedle()));
  this->connect(d->BaRadioButton, SIGNAL(clicked()),
                SLOT(showBaNeedle()));
  this->connect(d->BbRadioButton, SIGNAL(clicked()),
                SLOT(showBbNeedle()));
  this->connect(d->BcRadioButton, SIGNAL(clicked()),
                SLOT(showBcNeedle()));
  this->connect(d->BdRadioButton, SIGNAL(clicked()),
                SLOT(showBdNeedle()));
  this->connect(d->BeRadioButton, SIGNAL(clicked()),
                SLOT(showBeNeedle()));
  this->connect(d->BfRadioButton, SIGNAL(clicked()),
                SLOT(showBfNeedle()));
  this->connect(d->BgRadioButton, SIGNAL(clicked()),
                SLOT(showBgNeedle()));
  this->connect(d->BhRadioButton, SIGNAL(clicked()),
                SLOT(showBhNeedle()));
  this->connect(d->BiRadioButton, SIGNAL(clicked()),
                SLOT(showBiNeedle()));
  this->connect(d->BjRadioButton, SIGNAL(clicked()),
                SLOT(showBjNeedle()));
  this->connect(d->BkRadioButton, SIGNAL(clicked()),
                SLOT(showBkNeedle()));
  this->connect(d->BlRadioButton, SIGNAL(clicked()),
                SLOT(showBlNeedle()));
  this->connect(d->CaRadioButton, SIGNAL(clicked()),
                SLOT(showCaNeedle()));
  this->connect(d->CbRadioButton, SIGNAL(clicked()),
                SLOT(showCbNeedle()));
  this->connect(d->CcRadioButton, SIGNAL(clicked()),
                SLOT(showCcNeedle()));
  this->connect(d->CdRadioButton, SIGNAL(clicked()),
                SLOT(showCdNeedle()));
  this->connect(d->CeRadioButton, SIGNAL(clicked()),
                SLOT(showCeNeedle()));
  this->connect(d->CfRadioButton, SIGNAL(clicked()),
                SLOT(showCfNeedle()));
  this->connect(d->CgRadioButton, SIGNAL(clicked()),
                SLOT(showCgNeedle()));
  this->connect(d->ChRadioButton, SIGNAL(clicked()),
                SLOT(showChNeedle()));
  this->connect(d->CiRadioButton, SIGNAL(clicked()),
                SLOT(showCiNeedle()));
  this->connect(d->CjRadioButton, SIGNAL(clicked()),
                SLOT(showCjNeedle()));
  this->connect(d->CkRadioButton, SIGNAL(clicked()),
                SLOT(showCkNeedle()));
  this->connect(d->ClRadioButton, SIGNAL(clicked()),
                SLOT(showClNeedle()));
  this->connect(d->CmRadioButton, SIGNAL(clicked()),
                SLOT(showCmNeedle()));
  this->connect(d->CnRadioButton, SIGNAL(clicked()),
                SLOT(showCnNeedle()));
  this->connect(d->CoRadioButton, SIGNAL(clicked()),
                SLOT(showCoNeedle()));
  this->connect(d->CpRadioButton, SIGNAL(clicked()),
                SLOT(showCpNeedle()));
  this->connect(d->CqRadioButton, SIGNAL(clicked()),
                SLOT(showCqNeedle()));
  this->connect(d->CrRadioButton, SIGNAL(clicked()),
                SLOT(showCrNeedle()));
  this->connect(d->DaRadioButton, SIGNAL(clicked()),
                SLOT(showDaNeedle()));
  this->connect(d->DbRadioButton, SIGNAL(clicked()),
                SLOT(showDbNeedle()));
  this->connect(d->DcRadioButton, SIGNAL(clicked()),
                SLOT(showDcNeedle()));
  this->connect(d->DdRadioButton, SIGNAL(clicked()),
                SLOT(showDdNeedle()));
  this->connect(d->DeRadioButton, SIGNAL(clicked()),
                SLOT(showDeNeedle()));
  this->connect(d->DfRadioButton, SIGNAL(clicked()),
                SLOT(showDfNeedle()));
  this->connect(d->DgRadioButton, SIGNAL(clicked()),
                SLOT(showDgNeedle()));
  this->connect(d->DhRadioButton, SIGNAL(clicked()),
                SLOT(showDhNeedle()));
  this->connect(d->DiRadioButton, SIGNAL(clicked()),
                SLOT(showDiNeedle()));
  this->connect(d->DjRadioButton, SIGNAL(clicked()),
                SLOT(showDjNeedle()));
  this->connect(d->EaRadioButton, SIGNAL(clicked()),
                SLOT(showEaNeedle()));
  this->connect(d->EbRadioButton, SIGNAL(clicked()),
                SLOT(showEbNeedle()));
  this->connect(d->EcRadioButton, SIGNAL(clicked()),
                SLOT(showEcNeedle()));
  this->connect(d->EdRadioButton, SIGNAL(clicked()),
                SLOT(showEdNeedle()));
  this->connect(d->EeRadioButton, SIGNAL(clicked()),
                SLOT(showEeNeedle()));
  this->connect(d->EfRadioButton, SIGNAL(clicked()),
                SLOT(showEfNeedle()));
  this->connect(d->EgRadioButton, SIGNAL(clicked()),
                SLOT(showEgNeedle()));
  this->connect(d->EhRadioButton, SIGNAL(clicked()),
                SLOT(showEhNeedle()));
   
  this->connect(d->RegisterNeedlesPushButton, SIGNAL(clicked()),
                SLOT(registerNeedles())); 
  this->connect(d->HideNeedlesPushButton, SIGNAL(clicked()),
                SLOT(hideNeedles()));
  this->connect(d->AddVolumePushButton, SIGNAL(clicked()),
                SLOT(addVolume())); 
  this->connect(d->CADmodel2ImageRegPushButton, SIGNAL(clicked()),
                SLOT(registerCADmodelToImage()));

  this->connect(d->IuSpinBox, SIGNAL(valueChanged(int)),
	            SLOT(pushIuNeedle(int)));
  this->connect(d->AaSpinBox, SIGNAL(valueChanged(int)),
	            SLOT(pushAaNeedle(int)));
  this->connect(d->AbSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushAbNeedle(int)));
  this->connect(d->AcSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushAcNeedle(int)));
  this->connect(d->AdSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushAdNeedle(int)));
  this->connect(d->AeSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushAeNeedle(int)));
  this->connect(d->AfSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushAfNeedle(int)));
  this->connect(d->BaSpinBox, SIGNAL(valueChanged(int)),
	            SLOT(pushBaNeedle(int)));
  this->connect(d->BbSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBbNeedle(int)));
  this->connect(d->BcSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBcNeedle(int)));
  this->connect(d->BdSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBdNeedle(int)));
  this->connect(d->BeSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBeNeedle(int)));
  this->connect(d->BfSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBfNeedle(int)));
  this->connect(d->BgSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBgNeedle(int)));
  this->connect(d->BhSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBhNeedle(int)));
  this->connect(d->BiSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBiNeedle(int)));
  this->connect(d->BjSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBjNeedle(int)));
  this->connect(d->BkSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBkNeedle(int)));
  this->connect(d->BlSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushBlNeedle(int)));
  this->connect(d->CaSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCaNeedle(int)));
  this->connect(d->CbSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCbNeedle(int)));
  this->connect(d->CcSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCcNeedle(int)));
  this->connect(d->CdSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCdNeedle(int)));
  this->connect(d->CeSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCeNeedle(int)));
  this->connect(d->CfSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCfNeedle(int)));
  this->connect(d->CgSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCgNeedle(int)));
  this->connect(d->ChSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushChNeedle(int)));
  this->connect(d->CiSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCiNeedle(int)));
  this->connect(d->CjSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCjNeedle(int)));
  this->connect(d->CkSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCkNeedle(int)));
  this->connect(d->ClSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushClNeedle(int)));
  this->connect(d->CmSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCmNeedle(int)));
  this->connect(d->CnSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCnNeedle(int)));
  this->connect(d->CoSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCoNeedle(int)));
  this->connect(d->CpSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCpNeedle(int)));
  this->connect(d->CqSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCqNeedle(int)));
  this->connect(d->CrSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushCrNeedle(int)));
  this->connect(d->DaSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDaNeedle(int)));
  this->connect(d->DbSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDbNeedle(int)));
  this->connect(d->DcSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDcNeedle(int)));
  this->connect(d->DdSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDdNeedle(int)));
  this->connect(d->DeSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDeNeedle(int)));
  this->connect(d->DfSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDfNeedle(int)));
  this->connect(d->DgSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDgNeedle(int)));
  this->connect(d->DhSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDhNeedle(int)));
  this->connect(d->DiSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDiNeedle(int)));
  this->connect(d->DjSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushDjNeedle(int)));
  this->connect(d->EaSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEaNeedle(int)));
  this->connect(d->EbSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEbNeedle(int)));
  this->connect(d->EcSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEcNeedle(int)));
  this->connect(d->EdSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEdNeedle(int)));
  this->connect(d->EeSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEeNeedle(int)));
  this->connect(d->EfSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEfNeedle(int)));
  this->connect(d->EgSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEgNeedle(int)));
  this->connect(d->EhSpinBox, SIGNAL(valueChanged(int)),
                SLOT(pushEhNeedle(int)));


  this->connect(d->IuColorPushButton, SIGNAL(clicked()),
	            SLOT(setIuColor()));
  this->connect(d->AaColorPushButton, SIGNAL(clicked()),
	            SLOT(setAaColor()));
  this->connect(d->AbColorPushButton, SIGNAL(clicked()),
                SLOT(setAbColor()));
  this->connect(d->AcColorPushButton, SIGNAL(clicked()),
                SLOT(setAcColor()));
  this->connect(d->AdColorPushButton, SIGNAL(clicked()),
                SLOT(setAdColor()));
  this->connect(d->AeColorPushButton, SIGNAL(clicked()),
                SLOT(setAeColor()));
  this->connect(d->AfColorPushButton, SIGNAL(clicked()),
                SLOT(setAfColor()));
  this->connect(d->BaColorPushButton, SIGNAL(clicked()),
	            SLOT(setBaColor()));
  this->connect(d->BbColorPushButton, SIGNAL(clicked()),
                SLOT(setBbColor()));
  this->connect(d->BcColorPushButton, SIGNAL(clicked()),
                SLOT(setBcColor()));
  this->connect(d->BdColorPushButton, SIGNAL(clicked()),
                SLOT(setBdColor()));
  this->connect(d->BeColorPushButton, SIGNAL(clicked()),
                SLOT(setBeColor()));
  this->connect(d->BfColorPushButton, SIGNAL(clicked()),
                SLOT(setBfColor()));
  this->connect(d->BgColorPushButton, SIGNAL(clicked()),
                SLOT(setBgColor()));
  this->connect(d->BhColorPushButton, SIGNAL(clicked()),
                SLOT(setBhColor()));
  this->connect(d->BiColorPushButton, SIGNAL(clicked()),
                SLOT(setBiColor()));
  this->connect(d->BjColorPushButton, SIGNAL(clicked()),
                SLOT(setBjColor()));
  this->connect(d->BkColorPushButton, SIGNAL(clicked()),
                SLOT(setBkColor()));
  this->connect(d->BlColorPushButton, SIGNAL(clicked()),
                SLOT(setBlColor()));
  this->connect(d->CaColorPushButton, SIGNAL(clicked()),
                SLOT(setCaColor()));
  this->connect(d->CbColorPushButton, SIGNAL(clicked()),
                SLOT(setCbColor()));
  this->connect(d->CcColorPushButton, SIGNAL(clicked()),
                SLOT(setCcColor()));
  this->connect(d->CdColorPushButton, SIGNAL(clicked()),
                SLOT(setCdColor()));
  this->connect(d->CeColorPushButton, SIGNAL(clicked()),
                SLOT(setCeColor()));
  this->connect(d->CfColorPushButton, SIGNAL(clicked()),
                SLOT(setCfColor()));
  this->connect(d->CgColorPushButton, SIGNAL(clicked()),
                SLOT(setCgColor()));
  this->connect(d->ChColorPushButton, SIGNAL(clicked()),
                SLOT(setChColor()));
  this->connect(d->CiColorPushButton, SIGNAL(clicked()),
                SLOT(setCiColor()));
  this->connect(d->CjColorPushButton, SIGNAL(clicked()),
                SLOT(setCjColor()));
  this->connect(d->CkColorPushButton, SIGNAL(clicked()),
                SLOT(setCkColor()));
  this->connect(d->ClColorPushButton, SIGNAL(clicked()),
                SLOT(setClColor()));
  this->connect(d->CmColorPushButton, SIGNAL(clicked()),
                SLOT(setCmColor()));
  this->connect(d->CnColorPushButton, SIGNAL(clicked()),
                SLOT(setCnColor()));
  this->connect(d->CoColorPushButton, SIGNAL(clicked()),
                SLOT(setCoColor()));
  this->connect(d->CpColorPushButton, SIGNAL(clicked()),
                SLOT(setCpColor()));
  this->connect(d->CqColorPushButton, SIGNAL(clicked()),
                SLOT(setCqColor()));
  this->connect(d->CrColorPushButton, SIGNAL(clicked()),
                SLOT(setCrColor()));
  this->connect(d->DaColorPushButton, SIGNAL(clicked()),
                SLOT(setDaColor()));
  this->connect(d->DbColorPushButton, SIGNAL(clicked()),
                SLOT(setDbColor()));
  this->connect(d->DcColorPushButton, SIGNAL(clicked()),
                SLOT(setDcColor()));
  this->connect(d->DdColorPushButton, SIGNAL(clicked()),
                SLOT(setDdColor()));
  this->connect(d->DeColorPushButton, SIGNAL(clicked()),
                SLOT(setDeColor()));
  this->connect(d->DfColorPushButton, SIGNAL(clicked()),
                SLOT(setDfColor()));
  this->connect(d->DgColorPushButton, SIGNAL(clicked()),
                SLOT(setDgColor()));
  this->connect(d->DhColorPushButton, SIGNAL(clicked()),
                SLOT(setDhColor()));
  this->connect(d->DiColorPushButton, SIGNAL(clicked()),
                SLOT(setDiColor()));
  this->connect(d->DjColorPushButton, SIGNAL(clicked()),
                SLOT(setDjColor()));
  this->connect(d->EaColorPushButton, SIGNAL(clicked()),
                SLOT(setEaColor()));
  this->connect(d->EbColorPushButton, SIGNAL(clicked()),
                SLOT(setEbColor()));
  this->connect(d->EcColorPushButton, SIGNAL(clicked()),
                SLOT(setEcColor()));
  this->connect(d->EdColorPushButton, SIGNAL(clicked()),
                SLOT(setEdColor()));
  this->connect(d->EeColorPushButton, SIGNAL(clicked()),
                SLOT(setEeColor()));
  this->connect(d->EfColorPushButton, SIGNAL(clicked()),
                SLOT(setEfColor()));
  this->connect(d->EgColorPushButton, SIGNAL(clicked()),
                SLOT(setEgColor()));
  this->connect(d->EhColorPushButton, SIGNAL(clicked()),
                SLOT(setEhColor())); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::loadTemplate()
{
  Q_D(qSlicerIgyneModuleWidget);

  qSlicerApplication * app = qSlicerApplication::application();
  
  if(app->ioManager()->openLoadSceneDialog())
    {
	if (app->layoutManager())
		{    
		vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
		if (activeRenderer)
			{
			for(int i=0; i<55; i++)
				{
				vtkPoints *Points=vtkPoints::New();
				vtkLine *Line=vtkLine::New();
				vtkUnstructuredGrid *LineGrid=vtkUnstructuredGrid::New();
				vtkDataSetMapper *LineMapper=vtkDataSetMapper::New() ;
				LineActor[i]=vtkActor::New() ;

				Points->SetNumberOfPoints(2);
				setNeedleCoordinates(i,Points,30.0f,-150.0f);

				LineActor[i]->GetProperty()->SetDiffuseColor(0,1,0);

				Line->GetPointIds()->SetNumberOfIds(2);
				Line->GetPointIds()->SetId(0, 0);
				Line->GetPointIds()->SetId(1, 1);
				Line->GetPoints()->SetNumberOfPoints(2);

				LineGrid->Allocate(1, 1);
				LineGrid->InsertNextCell(Line->GetCellType(),Line->GetPointIds());
				LineGrid->SetPoints(Points);

				LineMapper->SetInput(LineGrid);		
				LineActor[i]->SetMapper(LineMapper);
				LineActor[i]->VisibilityOff();
				activeRenderer->AddActor(LineActor[i]);			  

				Points->Delete();
				Line->Delete();
				LineGrid->Delete();
				LineMapper->Delete();			  
				}			

			d->RegisterNeedlesPushButton->setEnabled(true);
			d->HideNeedlesPushButton->setEnabled(true);
			d->IuRadioButton->setEnabled(true);
			d->AaRadioButton->setEnabled(true);
			d->AbRadioButton->setEnabled(true);
			d->AcRadioButton->setEnabled(true);
			d->AdRadioButton->setEnabled(true);
			d->AeRadioButton->setEnabled(true);
			d->AfRadioButton->setEnabled(true);
			d->BaRadioButton->setEnabled(true);
			d->BbRadioButton->setEnabled(true);
			d->BcRadioButton->setEnabled(true);
			d->BdRadioButton->setEnabled(true);
			d->BeRadioButton->setEnabled(true);
			d->BfRadioButton->setEnabled(true);
			d->BgRadioButton->setEnabled(true);
			d->BhRadioButton->setEnabled(true);
			d->BiRadioButton->setEnabled(true);
			d->BjRadioButton->setEnabled(true);
			d->BkRadioButton->setEnabled(true);
			d->BlRadioButton->setEnabled(true);
			d->CaRadioButton->setEnabled(true);
			d->CbRadioButton->setEnabled(true);
			d->CcRadioButton->setEnabled(true);
			d->CdRadioButton->setEnabled(true);
			d->CeRadioButton->setEnabled(true);
			d->CfRadioButton->setEnabled(true);
			d->CgRadioButton->setEnabled(true);
			d->ChRadioButton->setEnabled(true);
			d->CiRadioButton->setEnabled(true);
			d->CjRadioButton->setEnabled(true);
			d->CkRadioButton->setEnabled(true);
			d->ClRadioButton->setEnabled(true);
			d->CmRadioButton->setEnabled(true);
			d->CnRadioButton->setEnabled(true);
			d->CoRadioButton->setEnabled(true);
			d->CpRadioButton->setEnabled(true);
			d->CqRadioButton->setEnabled(true);
			d->CrRadioButton->setEnabled(true);
			d->DaRadioButton->setEnabled(true);
			d->DbRadioButton->setEnabled(true);
			d->DcRadioButton->setEnabled(true);
			d->DdRadioButton->setEnabled(true);
			d->DeRadioButton->setEnabled(true);
			d->DfRadioButton->setEnabled(true);
			d->DgRadioButton->setEnabled(true);
			d->DhRadioButton->setEnabled(true);
			d->DiRadioButton->setEnabled(true);
			d->DjRadioButton->setEnabled(true);
			d->EaRadioButton->setEnabled(true);
			d->EbRadioButton->setEnabled(true);
			d->EcRadioButton->setEnabled(true);
			d->EdRadioButton->setEnabled(true);
			d->EeRadioButton->setEnabled(true);
			d->EfRadioButton->setEnabled(true);
			d->EgRadioButton->setEnabled(true);
			d->EhRadioButton->setEnabled(true);
			}    
		}
	}
}

void qSlicerIgyneModuleWidget::setNeedleCoordinates(int i,vtkPoints *Points, double z1, double z2)
{
	switch(i)
	{
	case 0:
		{
		  Points->InsertPoint(0,35,34,z1);
		  Points->InsertPoint(1,35,34,z2);
		}
		break;
	case 1:
		{
		  Points->InsertPoint(0,25,36.679,z1);
		  Points->InsertPoint(1,25,36.679,z2);
		}
		break;
	case 2:
		{
		  Points->InsertPoint(0,17.679,44,z1);
		  Points->InsertPoint(1,17.679,44,z2);
		}
		break;
	case 3:
		{
		  Points->InsertPoint(0,15,54,z1);
		  Points->InsertPoint(1,15,54,z2);
		}
		break;
	case 4:
		{
		  Points->InsertPoint(0,17.679,64,z1);
		  Points->InsertPoint(1,17.679,64,z2);
		}
		break;
	case 5:
		{
		  Points->InsertPoint(0,25,71.321,z1);
		  Points->InsertPoint(1,25,71.321,z2);
		}
		break;
	case 6:
		{
		  Points->InsertPoint(0,35,74,z1);
		  Points->InsertPoint(1,35,74,z2);
		}
		break;
	case 7:
		{
		  Points->InsertPoint(0,45,71.321,z1);
		  Points->InsertPoint(1,45,71.321,z2);
		}
		break;
	case 8:
		{
		  Points->InsertPoint(0,52.321,64,z1);
		  Points->InsertPoint(1,52.321,64,z2);
		}
		break;
	case 9:
		{
		  Points->InsertPoint(0,55,54,z1);
		  Points->InsertPoint(1,55,54,z2);
		}
		break;
	case 10:
		{
		  Points->InsertPoint(0,52.321,44,z1);
		  Points->InsertPoint(1,52.321,44,z2);
		}
		break;
	case 11:
		{
		  Points->InsertPoint(0,45,36.679,z1);
		  Points->InsertPoint(1,45,36.679,z2);
		}
		break;		
	case 12:
		{
		  Points->InsertPoint(0,29.791,24.456,z1);
		  Points->InsertPoint(1,29.791,24.456,z2);
		}
		break;
	case 13:
		{
		  Points->InsertPoint(0,20,28.019,z1);
		  Points->InsertPoint(1,20,28.019,z2);
		}
		break;
	case 14:
		{
		  Points->InsertPoint(0,12.019,34.716,z1);
		  Points->InsertPoint(1,12.019,34.716,z2);
		}
		break;
	case 15:
		{
		  Points->InsertPoint(0,6.809,43.739,z1);
		  Points->InsertPoint(1,6.809,43.739,z2);
		}
		break;
	case 16:
		{
		  Points->InsertPoint(0,5,54,z1);
		  Points->InsertPoint(1,5,54,z2);
		}
		break;
	case 17:
		{
		  Points->InsertPoint(0,6.809,64.261,z1);
		  Points->InsertPoint(1,6.809,64.261,z2);
		}
		break;
	case 18:
		{
		  Points->InsertPoint(0,12.019,73.284,z1);
		  Points->InsertPoint(1,12.019,73.284,z2);
		}
		break;
	case 19:
		{
		  Points->InsertPoint(0,20,79.981,z1);
		  Points->InsertPoint(1,20,79.981,z2);
		}
		break;
	case 20:
		{
		  Points->InsertPoint(0,29.791,83.544,z1);
		  Points->InsertPoint(1,29.791,83.544,z2);
		}
		break;
	case 21:
		{
		  Points->InsertPoint(0,40.209,83.544,z1);
		  Points->InsertPoint(1,40.209,83.544,z2);
		}
		break;	
	case 22:
		{
		  Points->InsertPoint(0,50,79.981,z1);
		  Points->InsertPoint(1,50,79.981,z2);
		}
		break;
	case 23:
		{
		  Points->InsertPoint(0,57.981,73.284,z1);
		  Points->InsertPoint(1,57.981,73.284,z2);
		}
		break;
	case 24:
		{
		  Points->InsertPoint(0,63.191,64.262,z1);
		  Points->InsertPoint(1,63.191,64.262,z2);
		}
		break;
	case 25:
		{
		  Points->InsertPoint(0,65,54,z1);
		  Points->InsertPoint(1,65,54,z2);
		}
		break;
	case 26:
		{
		  Points->InsertPoint(0,63.191,43.739,z1);
		  Points->InsertPoint(1,63.191,43.739,z2);
		}
		break;
	case 27:
		{
		  Points->InsertPoint(0,57.981,34.716,z1);
		  Points->InsertPoint(1,57.981,34.716,z2);
		}
		break;
	case 28:
		{
		  Points->InsertPoint(0,50,28.019,z1);
		  Points->InsertPoint(1,50,28.019,z2);
		}
		break;
	case 29:
		{
		  Points->InsertPoint(0,40.209,24.456,z1);
		  Points->InsertPoint(1,40.209,24.456,z2);
		}
		break;
	case 30:
		{
		  Points->InsertPoint(0,35,14,z1);
		  Points->InsertPoint(1,35,14,z2);
		}
		break;
	case 31:
		{
		  Points->InsertPoint(0,24.647,15.363,z1);
		  Points->InsertPoint(1,24.647,15.363,z2);
		}
		break;	
	case 32:
		{
		  Points->InsertPoint(0,15,19.359,z1);
		  Points->InsertPoint(1,15,19.359,z2);
		}
		break;
	case 33:
		{
		  Points->InsertPoint(0,15,88.641,z1);
		  Points->InsertPoint(1,15,88.641,z2);
		}
		break;
	case 34:
		{
		  Points->InsertPoint(0,24.647,92.637,z1);
		  Points->InsertPoint(1,24.647,92.637,z2);
		}
		break;
	case 35:
		{
		  Points->InsertPoint(0,35,94,z1);
		  Points->InsertPoint(1,35,94,z2);
		}
		break;
	case 36:
		{
		  Points->InsertPoint(0,45.353,92.637,z1);
		  Points->InsertPoint(1,45.353,92.637,z2);
		}
		break;
	case 37:
		{
		  Points->InsertPoint(0,55,88.641,z1);
		  Points->InsertPoint(1,55,88.641,z2);
		}
		break;
	case 38:
		{
		  Points->InsertPoint(0,55,19.359,z1);
		  Points->InsertPoint(1,55,19.359,z2);
		}
		break;
	case 39:
		{
		  Points->InsertPoint(0,45.353,15.363,z1);
		  Points->InsertPoint(1,45.353,15.363,z2);
		}
		break;
	case 40:
		{
		  Points->InsertPoint(0,30.642,4.19,z1);
		  Points->InsertPoint(1,30.642,4.19,z2);
		}
		break;
	case 41:
		{
		  Points->InsertPoint(0,22.059,5.704,z1);
		  Points->InsertPoint(1,22.059,5.704,z2);
		}
		break;
	case 42:
		{
		  Points->InsertPoint(0,22.059,102.296,z1);
		  Points->InsertPoint(1,22.059,102.296,z2);
		}
		break;
	case 43:
		{
		  Points->InsertPoint(0,30.642,103.81,z1);
		  Points->InsertPoint(1,30.642,103.81,z2);
		}
		break;
	case 44:
		{
		  Points->InsertPoint(0,39.358,103.81,z1);
		  Points->InsertPoint(1,39.358,103.81,z2);
		}
		break;
	case 45:
		{
		  Points->InsertPoint(0,47.941,102.296,z1);
		  Points->InsertPoint(1,47.941,102.296,z2);
		}
		break;
	case 46:
		{
		  Points->InsertPoint(0,47.941,5.704,z1);
		  Points->InsertPoint(1,47.941,5.704,z2);
		}
		break;
	case 47:
		{
		  Points->InsertPoint(0,39.358,4.19,z1);
		  Points->InsertPoint(1,39.358,4.19,z2);
		}
		break;	
	case 48:
		{
		  Points->InsertPoint(0,29.7,44.82,z1);
		  Points->InsertPoint(1,29.7,44.82,z2);
		}
		break;
	case 49:
		{
		  Points->InsertPoint(0,24.4,54,z1);
		  Points->InsertPoint(1,24.4,54,z2);
		}
		break;
	case 50:
		{
		  Points->InsertPoint(0,29.7,63.18,z1);
		  Points->InsertPoint(1,29.7,63.18,z2);
		}
		break;
	case 51:
		{
		  Points->InsertPoint(0,40.3,63.18,z1);
		  Points->InsertPoint(1,40.3,63.18,z2);
		}
		break;
	case 52:
		{
		  Points->InsertPoint(0,45.6,54,z1);
		  Points->InsertPoint(1,45.6,54,z2);
		}
		break;
	case 53:
		{
		  Points->InsertPoint(0,40.3,44.82,z1);
		  Points->InsertPoint(1,40.3,44.82,z2);
		}
		break;
	case 54:
		{
		  Points->InsertPoint(0,35,54,z1);
		  Points->InsertPoint(1,35,54,z2);
		}
		break;
	default:
        break;
  }
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showIuNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[54],d->IuRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAaNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[48],d->AaRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAbNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[49],d->AbRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAcNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[50],d->AcRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAdNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[51],d->AdRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAeNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[52],d->AeRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showAfNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[53],d->AfRadioButton);
}


//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBaNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[0],d->BaRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBbNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[1],d->BbRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBcNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[2],d->BcRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBdNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[3],d->BdRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBeNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[4],d->BeRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBfNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[5],d->BfRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBgNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[6],d->BgRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBhNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[7],d->BhRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBiNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[8],d->BiRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBjNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[9],d->BjRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBkNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[10],d->BkRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showBlNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[11],d->BlRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCaNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[12],d->CaRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCbNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[13],d->CbRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCcNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[14],d->CcRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCdNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[15],d->CdRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCeNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[16],d->CeRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCfNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[17],d->CfRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCgNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[18],d->CgRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showChNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[19],d->ChRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCiNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[20],d->CiRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCjNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[21],d->CjRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCkNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[22],d->CkRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showClNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[23],d->ClRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCmNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[24],d->CmRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCnNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[25],d->CnRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCoNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[26],d->CoRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCpNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[27],d->CpRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCqNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[28],d->CqRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showCrNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[29],d->CrRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDaNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[30],d->DaRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDbNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[31],d->DbRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDcNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[32],d->DcRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDdNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[33],d->DdRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDeNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[34],d->DeRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDfNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[35],d->DfRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDgNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[36],d->DgRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDhNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[37],d->DhRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDiNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[38],d->DiRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showDjNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[39],d->DjRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEaNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[40],d->EaRadioButton); 
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEbNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[41],d->EbRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEcNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[42],d->EcRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEdNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[43],d->EdRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEeNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[44],d->EeRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEfNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[45],d->EfRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEgNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[46],d->EgRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showEhNeedle()
{
  Q_D(qSlicerIgyneModuleWidget);

  showOneNeedle(LineActor[47],d->EhRadioButton);
}

//-----------------------------------------------------------------------------
void qSlicerIgyneModuleWidget::showOneNeedle(vtkActor *Actor,QRadioButton *RadioButton)
{
  if(Actor->GetVisibility())
  {
	  Actor->VisibilityOff();
	  RadioButton->setChecked(false);
  }
  else
  {
	  Actor->VisibilityOn();
	  RadioButton->setChecked(true);
  }
  
  qSlicerApplication * app = qSlicerApplication::application();
  vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
  activeRenderer->GetRenderWindow()->Render();
}

void qSlicerIgyneModuleWidget::registerNeedles()
{
  Q_D(qSlicerIgyneModuleWidget);

  qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();  
  vtkMRMLLinearTransformNode* transformNode = vtkMRMLLinearTransformNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLLinearTransformNode4"));
  
  vtkMatrix4x4* matrix = transformNode->GetMatrixTransformToParent();
  for(int i=0; i<55; i++)
    {	
	LineActor[i]->SetUserMatrix(matrix);
	LineActor[i]->VisibilityOn();
    }

  vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
  activeRenderer->GetRenderWindow()->Render();

  d->IuRadioButton->setChecked(true);
  d->AaRadioButton->setChecked(true);
  d->AbRadioButton->setChecked(true);
  d->AcRadioButton->setChecked(true);
  d->AdRadioButton->setChecked(true);
  d->AeRadioButton->setChecked(true);
  d->AfRadioButton->setChecked(true);
  d->BaRadioButton->setChecked(true);
  d->BbRadioButton->setChecked(true);
  d->BcRadioButton->setChecked(true);
  d->BdRadioButton->setChecked(true);
  d->BeRadioButton->setChecked(true);
  d->BfRadioButton->setChecked(true);
  d->BgRadioButton->setChecked(true);
  d->BhRadioButton->setChecked(true);
  d->BiRadioButton->setChecked(true);
  d->BjRadioButton->setChecked(true);
  d->BkRadioButton->setChecked(true);
  d->BlRadioButton->setChecked(true);
  d->CaRadioButton->setChecked(true);
  d->CbRadioButton->setChecked(true);
  d->CcRadioButton->setChecked(true);
  d->CdRadioButton->setChecked(true);
  d->CeRadioButton->setChecked(true);
  d->CfRadioButton->setChecked(true);
  d->CgRadioButton->setChecked(true);
  d->ChRadioButton->setChecked(true);
  d->CiRadioButton->setChecked(true);
  d->CjRadioButton->setChecked(true);
  d->CkRadioButton->setChecked(true);
  d->ClRadioButton->setChecked(true);
  d->CmRadioButton->setChecked(true);
  d->CnRadioButton->setChecked(true);
  d->CoRadioButton->setChecked(true);
  d->CpRadioButton->setChecked(true);
  d->CqRadioButton->setChecked(true);
  d->CrRadioButton->setChecked(true);
  d->DaRadioButton->setChecked(true);
  d->DbRadioButton->setChecked(true);
  d->DcRadioButton->setChecked(true);
  d->DdRadioButton->setChecked(true);
  d->DeRadioButton->setChecked(true);
  d->DfRadioButton->setChecked(true);
  d->DgRadioButton->setChecked(true);
  d->DhRadioButton->setChecked(true);
  d->DiRadioButton->setChecked(true);
  d->DjRadioButton->setChecked(true);
  d->EaRadioButton->setChecked(true);
  d->EbRadioButton->setChecked(true);
  d->EcRadioButton->setChecked(true);
  d->EdRadioButton->setChecked(true);
  d->EeRadioButton->setChecked(true);
  d->EfRadioButton->setChecked(true);
  d->EgRadioButton->setChecked(true);
  d->EhRadioButton->setChecked(true);  
}

void qSlicerIgyneModuleWidget::hideNeedles()
{
  Q_D(qSlicerIgyneModuleWidget);

  for(int i=0; i<55; i++)
   {	
	LineActor[i]->VisibilityOff();
    }

  qSlicerApplication * app = qSlicerApplication::application();
  vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
  activeRenderer->GetRenderWindow()->Render();

  d->IuRadioButton->setChecked(false);
  d->AaRadioButton->setChecked(false);
  d->AbRadioButton->setChecked(false);
  d->AcRadioButton->setChecked(false);
  d->AdRadioButton->setChecked(false);
  d->AeRadioButton->setChecked(false);
  d->AfRadioButton->setChecked(false);
  d->BaRadioButton->setChecked(false);
  d->BbRadioButton->setChecked(false);
  d->BcRadioButton->setChecked(false);
  d->BdRadioButton->setChecked(false);
  d->BeRadioButton->setChecked(false);
  d->BfRadioButton->setChecked(false);
  d->BgRadioButton->setChecked(false);
  d->BhRadioButton->setChecked(false);
  d->BiRadioButton->setChecked(false);
  d->BjRadioButton->setChecked(false);
  d->BkRadioButton->setChecked(false);
  d->BlRadioButton->setChecked(false);
  d->CaRadioButton->setChecked(false);
  d->CbRadioButton->setChecked(false);
  d->CcRadioButton->setChecked(false);
  d->CdRadioButton->setChecked(false);
  d->CeRadioButton->setChecked(false);
  d->CfRadioButton->setChecked(false);
  d->CgRadioButton->setChecked(false);
  d->ChRadioButton->setChecked(false);
  d->CiRadioButton->setChecked(false);
  d->CjRadioButton->setChecked(false);
  d->CkRadioButton->setChecked(false);
  d->ClRadioButton->setChecked(false);
  d->CmRadioButton->setChecked(false);
  d->CnRadioButton->setChecked(false);
  d->CoRadioButton->setChecked(false);
  d->CpRadioButton->setChecked(false);
  d->CqRadioButton->setChecked(false);
  d->CrRadioButton->setChecked(false);
  d->DaRadioButton->setChecked(false);
  d->DbRadioButton->setChecked(false);
  d->DcRadioButton->setChecked(false);
  d->DdRadioButton->setChecked(false);
  d->DeRadioButton->setChecked(false);
  d->DfRadioButton->setChecked(false);
  d->DgRadioButton->setChecked(false);
  d->DhRadioButton->setChecked(false);
  d->DiRadioButton->setChecked(false);
  d->DjRadioButton->setChecked(false);
  d->EaRadioButton->setChecked(false);
  d->EbRadioButton->setChecked(false);
  d->EcRadioButton->setChecked(false);
  d->EdRadioButton->setChecked(false);
  d->EeRadioButton->setChecked(false);
  d->EfRadioButton->setChecked(false);
  d->EgRadioButton->setChecked(false);
  d->EhRadioButton->setChecked(false);
}

void qSlicerIgyneModuleWidget::addVolume()
{
  Q_D(qSlicerIgyneModuleWidget);

  qSlicerApplication * app = qSlicerApplication::application();
  app->ioManager()->openAddVolumesDialog();
}

void qSlicerIgyneModuleWidget::pushIuNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(54, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAaNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(48, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAbNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(49, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAcNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(50, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAdNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(51, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAeNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(52, nDepth);   
}

void qSlicerIgyneModuleWidget::pushAfNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(53, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBaNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(0, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBbNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(1, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBcNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(2, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBdNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(3, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBeNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(4, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBfNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(5, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBgNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(6, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBhNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(7, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBiNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(8, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBjNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(9, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBkNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(10, nDepth);   
}

void qSlicerIgyneModuleWidget::pushBlNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(11, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCaNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(12, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCbNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(13, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCcNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(14, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCdNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(15, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCeNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(16, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCfNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(17, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCgNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(18, nDepth);   
}

void qSlicerIgyneModuleWidget::pushChNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(19, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCiNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(20, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCjNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(21, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCkNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(22, nDepth);   
}

void qSlicerIgyneModuleWidget::pushClNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(23, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCmNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(24, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCnNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(25, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCoNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(26, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCpNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(27, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCqNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(28, nDepth);   
}

void qSlicerIgyneModuleWidget::pushCrNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(29, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDaNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(30, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDbNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(31, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDcNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(32, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDdNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(33, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDeNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(34, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDfNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(35, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDgNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(36, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDhNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(37, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDiNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(38, nDepth);   
}

void qSlicerIgyneModuleWidget::pushDjNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(39, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEaNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(40, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEbNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(41, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEcNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(42, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEdNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(43, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEeNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(44, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEfNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(45, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEgNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(46, nDepth);   
}

void qSlicerIgyneModuleWidget::pushEhNeedle(int nDepth)
{
  Q_D(qSlicerIgyneModuleWidget);
  pushOneNeedle(47, nDepth);   
}

void qSlicerIgyneModuleWidget::pushOneNeedle(int i, int nDepth)
{
  qSlicerApplication * app = qSlicerApplication::application();
  vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();

  double* pColor=LineActor[i]->GetProperty()->GetDiffuseColor();
  double fColor[3];
  fColor[0]=pColor[0];fColor[1]=pColor[1];fColor[2]=pColor[2];

  activeRenderer->RemoveActor(LineActor[i]);

  vtkPoints *Points=vtkPoints::New();
  vtkLine *Line=vtkLine::New();
  vtkUnstructuredGrid *LineGrid=vtkUnstructuredGrid::New();
  vtkDataSetMapper *LineMapper=vtkDataSetMapper::New() ;
  LineActor[i]->Delete();
  LineActor[i]=vtkActor::New() ;

  Points->SetNumberOfPoints(2);
  setNeedleCoordinates(i,Points,200.0f-nDepth,20.0f-nDepth);

  LineActor[i]->GetProperty()->SetDiffuseColor(fColor[0],fColor[1],fColor[2]);
  Line->GetPointIds()->SetNumberOfIds(2);
  Line->GetPointIds()->SetId(0, 0);
  Line->GetPointIds()->SetId(1, 1);
  Line->GetPoints()->SetNumberOfPoints(2);

  LineGrid->Allocate(1, 1);
  LineGrid->InsertNextCell(Line->GetCellType(),Line->GetPointIds());
  LineGrid->SetPoints(Points);

  LineMapper->SetInput(LineGrid);		
  LineActor[i]->SetMapper(LineMapper);
  activeRenderer->AddActor(LineActor[i]);			  

  Points->Delete();
  Line->Delete();
  LineGrid->Delete();
  LineMapper->Delete();	
  
  vtkMRMLScene* mrmlScene=app->mrmlScene();  
  vtkMRMLLinearTransformNode* transformNode = vtkMRMLLinearTransformNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLLinearTransformNode4"));
  vtkMatrix4x4* matrix = transformNode->GetMatrixTransformToParent();
  LineActor[i]->SetUserMatrix(matrix);
  
  activeRenderer->GetRenderWindow()->Render();
}

void qSlicerIgyneModuleWidget::setIuColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(54,d->IuColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAaColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(48,d->AaColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAbColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(49,d->AbColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAcColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(50,d->AcColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAdColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(51,d->AdColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAeColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(52,d->AeColorPushButton);  
}

void qSlicerIgyneModuleWidget::setAfColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(53,d->AfColorPushButton);  
}


void qSlicerIgyneModuleWidget::setBaColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(0,d->BaColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBbColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(1,d->BbColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBcColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(2,d->BcColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBdColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(3,d->BdColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBeColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(4,d->BeColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBfColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(5,d->BfColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBgColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(6,d->BgColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBhColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(7,d->BhColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBiColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(8,d->BiColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBjColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(9,d->BjColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBkColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(10,d->BkColorPushButton);  
}

void qSlicerIgyneModuleWidget::setBlColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(11,d->BlColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCaColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(12,d->CaColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCbColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(13,d->CbColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCcColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(14,d->CcColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCdColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(15,d->CdColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCeColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(16,d->CeColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCfColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(17,d->CfColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCgColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(18,d->CgColorPushButton);  
}

void qSlicerIgyneModuleWidget::setChColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(19,d->ChColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCiColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(20,d->CiColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCjColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(21,d->CjColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCkColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(22,d->CkColorPushButton);  
}

void qSlicerIgyneModuleWidget::setClColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(23,d->ClColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCmColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(24,d->CmColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCnColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(25,d->CnColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCoColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(26,d->CoColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCpColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(27,d->CpColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCqColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(28,d->CqColorPushButton);  
}

void qSlicerIgyneModuleWidget::setCrColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(29,d->CrColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDaColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(30,d->DaColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDbColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(31,d->DbColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDcColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(32,d->DcColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDdColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(33,d->DdColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDeColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(34,d->DeColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDfColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(35,d->DfColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDgColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(36,d->DgColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDhColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(37,d->DhColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDiColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(38,d->DiColorPushButton);  
}

void qSlicerIgyneModuleWidget::setDjColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(39,d->DjColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEaColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(40,d->EaColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEbColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(41,d->EbColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEcColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(42,d->EcColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEdColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(43,d->EdColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEeColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(44,d->EeColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEfColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(45,d->EfColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEgColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(46,d->EgColorPushButton);  
}

void qSlicerIgyneModuleWidget::setEhColor()
{
  Q_D(qSlicerIgyneModuleWidget);
  setOneNeedleColor(47,d->EhColorPushButton);  
}

void qSlicerIgyneModuleWidget::setOneNeedleColor(int i,QPushButton *ColorPushButton)
{
  QColor color = QColorDialog::getColor(Qt::green, this);

  QString sColor;
  sColor.sprintf("background-color: rgb(%d,%d,%d);", color.red(),color.green(),color.blue());

  if(color.isValid())
    {
	LineActor[i]->GetProperty()->SetDiffuseColor(color.red()/255.0f,color.green()/255.0f,color.blue()/255.0f);
	qSlicerApplication * app = qSlicerApplication::application();
    vtkRenderer* activeRenderer = app->layoutManager()->activeThreeDRenderer();
	activeRenderer->GetRenderWindow()->Render(); 
	ColorPushButton->setStyleSheet(sColor);
    }
}

