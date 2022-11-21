// File created by Aditya Sharma for Learning Opencascade and Qt
/*
THE FILE IS PROVIDED AS IS WIHTOUT WARRANTY OF ANY KIND 
*/

#include <QtWidgets/qmessagebox.h>

#include "LearnQT.h"
#include "Viewer.h"

#include <BRepPreviewAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

#include <AIS_Shape.hxx>

LearnQT::LearnQT(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_Viewer = new Viewer(this);

    setCentralWidget(m_Viewer);
}

LearnQT::~LearnQT()
{}

void LearnQT::on_actionBox_triggered()
{
    TopoDS_Shape shape= BRepPrimAPI_MakeBox(100.0, 200.0, 300.0).Shape();

    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);

    aisShape->SetColor(Quantity_NOC_WHITE);

    m_Viewer->getContext()->Display(aisShape, Standard_True);
}

void LearnQT::on_actionSphere_triggered()
{
    TopoDS_Shape shape = BRepPrimAPI_MakeSphere(gp_Pnt(0,0,0), 300.0).Shape();

    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);

    aisShape->SetColor(Quantity_NOC_BROWN);

    m_Viewer->getContext()->Display(aisShape, Standard_True);
}

void LearnQT::on_actionAbout_triggered()
{
    QMessageBox msg;
    msg.setText("This is a demo OCCQT application created by Aditya Sharma");
    msg.exec();
}

void LearnQT::on_actionReset_triggered()
{
    m_Viewer->reset();
}
