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

#ifndef __qTemplateSheetWidget_h
#define __qTemplateSheetWidget_h

// Qt includes
#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui>

// VTK includes
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkMRMLModelNode.h>
#include <vtkMatrix4x4.h>

// ITK includes
#include <itkPointSet.h>

// CTK includes
#include <ctkPopupWidget.h>

class qTemplateSheetWidgetPrivate;

class qTemplateSheetWidget : public QWidget
{
  Q_OBJECT;  

public:
  /// Constructors
  qTemplateSheetWidget(QWidget* parentWidget = 0);  
  virtual ~qTemplateSheetWidget();  

public Q_SLOTS:
  void addVolume();
  void loadTemplate();
	void selectNeedles();

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
	void showFaNeedle();
  void showFbNeedle();
  void showFcNeedle();
  void showFdNeedle();
  void showFeNeedle();
  void showFfNeedle();
  void showFgNeedle();
  void showFhNeedle();

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
	void setFaColor();
  void setFbColor();
  void setFcColor();
  void setFdColor();
  void setFeColor();
  void setFfColor();
  void setFgColor();
  void setFhColor();

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
	void pushFaNeedle(int nDepth);
  void pushFbNeedle(int nDepth);
  void pushFcNeedle(int nDepth);
  void pushFdNeedle(int nDepth);
  void pushFeNeedle(int nDepth);
  void pushFfNeedle(int nDepth);
  void pushFgNeedle(int nDepth);
  void pushFhNeedle(int nDepth);

  void pushObutrator(int nDepth);
	void registerCADmodelToImage();
	void showNeedles();
  //void hideNeedles();

Q_SIGNALS:

protected:
  QScopedPointer<qTemplateSheetWidgetPrivate> d_ptr;

  void setNeedleCoordinates();
  void computerPolydataAndMatrix();
  void AddModel (int i,vtkPolyData *polyData);
  void showOneNeedle(int i,QRadioButton *RadioButton);
	void showOneNeedle(int i,bool bShowNeedels);
  void setOneNeedleColor(int i,QPushButton *ColorPushButton);
  void pushOneNeedle(int i, int nDepth);	
	void createSpinbox(ctkPopupWidget* popup,QSpinBox* popupSpinbox);

/*	void registerCADmodelToImageTest();
	void registerCADmodelToImageTest2();*/	
  
  vtkSmartPointer<vtkPolyData> m_poly,m_polyCylinder;
  vtkSmartPointer<vtkMatrix4x4> m_vtkmat;
  double p[2][63];

	typedef itk::PointSet< double, 3 > PointSetType;
  PointSetType::Pointer m_pointSet;
  //void setPointData(double fHoleOriginX,double fHoleOriginY,vtkSmartPointer<vtkMatrix4x4> vtkmatInitial,
		//									unsigned int *pointId,PointSetType::Pointer pointSet);
	void setPointData(double fHoleOriginX,double fHoleOriginY,vtkSmartPointer<vtkMatrix4x4> vtkmatInitial,
											unsigned int *pointId,vtkSmartPointer<vtkPoints> glyphPoints);
	void setRadioButton(int i,bool bShowNeedels);  

private:
  Q_DECLARE_PRIVATE(qTemplateSheetWidget);
  Q_DISABLE_COPY(qTemplateSheetWidget);
  
};

#endif
