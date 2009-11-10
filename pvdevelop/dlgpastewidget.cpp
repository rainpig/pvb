/****************************************************************************
**
** Copyright (C) 2000-2006 Lehrig Software Engineering.
**
** This file is part of the pvbrowser project.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "../pvbrowser/pvdefine.h"
#include "dlgpastewidget.h"
#include "ui_dlgpastewidget.h"
#include <QPushButton>
#include "opt.h"

extern OPT opt;

dlgPasteWidget::dlgPasteWidget()
{
  form = new Ui_DialogPasteWidget;
  form->setupUi(this);
  QObject::connect(form->pushButtonCancel,SIGNAL(clicked()),this,SLOT(reject()));
  QObject::connect(form->pushButtonInsert,SIGNAL(clicked()),this,SLOT(accept()));
}

dlgPasteWidget::~dlgPasteWidget()
{
  delete form;
}

QString dlgPasteWidget::run(const char *widgetname, QString *filename)
{
  QString text;
  int ret = exec();
  if(ret == QDialog::Accepted)
  {
    text = "";
    if(filename->contains(".py"))
    {
      if(form->radioButtonPrintf->isChecked())         { text = "    pv.pvPrintf(self.p, self."; text += widgetname; text += ",'text')"; }
      if(form->radioButtonTablePrintf->isChecked())    { text = "    pv.pvTablePrintf(self.p, self."; text += widgetname; text += ", x, y, 'text')"; }
      if(form->radioButtonListViewPrintf->isChecked()) { text = "    pv.pvListViewPrintf(self.p, self."; text += widgetname; text += ", path, column, 'text')"; }
      if(form->radioButtonEvent->isChecked())          { text = "  if id == self."; text += widgetname; text += ":\n    return 1 # call mask 1";}
    }
    else
    {
      if(form->radioButtonPrintf->isChecked())         { text = "    pvPrintf(p,"; text += widgetname; text += ",\"%d\",val);"; }
      if(form->radioButtonTablePrintf->isChecked())    { text = "    pvTablePrintf(p,"; text += widgetname; text += ",x,y,\"%d\",val);"; }
      if(form->radioButtonListViewPrintf->isChecked()) { text = "    pvListViewPrintf(p,"; text += widgetname; text += ",path,column,\"%d\",val);"; }
      if(form->radioButtonEvent->isChecked())          { text = "  if(id == "; text += widgetname; text += ")\n  {\n    return 1; // call mask 1\n  }";}
    }
    return text;
  }
  return "";
}
