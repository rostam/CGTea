//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_BASICDRAWPANE_H
#define CGTEA_BASICDRAWPANE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "datatypes.h"
#include <string>
#endif
#include <wx/graphics.h>
#include <map>

class BasicDrawPane : public wxPanel
{
public:
    std::map<int, wxColour> distinctColors;

    BasicDrawPane(wxWindow* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxPaintDC& dc);

    void drawEdges(const Graph &g, wxGraphicsContext* gc);
    void drawVertices(const Graph &g, wxGraphicsContext* gc);
    void drawShape(wxGraphicsContext* gc, VertexShape shape, const cgtea_geometry::Point& pos, double size);
    void drawCircle(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size);
    void drawSquare(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size);
    void drawTriangle(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size);
    void drawDiamond(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size);

     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
    

    DECLARE_EVENT_TABLE()
};



#endif //CGTEA_BASICDRAWPANE_H
