// File created by Aditya Sharma for Learning Opencascade and Qt
/*
THE FILE IS PROVIDED AS IS WIHTOUT WARRANTY OF ANY KIND
*/

#pragma once

#include <IVtkTools_ShapeDataSource.hxx>

#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>


VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render(const TopoDS_Shape& shape);

private:
	vtkNew<vtkRenderer> m_Renderer;
	vtkNew<vtkRenderWindow> m_RenderWindow;

	vtkNew<vtkInteractorStyleTrackballCamera> m_InteractorStyleTrackballCamera;
	vtkNew<vtkRenderWindowInteractor> m_RenderWindowInteractor;

	vtkNew<IVtkTools_ShapeDataSource> m_ShapeSource;

	vtkNew<vtkPolyDataMapper> m_DataMapper;

	vtkNew<vtkActor> m_Actor;
};