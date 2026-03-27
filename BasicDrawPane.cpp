//
// Created by rostam on 15.10.19.
//

#include "BasicDrawPane.h"
#include "CGTeaFrame.h"
#include <wx/dcclient.h>


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events

 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_DCLICK(BasicDrawPane::mouseDoubleClick)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()


// some useful events

 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {
    if (m_edgeDrawing) {
        m_rubberX = event.GetPosition().x;
        m_rubberY = event.GetPosition().y;
        Refresh();
        return;
    }
    if (!m_dragging || !event.Dragging()) return;

    const double mx = event.GetPosition().x;
    const double my = event.GetPosition().y;
    const double dx = mx - m_dragLastX;
    const double dy = my - m_dragLastY;
    m_dragLastX = mx;
    m_dragLastY = my;

    Graph& g = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;

    if (m_selectedVertex != -1) {
        // Move the selected vertex
        for_each_v(g, [&](Ver v) {
            if ((int)boost::get(boost::vertex_index, g, v) == m_selectedVertex) {
                cgtea_geometry::Point p = boost::get(boost::vertex_distance, g, v);
                p.x += dx;
                p.y += dy;
                boost::put(boost::vertex_distance, g, v, p);
            }
        });
    } else if (m_edgeSelected) {
        // Move both endpoints of the selected edge
        auto moveVert = [&](Ver v) {
            cgtea_geometry::Point p = boost::get(boost::vertex_distance, g, v);
            p.x += dx;
            p.y += dy;
            boost::put(boost::vertex_distance, g, v, p);
        };
        moveVert(m_edgeSrc);
        moveVert(m_edgeTgt);
    }

    Refresh();
 }

 void BasicDrawPane::mouseDown(wxMouseEvent& event) {
    const Graph& g = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;
    const double mx = event.GetPosition().x;
    const double my = event.GetPosition().y;
    const double r  = 16.0;

    // Hit-test vertices first
    m_selectedVertex = -1;
    m_edgeSelected   = false;
    for_each_v_const(g, [&](Ver v) {
        const cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
        const double dx = pos.x - mx, dy = pos.y - my;
        if (dx*dx + dy*dy <= r*r)
            m_selectedVertex = (int)boost::get(boost::vertex_index, g, v);
    });

    // Shift+click on a vertex starts edge drawing — don't drag
    if (event.ShiftDown() && m_selectedVertex != -1) {
        m_edgeDrawing = true;
        m_edgeSrc = 0;
        for_each_v_const(g, [&](Ver v) {
            if ((int)boost::get(boost::vertex_index, g, v) == m_selectedVertex)
                m_edgeDrawSrc = v;
        });
        m_rubberX = mx;
        m_rubberY = my;
        m_dragging = false;
        Refresh();
        return;
    }
    m_edgeDrawing = false;

    if (m_selectedVertex == -1) {
        // Hit-test edges (point-to-segment distance < 6)
        for_each_e_const(g, [&](Edge e) {
            if (m_edgeSelected) return;
            const Ver s = boost::source(e, g), t = boost::target(e, g);
            const cgtea_geometry::Point sp = boost::get(boost::vertex_distance, g, s);
            const cgtea_geometry::Point tp = boost::get(boost::vertex_distance, g, t);
            const double ax = tp.x - sp.x, ay = tp.y - sp.y;
            const double len2 = ax*ax + ay*ay;
            if (len2 < 1.0) return;
            const double t2 = ((mx - sp.x)*ax + (my - sp.y)*ay) / len2;
            const double tc = t2 < 0.0 ? 0.0 : (t2 > 1.0 ? 1.0 : t2);
            const double px = sp.x + tc*ax - mx;
            const double py = sp.y + tc*ay - my;
            if (px*px + py*py <= 36.0) { // 6^2
                m_edgeSelected = true;
                m_edgeSrc = s;
                m_edgeTgt = t;
            }
        });
    }

    m_dragging  = (m_selectedVertex != -1 || m_edgeSelected);
    m_dragLastX = mx;
    m_dragLastY = my;

    Refresh();
 }

 void BasicDrawPane::mouseDoubleClick(wxMouseEvent& event) {
    // Only create a vertex if the double-click did not land on an existing vertex
    const Graph& g = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;
    const double mx = event.GetPosition().x;
    const double my = event.GetPosition().y;
    const double r  = 16.0;
    bool hitVertex = false;
    for_each_v_const(g, [&](Ver v) {
        const cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
        const double dx = pos.x - mx, dy = pos.y - my;
        if (dx*dx + dy*dy <= r*r) hitVertex = true;
    });
    if (hitVertex) return;

    Graph& gw = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;
    const Ver vv = boost::num_vertices(gw);
    boost::add_vertex(vv, gw);
    boost::put(boost::vertex_distance, gw, vv, cgtea_geometry::Point(mx, my));
    m_selectedVertex = -1;
    m_edgeSelected   = false;
    Refresh();
 }

 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {
    m_dragging = false;
    if (!m_edgeDrawing) return;
    m_edgeDrawing = false;

    const double mx = event.GetPosition().x;
    const double my = event.GetPosition().y;
    const double r  = 16.0;
    Graph& g = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;
    Ver target = boost::graph_traits<Graph>::null_vertex();
    for_each_v_const(g, [&](Ver v) {
        const cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
        const double dx = pos.x - mx, dy = pos.y - my;
        if (dx*dx + dy*dy <= r*r && v != m_edgeDrawSrc)
            target = v;
    });
    if (target != boost::graph_traits<Graph>::null_vertex())
        boost::add_edge(m_edgeDrawSrc, target, g);

    Refresh();
 }
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 

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
    for(int i=21;i<1000;i++) {
        auto col = distinctColors[i%20];
        auto r = col.Red();
        auto g = col.Green();
        auto b = col.Blue();
        r = r < 200 ? r + 40 : r - 50;
        g = g < 200 ? g + 40 : g - 50;
        b = b < 200 ? b + 40 : b - 50;
        distinctColors[i] = wxColor(r,g,b,150);
    }
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
 * background and expects you will redraw it when the window comes
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
 * (e.g., wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxPaintDC&  dc) {

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
        font.SetPointSize(10);
        gc->SetFont(font, *wxBLACK);

        // Clean white background
        gc->SetPen(*wxTRANSPARENT_PEN);
        gc->SetBrush(wxBrush(wxColour(255, 255, 255)));
        gc->DrawRectangle(0, 0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight());

        try {
            const Graph& g = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this))->currentGraph;
            drawEdges(g, gc);
            drawVertices(g, gc);

            // Rubber-band line while drawing a new edge
            if (m_edgeDrawing) {
                const cgtea_geometry::Point sp = boost::get(boost::vertex_distance, g, m_edgeDrawSrc);
                wxPen rubberPen(wxColour(80, 80, 220), 2, wxPENSTYLE_DOT);
                gc->SetPen(rubberPen);
                wxGraphicsPath path = gc->CreatePath();
                path.MoveToPoint(sp.x, sp.y);
                path.AddLineToPoint(m_rubberX, m_rubberY);
                gc->StrokePath(path);
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        delete gc;
    }

}

