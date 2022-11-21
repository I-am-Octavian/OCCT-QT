//-----------------------------------------------------------------------------
// Created on: 24 August 2017
//-----------------------------------------------------------------------------
// Copyright (c) 2017, Sergey Slyadnev (sergey.slyadnev@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of the copyright holder(s) nor the
//      names of all contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------


#pragma once

#ifndef VIEWER_H
#define VIEWER_H

#include <QtWidgets/QWidget>

#include <AIS_InteractiveContext.hxx>

class QMenu;
class QRubberBand;

class Viewer : public QWidget
{
    Q_OBJECT

public:
    Viewer(QWidget* parent);

    const Handle(AIS_InteractiveContext)& getContext() const;

public slots:
    void reset();
    void zoom();
    void rotate();

protected:
    void init();

protected:
    virtual void resizeEvent(QResizeEvent* theEvent);
    virtual void wheelEvent(QWheelEvent* theEvent);
    virtual void mousePressEvent(QMouseEvent* theEvent);
    virtual void mouseMoveEvent(QMouseEvent* theEvent);

    virtual void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
    virtual void onLButtonDown(const int theFlags, const QPoint thePoint);
    virtual void onMoveMouse(const int theFlags, const QPoint thePoint);



private:
    Handle(V3d_View) m_View; // 3d View

    Handle(V3d_Viewer) m_Viewer; // 3d Viewer

    Handle(AIS_InteractiveContext) m_Context; // To interact with viewer

    // To store position of mouse(for mouse events)
    Standard_Integer m_Xmin;
    Standard_Integer m_Xmax;
    Standard_Integer m_Ymin;
    Standard_Integer m_Ymax;

};

#endif // VIEWER_H
