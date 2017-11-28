//
// Created by koncord on 07.01.16.
//

#ifndef OPENMW_BASEPLAYER_HPP
#define OPENMW_BASEPLAYER_HPP

#include <components/esm/loadcell.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/esm/npcstats.hpp>
#include <components/esm/loadclas.hpp>
#include <components/esm/loadspel.hpp>
#include <components/esm/activespells.hpp>

#include <components/openmw-mp/Base/BaseStructs.hpp>
#include <components/openmw-mp/Base/BaseNetCreature.hpp>

#include <RakNetTypes.h>

namespace mwmp
{
    struct CurrentContainer
    {
        std::string refId;
        int refNumIndex;
        int mpNum;
        bool loot;
    };

    struct JournalItem
    {
        std::string quest;
        int index;
        enum JOURNAL_ITEM_TYPE
        {
            ENTRY = 0,
            INDEX = 1
        };

        std::string actorRefId;

        int type; // 0 - An entire entry, 1 - An index
    };

    struct Faction
    {
        std::string factionId;
        int rank;
        int reputation;
        bool isExpelled;
    };

    struct Topic
    {
        std::string topicId;
    };

    struct Kill
    {
        std::string refId;
        int number;
    };

    struct Book
    {
        std::string bookId;
    };

    struct CellState
    {
        ESM::Cell cell;

        enum CELL_STATE_ACTION
        {
            LOAD = 0,
            UNLOAD = 1
        };

        int type; // 0 - Cell load, 1 - Cell unload
    };

    // Track only the indexes of the attributes that have been changed,
    // with the attribute values themselves being stored in creatureStats.mAttributes
    struct AttributeChanges
    {
        std::vector<int> attributeIndexes;
    };

    // Track only the indexes of the skills that have been changed,
    // with the skill values themselves being stored in npcStats.mSkills
    struct SkillChanges
    {
        std::vector<int> skillIndexes;
    };

    struct JournalChanges
    {
        std::vector<JournalItem> journalItems;
    };

    struct FactionChanges
    {
        std::vector<Faction> factions;

        enum FACTION_ACTION
        {
            RANK = 0,
            EXPULSION = 1,
            REPUTATION = 2
        };

        int action; // 0 - Rank, 1 - Expulsion state, 2 - Both
    };

    struct TopicChanges
    {
        std::vector<Topic> topics;
    };

    struct KillChanges
    {
        std::vector<Kill> kills;
    };

    struct BookChanges
    {
        std::vector<Book> books;
    };

    struct MapChanges
    {
        std::vector<ESM::Cell> cellsExplored;
    };

    struct SpellbookChanges
    {
        std::vector<ESM::Spell> spells;

        enum ACTION_TYPE
        {
            SET = 0,
            ADD,
            REMOVE
        };
        int action; // 0 - Clear and set in entirety, 1 - Add spell, 2 - Remove spell
    };

    struct CellStateChanges
    {
        std::vector<CellState> cellStates;
    };

    enum RESURRECT_TYPE
    {
        REGULAR = 0,
        IMPERIAL_SHRINE,
        TRIBUNAL_TEMPLE
    };

    class BasePlayer : public mwmp::BaseNetCreature
    {
    public:

        struct CharGenState
        {
            int currentStage, endStage;
            bool isFinished;
        };

        struct GUIMessageBox
        {
            int id;
            int type;
            enum GUI_TYPE
            {
                MessageBox = 0,
                CustomMessageBox,
                InputDialog,
                PasswordDialog,
                ListBox
            };
            std::string label;
            std::string note;
            std::string buttons;

            std::string data;
        };

        struct GUIWindow
        {
            int32_t id;
            short width, height;
            enum class WidgetType: uint8_t
            {
                Button,
                Editbox,
                Label,
                ListBoxActive,
                ListBoxPassive,
                Slider
            };

            struct Widget
            {
                WidgetType type;
                std::string name;
                bool disabled;
                short posX, posY;
                short width, height;
                std::vector<std::string> data;
            };

            std::vector<Widget> widgets;
        };

        BasePlayer(RakNet::RakNetGUID guid) : guid(guid)
        {
            inventoryChanges.action = 0;
            spellbookChanges.action = 0;
            useCreatureName = false;
            isWerewolf = false;
        }

        BasePlayer()
        {

        }

        ~BasePlayer()
        {

        }

        RakNet::RakNetGUID guid;
        GUIMessageBox guiMessageBox;
        int month;
        int day;
        GUIWindow guiWindow;
        double hour;

        AttributeChanges attributeChanges;
        SkillChanges skillChanges;

        SpellbookChanges spellbookChanges;
        JournalChanges journalChanges;
        FactionChanges factionChanges;
        TopicChanges topicChanges;
        KillChanges killChanges;
        BookChanges bookChanges;
        MapChanges mapChanges;
        CellStateChanges cellStateChanges;

        ESM::ActiveSpells activeSpells;
        CurrentContainer currentContainer;

        bool consoleAllowed;
        int difficulty;

        bool ignorePosPacket;

        ESM::Position previousCellPosition;
        ESM::NPC npc;
        ESM::NpcStats npcStats;
        ESM::Class charClass;
        std::string birthsign;
        std::string chatMessage;
        CharGenState charGenState;
        std::string passw;

        bool isWerewolf;
        std::string creatureModel;
        bool useCreatureName;

        std::string deathReason;

        int jailDays;
        bool ignoreJailTeleportation;
        bool ignoreJailSkillIncreases;
        std::string jailProgressText;
        std::string jailEndText;

        unsigned int resurrectType;

        bool diedSinceArrestAttempt;
    };
}

#endif //OPENMW_BASEPLAYER_HPP
