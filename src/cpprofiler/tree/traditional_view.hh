#ifndef CPPROFILER_TREE_TRADITIONAL_VIEW_HH
#define CPPROFILER_TREE_TRADITIONAL_VIEW_HH

#include <QWidget>
#include <QAbstractScrollArea>

#include <memory>
#include "node_id.hh"

namespace cpprofiler {
    class UserData;
}

namespace cpprofiler { namespace tree {

class Layout;
class LayoutComputer;
class NodeTree;
class NodeID;
class Structure;

struct DisplayState {
    float scale;
    int x_off = 0;
    int y_off = 0;
};

class NodeFlags {

    std::vector<bool> m_label_shown;

public:
    void set_label_shown(NodeID nid, bool val);
    bool get_label_shown(NodeID nid) const;
};

class TreeScrollArea : public QAbstractScrollArea {
Q_OBJECT
    const NodeTree& m_tree;
    const UserData& m_user_data;
    const Layout& m_layout;

    const DisplayState& m_options;
    const NodeFlags& m_node_flags;

    NodeID findNodeClicked(int x, int y);

    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void nodeClicked(NodeID nid);

public:

    TreeScrollArea(const NodeTree&,
                   const UserData&,
                   const Layout&,
                   const DisplayState&,
                   const NodeFlags&);

};


class TraditionalView : public QObject {
    Q_OBJECT

    NodeFlags m_flags;
    std::unique_ptr<Layout> m_layout;
    std::unique_ptr<UserData> m_user_data;
    TreeScrollArea m_scroll_area;
    DisplayState m_options;
    const Structure& m_tree;
    std::unique_ptr<LayoutComputer> m_layout_computer;

public:

    TraditionalView(const NodeTree& tree);
    ~TraditionalView();

    QWidget* widget();

signals:
    void nodeClicked(NodeID nid);

    void needsRedrawing();

public slots:
    void setScale(int scale);

    void centerNode(NodeID nid);

    void navUp();
    void navDown();
    void navLeft();
    void navRight();

    void toggleShowLabel();

    void selectNode(NodeID nid);

    void forceComputeLayout();

    void setLayoutOutdated();


};

}}

#endif