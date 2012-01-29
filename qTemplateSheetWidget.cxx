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

// SlicerQt includes
#include "qSlicerApplication.h"
#include "qSlicerIOManager.h"
#include "qSlicerLayoutManager.h"

// Qt includes
#include "qTemplateSheetWidget.h"
#include "ui_qTemplateSheetWidget.h"
//#include "ui_qSpinBoxDepthWidget.h"

// CTK includes
#include <ctkPopupWidget.h>
//#include "ctkSliderWidget.h"

// MRML includes
#include <vtkMRMLLinearTransformNode.h>
#include <vtkMRMLModelNode.h>
#include <vtkMRMLScene.h>
#include <vtkMRMLAnnotationHierarchyNode.h>
#include <vtkMRMLModelNode.h>
#include <vtkMRMLModelStorageNode.h>
#include <vtkMRMLFreeSurferModelStorageNode.h>
#include <vtkMRMLModelDisplayNode.h>

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
#include <vtkGeneralTransform.h>
#include <vtkPolyDataNormals.h>
#include <vtkGlyph3D.h>
#include <vtkSphereSource.h>
#include <vtkIterativeClosestPointTransform.h>
#include <vtkLandmarkTransform.h>
#include <vtkCollisionDetectionFilter.h>

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

const double pi=3.14159265358979f;

//-----------------------------------------------------------------------------
class qTemplateSheetWidgetPrivate: public Ui_TemplateSheetWidget
{
  Q_DECLARE_PUBLIC(qTemplateSheetWidget);
protected:
  qTemplateSheetWidget* const q_ptr;  

public:
  qTemplateSheetWidgetPrivate(qTemplateSheetWidget& object);
  void init();
  
};

