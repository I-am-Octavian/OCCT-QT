// File created by Aditya Sharma for Learning Opencascade and Qt
/*
THE FILE IS PROVIDED AS IS WIHTOUT WARRANTY OF ANY KIND
*/

#include <IVtkTools_ShapeDataSource.hxx>

#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>

#include "Renderer.h"

Renderer::Renderer()
{
	m_RenderWindow->AddRenderer(m_Renderer);

	m_RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
	m_RenderWindowInteractor->SetInteractorStyle(m_InteractorStyleTrackballCamera);
	
}

Renderer::~Renderer()
{
}

void Renderer::Render(const TopoDS_Shape& shape)
{
	vtkNew<IVtkTools_ShapeDataSource> occSource;
	occSource->SetShape(new IVtkOCC_Shape(shape));

	m_DataMapper->SetInputConnection(occSource->GetOutputPort());

	m_Actor->SetMapper(m_DataMapper);
	m_Renderer->AddActor(m_Actor);

	m_RenderWindow->Render();
	m_RenderWindowInteractor->Start();
	
	return void();
}