void BasicDrawPane::drawShape(wxGraphicsContext* gc, const VertexShape shape,
                            const cgtea_geometry::Point& pos, double size) {
    switch(shape) {
        case VertexShape::Square:
            drawSquare(gc, pos, size);
            break;
        case VertexShape::Triangle:
            drawTriangle(gc, pos, size);
            break;
        case VertexShape::Diamond:
            drawDiamond(gc, pos, size);
            break;
        case VertexShape::Circle:
        default:
            drawCircle(gc, pos, size);
            break;
    }
}

void BasicDrawPane::drawCircle(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size) {
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(pos.x, pos.y, size);
    gc->FillPath(path);
}

void BasicDrawPane::drawSquare(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size) {
    wxGraphicsPath path = gc->CreatePath();
    path.AddRectangle(pos.x - size, pos.y - size, size * 2, size * 2);
    gc->FillPath(path);
}

void BasicDrawPane::drawTriangle(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size) {
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(pos.x, pos.y - size);
    path.AddLineToPoint(pos.x - size, pos.y + size);
    path.AddLineToPoint(pos.x + size, pos.y + size);
    path.CloseSubpath();
    gc->FillPath(path);
}

void BasicDrawPane::drawDiamond(wxGraphicsContext* gc, const cgtea_geometry::Point& pos, double size) {
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(pos.x, pos.y - size);
    path.AddLineToPoint(pos.x + size, pos.y);
    path.AddLineToPoint(pos.x, pos.y + size);
    path.AddLineToPoint(pos.x - size, pos.y);
    path.CloseSubpath();
    gc->FillPath(path);
}

void BasicDrawPane::drawVertices(const Graph &g, wxGraphicsContext* gc) {
    for_each_v_const(g, [&](Ver v) {
        const int color = boost::get(vertex_color, g, v);
        const cgtea_geometry::Point pos = boost::get(boost::vertex_distance, g, v);
        //auto shape = VertexShape::Diamond;
        const auto frame = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this));
        const auto shape = frame ? frame->getCurrentVertexShape() : VertexShape::Circle;


        // Draw selection ring if selected
        const int vidx = (int)boost::get(boost::vertex_index, g, v);
        if (vidx == m_selectedVertex) {
            gc->SetPen(wxPen(wxColour(255, 140, 0), 3));
            gc->SetBrush(*wxTRANSPARENT_BRUSH);
            wxGraphicsPath ring = gc->CreatePath();
            ring.AddCircle(pos.x, pos.y, 21);
            gc->DrawPath(ring);
        }

        // Draw a white background with subtle shadow effect
        gc->SetPen(wxPen(wxColour(160, 160, 160), 1));
        gc->SetBrush(wxBrush(wxColour(255, 255, 255)));
        drawShape(gc, shape, pos, 16);

        // Draw a colored shape
        gc->SetBrush(wxBrush(distinctColors[color + 1]));
        drawShape(gc, shape, pos, 16);

        // Draw a vertex number
        gc->SetBrush(wxBrush(wxColour(0, 0, 0, 255)));
        int tmp = boost::get(boost::vertex_index, g, v) + 1;
        wxString mystring = wxString::Format(wxT("%i"), tmp);
        wxDouble w, h;
        gc->GetTextExtent(mystring, &w, &h, nullptr, nullptr);
        gc->DrawText(mystring, pos.x-w/2, pos.y-h/2);
    });
}

