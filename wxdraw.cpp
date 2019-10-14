// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/sizer.h>
    #include "datatypes.h"
    #include <string>
#endif
#include "generators/Cycle.h"
#include "generators/Complete.h"
#include "generators/Antiprism.h"
#include "generators/Prism.h"
#include "generators/Star.h"
#include "reports/NumOfVertices.h"
#include <exception>

class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(wxWindow* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void drawEdges(const Graph &g, wxDC&  dc);
    void drawVertices(const Graph &g, wxDC&  dc);
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
    Graph currentGraph;
    wxStaticText* statistics_text = nullptr;
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    std::vector<GeneratorInterface*> availableGenerators =
            vector<GeneratorInterface*>({new Cycle(), new Complete(), new Antiprism(),
                                           new Prism(), new Star()});

    std::vector<ReportInterface*> availableReports =
            vector<ReportInterface*>({new NumOfVertices()});
//    std::tuple<Cycle, Complete, Antiprism> availableGenerators = std::make_tuple(Cycle(), Complete(), Antiprism());

    void Generate(wxCommandEvent &event);

    void Report(wxCommandEvent &event);

    void Layout(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    MyFrame *frame = new MyFrame( "CGTea", wxPoint(100, 100), wxSize(1000, 1000) );

    // Create the sidebar
    wxPanel* panel1 = new wxPanel(frame, wxID_ANY);
    wxStaticText * textStatistics = new wxStaticText (panel1, wxID_ANY, L"Statistics",wxDefaultPosition, wxSize(350, 15));
    wxFont font = textStatistics->GetFont();
    font.SetPointSize(14);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    textStatistics->SetFont(font);
    wxString string1="Number of vertices:\nNumber of edges:\nMaximum degree:\nMaximum eigenvalue:\n"
                     "Minimum eigenvalue:\nSum of eigenvalues:";
    frame->statistics_text = new wxStaticText (panel1, wxID_ANY, string1,wxDefaultPosition, wxDefaultSize);
    wxFont font2 = frame->statistics_text->GetFont();
    font2.SetPointSize(14);
    frame->statistics_text->SetFont(font2);
    wxBoxSizer* panel1Sizer = new wxBoxSizer(wxVERTICAL);
    panel1Sizer->Add(textStatistics, 1, wxLEFT, 8);
    panel1Sizer->Add(frame->statistics_text, 1, wxLEFT, 8);
    panel1->SetSizer(panel1Sizer);

    drawPane = new BasicDrawPane( frame );
    sizer->Add(panel1);
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
//    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H","Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuGenerate = new wxMenu;
    int i=0;
//    std::apply([&](auto&&... args) {((menuGenerate->Append(i, wxString(args.name().c_str(), wxConvUTF8), wxString(args.description().c_str(), wxConvUTF8)),i++), ...);}, availableGenerators);
    for(GeneratorInterface* gi : availableGenerators) {
        menuGenerate->Append(i, wxString(gi->name().c_str(), wxConvUTF8), wxString(gi->description().c_str(), wxConvUTF8));
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Generate));
        i++;
    }

    wxMenu *menuReport = new wxMenu;
    for(ReportInterface* ri : availableReports) {
        menuReport->Append(i, wxString(ri->name().c_str(), wxConvUTF8), wxString(ri->description().c_str(), wxConvUTF8));
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Report));
        i++;
    }

    wxMenu *menuLayout = new wxMenu;
    menuLayout->Append(i, "Force-directed drawing", "Force-directed drawing");
    Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Layout));
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append(menuGenerate, "&Generate");
    menuBar->Append(menuReport, "&Report");
    menuBar->Append(menuLayout, "&Layout");
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
    wxMessageBox( "CGTea is a c++-version of GraphTea, a software for working with graphs.",
                  "CGTea 1.0", wxOK | wxICON_INFORMATION );
}

void MyFrame::Generate(wxCommandEvent& event)
{
    wxString valueTyped;
    wxTextEntryDialog myDialog(this, _("n"), _("Enter graph parameters"), _("10"));
    if ( myDialog.ShowModal() == wxID_OK ) {
        valueTyped = myDialog.GetValue();
    }
    long value;
    if(!valueTyped.ToLong(&value)) { return; }

    int id = event.GetId();
    currentGraph = availableGenerators[id]->generate_with_positions(value, 0, 300, 300);
    this->statistics_text->SetLabelText(wxString(statistics(currentGraph)));
    Refresh();
}

void MyFrame::Layout(wxCommandEvent& event)
{
//    int id = event.GetId();
//    currentGraph = availableGenerators[id]->generate_with_force_directed(10,0,500,500);
    std::vector<cgtea_geometry::Point> pos = compute_force_directed(10,10, 300, 300, currentGraph);
    int i = 0;
    for_each_v(currentGraph, [&](Ver v) {
        boost::put(boost::vertex_distance, currentGraph, v, pos[i]);
        i++;
    });
    Refresh();
}

void MyFrame::Report(wxCommandEvent& event)
{

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