//-----------------------------------------------------------------------------
qTemplateSheetWidgetPrivate::qTemplateSheetWidgetPrivate(qTemplateSheetWidget& object)
  :q_ptr(&object)
{
  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidgetPrivate::init()
{
  Q_Q(qTemplateSheetWidget);
  this->setupUi(q);

  QObject::connect(this->AddVolumePushButton, SIGNAL(clicked()),
                q, SLOT(addVolume()));
  QObject::connect(this->LoadTemplatePushButton, SIGNAL(clicked()),
                q, SLOT(loadTemplate()));
	QObject::connect(this->SelectNeedlesPushButton, SIGNAL(clicked()),
                q, SLOT(selectNeedles()));

  QObject::connect(this->IuRadioButton, SIGNAL(clicked()),
                q, SLOT(showIuNeedle()));
  QObject::connect(this->AaRadioButton, SIGNAL(clicked()),
                q, SLOT(showAaNeedle()));
  QObject::connect(this->AbRadioButton, SIGNAL(clicked()),
                q, SLOT(showAbNeedle()));
  QObject::connect(this->AcRadioButton, SIGNAL(clicked()),
                q, SLOT(showAcNeedle()));
  QObject::connect(this->AdRadioButton, SIGNAL(clicked()),
                q, SLOT(showAdNeedle()));
  QObject::connect(this->AeRadioButton, SIGNAL(clicked()),
                q, SLOT(showAeNeedle()));
  QObject::connect(this->AfRadioButton, SIGNAL(clicked()),
                q, SLOT(showAfNeedle()));
  QObject::connect(this->BaRadioButton, SIGNAL(clicked()),
                q, SLOT(showBaNeedle()));
  QObject::connect(this->BbRadioButton, SIGNAL(clicked()),
                q, SLOT(showBbNeedle()));
  QObject::connect(this->BcRadioButton, SIGNAL(clicked()),
                q, SLOT(showBcNeedle()));
  QObject::connect(this->BdRadioButton, SIGNAL(clicked()),
                q, SLOT(showBdNeedle()));
  QObject::connect(this->BeRadioButton, SIGNAL(clicked()),
                q, SLOT(showBeNeedle()));
  QObject::connect(this->BfRadioButton, SIGNAL(clicked()),
                q, SLOT(showBfNeedle()));
  QObject::connect(this->BgRadioButton, SIGNAL(clicked()),
                q, SLOT(showBgNeedle()));
  QObject::connect(this->BhRadioButton, SIGNAL(clicked()),
                q, SLOT(showBhNeedle()));
  QObject::connect(this->BiRadioButton, SIGNAL(clicked()),
                q, SLOT(showBiNeedle()));
  QObject::connect(this->BjRadioButton, SIGNAL(clicked()),
                q, SLOT(showBjNeedle()));
  QObject::connect(this->BkRadioButton, SIGNAL(clicked()),
                q, SLOT(showBkNeedle()));
  QObject::connect(this->BlRadioButton, SIGNAL(clicked()),
                q, SLOT(showBlNeedle()));
  QObject::connect(this->CaRadioButton, SIGNAL(clicked()),
                q, SLOT(showCaNeedle()));
  QObject::connect(this->CbRadioButton, SIGNAL(clicked()),
                q, SLOT(showCbNeedle()));
  QObject::connect(this->CcRadioButton, SIGNAL(clicked()),
                q, SLOT(showCcNeedle()));
  QObject::connect(this->CdRadioButton, SIGNAL(clicked()),
                q, SLOT(showCdNeedle()));
  QObject::connect(this->CeRadioButton, SIGNAL(clicked()),
                q, SLOT(showCeNeedle()));
  QObject::connect(this->CfRadioButton, SIGNAL(clicked()),
                q, SLOT(showCfNeedle()));
  QObject::connect(this->CgRadioButton, SIGNAL(clicked()),
                q, SLOT(showCgNeedle()));
  QObject::connect(this->ChRadioButton, SIGNAL(clicked()),
                q, SLOT(showChNeedle()));
  QObject::connect(this->CiRadioButton, SIGNAL(clicked()),
                q, SLOT(showCiNeedle()));
  QObject::connect(this->CjRadioButton, SIGNAL(clicked()),
                q, SLOT(showCjNeedle()));
  QObject::connect(this->CkRadioButton, SIGNAL(clicked()),
                q, SLOT(showCkNeedle()));
  QObject::connect(this->ClRadioButton, SIGNAL(clicked()),
                q, SLOT(showClNeedle()));
  QObject::connect(this->CmRadioButton, SIGNAL(clicked()),
                q, SLOT(showCmNeedle()));
  QObject::connect(this->CnRadioButton, SIGNAL(clicked()),
                q, SLOT(showCnNeedle()));
  QObject::connect(this->CoRadioButton, SIGNAL(clicked()),
                q, SLOT(showCoNeedle()));
  QObject::connect(this->CpRadioButton, SIGNAL(clicked()),
                q, SLOT(showCpNeedle()));
  QObject::connect(this->CqRadioButton, SIGNAL(clicked()),
                q, SLOT(showCqNeedle()));
  QObject::connect(this->CrRadioButton, SIGNAL(clicked()),
                q, SLOT(showCrNeedle()));
  QObject::connect(this->DaRadioButton, SIGNAL(clicked()),
                q, SLOT(showDaNeedle()));
  QObject::connect(this->DbRadioButton, SIGNAL(clicked()),
                q, SLOT(showDbNeedle()));
  QObject::connect(this->DcRadioButton, SIGNAL(clicked()),
                q, SLOT(showDcNeedle()));
  QObject::connect(this->DdRadioButton, SIGNAL(clicked()),
                q, SLOT(showDdNeedle()));
  QObject::connect(this->DeRadioButton, SIGNAL(clicked()),
                q, SLOT(showDeNeedle()));
  QObject::connect(this->DfRadioButton, SIGNAL(clicked()),
                q, SLOT(showDfNeedle()));
  QObject::connect(this->DgRadioButton, SIGNAL(clicked()),
                q, SLOT(showDgNeedle()));
  QObject::connect(this->DhRadioButton, SIGNAL(clicked()),
                q, SLOT(showDhNeedle()));
  QObject::connect(this->DiRadioButton, SIGNAL(clicked()),
                q, SLOT(showDiNeedle()));
  QObject::connect(this->DjRadioButton, SIGNAL(clicked()),
                q, SLOT(showDjNeedle()));
  QObject::connect(this->EaRadioButton, SIGNAL(clicked()),
                q, SLOT(showEaNeedle()));
  QObject::connect(this->EbRadioButton, SIGNAL(clicked()),
                q, SLOT(showEbNeedle()));
  QObject::connect(this->EcRadioButton, SIGNAL(clicked()),
                q, SLOT(showEcNeedle()));
  QObject::connect(this->EdRadioButton, SIGNAL(clicked()),
                q, SLOT(showEdNeedle()));
  QObject::connect(this->EeRadioButton, SIGNAL(clicked()),
                q, SLOT(showEeNeedle()));
  QObject::connect(this->EfRadioButton, SIGNAL(clicked()),
                q, SLOT(showEfNeedle()));
  QObject::connect(this->EgRadioButton, SIGNAL(clicked()),
                q, SLOT(showEgNeedle()));
  QObject::connect(this->EhRadioButton, SIGNAL(clicked()),
                q, SLOT(showEhNeedle()));
	QObject::connect(this->FaRadioButton, SIGNAL(clicked()),
                q, SLOT(showFaNeedle()));
  QObject::connect(this->FbRadioButton, SIGNAL(clicked()),
                q, SLOT(showFbNeedle()));
  QObject::connect(this->FcRadioButton, SIGNAL(clicked()),
                q, SLOT(showFcNeedle()));
  QObject::connect(this->FdRadioButton, SIGNAL(clicked()),
                q, SLOT(showFdNeedle()));
  QObject::connect(this->FeRadioButton, SIGNAL(clicked()),
                q, SLOT(showFeNeedle()));
  QObject::connect(this->FfRadioButton, SIGNAL(clicked()),
                q, SLOT(showFfNeedle()));
  QObject::connect(this->FgRadioButton, SIGNAL(clicked()),
                q, SLOT(showFgNeedle()));
  QObject::connect(this->FhRadioButton, SIGNAL(clicked()),
                q, SLOT(showFhNeedle()));
   
  QObject::connect(this->ShowNeedlesPushButton, SIGNAL(clicked()),
                q, SLOT(showNeedles()));
  QObject::connect(this->CADmodel2ImageRegPushButton, SIGNAL(clicked()),
                q, SLOT(registerCADmodelToImage()));  
  QObject::connect(this->ObturatorSpinBox, SIGNAL(valueChanged(int)),
                q, SLOT(pushObutrator(int)));

  QObject::connect(this->IuColorPushButton, SIGNAL(clicked()),
	            q, SLOT(setIuColor()));
  QObject::connect(this->AaColorPushButton, SIGNAL(clicked()),
	            q, SLOT(setAaColor()));
  QObject::connect(this->AbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setAbColor()));
  QObject::connect(this->AcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setAcColor()));
  QObject::connect(this->AdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setAdColor()));
  QObject::connect(this->AeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setAeColor()));
  QObject::connect(this->AfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setAfColor()));
  QObject::connect(this->BaColorPushButton, SIGNAL(clicked()),
	            q, SLOT(setBaColor()));
  QObject::connect(this->BbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBbColor()));
  QObject::connect(this->BcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBcColor()));
  QObject::connect(this->BdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBdColor()));
  QObject::connect(this->BeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBeColor()));
  QObject::connect(this->BfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBfColor()));
  QObject::connect(this->BgColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBgColor()));
  QObject::connect(this->BhColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBhColor()));
  QObject::connect(this->BiColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBiColor()));
  QObject::connect(this->BjColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBjColor()));
  QObject::connect(this->BkColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBkColor()));
  QObject::connect(this->BlColorPushButton, SIGNAL(clicked()),
                q, SLOT(setBlColor()));
  QObject::connect(this->CaColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCaColor()));
  QObject::connect(this->CbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCbColor()));
  QObject::connect(this->CcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCcColor()));
  QObject::connect(this->CdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCdColor()));
  QObject::connect(this->CeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCeColor()));
  QObject::connect(this->CfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCfColor()));
  QObject::connect(this->CgColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCgColor()));
  QObject::connect(this->ChColorPushButton, SIGNAL(clicked()),
                q, SLOT(setChColor()));
  QObject::connect(this->CiColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCiColor()));
  QObject::connect(this->CjColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCjColor()));
  QObject::connect(this->CkColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCkColor()));
  QObject::connect(this->ClColorPushButton, SIGNAL(clicked()),
                q, SLOT(setClColor()));
  QObject::connect(this->CmColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCmColor()));
  QObject::connect(this->CnColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCnColor()));
  QObject::connect(this->CoColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCoColor()));
  QObject::connect(this->CpColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCpColor()));
  QObject::connect(this->CqColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCqColor()));
  QObject::connect(this->CrColorPushButton, SIGNAL(clicked()),
                q, SLOT(setCrColor()));
  QObject::connect(this->DaColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDaColor()));
  QObject::connect(this->DbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDbColor()));
  QObject::connect(this->DcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDcColor()));
  QObject::connect(this->DdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDdColor()));
  QObject::connect(this->DeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDeColor()));
  QObject::connect(this->DfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDfColor()));
  QObject::connect(this->DgColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDgColor()));
  QObject::connect(this->DhColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDhColor()));
  QObject::connect(this->DiColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDiColor()));
  QObject::connect(this->DjColorPushButton, SIGNAL(clicked()),
                q, SLOT(setDjColor()));
  QObject::connect(this->EaColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEaColor()));
  QObject::connect(this->EbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEbColor()));
  QObject::connect(this->EcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEcColor()));
  QObject::connect(this->EdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEdColor()));
  QObject::connect(this->EeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEeColor()));
  QObject::connect(this->EfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEfColor()));
  QObject::connect(this->EgColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEgColor()));
  QObject::connect(this->EhColorPushButton, SIGNAL(clicked()),
                q, SLOT(setEhColor()));	
	QObject::connect(this->FaColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFaColor()));
  QObject::connect(this->FbColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFbColor()));
  QObject::connect(this->FcColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFcColor()));
  QObject::connect(this->FdColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFdColor()));
  QObject::connect(this->FeColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFeColor()));
  QObject::connect(this->FfColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFfColor()));
  QObject::connect(this->FgColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFgColor()));
  QObject::connect(this->FhColorPushButton, SIGNAL(clicked()),
                q, SLOT(setFhColor()));	
	 
	ctkPopupWidget* popup = new ctkPopupWidget(this->BaColorPushButton);
	QSpinBox* popupSpinboxBa = new QSpinBox(popup);
	q->createSpinbox(popup,popupSpinboxBa);
	QObject::connect(popupSpinboxBa, SIGNAL(valueChanged(int)),
				q, SLOT(pushBaNeedle(int)));

	ctkPopupWidget* popupBb = new ctkPopupWidget(this->BbColorPushButton);
	QSpinBox* popupSpinboxBb = new QSpinBox(popupBb);
	q->createSpinbox(popupBb,popupSpinboxBb);
	QObject::connect(popupSpinboxBb, SIGNAL(valueChanged(int)),
				q, SLOT(pushBbNeedle(int)));

	ctkPopupWidget* popupBc = new ctkPopupWidget(this->BcColorPushButton);
	QSpinBox* popupSpinboxBc = new QSpinBox(popupBc);
	q->createSpinbox(popupBc,popupSpinboxBc);
	QObject::connect(popupSpinboxBc, SIGNAL(valueChanged(int)),
				q, SLOT(pushBcNeedle(int)));

	ctkPopupWidget* popupBd = new ctkPopupWidget(this->BdColorPushButton);
	QSpinBox* popupSpinboxBd = new QSpinBox(popupBd);
	q->createSpinbox(popupBd,popupSpinboxBd);
	QObject::connect(popupSpinboxBd, SIGNAL(valueChanged(int)),
				q, SLOT(pushBdNeedle(int)));

	ctkPopupWidget* popupBe = new ctkPopupWidget(this->BeColorPushButton);
	QSpinBox* popupSpinboxBe = new QSpinBox(popupBe);
	q->createSpinbox(popupBe,popupSpinboxBe);
	QObject::connect(popupSpinboxBe, SIGNAL(valueChanged(int)),
				q, SLOT(pushBeNeedle(int)));

	ctkPopupWidget* popupBf = new ctkPopupWidget(this->BfColorPushButton);
	QSpinBox* popupSpinboxBf = new QSpinBox(popupBf);
	q->createSpinbox(popupBf,popupSpinboxBf);
	QObject::connect(popupSpinboxBf, SIGNAL(valueChanged(int)),
				q, SLOT(pushBfNeedle(int)));

	ctkPopupWidget* popupBg = new ctkPopupWidget(this->BgColorPushButton);
	QSpinBox* popupSpinboxBg = new QSpinBox(popupBg);
	q->createSpinbox(popupBg,popupSpinboxBg);
	QObject::connect(popupSpinboxBg, SIGNAL(valueChanged(int)),
				q, SLOT(pushBgNeedle(int)));

	ctkPopupWidget* popupBh = new ctkPopupWidget(this->BhColorPushButton);
	QSpinBox* popupSpinboxBh = new QSpinBox(popupBh);
	q->createSpinbox(popupBh,popupSpinboxBh);
	QObject::connect(popupSpinboxBh, SIGNAL(valueChanged(int)),
				q, SLOT(pushBhNeedle(int)));

	ctkPopupWidget* popupBi = new ctkPopupWidget(this->BiColorPushButton);
	QSpinBox* popupSpinboxBi = new QSpinBox(popupBi);
	q->createSpinbox(popupBi,popupSpinboxBi);
	QObject::connect(popupSpinboxBi, SIGNAL(valueChanged(int)),
				q, SLOT(pushBiNeedle(int)));

	ctkPopupWidget* popupBj = new ctkPopupWidget(this->BjColorPushButton);
	QSpinBox* popupSpinboxBj = new QSpinBox(popupBj);
	q->createSpinbox(popupBj,popupSpinboxBj);
	QObject::connect(popupSpinboxBj, SIGNAL(valueChanged(int)),
				q, SLOT(pushBjNeedle(int)));

	ctkPopupWidget* popupBk = new ctkPopupWidget(this->BkColorPushButton);
	QSpinBox* popupSpinboxBk = new QSpinBox(popupBk);
	q->createSpinbox(popupBk,popupSpinboxBk);
	QObject::connect(popupSpinboxBk, SIGNAL(valueChanged(int)),
				q, SLOT(pushBkNeedle(int)));

	ctkPopupWidget* popupBl = new ctkPopupWidget(this->BlColorPushButton);
	QSpinBox* popupSpinboxBl = new QSpinBox(popupBl);
	q->createSpinbox(popupBl,popupSpinboxBl);
	QObject::connect(popupSpinboxBl, SIGNAL(valueChanged(int)),
				q, SLOT(pushBlNeedle(int)));

	ctkPopupWidget* popupAa = new ctkPopupWidget(this->AaColorPushButton);
	QSpinBox* popupSpinboxAa = new QSpinBox(popupAa);
	q->createSpinbox(popupAa,popupSpinboxAa);
	QObject::connect(popupSpinboxAa, SIGNAL(valueChanged(int)),
				q, SLOT(pushAaNeedle(int)));

	ctkPopupWidget* popupAb = new ctkPopupWidget(this->AbColorPushButton);
	QSpinBox* popupSpinboxAb = new QSpinBox(popupAb);
	q->createSpinbox(popupAb,popupSpinboxAb);
	QObject::connect(popupSpinboxAb, SIGNAL(valueChanged(int)),
				q, SLOT(pushAbNeedle(int)));

	ctkPopupWidget* popupAc = new ctkPopupWidget(this->AcColorPushButton);
	QSpinBox* popupSpinboxAc = new QSpinBox(popupAc);
	q->createSpinbox(popupAc,popupSpinboxAc);
	QObject::connect(popupSpinboxAc, SIGNAL(valueChanged(int)),
				q, SLOT(pushAcNeedle(int)));

	ctkPopupWidget* popupAd = new ctkPopupWidget(this->AdColorPushButton);
	QSpinBox* popupSpinboxAd = new QSpinBox(popupAd);
	q->createSpinbox(popupAd,popupSpinboxAd);
	QObject::connect(popupSpinboxAd, SIGNAL(valueChanged(int)),
				q, SLOT(pushAdNeedle(int)));

	ctkPopupWidget* popupAe = new ctkPopupWidget(this->AeColorPushButton);
	QSpinBox* popupSpinboxAe = new QSpinBox(popupAe);
	q->createSpinbox(popupAe,popupSpinboxAe);
	QObject::connect(popupSpinboxAe, SIGNAL(valueChanged(int)),
				q, SLOT(pushAeNeedle(int)));

	ctkPopupWidget* popupAf = new ctkPopupWidget(this->AfColorPushButton);
	QSpinBox* popupSpinboxAf = new QSpinBox(popupAf);
	q->createSpinbox(popupAf,popupSpinboxAf);
	QObject::connect(popupSpinboxAf, SIGNAL(valueChanged(int)),
				q, SLOT(pushAfNeedle(int)));

	ctkPopupWidget* popupCa = new ctkPopupWidget(this->CaColorPushButton);
	QSpinBox* popupSpinboxCa = new QSpinBox(popupCa);
	q->createSpinbox(popupCa,popupSpinboxCa);
	QObject::connect(popupSpinboxCa, SIGNAL(valueChanged(int)),
				q, SLOT(pushCaNeedle(int)));

	ctkPopupWidget* popupCb = new ctkPopupWidget(this->CbColorPushButton);
	QSpinBox* popupSpinboxCb = new QSpinBox(popupCb);
	q->createSpinbox(popupCb,popupSpinboxCb);
	QObject::connect(popupSpinboxCb, SIGNAL(valueChanged(int)),
				q, SLOT(pushCbNeedle(int)));

	ctkPopupWidget* popupCc = new ctkPopupWidget(this->CcColorPushButton);
	QSpinBox* popupSpinboxCc = new QSpinBox(popupCc);
	q->createSpinbox(popupCc,popupSpinboxCc);
	QObject::connect(popupSpinboxCc, SIGNAL(valueChanged(int)),
				q, SLOT(pushCcNeedle(int)));

	ctkPopupWidget* popupCd = new ctkPopupWidget(this->CdColorPushButton);
	QSpinBox* popupSpinboxCd = new QSpinBox(popupCd);
	q->createSpinbox(popupCd,popupSpinboxCd);
	QObject::connect(popupSpinboxCd, SIGNAL(valueChanged(int)),
				q, SLOT(pushCdNeedle(int)));

	ctkPopupWidget* popupCe = new ctkPopupWidget(this->CeColorPushButton);
	QSpinBox* popupSpinboxCe = new QSpinBox(popupCe);
	q->createSpinbox(popupCe,popupSpinboxCe);
	QObject::connect(popupSpinboxCe, SIGNAL(valueChanged(int)),
				q, SLOT(pushCeNeedle(int)));

	ctkPopupWidget* popupCf = new ctkPopupWidget(this->CfColorPushButton);
	QSpinBox* popupSpinboxCf = new QSpinBox(popupCf);
	q->createSpinbox(popupCf,popupSpinboxCf);
	QObject::connect(popupSpinboxCf, SIGNAL(valueChanged(int)),
				q, SLOT(pushCfNeedle(int)));

	ctkPopupWidget* popupCg = new ctkPopupWidget(this->CgColorPushButton);
	QSpinBox* popupSpinboxCg = new QSpinBox(popupCg);
	q->createSpinbox(popupCg,popupSpinboxCg);
	QObject::connect(popupSpinboxCg, SIGNAL(valueChanged(int)),
				q, SLOT(pushCgNeedle(int)));

	ctkPopupWidget* popupCh = new ctkPopupWidget(this->ChColorPushButton);
	QSpinBox* popupSpinboxCh = new QSpinBox(popupCh);
	q->createSpinbox(popupCh,popupSpinboxCh);
	QObject::connect(popupSpinboxCh, SIGNAL(valueChanged(int)),
				q, SLOT(pushChNeedle(int)));

	ctkPopupWidget* popupCi = new ctkPopupWidget(this->CiColorPushButton);
	QSpinBox* popupSpinboxCi = new QSpinBox(popupCi);
	q->createSpinbox(popupCi,popupSpinboxCi);
	QObject::connect(popupSpinboxCi, SIGNAL(valueChanged(int)),
				q, SLOT(pushCiNeedle(int)));

	ctkPopupWidget* popupCj = new ctkPopupWidget(this->CjColorPushButton);
	QSpinBox* popupSpinboxCj = new QSpinBox(popupCj);
	q->createSpinbox(popupCj,popupSpinboxCj);
	QObject::connect(popupSpinboxCj, SIGNAL(valueChanged(int)),
				q, SLOT(pushCjNeedle(int)));

	ctkPopupWidget* popupCk = new ctkPopupWidget(this->CkColorPushButton);
	QSpinBox* popupSpinboxCk = new QSpinBox(popupCk);
	q->createSpinbox(popupCk,popupSpinboxCk);
	QObject::connect(popupSpinboxCk, SIGNAL(valueChanged(int)),
				q, SLOT(pushCkNeedle(int)));

	ctkPopupWidget* popupCl = new ctkPopupWidget(this->ClColorPushButton);
	QSpinBox* popupSpinboxCl = new QSpinBox(popupCl);
	q->createSpinbox(popupCl,popupSpinboxCl);
	QObject::connect(popupSpinboxCl, SIGNAL(valueChanged(int)),
				q, SLOT(pushClNeedle(int)));

	ctkPopupWidget* popupCm = new ctkPopupWidget(this->CmColorPushButton);
	QSpinBox* popupSpinboxCm = new QSpinBox(popupCm);
	q->createSpinbox(popupCm,popupSpinboxCm);
	QObject::connect(popupSpinboxCm, SIGNAL(valueChanged(int)),
				q, SLOT(pushCmNeedle(int)));

	ctkPopupWidget* popupCn = new ctkPopupWidget(this->CnColorPushButton);
	QSpinBox* popupSpinboxCn = new QSpinBox(popupCn);
	q->createSpinbox(popupCn,popupSpinboxCn);
	QObject::connect(popupSpinboxCn, SIGNAL(valueChanged(int)),
				q, SLOT(pushCnNeedle(int)));

	ctkPopupWidget* popupCo = new ctkPopupWidget(this->CoColorPushButton);
	QSpinBox* popupSpinboxCo = new QSpinBox(popupCo);
	q->createSpinbox(popupCo,popupSpinboxCo);
	QObject::connect(popupSpinboxCo, SIGNAL(valueChanged(int)),
				q, SLOT(pushCoNeedle(int)));

	ctkPopupWidget* popupCp = new ctkPopupWidget(this->CpColorPushButton);
	QSpinBox* popupSpinboxCp = new QSpinBox(popupCp);
	q->createSpinbox(popupCp,popupSpinboxCp);
	QObject::connect(popupSpinboxCp, SIGNAL(valueChanged(int)),
				q, SLOT(pushCpNeedle(int)));

	ctkPopupWidget* popupCq = new ctkPopupWidget(this->CqColorPushButton);
	QSpinBox* popupSpinboxCq = new QSpinBox(popupCq);
	q->createSpinbox(popupCq,popupSpinboxCq);
	QObject::connect(popupSpinboxCq, SIGNAL(valueChanged(int)),
				q, SLOT(pushCqNeedle(int)));

	ctkPopupWidget* popupCr = new ctkPopupWidget(this->CrColorPushButton);
	QSpinBox* popupSpinboxCr = new QSpinBox(popupCr);
	q->createSpinbox(popupCr,popupSpinboxCr);
	QObject::connect(popupSpinboxCr, SIGNAL(valueChanged(int)),
				q, SLOT(pushCrNeedle(int)));

	ctkPopupWidget* popupDa = new ctkPopupWidget(this->DaColorPushButton);
	QSpinBox* popupSpinboxDa = new QSpinBox(popupDa);
	q->createSpinbox(popupDa,popupSpinboxDa);
	QObject::connect(popupSpinboxDa, SIGNAL(valueChanged(int)),
				q, SLOT(pushDaNeedle(int)));

	ctkPopupWidget* popupDb = new ctkPopupWidget(this->DbColorPushButton);
	QSpinBox* popupSpinboxDb = new QSpinBox(popupDb);
	q->createSpinbox(popupDb,popupSpinboxDb);
	QObject::connect(popupSpinboxDb, SIGNAL(valueChanged(int)),
				q, SLOT(pushDbNeedle(int)));

	ctkPopupWidget* popupDc = new ctkPopupWidget(this->DcColorPushButton);
	QSpinBox* popupSpinboxDc = new QSpinBox(popupDc);
	q->createSpinbox(popupDc,popupSpinboxDc);
	QObject::connect(popupSpinboxDc, SIGNAL(valueChanged(int)),
				q, SLOT(pushDcNeedle(int)));

	ctkPopupWidget* popupDd = new ctkPopupWidget(this->DdColorPushButton);
	QSpinBox* popupSpinboxDd = new QSpinBox(popupDd);
	q->createSpinbox(popupDd,popupSpinboxDd);
	QObject::connect(popupSpinboxDd, SIGNAL(valueChanged(int)),
				q, SLOT(pushDdNeedle(int)));

	ctkPopupWidget* popupDe = new ctkPopupWidget(this->DeColorPushButton);
	QSpinBox* popupSpinboxDe = new QSpinBox(popupDe);
	q->createSpinbox(popupDe,popupSpinboxDe);
	QObject::connect(popupSpinboxDe, SIGNAL(valueChanged(int)),
				q, SLOT(pushDeNeedle(int)));

	ctkPopupWidget* popupDf = new ctkPopupWidget(this->DfColorPushButton);
	QSpinBox* popupSpinboxDf = new QSpinBox(popupDf);
	q->createSpinbox(popupDf,popupSpinboxDf);
	QObject::connect(popupSpinboxDf, SIGNAL(valueChanged(int)),
				q, SLOT(pushDfNeedle(int)));

	ctkPopupWidget* popupDg = new ctkPopupWidget(this->DgColorPushButton);
	QSpinBox* popupSpinboxDg = new QSpinBox(popupDg);
	q->createSpinbox(popupDg,popupSpinboxDg);
	QObject::connect(popupSpinboxDg, SIGNAL(valueChanged(int)),
				q, SLOT(pushDgNeedle(int)));

	ctkPopupWidget* popupDh = new ctkPopupWidget(this->DhColorPushButton);
	QSpinBox* popupSpinboxDh = new QSpinBox(popupDh);
	q->createSpinbox(popupDh,popupSpinboxDh);
	QObject::connect(popupSpinboxDh, SIGNAL(valueChanged(int)),
				q, SLOT(pushDhNeedle(int)));

	ctkPopupWidget* popupDi = new ctkPopupWidget(this->DiColorPushButton);
	QSpinBox* popupSpinboxDi = new QSpinBox(popupDi);
	q->createSpinbox(popupDi,popupSpinboxDi);
	QObject::connect(popupSpinboxDi, SIGNAL(valueChanged(int)),
				q, SLOT(pushDiNeedle(int)));

	ctkPopupWidget* popupDj = new ctkPopupWidget(this->DjColorPushButton);
	QSpinBox* popupSpinboxDj = new QSpinBox(popupDj);
	q->createSpinbox(popupDj,popupSpinboxDj);
	QObject::connect(popupSpinboxDj, SIGNAL(valueChanged(int)),
				q, SLOT(pushDjNeedle(int)));

	ctkPopupWidget* popupEa = new ctkPopupWidget(this->EaColorPushButton);
	QSpinBox* popupSpinboxEa = new QSpinBox(popupEa);
	q->createSpinbox(popupEa,popupSpinboxEa);
	QObject::connect(popupSpinboxEa, SIGNAL(valueChanged(int)),
				q, SLOT(pushEaNeedle(int)));

	ctkPopupWidget* popupEb = new ctkPopupWidget(this->EbColorPushButton);
	QSpinBox* popupSpinboxEb = new QSpinBox(popupEb);
	q->createSpinbox(popupEb,popupSpinboxEb);
	QObject::connect(popupSpinboxEb, SIGNAL(valueChanged(int)),
				q, SLOT(pushEbNeedle(int)));

	ctkPopupWidget* popupEc = new ctkPopupWidget(this->EcColorPushButton);
	QSpinBox* popupSpinboxEc = new QSpinBox(popupEc);
	q->createSpinbox(popupEc,popupSpinboxEc);
	QObject::connect(popupSpinboxEc, SIGNAL(valueChanged(int)),
				q, SLOT(pushEcNeedle(int)));

	ctkPopupWidget* popupEd = new ctkPopupWidget(this->EdColorPushButton);
	QSpinBox* popupSpinboxEd = new QSpinBox(popupEd);
	q->createSpinbox(popupEd,popupSpinboxEd);
	QObject::connect(popupSpinboxEd, SIGNAL(valueChanged(int)),
				q, SLOT(pushEdNeedle(int)));

	ctkPopupWidget* popupEe = new ctkPopupWidget(this->EeColorPushButton);
	QSpinBox* popupSpinboxEe = new QSpinBox(popupEe);
	q->createSpinbox(popupEe,popupSpinboxEe);
	QObject::connect(popupSpinboxEe, SIGNAL(valueChanged(int)),
				q, SLOT(pushEeNeedle(int)));

	ctkPopupWidget* popupEf = new ctkPopupWidget(this->EfColorPushButton);
	QSpinBox* popupSpinboxEf = new QSpinBox(popupEf);
	q->createSpinbox(popupEf,popupSpinboxEf);
	QObject::connect(popupSpinboxEf, SIGNAL(valueChanged(int)),
				q, SLOT(pushEfNeedle(int)));

	ctkPopupWidget* popupEg = new ctkPopupWidget(this->EgColorPushButton);
	QSpinBox* popupSpinboxEg = new QSpinBox(popupEg);
	q->createSpinbox(popupEg,popupSpinboxEg);
	QObject::connect(popupSpinboxEg, SIGNAL(valueChanged(int)),
				q, SLOT(pushEgNeedle(int)));

	ctkPopupWidget* popupEh = new ctkPopupWidget(this->EhColorPushButton);
	QSpinBox* popupSpinboxEh = new QSpinBox(popupEh);
	q->createSpinbox(popupEh,popupSpinboxEh);
	QObject::connect(popupSpinboxEh, SIGNAL(valueChanged(int)),
				q, SLOT(pushEhNeedle(int)));

	ctkPopupWidget* popupFa = new ctkPopupWidget(this->FaColorPushButton);
	QSpinBox* popupSpinboxFa = new QSpinBox(popupFa);
	q->createSpinbox(popupFa,popupSpinboxFa);
	QObject::connect(popupSpinboxFa, SIGNAL(valueChanged(int)),
				q, SLOT(pushFaNeedle(int)));

	ctkPopupWidget* popupFb = new ctkPopupWidget(this->FbColorPushButton);
	QSpinBox* popupSpinboxFb = new QSpinBox(popupFb);
	q->createSpinbox(popupFb,popupSpinboxFb);
	QObject::connect(popupSpinboxFb, SIGNAL(valueChanged(int)),
				q, SLOT(pushFbNeedle(int)));

	ctkPopupWidget* popupFc = new ctkPopupWidget(this->FcColorPushButton);
	QSpinBox* popupSpinboxFc = new QSpinBox(popupFc);
	q->createSpinbox(popupFc,popupSpinboxFc);
	QObject::connect(popupSpinboxFc, SIGNAL(valueChanged(int)),
				q, SLOT(pushFcNeedle(int)));

	ctkPopupWidget* popupFd = new ctkPopupWidget(this->FdColorPushButton);
	QSpinBox* popupSpinboxFd = new QSpinBox(popupFd);
	q->createSpinbox(popupFd,popupSpinboxFd);
	QObject::connect(popupSpinboxFd, SIGNAL(valueChanged(int)),
				q, SLOT(pushFdNeedle(int)));

	ctkPopupWidget* popupFe = new ctkPopupWidget(this->FeColorPushButton);
	QSpinBox* popupSpinboxFe = new QSpinBox(popupFe);
	q->createSpinbox(popupFe,popupSpinboxFe);
	QObject::connect(popupSpinboxFe, SIGNAL(valueChanged(int)),
				q, SLOT(pushFeNeedle(int)));

	ctkPopupWidget* popupFf = new ctkPopupWidget(this->FfColorPushButton);
	QSpinBox* popupSpinboxFf = new QSpinBox(popupFf);
	q->createSpinbox(popupFf,popupSpinboxFf);
	QObject::connect(popupSpinboxFf, SIGNAL(valueChanged(int)),
				q, SLOT(pushFfNeedle(int)));

	ctkPopupWidget* popupFg = new ctkPopupWidget(this->FgColorPushButton);
	QSpinBox* popupSpinboxFg = new QSpinBox(popupFg);
	q->createSpinbox(popupFg,popupSpinboxFg);
	QObject::connect(popupSpinboxFg, SIGNAL(valueChanged(int)),
				q, SLOT(pushFgNeedle(int)));

	ctkPopupWidget* popupFh = new ctkPopupWidget(this->FhColorPushButton);
	QSpinBox* popupSpinboxFh = new QSpinBox(popupFh);
	q->createSpinbox(popupFh,popupSpinboxFh);
	QObject::connect(popupSpinboxFh, SIGNAL(valueChanged(int)),
				q, SLOT(pushFhNeedle(int)));	

	ctkPopupWidget* popupIu = new ctkPopupWidget(this->IuColorPushButton);
	QSpinBox* popupSpinboxIu = new QSpinBox(popupIu);
	q->createSpinbox(popupIu,popupSpinboxIu);
	QObject::connect(popupSpinboxIu, SIGNAL(valueChanged(int)),
				q, SLOT(pushIuNeedle(int)));

	qSlicerApplication * app = qSlicerApplication::application();
	vtkMRMLScene* mrmlScene=app->mrmlScene();
	vtkMRMLModelNode* ObutratorNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode5"));

	if(ObutratorNode!=NULL)
		{
		q->setNeedleCoordinates();
		q->computerPolydataAndMatrix();		
		
		q->m_poly = vtkSmartPointer<vtkPolyData>::New();  
		q->m_poly->DeepCopy(ObutratorNode->GetPolyData());

		QString sfileName;
		char* filename;

		for(int i=0; i<63; i++)
			{
			sfileName.sprintf("%d", i+6);
			sfileName="vtkMRMLModelNode"+sfileName;
			
			filename=sfileName.toLatin1().data();
			vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));

			if(NeedleNode!=NULL)
				{
				vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

				int nVisibility=displayNode->GetVisibility();  

				QString str,str1;				

				if(nVisibility==1)
					{
					q->setRadioButton(i,true);					
					}
				else
					{
					q->setRadioButton(i,false);					
					}
				}
			}
		}
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::createSpinbox(ctkPopupWidget* popup,QSpinBox* popupSpinbox)
{
  Q_D(qTemplateSheetWidget);  

  QHBoxLayout* popupLayout = new QHBoxLayout(popup);	
  popupLayout->addWidget(popupSpinbox); 

  QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
  sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(popupSpinbox->sizePolicy().hasHeightForWidth());
	popupSpinbox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
	popupSpinbox->setSizePolicy(sizePolicy1);
	popupSpinbox->setMaximum(300);
	popupSpinbox->setValue(170);	
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::addVolume()
{
  Q_D(qTemplateSheetWidget);

  qSlicerApplication * app = qSlicerApplication::application();
  app->ioManager()->openAddVolumesDialog();
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::loadTemplate()
{
  Q_D(qTemplateSheetWidget);

  qSlicerApplication * app = qSlicerApplication::application();  
  
  if(app->ioManager()->openLoadSceneDialog())
		{	  
		vtkMRMLScene* mrmlScene=app->mrmlScene();
		vtkMRMLModelNode* ObutratorNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode5"));

		if(ObutratorNode!=NULL)
			{
			setNeedleCoordinates();
			computerPolydataAndMatrix();		
			
			m_poly = vtkSmartPointer<vtkPolyData>::New();  
			m_poly->DeepCopy(ObutratorNode->GetPolyData());
			}

		vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode6"));
		if(NeedleNode==NULL)
			{
			vtkSmartPointer<vtkMatrix4x4> vtkmat = vtkSmartPointer<vtkMatrix4x4>::New();
			vtkmat->DeepCopy(m_vtkmat);
	 
			for(int i=0; i<63; i++)
				{
				vtkmat->SetElement(0,3,m_vtkmat->GetElement(0,3)+p[0][i]);
				vtkmat->SetElement(1,3,m_vtkmat->GetElement(1,3)+p[1][i]);
				vtkmat->SetElement(2,3,m_vtkmat->GetElement(2,3)+(30.0-150.0)/2.0);

				vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
				vtkSmartPointer<vtkTransform> Transform=vtkSmartPointer<vtkTransform>::New();				
				TransformPolyDataFilter->SetInput(m_polyCylinder);
				Transform->SetMatrix(vtkmat);
				TransformPolyDataFilter->SetTransform(Transform);
				TransformPolyDataFilter->Update();

				vtkSmartPointer<vtkTriangleFilter> triangles=vtkSmartPointer<vtkTriangleFilter>::New();
				triangles->SetInput(TransformPolyDataFilter->GetOutput());	
			   
				AddModel(i,(vtkPolyData *) triangles->GetOutput());
				}
			}
		else
			{
			QString sfileName;
			char* filename;

			for(int i=0; i<63; i++)
				{
				sfileName.sprintf("%d", i+6);
				sfileName="vtkMRMLModelNode"+sfileName;
				
				filename=sfileName.toLatin1().data();
				NeedleNode= vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));	
				vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

				int nVisibility=displayNode->GetVisibility();  

				QString str,str1;				

				if(nVisibility==1)
					{
					setRadioButton(i,true);					
					}
				else
					{
					setRadioButton(i,false);					
					}
				}
			}
		}
}

