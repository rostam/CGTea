// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/sizer.h>
    #include "datatypes.h"
    #include <string>
#include "generators/Cycle.h"
#endif

class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void drawEdges(Graph &g, wxDC&  dc);
    void drawVertices(Graph &g, wxDC&  dc);
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

DECLARE_EVENT_TABLE()
};

class MyApp: public wxApp {
    BasicDrawPane *drawPane;
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame {
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnHello(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    MyFrame *frame = new MyFrame( "GTea", wxPoint(100, 100), wxSize(1000, 1000) );
    drawPane = new BasicDrawPane( (wxFrame*) frame );
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
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

BasicDrawPane::BasicDrawPane(wxFrame* parent) :
        wxPanel(parent)
{
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
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc) {
    // Look at the wxDC docs to learn how to draw other stuff
    Cycle cy(10);
    Graph g = cy.generate_with_positions(500, 500);
    drawEdges(g,dc);
    drawVertices(g, dc);

    Graph gg = cy.generate_with_force_directed(500, 500);
//    drawEdges(gg,dc);
//    drawVertices(gg, dc);
}

void BasicDrawPane::drawEdges(Graph &g, wxDC &dc) {
    for_each_e(g, [&](Edge e) {
        Ver src = boost::source(e,g);
        Ver tgt = boost::target(e,g);
        std::pair<double,double> src_pos = boost::get(boost::vertex_distance, g, src);
        std::pair<double,double> tgt_pos = boost::get(boost::vertex_distance, g, tgt);
        dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
        dc.DrawLine(src_pos.first, src_pos.second, tgt_pos.first, tgt_pos.second); // draw line across the rectangle
    });
}

void BasicDrawPane::drawVertices(Graph &g, wxDC &dc) {
    for_each_v(g, [&](Ver v) {
        dc.SetBrush(*wxGREEN_BRUSH); // green filling
        dc.SetPen(wxPen(wxColor(255, 0, 0), 1)); // 5-pixels-thick red outline
        std::pair<double,double> pos = boost::get(boost::vertex_distance, g, v);
        dc.DrawCircle(wxPoint(pos.first, pos.second), 20 /* radius */ );
        int tmp = boost::get(boost::vertex_index, g, v);
        std::string stlstring = "CGTea";
        wxString mystring = wxString::Format(wxT("%i"),tmp);
        dc.DrawText(mystring, pos.first, pos.second);
    });
}
