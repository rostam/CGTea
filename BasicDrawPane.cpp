//
// Created by rostam on 15.10.19.
//

#include "BasicDrawPane.h"
#include "MyFrame.h"


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
                EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()


// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

BasicDrawPane::BasicDrawPane(wxWindow* parent) : wxPanel(parent, wxID_ANY) {}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc) {
    dc.SetPen(wxPen(wxColor(0, 0, 0), 1)); // black line, 3 pixels thick
    dc.DrawRectangle(0,0,dc.GetSize().GetWidth(),dc.GetSize().GetHeight());
    try {
        const Graph& g = ((MyFrame*)this->m_parent)->currentGraph;
        drawEdges(g, dc);
        drawVertices(g, dc);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void BasicDrawPane::drawEdges(const Graph &g, wxDC &dc) {
    for_each_e_const(g, [&](Edge e) {
        Ver src = boost::source(e,g);
        Ver tgt = boost::target(e,g);
        cgtea_geometry::Point src_pos = boost::get(boost::vertex_distance, g, src);
        cgtea_geometry::Point tgt_pos = boost::get(boost::vertex_distance, g, tgt);
        dc.SetPen(wxPen(wxColor(0, 0, 0), 2)); // black line, 3 pixels thick
        dc.DrawLine(src_pos.x, src_pos.y, tgt_pos.x, tgt_pos.y); // draw line across the rectangle
    });
}

void BasicDrawPane::drawVertices(const Graph &g, wxDC &dc) {
    for_each_v_const(g, [&](Ver v) {
        dc.SetBrush(*wxGREEN_BRUSH); // green filling
        dc.SetPen(wxPen(wxColor(255, 0, 0), 1)); // 5-pixels-thick red outline
        cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
        dc.DrawCircle(wxPoint(pos.x, pos.y), 20 /* radius */ );
        int tmp = boost::get(boost::vertex_index, g, v);
        std::string stlstring = "CGTea";
        wxString mystring = wxString::Format(wxT("%i"),tmp);
        dc.DrawText(mystring, pos.x-3, pos.y-6);
    });
}