//----------------------------------------------------------------------------
void qTemplateSheetWidget::computerPolydataAndMatrix()
{
	vtkSmartPointer<vtkCylinderSource> Cylinder=vtkSmartPointer<vtkCylinderSource>::New();		

	Cylinder->SetResolution(1000);
	Cylinder->SetCapping(1) ;
	Cylinder->SetHeight( 200.0f );
	Cylinder->SetRadius( 1.0f );
	m_polyCylinder=Cylinder->GetOutput();

	m_vtkmat = vtkSmartPointer<vtkMatrix4x4>::New();
	m_vtkmat->Identity();

	vtkSmartPointer<vtkMatrix4x4> RestruMatrix=vtkSmartPointer<vtkMatrix4x4>::New();
	vtkSmartPointer<vtkMatrix4x4> WorldMatrix=vtkSmartPointer<vtkMatrix4x4>::New();
	vtkSmartPointer<vtkMatrix4x4> Restru2WorldMatrix=vtkSmartPointer<vtkMatrix4x4>::New();

	RestruMatrix->SetElement(0,0,0);
	RestruMatrix->SetElement(1,0,0);
	RestruMatrix->SetElement(2,0,0);
	RestruMatrix->SetElement(3,0,1);

	RestruMatrix->SetElement(0,1,1);
	RestruMatrix->SetElement(1,1,0);
	RestruMatrix->SetElement(2,1,0);
	RestruMatrix->SetElement(3,1,1);

	RestruMatrix->SetElement(0,2,0);
	RestruMatrix->SetElement(1,2,1);
	RestruMatrix->SetElement(2,2,0);
	RestruMatrix->SetElement(3,2,1);

	RestruMatrix->SetElement(0,3,0);
	RestruMatrix->SetElement(1,3,0);
	RestruMatrix->SetElement(2,3,1);
	RestruMatrix->SetElement(3,3,1);

	WorldMatrix->SetElement(0,0,0);
	WorldMatrix->SetElement(1,0,0);
	WorldMatrix->SetElement(2,0,0);
	WorldMatrix->SetElement(3,0,1);

	WorldMatrix->SetElement(0,1,1);
	WorldMatrix->SetElement(1,1,0);
	WorldMatrix->SetElement(2,1,0);
	WorldMatrix->SetElement(3,1,1);

	WorldMatrix->SetElement(0,2,0);
	WorldMatrix->SetElement(1,2,0);
	WorldMatrix->SetElement(2,2,-1);
	WorldMatrix->SetElement(3,2,1);

	WorldMatrix->SetElement(0,3,0);
	WorldMatrix->SetElement(1,3,1);
	WorldMatrix->SetElement(2,3,0);
	WorldMatrix->SetElement(3,3,1);

	WorldMatrix->Invert();
	Restru2WorldMatrix->Multiply4x4(RestruMatrix,WorldMatrix,m_vtkmat);	
}


