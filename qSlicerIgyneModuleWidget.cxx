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
#include <QFileDialog>
#include <QtGui/QMainWindow>
#include <QtGui>

// SlicerQt includes
#include "qSlicerIgyneModuleWidget.h"
#include "qSlicerApplication.h"
#include "qSlicerIOManager.h"
#include "qSlicerLayoutManager.h"
#include "ui_qSlicerIgyneModule.h"

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
}