void BasicDrawPane::drawEdgeShape(wxGraphicsContext* gc, EdgeShape shape,
                                const cgtea_geometry::Point& src,
                                const cgtea_geometry::Point& tgt) {
    switch(shape) {
        case EdgeShape::Curve:
            drawCurve(gc, src, tgt);
            break;
        case EdgeShape::DoubleArrow:
            drawDoubleArrow(gc, src, tgt);
            break;
        case EdgeShape::Dashed:
            drawDashed(gc, src, tgt);
            break;
        case EdgeShape::Line:
        default:
            drawLine(gc, src, tgt);
            break;
    }
}

void BasicDrawPane::drawLine(wxGraphicsContext* gc,
                           const cgtea_geometry::Point& src,
                           const cgtea_geometry::Point& tgt) {
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(src.x, src.y);
    path.AddLineToPoint(tgt.x, tgt.y);
    gc->StrokePath(path);
}

void BasicDrawPane::drawCurve(wxGraphicsContext* gc,
                            const cgtea_geometry::Point& src,
                            const cgtea_geometry::Point& tgt) {
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(src.x, src.y);
    // Calculate control point for quadratic curve
    double midX = (src.x + tgt.x) / 2;
    double midY = (src.y + tgt.y) / 2;
    double offsetY = 30; // Curve height
    path.AddQuadCurveToPoint(midX, midY - offsetY, tgt.x, tgt.y);
    gc->StrokePath(path);
}

void BasicDrawPane::drawDoubleArrow(wxGraphicsContext* gc,
                                  const cgtea_geometry::Point& src,
                                  const cgtea_geometry::Point& tgt) {
    // Draw main line
    drawLine(gc, src, tgt);

    // Calculate arrow parameters
    double angle = atan2(tgt.y - src.y, tgt.x - src.x);
    double arrowLength = 15;
    double arrowAngle = M_PI / 6;  // 30 degrees

    // Draw arrows at both ends
    for(const auto& point : {src, tgt}) {
        double baseAngle = (point.x == src.x && point.y == src.y) ?
                          angle + M_PI : angle;

        wxGraphicsPath arrowPath = gc->CreatePath();
        arrowPath.MoveToPoint(point.x, point.y);
        arrowPath.AddLineToPoint(
            point.x + arrowLength * cos(baseAngle + arrowAngle),
            point.y + arrowLength * sin(baseAngle + arrowAngle)
        );
        arrowPath.MoveToPoint(point.x, point.y);
        arrowPath.AddLineToPoint(
            point.x + arrowLength * cos(baseAngle - arrowAngle),
            point.y + arrowLength * sin(baseAngle - arrowAngle)
        );
        gc->StrokePath(arrowPath);
    }
}

void BasicDrawPane::drawDashed(wxGraphicsContext* gc,
                             const cgtea_geometry::Point& src,
                             const cgtea_geometry::Point& tgt) {
    // Create a new dashed pen
    wxPen dashedPen(wxColor(0, 0, 0), 2); // Match the regular pen style
    wxDash dashes[] = {5, 5}; // 5 pixel dash, 5 pixel gap
    dashedPen.SetDashes(2, dashes);
    dashedPen.SetStyle(wxPENSTYLE_USER_DASH);
    gc->SetPen(dashedPen);

    // Draw the dashed line
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(src.x, src.y);
    path.AddLineToPoint(tgt.x, tgt.y);
    gc->StrokePath(path);

    // Reset to solid pen
    gc->SetPen(wxPen(wxColor(0, 0, 0), 2));
}

void BasicDrawPane::drawEdges(const Graph &g, wxGraphicsContext* gc) {
    for_each_e_const(g, [&](Edge e) {
        const Ver src = boost::source(e,g);
        const Ver tgt = boost::target(e,g);
        const cgtea_geometry::Point src_pos = boost::get(boost::vertex_distance, g, src);
        const cgtea_geometry::Point tgt_pos = boost::get(boost::vertex_distance, g, tgt);
        const bool selected = m_edgeSelected &&
            ((src == m_edgeSrc && tgt == m_edgeTgt) ||
             (src == m_edgeTgt && tgt == m_edgeSrc));
        if (selected)
            gc->SetPen(wxPen(wxColour(30, 100, 220), 4));
        else
            gc->SetPen(wxPen(wxColor(0, 0, 0), 2));

        const auto frame = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this));
        const auto edgeShape = frame ? frame->getCurrentEdgeShape() : EdgeShape::Line;

        drawEdgeShape(gc, edgeShape, src_pos, tgt_pos);
    });
}