//----------------------------------------------------------------------------
void qTemplateSheetWidget::AddModel (int i,vtkPolyData *polyData)
{
  vtkSmartPointer<vtkMRMLModelNode> modelNode = vtkSmartPointer<vtkMRMLModelNode>::New();
  vtkSmartPointer<vtkMRMLModelDisplayNode> displayNode = vtkSmartPointer<vtkMRMLModelDisplayNode>::New();
  vtkSmartPointer<vtkMRMLModelStorageNode> storageNode = vtkSmartPointer<vtkMRMLModelStorageNode>::New();

	char filename[5];
	sprintf(filename, "%d", i);

	std::string fileName;
	fileName =  std::string("Model_")+std::string(filename) + std::string(".vtk");  

  qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();
  modelNode->SetName(fileName.c_str());	
	modelNode->SetAndObservePolyData(polyData);
	mrmlScene->SaveStateForUndo();
	modelNode->SetScene(mrmlScene);
  storageNode->SetScene(mrmlScene);
	storageNode->SetFileName(fileName.c_str());	
	displayNode->SetScene(mrmlScene);
	mrmlScene->AddNode(storageNode);
	mrmlScene->AddNode(displayNode);
	modelNode->SetAndObserveStorageNodeID(storageNode->GetID());
	modelNode->SetAndObserveDisplayNodeID(displayNode->GetID());

	vtkMRMLLinearTransformNode* transformNode = vtkMRMLLinearTransformNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLLinearTransformNode4"));
	modelNode->SetAndObserveTransformNodeID(transformNode->GetID());
	displayNode->SetPolyData(modelNode->GetPolyData());
	displayNode->SetColor(0,1,0);
	displayNode->SetSliceIntersectionVisibility(0);
	displayNode->SetVisibility(0);

	mrmlScene->AddNode(modelNode); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setNeedleCoordinates()
{
	p[0][0]=35;p[1][0]=34;
	p[0][1]=25;p[1][1]=36.679;
	p[0][2]=17.679;p[1][2]=44;
	p[0][3]=15;p[1][3]=54;
	p[0][4]=17.679;p[1][4]=64;
	p[0][5]=25;p[1][5]=71.321;
	p[0][6]=35;p[1][6]=74;
	p[0][7]=45;p[1][7]=71.321;
	p[0][8]=52.321;p[1][8]=64;
	p[0][9]=55;p[1][9]=54;
	p[0][10]=52.321;p[1][10]=44;
	p[0][11]=45;p[1][11]=36.679;
	p[0][12]=29.791;p[1][12]=24.456;
	p[0][13]=20;p[1][13]=28.019;
	p[0][14]=12.019;p[1][14]=34.716;
	p[0][15]=6.809;p[1][15]=43.739;
	p[0][16]=5;p[1][16]=54;
	p[0][17]=6.809;p[1][17]=64.261;
	p[0][18]=12.019;p[1][18]=73.284;
	p[0][19]=20;p[1][19]=79.981;
	p[0][20]=29.791;p[1][20]=83.544;
	p[0][21]=40.209;p[1][21]=83.544;
	p[0][22]=50;p[1][22]=79.981;
	p[0][23]=57.981;p[1][23]=73.284;
	p[0][24]=63.191;p[1][24]=64.262;
	p[0][25]=65;p[1][25]=54;
	p[0][26]=63.191;p[1][26]=43.739;
	p[0][27]=57.981;p[1][27]=34.716;
	p[0][28]=50;p[1][28]=28.019;
	p[0][29]=40.209;p[1][29]=24.456;
	p[0][30]=35;p[1][30]=14;
	p[0][31]=24.647;p[1][31]=15.363;
	p[0][32]=15;p[1][32]=19.359;
	p[0][33]=15;p[1][33]=88.641;
	p[0][34]=24.647;p[1][34]=92.637;
	p[0][35]=35;p[1][35]=94;
	p[0][36]=45.353;p[1][36]=92.637;
	p[0][37]=55;p[1][37]=88.641;
	p[0][38]=55;p[1][38]=19.359;
	p[0][39]=45.353;p[1][39]=15.363;
	p[0][40]=30.642;p[1][40]=4.19;
	p[0][41]=22.059;p[1][41]=5.704;
	p[0][42]=22.059;p[1][42]=102.296;
	p[0][43]=30.642;p[1][43]=103.81;
	p[0][44]=39.358;p[1][44]=103.81;
	p[0][45]=47.941;p[1][45]=102.296;
	p[0][46]=47.941;p[1][46]=5.704;
	p[0][47]=39.358;p[1][47]=4.19;
	p[0][48]=29.7;p[1][48]=44.82;
	p[0][49]=24.4;p[1][49]=54;
	p[0][50]=29.7;p[1][50]=63.18;
	p[0][51]=40.3;p[1][51]=63.18;
	p[0][52]=45.6;p[1][52]=54;
	p[0][53]=40.3;p[1][53]=44.82;
	p[0][54]=35;p[1][54]=54;
	p[0][55]=9;p[1][55]=12;
	p[0][56]=5;p[1][56]=18;
	p[0][57]=5;p[1][57]=90;
	p[0][58]=9;p[1][58]=96;
	p[0][59]=61;p[1][59]=96;
	p[0][60]=65;p[1][60]=90;
	p[0][61]=65;p[1][61]=18;
	p[0][62]=61;p[1][62]=12;
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showIuNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(54,d->IuRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(48,d->AaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(49,d->AbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(50,d->AcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(51,d->AdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(52,d->AeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showAfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(53,d->AfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(0,d->BaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(1,d->BbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(2,d->BcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(3,d->BdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(4,d->BeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(5,d->BfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBgNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(6,d->BgRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBhNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(7,d->BhRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBiNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(8,d->BiRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBjNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(9,d->BjRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBkNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(10,d->BkRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showBlNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(11,d->BlRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(12,d->CaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(13,d->CbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(14,d->CcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(15,d->CdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(16,d->CeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(17,d->CfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCgNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(18,d->CgRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showChNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(19,d->ChRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCiNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(20,d->CiRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCjNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(21,d->CjRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCkNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(22,d->CkRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showClNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(23,d->ClRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCmNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(24,d->CmRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCnNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(25,d->CnRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCoNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(26,d->CoRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCpNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(27,d->CpRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCqNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(28,d->CqRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showCrNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(29,d->CrRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(30,d->DaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(31,d->DbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(32,d->DcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(33,d->DdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(34,d->DeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(35,d->DfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDgNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(36,d->DgRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDhNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(37,d->DhRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDiNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(38,d->DiRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showDjNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(39,d->DjRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(40,d->EaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(41,d->EbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(42,d->EcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(43,d->EdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(44,d->EeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(45,d->EfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEgNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(46,d->EgRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showEhNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(47,d->EhRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFaNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(55,d->FaRadioButton); 
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFbNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(56,d->FbRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFcNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(57,d->FcRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFdNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(58,d->FdRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFeNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(59,d->FeRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFfNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(60,d->FfRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFgNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(61,d->FgRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showFhNeedle()
{
  Q_D(qTemplateSheetWidget);

  showOneNeedle(62,d->FhRadioButton);
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushIuNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(54, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(48, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(49, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(50, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(51, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(52, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushAfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(53, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(0, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(1, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(2, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(3, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(4, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(5, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBgNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(6, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBhNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(7, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBiNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(8, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBjNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(9, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBkNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(10, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushBlNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(11, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(12, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(13, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(14, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(15, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(16, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(17, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCgNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(18, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushChNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(19, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCiNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(20, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCjNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(21, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCkNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(22, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushClNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(23, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCmNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(24, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCnNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(25, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCoNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(26, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCpNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(27, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCqNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(28, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushCrNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(29, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(30, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(31, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(32, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(33, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(34, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(35, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDgNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(36, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDhNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(37, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDiNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(38, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushDjNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(39, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(40, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(41, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(42, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(43, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(44, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(45, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEgNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(46, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushEhNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(47, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFaNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(55, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFbNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(56, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFcNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(57, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFdNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(58, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFeNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(59, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFfNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(60, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFgNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(61, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushFhNeedle(int nDepth)
{
  Q_D(qTemplateSheetWidget);
  pushOneNeedle(62, nDepth);   
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setIuColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(54,d->IuColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(48,d->AaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(49,d->AbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(50,d->AcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(51,d->AdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(52,d->AeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setAfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(53,d->AfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(0,d->BaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(1,d->BbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(2,d->BcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(3,d->BdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(4,d->BeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(5,d->BfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBgColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(6,d->BgColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBhColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(7,d->BhColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBiColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(8,d->BiColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBjColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(9,d->BjColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBkColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(10,d->BkColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setBlColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(11,d->BlColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(12,d->CaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(13,d->CbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(14,d->CcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(15,d->CdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(16,d->CeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(17,d->CfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCgColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(18,d->CgColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setChColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(19,d->ChColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCiColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(20,d->CiColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCjColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(21,d->CjColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCkColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(22,d->CkColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setClColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(23,d->ClColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCmColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(24,d->CmColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCnColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(25,d->CnColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCoColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(26,d->CoColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCpColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(27,d->CpColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCqColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(28,d->CqColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setCrColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(29,d->CrColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(30,d->DaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(31,d->DbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(32,d->DcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(33,d->DdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(34,d->DeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(35,d->DfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDgColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(36,d->DgColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDhColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(37,d->DhColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDiColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(38,d->DiColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setDjColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(39,d->DjColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(40,d->EaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(41,d->EbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(42,d->EcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(43,d->EdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(44,d->EeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(45,d->EfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEgColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(46,d->EgColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setEhColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(47,d->EhColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFaColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(55,d->FaColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFbColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(56,d->FbColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFcColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(57,d->FcColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFdColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(58,d->FdColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFeColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(59,d->FeColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFfColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(60,d->FfColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFgColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(61,d->FgColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setFhColor()
{
  Q_D(qTemplateSheetWidget);
  setOneNeedleColor(62,d->FhColorPushButton);  
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushObutrator(int nDepth)
{
  Q_D(qTemplateSheetWidget);

  qSlicerApplication * app = qSlicerApplication::application();  

  vtkMRMLScene* mrmlScene=app->mrmlScene();  
  vtkMRMLModelNode* ObutratorNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode5"));

  vtkSmartPointer<vtkMatrix4x4> vtkmat = vtkSmartPointer<vtkMatrix4x4>::New();
  vtkmat->Identity();
  vtkmat->SetElement(2,3,nDepth);

  vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  vtkSmartPointer<vtkTransform> Transform=vtkSmartPointer<vtkTransform>::New();
  TransformPolyDataFilter->SetInput(m_poly);
  Transform->SetMatrix(vtkmat);
  TransformPolyDataFilter->SetTransform(Transform);
  TransformPolyDataFilter->Update();

  vtkSmartPointer<vtkTriangleFilter> triangles=vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInput(TransformPolyDataFilter->GetOutput());
  ObutratorNode->SetAndObservePolyData(triangles->GetOutput());    
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showOneNeedle(int i,QRadioButton *RadioButton)
{
  QString sfileName;
  sfileName.sprintf("%d", i+6);
  sfileName="vtkMRMLModelNode"+sfileName;

  qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();

  char* filename;
  filename=sfileName.toLatin1().data();
  vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));
  vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

  int nVisibility=displayNode->GetVisibility();  

  if(nVisibility==1)
		{
		displayNode->SetVisibility(0);
		displayNode->SetSliceIntersectionVisibility(0);
		RadioButton->setChecked(false);
		}
  else
		{
		displayNode->SetVisibility(1);
		displayNode->SetSliceIntersectionVisibility(1);
		RadioButton->setChecked(true);
		}
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showOneNeedle(int i,bool bShowNeedels)
{
  QString sfileName;
  sfileName.sprintf("%d", i+6);
  sfileName="vtkMRMLModelNode"+sfileName;

  qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();

  char* filename;
  filename=sfileName.toLatin1().data();
  vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));
  vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

  if(bShowNeedels)
		{
		displayNode->SetVisibility(1);
		displayNode->SetSliceIntersectionVisibility(1);	  
		}
  else
		{
		displayNode->SetVisibility(0);
		displayNode->SetSliceIntersectionVisibility(0);	  
		}
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::pushOneNeedle(int i, int nDepth)
{
  QString sfileName;
  sfileName.sprintf("%d", i+6);
  sfileName="vtkMRMLModelNode"+sfileName;

  qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();

  char* filename;
  filename=sfileName.toLatin1().data();
  vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));

  vtkSmartPointer<vtkMatrix4x4> vtkmat = vtkSmartPointer<vtkMatrix4x4>::New();
  vtkmat->DeepCopy(m_vtkmat); 

  vtkmat->SetElement(0,3,m_vtkmat->GetElement(0,3)+p[0][i]);
  vtkmat->SetElement(1,3,m_vtkmat->GetElement(1,3)+p[1][i]);
  vtkmat->SetElement(2,3,m_vtkmat->GetElement(2,3)+110.0-nDepth);

  vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  vtkSmartPointer<vtkTransform> Transform=vtkSmartPointer<vtkTransform>::New();
  TransformPolyDataFilter->SetInput(m_polyCylinder);
  Transform->SetMatrix(vtkmat);
  TransformPolyDataFilter->SetTransform(Transform);
  TransformPolyDataFilter->Update();

  vtkSmartPointer<vtkTriangleFilter> triangles=vtkSmartPointer<vtkTriangleFilter>::New();
  triangles->SetInput(TransformPolyDataFilter->GetOutput());
  NeedleNode->SetAndObservePolyData(triangles->GetOutput());
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setOneNeedleColor(int i,QPushButton *ColorPushButton)
{
  QColor color = QColorDialog::getColor(Qt::green, this);

  QString sColor;
  sColor.sprintf("background-color: rgb(%d,%d,%d);", color.red(),color.green(),color.blue());

  if(color.isValid())
    {
    QString sfileName;
		sfileName.sprintf("%d", i+6);
		sfileName="vtkMRMLModelNode"+sfileName;

		qSlicerApplication * app = qSlicerApplication::application();
		vtkMRMLScene* mrmlScene=app->mrmlScene();

		char* filename;
		filename=sfileName.toLatin1().data();
		vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));
		vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

		displayNode->SetColor(color.red()/255.0f,color.green()/255.0f,color.blue()/255.0f);		
		ColorPushButton->setStyleSheet(sColor);
    }
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::showNeedles()
{
  Q_D(qTemplateSheetWidget);

	if(d->ShowNeedlesPushButton->isChecked())
		{
		for(int i=0; i<63; i++)
			{
			showOneNeedle(i,true);
			}

		d->ShowNeedlesPushButton->setChecked(true);
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
		d->FaRadioButton->setChecked(true);
		d->FbRadioButton->setChecked(true);
		d->FcRadioButton->setChecked(true);
		d->FdRadioButton->setChecked(true);
		d->FeRadioButton->setChecked(true);
		d->FfRadioButton->setChecked(true);
		d->FgRadioButton->setChecked(true);
		d->FhRadioButton->setChecked(true);
		}
	else
		{
		for(int i=0; i<63; i++)
			{
			showOneNeedle(i,false);
			}

		d->ShowNeedlesPushButton->setChecked(false);
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
		d->FaRadioButton->setChecked(false);
		d->FbRadioButton->setChecked(false);
		d->FcRadioButton->setChecked(false);
		d->FdRadioButton->setChecked(false);
		d->FeRadioButton->setChecked(false);
		d->FfRadioButton->setChecked(false);
		d->FgRadioButton->setChecked(false);
		d->FhRadioButton->setChecked(false);
		}		
}

//-----------------------------------------------------------------------------
 void qTemplateSheetWidget::registerCADmodelToImage()
{
	std::cout << "Registration is Processing... " << std::endl;
//--------------------------------------------------------------------------------------------------
// Set the initial registration matrix for the template
//--------------------------------------------------------------------------------------------------

	qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();

	vtkMRMLModelNode* ModelFromImageNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode69"));
	if(ModelFromImageNode!=NULL)
		{
		vtkMRMLLinearTransformNode* transformNode = vtkMRMLLinearTransformNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLLinearTransformNode4"));
		vtkMatrix4x4* vtkmatInitial = transformNode->GetMatrixTransformToParent();

	//--------------------------------------------------------------------------------------------------
	// Set the point value for the points extracted from the inner surface at each hole in the template
	//--------------------------------------------------------------------------------------------------
		vtkSmartPointer<vtkPoints> glyphPoints=vtkSmartPointer<vtkPoints>::New();
		vtkSmartPointer<vtkPolyData> glyphInputData=vtkSmartPointer<vtkPolyData>::New();
		vtkSmartPointer<vtkSphereSource> glyphBalls=vtkSmartPointer<vtkSphereSource>::New();
		vtkSmartPointer<vtkGlyph3D> glyphPoints3D=vtkSmartPointer<vtkGlyph3D>::New();
		//vtkSmartPointer<vtkPolyDataMapper> glyphMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
		//vtkSmartPointer<vtkActor> glyphActor=vtkSmartPointer<vtkActor>::New();

		unsigned int pointId=0;
		//setPointData(35,34,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(25,36.679,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(17.679,44,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(15,54,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(17.679,64,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(25,71.321,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(35,74,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(45,71.321,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(52.321,64,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(55,54,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(52.321,44,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(45,36.679,vtkmatInitial,&pointId,glyphPoints);

		//setPointData(29.791,24.456,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(20,28.019,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(12.019,34.716,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(6.809,43.739,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(5,54,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(6.809,64.261,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(12.019,73.284,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(20,79.981,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(29.791,83.544,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(40.209,83.544,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(50,79.981,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(57.981,73.284,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(63.191,64.262,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(65,54,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(63.191,43.739,vtkmatInitial,&pointId,glyphPoints);
		//setPointData(57.981,34.716,vtkmatInitial,&pointId,glyphPoints);

		setPointData(50,28.019,vtkmatInitial,&pointId,glyphPoints);
		setPointData(40.209,24.456,vtkmatInitial,&pointId,glyphPoints);
		setPointData(35,14,vtkmatInitial,&pointId,glyphPoints);
		setPointData(24.647,15.363,vtkmatInitial,&pointId,glyphPoints);
		setPointData(15,19.359,vtkmatInitial,&pointId,glyphPoints);
		setPointData(15,88.641,vtkmatInitial,&pointId,glyphPoints);
		setPointData(24.647,92.637,vtkmatInitial,&pointId,glyphPoints);
		setPointData(35,94,vtkmatInitial,&pointId,glyphPoints);
		setPointData(45.353,92.637,vtkmatInitial,&pointId,glyphPoints);
		setPointData(55,88.641,vtkmatInitial,&pointId,glyphPoints);
		setPointData(55,19.359,vtkmatInitial,&pointId,glyphPoints);
		setPointData(45.353,15.363,vtkmatInitial,&pointId,glyphPoints);
		setPointData(30.642,4.19,vtkmatInitial,&pointId,glyphPoints);
		setPointData(22.059,5.704,vtkmatInitial,&pointId,glyphPoints);
		setPointData(22.059,102.296,vtkmatInitial,&pointId,glyphPoints);
		setPointData(30.642,103.81,vtkmatInitial,&pointId,glyphPoints);
		setPointData(39.358,103.81,vtkmatInitial,&pointId,glyphPoints);
		setPointData(47.941,102.296,vtkmatInitial,&pointId,glyphPoints);
		setPointData(47.941,5.704,vtkmatInitial,&pointId,glyphPoints);
		setPointData(39.358,4.19,vtkmatInitial,&pointId,glyphPoints);

		glyphInputData->SetPoints(glyphPoints);
		glyphInputData->Update();		

		glyphBalls->SetRadius(0.05);
		glyphBalls->SetThetaResolution(6);
		glyphBalls->SetPhiResolution(10);

		glyphPoints3D->SetInput(glyphInputData);
		glyphPoints3D->SetSource(glyphBalls->GetOutput());
		glyphPoints3D->Update();
		//glyphMapper->SetInput(glyphPoints3D->GetOutput());
		//glyphMapper->Update();

		//glyphActor->SetMapper(glyphMapper);		
		//glyphActor->GetProperty()->SetColor(0, 1, 0);

		vtkSmartPointer<vtkIterativeClosestPointTransform> ICPtransform = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
		ICPtransform->SetSource((vtkPolyData *)glyphInputData);			
		ICPtransform->SetTarget((vtkPolyData *) ModelFromImageNode->GetPolyData());

		ICPtransform->SetCheckMeanDistance(0);
		ICPtransform->SetMaximumMeanDistance(0.01);
		ICPtransform->SetMaximumNumberOfIterations(300);
		ICPtransform->SetMaximumNumberOfLandmarks(1000);
		ICPtransform->SetMeanDistanceModeToRMS();

		vtkLandmarkTransform* LandmarkTransform=ICPtransform->GetLandmarkTransform() ;
		LandmarkTransform->SetModeToRigidBody();
		ICPtransform->Update();		

		int nIterations=ICPtransform->GetNumberOfIterations();
		vtkSmartPointer<vtkMatrix4x4> FinalMatrix = vtkSmartPointer<vtkMatrix4x4>::New();		
		FinalMatrix->Multiply4x4(ICPtransform->GetMatrix(), vtkmatInitial,FinalMatrix);		
		transformNode->SetAndObserveMatrixTransformToParent(FinalMatrix);	

		//register the obturator
		//vtkMRMLModelNode* ModelFromImageNode1 = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode70"));
		//if(ModelFromImageNode1!=NULL)
		//	{
		//	//vtkMRMLModelNode* ObutratorNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode5"));			

		//	vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		//	vtkSmartPointer<vtkTransform> Transform=vtkSmartPointer<vtkTransform>::New();
		//	TransformPolyDataFilter->SetInput(m_poly);
		//	Transform->SetMatrix(FinalMatrix);
		//	TransformPolyDataFilter->SetTransform(Transform);
		//	TransformPolyDataFilter->Update();

		//	vtkSmartPointer<vtkIterativeClosestPointTransform> ICPtransform1 = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
		//	ICPtransform1->SetSource((vtkPolyData *) TransformPolyDataFilter->GetOutput());			
		//	ICPtransform1->SetTarget((vtkPolyData *) ModelFromImageNode1->GetPolyData());

		//	ICPtransform1->SetCheckMeanDistance(0);
		//	ICPtransform1->SetMaximumMeanDistance(0.01);
		//	ICPtransform1->SetMaximumNumberOfIterations(300);
		//	ICPtransform1->SetMaximumNumberOfLandmarks(1000);
		//	ICPtransform1->SetMeanDistanceModeToRMS();

		//	vtkLandmarkTransform* LandmarkTransform1=ICPtransform1->GetLandmarkTransform() ;
		//	LandmarkTransform1->SetModeToRigidBody();
		//	ICPtransform1->Update();
		//	//QMessageBox::information(0, "", "false");

		//	int nIterations1=ICPtransform1->GetNumberOfIterations();
		//	vtkSmartPointer<vtkMatrix4x4> FinalMatrix1 = vtkSmartPointer<vtkMatrix4x4>::New();		
		//	FinalMatrix1->Multiply4x4(ICPtransform1->GetMatrix(), FinalMatrix,FinalMatrix1);		
		//	transformNode->SetAndObserveMatrixTransformToParent(FinalMatrix1);
		//	}

		std::cout << "Result = " << std::endl;
		std::cout << " Number of Iterations       = " << nIterations  << std::endl;		
		}
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setPointData(double fHoleOriginX,double fHoleOriginY,vtkSmartPointer<vtkMatrix4x4> vtkmatInitial,
											unsigned int *pointId,vtkSmartPointer<vtkPoints> glyphPoints)
{
	for (int k=0; k<10; k++) 
		{
		for (int i=0; i<36; i++) 
			{
			double fTipPoint[4],fTipPointTrans[4];
			fTipPoint[0]=fHoleOriginX+1.25*cos(pi/180.0*i*10);
			fTipPoint[1]=fHoleOriginY+1.25*sin(pi/180.0*i*10);
			fTipPoint[2]=k;
			fTipPoint[3]=1.0f;
			vtkmatInitial->MultiplyPoint(fTipPoint, fTipPointTrans);

			glyphPoints->InsertPoint((*pointId), fTipPointTrans[0], fTipPointTrans[1],fTipPointTrans[2]);			
			++(*pointId);
			}		
		}
}

//-----------------------------------------------------------------------------
qTemplateSheetWidget::qTemplateSheetWidget(QWidget* parentWidget)
  :QWidget(parentWidget)
  , d_ptr(new qTemplateSheetWidgetPrivate(*this))
{
  Q_D(qTemplateSheetWidget);
  d->init();
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::selectNeedles()
{
  Q_D(qTemplateSheetWidget);

	qSlicerApplication * app = qSlicerApplication::application();
  vtkMRMLScene* mrmlScene=app->mrmlScene();
	vtkMRMLModelNode* ModelFromImageNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLModelNode70"));

	if(ModelFromImageNode!=NULL)
		{
		vtkSmartPointer<vtkCollisionDetectionFilter> collide = vtkSmartPointer<vtkCollisionDetectionFilter>::New();
		vtkSmartPointer<vtkMatrix4x4> matrix0 = vtkSmartPointer<vtkMatrix4x4>::New();
		vtkSmartPointer<vtkMatrix4x4> matrix1 = vtkSmartPointer<vtkMatrix4x4>::New();		
		vtkSmartPointer<vtkMatrix4x4> matrix2 = vtkSmartPointer<vtkMatrix4x4>::New();	

		collide->SetInput(0,(vtkPolyData *) ModelFromImageNode->GetPolyData());
		//collide->SetInput(1,m_polyCylinder);
		collide->SetMatrix(0, matrix0);

		vtkMRMLLinearTransformNode* transformNode = vtkMRMLLinearTransformNode::SafeDownCast(mrmlScene->GetNodeByID("vtkMRMLLinearTransformNode4"));
		vtkMatrix4x4* vtkmatInitial = transformNode->GetMatrixTransformToParent();

		int nContacts;
		for(int i=0; i<63; i++)
			{
			QString sfileName;
			sfileName.sprintf("%d", i+6);
			sfileName="vtkMRMLModelNode"+sfileName;		

			char* filename;
			filename=sfileName.toLatin1().data();
			vtkMRMLModelNode* NeedleNode = vtkMRMLModelNode::SafeDownCast(mrmlScene->GetNodeByID(filename));

			vtkSmartPointer<vtkMatrix4x4> vtkmat = vtkSmartPointer<vtkMatrix4x4>::New();
			vtkmat->DeepCopy(m_vtkmat); 

			vtkmat->SetElement(0,3,m_vtkmat->GetElement(0,3)+p[0][i]);
			vtkmat->SetElement(1,3,m_vtkmat->GetElement(1,3)+p[1][i]);
			vtkmat->SetElement(2,3,m_vtkmat->GetElement(2,3)-100.0);

			matrix1->Multiply4x4(vtkmatInitial,vtkmat,matrix1);	

			vtkSmartPointer<vtkTransformPolyDataFilter> TransformPolyDataFilter=vtkSmartPointer<vtkTransformPolyDataFilter>::New();
			vtkSmartPointer<vtkTransform> Transform=vtkSmartPointer<vtkTransform>::New();
			TransformPolyDataFilter->SetInput(m_polyCylinder);
			Transform->SetMatrix(matrix1);
			TransformPolyDataFilter->SetTransform(Transform);
			TransformPolyDataFilter->Update();

			vtkSmartPointer<vtkTriangleFilter> triangles=vtkSmartPointer<vtkTriangleFilter>::New();
			triangles->SetInput(TransformPolyDataFilter->GetOutput());

			collide->SetInput(1,(vtkPolyData *) triangles->GetOutput());
			collide->SetMatrix(1, matrix2);
			collide->SetBoxTolerance(0.0);
			collide->SetCellTolerance(0.0);
			collide->SetNumberOfCellsPerBucket(2);
			collide->SetCollisionModeToAllContacts();
			collide->GenerateScalarsOn();
			collide->Update();

			nContacts=collide->GetNumberOfContacts();
			vtkMRMLModelDisplayNode* displayNode =NeedleNode->GetModelDisplayNode();

			if(nContacts>0)
				{
				displayNode->SetVisibility(1);
				displayNode->SetSliceIntersectionVisibility(1);
				setRadioButton(i,true);
				}	
			else
				{
				displayNode->SetVisibility(0);
				displayNode->SetSliceIntersectionVisibility(0);
				setRadioButton(i,false);
				}
			}	
		}
}

//-----------------------------------------------------------------------------
void qTemplateSheetWidget::setRadioButton(int i,bool bShowNeedels)
{
	Q_D(qTemplateSheetWidget);

	switch( i )
      {
      case 0:
        d->BaRadioButton->setChecked(bShowNeedels);
        break;
      case 1:
        d->BbRadioButton->setChecked(bShowNeedels);
        break;
      case 2:
        d->BcRadioButton->setChecked(bShowNeedels);
        break;
      case 3:
        d->BdRadioButton->setChecked(bShowNeedels);
        break;
			case 4:
        d->BeRadioButton->setChecked(bShowNeedels);
        break;
			case 5:
        d->BfRadioButton->setChecked(bShowNeedels);
        break;
			case 6:
        d->BgRadioButton->setChecked(bShowNeedels);
        break;
			case 7:
        d->BhRadioButton->setChecked(bShowNeedels);
        break;
			case 8:
        d->BiRadioButton->setChecked(bShowNeedels);
        break;
			case 9:
        d->BjRadioButton->setChecked(bShowNeedels);
        break;
			case 10:
        d->BkRadioButton->setChecked(bShowNeedels);
        break;
			case 11:
        d->BlRadioButton->setChecked(bShowNeedels);
        break;
			case 12:
        d->CaRadioButton->setChecked(bShowNeedels);
        break;
			case 13:
        d->CbRadioButton->setChecked(bShowNeedels);
        break;
			case 14:
        d->CcRadioButton->setChecked(bShowNeedels);
        break;
			case 15:
        d->CdRadioButton->setChecked(bShowNeedels);
        break;
			case 16:
        d->CeRadioButton->setChecked(bShowNeedels);
        break;
			case 17:
        d->CfRadioButton->setChecked(bShowNeedels);
        break;
			case 18:
        d->CgRadioButton->setChecked(bShowNeedels);
        break;
			case 19:
        d->ChRadioButton->setChecked(bShowNeedels);
        break;
			case 20:
        d->CiRadioButton->setChecked(bShowNeedels);
        break;
			case 21:
        d->CjRadioButton->setChecked(bShowNeedels);
        break;
			case 22:
        d->CkRadioButton->setChecked(bShowNeedels);
        break;
			case 23:
        d->ClRadioButton->setChecked(bShowNeedels);
        break;
			case 24:
        d->CmRadioButton->setChecked(bShowNeedels);
        break;
			case 25:
        d->CnRadioButton->setChecked(bShowNeedels);
        break;
			case 26:
        d->CoRadioButton->setChecked(bShowNeedels);
        break;
			case 27:
        d->CpRadioButton->setChecked(bShowNeedels);
        break;
			case 28:
        d->CqRadioButton->setChecked(bShowNeedels);
        break;
			case 29:
        d->CrRadioButton->setChecked(bShowNeedels);
        break;
			case 30:
        d->DaRadioButton->setChecked(bShowNeedels);
        break;
			case 31:
        d->DbRadioButton->setChecked(bShowNeedels);
        break;
			case 32:
        d->DcRadioButton->setChecked(bShowNeedels);
        break;
			case 33:
        d->DdRadioButton->setChecked(bShowNeedels);
        break;
			case 34:
        d->DeRadioButton->setChecked(bShowNeedels);
        break;
			case 35:
        d->DfRadioButton->setChecked(bShowNeedels);
        break;
			case 36:
        d->DgRadioButton->setChecked(bShowNeedels);
        break;
			case 37:
        d->DhRadioButton->setChecked(bShowNeedels);
        break;
			case 38:
        d->DiRadioButton->setChecked(bShowNeedels);
        break;
			case 39:
        d->DjRadioButton->setChecked(bShowNeedels);
        break;
			case 40:
        d->EaRadioButton->setChecked(bShowNeedels);
        break;
			case 41:
        d->EbRadioButton->setChecked(bShowNeedels);
        break;
			case 42:
        d->EcRadioButton->setChecked(bShowNeedels);
        break;
			case 43:
        d->EdRadioButton->setChecked(bShowNeedels);
        break;
			case 44:
        d->EeRadioButton->setChecked(bShowNeedels);
        break;
			case 45:
        d->EfRadioButton->setChecked(bShowNeedels);
        break;
			case 46:
        d->EgRadioButton->setChecked(bShowNeedels);
        break;
			case 47:
        d->EhRadioButton->setChecked(bShowNeedels);
        break;
			case 48:
        d->AaRadioButton->setChecked(bShowNeedels);
        break;
			case 49:
        d->AbRadioButton->setChecked(bShowNeedels);
        break;
			case 50:
        d->AcRadioButton->setChecked(bShowNeedels);
        break;
			case 51:
        d->AdRadioButton->setChecked(bShowNeedels);
        break;
			case 52:
        d->AeRadioButton->setChecked(bShowNeedels);
        break;
			case 53:
        d->AfRadioButton->setChecked(bShowNeedels);
        break;
			case 54:
        d->IuRadioButton->setChecked(bShowNeedels);
        break; 
			case 55:
        d->FaRadioButton->setChecked(bShowNeedels);
        break;
			case 56:
        d->FbRadioButton->setChecked(bShowNeedels);
        break;
			case 57:
        d->FcRadioButton->setChecked(bShowNeedels);
        break;
			case 58:
        d->FdRadioButton->setChecked(bShowNeedels);
        break;
			case 59:
        d->FeRadioButton->setChecked(bShowNeedels);
        break;
			case 60:
        d->FfRadioButton->setChecked(bShowNeedels);
        break;
			case 61:
        d->FgRadioButton->setChecked(bShowNeedels);
        break;
			case 62:
        d->FhRadioButton->setChecked(bShowNeedels);
        break;
      default:        
        break;
      }
}

//-----------------------------------------------------------------------------
qTemplateSheetWidget::~qTemplateSheetWidget()
{
}

