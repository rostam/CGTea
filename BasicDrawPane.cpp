//
// Created by rostam on 15.10.19.
//

#include "BasicDrawPane.h"
#include "CGTeaFrame.h"
#include <wx/dcclient.h>


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

BasicDrawPane::BasicDrawPane(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    distinctColors[0] = wxColour(255, 255, 255, 255);//white with alpha = 1
    distinctColors[1] = wxColour(230, 25, 75, 150);//red
    distinctColors[2] = wxColour(60, 180, 75, 150);//green
    distinctColors[3] = wxColour(255, 225, 25, 150);//yellow
    distinctColors[4] = wxColour(0, 130, 200, 150);//blue
    distinctColors[5] = wxColour(245, 130, 49, 150);//orange
    distinctColors[6] = wxColour(145, 30, 180, 150);//purple
    distinctColors[7] = wxColour(70, 240, 240, 150);//cyan
    distinctColors[8] = wxColour(240, 50, 230, 150);//magenta
    distinctColors[9] = wxColour(240, 50, 230, 150);//lime
    distinctColors[10] = wxColour(250, 190, 190, 150);//pink
    distinctColors[11] = wxColour(0, 128, 128, 150);//teal
    distinctColors[12] = wxColour(230, 190, 255, 150);//lavender
    distinctColors[13] = wxColour(170, 110, 40, 150);//brown
    distinctColors[14] = wxColour(255, 250, 200, 150);//beige
    distinctColors[15] = wxColour(128, 0, 0, 150);//maroon
    distinctColors[16] = wxColour(170, 255, 195, 150);//Mint
    distinctColors[17] = wxColour(128, 128, 0, 150);//olive
    distinctColors[18] = wxColour(255, 216, 177, 150);//Coral
    distinctColors[19] = wxColour(0, 0, 128, 150);//Navy
    distinctColors[20] = wxColour(128, 128, 128, 150);//Grey
}

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
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxPaintDC&  dc) {

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
        font.SetPointSize(16);
        gc->SetFont(font,*wxBLACK);
        gc->SetPen(wxPen(wxColor(0, 0, 0), 1)); // black line, 3 pixels thick
        gc->DrawRectangle(0,0,dc.GetSize().GetWidth(),dc.GetSize().GetHeight());
        try {
            const Graph& g = ((CGTeaFrame*)this->m_parent)->currentGraph;
            drawEdges(g, gc);
            drawVertices(g, gc);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        delete gc;
    }

}

void BasicDrawPane::drawEdges(const Graph &g, wxGraphicsContext* gc) {
    for_each_e_const(g, [&](Edge e) {
        Ver src = boost::source(e,g);
        Ver tgt = boost::target(e,g);
        cgtea_geometry::Point src_pos = boost::get(boost::vertex_distance, g, src);
        cgtea_geometry::Point tgt_pos = boost::get(boost::vertex_distance, g, tgt);
        gc->SetPen(wxPen(wxColor(0, 0, 0), 2)); // black line, 3 pixels thick
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(src_pos.x, src_pos.y);
        path.AddLineToPoint(tgt_pos.x, tgt_pos.y);
        gc->StrokePath(path);
    });
}

void BasicDrawPane::drawVertices(const Graph &g, wxGraphicsContext* gc) {
    for_each_v_const(g, [&](Ver v) {
        int color =  boost::get(vertex_color, g,v);;
        gc->SetPen(wxPen(wxColor(255, 0, 0), 1)); // 5-pixels-thick red outline
        cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
//        gc->DrawCircle(wxPoint(pos.x, pos.y), 20 /* radius */ );
        gc->SetBrush(wxBrush( wxColour(255, 255, 255, 255))); // green filling
        wxGraphicsPath pathBackground = gc->CreatePath();
        pathBackground.AddCircle(pos.x, pos.y, 20 );
        gc->FillPath(pathBackground);

        gc->SetBrush(wxBrush( distinctColors[color + 1]));
        wxGraphicsPath path = gc->CreatePath();
        path.AddCircle(pos.x, pos.y, 20 );
        gc->FillPath(path);

        gc->SetBrush(wxBrush( wxColour(0, 0, 0, 255)));
        int tmp = boost::get(boost::vertex_index, g, v);
        wxString mystring = wxString::Format(wxT("%i"),tmp);
        wxDouble w, h;
        gc->GetTextExtent(mystring, &w, &h, NULL, NULL);
        gc->DrawText(mystring, pos.x-w/2, pos.y-h/2);
    });
}
