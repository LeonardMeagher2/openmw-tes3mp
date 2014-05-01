#ifndef CSV_WORLD_SCENESUBVIEW_H
#define CSV_WORLD_SCENESUBVIEW_H

#include <QHBoxLayout>

#include "../doc/subview.hpp"
#include "scenetoolbar.hpp"

class QModelIndex;

namespace CSMWorld
{
    class CellSelection;
}

namespace CSMDoc
{
    class Document;
}

namespace CSVRender
{
    class WorldspaceWidget;
}

namespace CSVWorld
{
    class Table;
    class TableBottomBox;
    class CreatorFactoryBase;

    class SceneSubView : public CSVDoc::SubView
    {
            Q_OBJECT

            TableBottomBox *mBottom;
            CSVRender::WorldspaceWidget *mScene;
            QHBoxLayout* mLayout;
            CSMDoc::Document& mDocument;
            SceneToolbar* mToolbar;

        public:

            SceneSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document);

            virtual void setEditLock (bool locked);

            virtual void updateEditorSetting (const QString& key, const QString& value);

            virtual void setStatusBar (bool show);

            virtual void useHint (const std::string& hint);

        private slots:

            void closeRequest();

            void cellSelectionChanged (const CSMWorld::CellSelection& selection);

            void changeToPaged(const std::vector<CSMWorld::UniversalId>& data);

            void changeToUnpaged(const std::vector<CSMWorld::UniversalId>& data);
    };
}

#endif
