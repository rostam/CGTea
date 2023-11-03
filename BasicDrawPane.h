//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_BASICDRAWPANE_H
#define CGTEA_BASICDRAWPANE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/sizer.h>
#include "datatypes.h"
#include <string>
#endif
#include <exception>
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
    // some useful events
    
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
