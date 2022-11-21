#include <QtWidgets/QMenu>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QRubberBand>
#include <QtWidgets/QStyleFactory>

#include <OpenGl_GraphicDriver.hxx>

#include "Viewer.h"

#include <V3d_View.hxx>

#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>


#ifdef WNT
#include <WNT_Window.hxx>
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
#include <Cocoa_Window.hxx>
#else
#undef Bool
#undef CursorShape
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose
#include <Xw_Window.hxx>
#endif

static Handle(Graphic3d_GraphicDriver)& GetGraphicDriver()
{
    static Handle(Graphic3d_GraphicDriver) aGraphicDriver;
    return aGraphicDriver;
}

Viewer::Viewer(QWidget* parent)
    : QWidget(parent)
{
    init();
}

void Viewer::reset()
{
    m_View->Reset();
}

void Viewer::zoom()
{
}

void Viewer::rotate()
{
}

void Viewer::init()
{
    Handle(Aspect_DisplayConnection) aDisplayConnection = new Aspect_DisplayConnection();

    if (GetGraphicDriver().IsNull())
    {
        GetGraphicDriver() = new OpenGl_GraphicDriver(aDisplayConnection);
    }

    WId window_handle = (WId)winId();

#ifdef WNT
    Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)window_handle);
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
    Handle(Cocoa_Window) window = new Cocoa_Window((NSView*)window_handle);
#else
    Handle(Xw_Window) window = new Xw_Window(aDisplayConnection, (Window)window_handle);
#endif

    m_Viewer = new V3d_Viewer(GetGraphicDriver());

    m_View = m_Viewer->CreateView();
    m_View->SetWindow(window);

    if (!window->IsMapped())
        window->Map();

    m_Context = new AIS_InteractiveContext(m_Viewer);

    m_Viewer->SetDefaultLights();
    m_Viewer->SetLightOn();

    m_View->SetBackgroundColor(Quantity_NOC_BLACK);
    m_View->MustBeResized();
    m_View->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);

    m_Context->SetDisplayMode(AIS_Shaded, Standard_True);
}

const Handle(AIS_InteractiveContext)& Viewer::getContext() const
{
    return m_Context;
}

void Viewer::resizeEvent(QResizeEvent* theEvent)
{
    if (!m_View.IsNull())
    {
        m_View->MustBeResized();
    }
}

void Viewer::wheelEvent(QWheelEvent* theEvent)
{
    onMouseWheel(theEvent->buttons(), theEvent->delta(), theEvent->pos());
}

void Viewer::mousePressEvent(QMouseEvent* theEvent)
{
    if (theEvent->button() == Qt::LeftButton)
    {
        onLButtonDown((theEvent->buttons() | theEvent->modifiers()), theEvent->pos());
    }
}

void Viewer::mouseMoveEvent(QMouseEvent* theEvent)
{
    onMoveMouse(theEvent->buttons(), theEvent->pos());
}

void Viewer::onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint)
{
    Standard_Integer aFactor = 16;

    Standard_Integer aX = thePoint.x();
    Standard_Integer aY = thePoint.y();

    if (theDelta > 0) // Zoom in (Move camera closer)
    {
        aX += aFactor;
        aY += aFactor;
    }
    else // Zoom out (Move camera away)
    {
        aX -= aFactor;
        aY -= aFactor;
    }

    m_View->Zoom(thePoint.x(), thePoint.y(), aX, aY);
}

void Viewer::onLButtonDown(const int /*theFlags*/, const QPoint thePoint)
{
    
    m_Xmin = thePoint.x();
    m_Xmin = thePoint.y();
    m_Xmax = thePoint.x();
    m_Ymax = thePoint.y();
    
    m_View->StartRotation(thePoint.x(), thePoint.y());
}

void Viewer::onMoveMouse(const int theFlags, const QPoint thePoint)
{
    if (theFlags & Qt::LeftButton)
    {
        m_View->Rotation(thePoint.x(), thePoint.y());
    }
}

